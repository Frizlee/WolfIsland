#include "Application.hpp"
#include "WolfMale.hpp"
#include "WolfFemale.hpp"
#include "Hare.hpp"
using namespace std;

static const int openglVersionMajor{ 3 };
static const int openglVersionMinor{ 3 };
static const float cameraMoveVelocity{ 100.0f };
static const float cameraZoomUnit{ 0.1f };
static const float tourTime{ 3.0f };
static const glm::vec3 oceanColorMin{ 19 / 256.0f, 27 / 256.0f, 50 / 256.0f };
static const glm::vec3 oceanColorMax{ 21 / 256.0f, 45 / 256.0f, 69 / 256.0f };
static const float colorChangeVelocity{ 1.0f };
static const string wolfMaleSpriteSheetPath{ "WolfMaleSpriteSheet.png" };
static const string wolfFemaleSpriteSheetPath{ "WolfFemaleSpriteSheet.png" };
static const string hareSpriteSheetPath{ "HareSpriteSheet.png" };
static const string boardSpriteSheetPath{ "GroundSpriteSheet.png" };
static const string guiSpriteSheetPath{ "GuiSpriteSheet.png" };
const float Application::spriteSize{ 48.0f };
random_device Application::randomDev;

Application::Application()
	: mWnd{ nullptr }, mIsGlfw{ false }, mTourTimer{ 0.0f }, mCameraMoveMultiplier{ 1.0f },
	mState{ State::MENU }, mColorChange{ 0.0f }
{
}

Application::Application(const std::string& windowTitle, const glm::tvec2<int32_t>& dimensions,
	bool fullscreen)
	: mWnd{ nullptr }, mIsGlfw{ false }, mTourTimer{ 0.0f }, mCameraMoveMultiplier{ 1.0f },
	mState{ State::MENU }, mColorChange{ 0.0f }
{
	init(windowTitle, dimensions, fullscreen);
}

void Application::init(const std::string& windowTitle, const glm::tvec2<int32_t>& dimensions,
	bool fullscreen)
{
	if (mIsGlfw || glfwInit() == GLFW_FALSE)
		throw ApplicationInitException();

	mIsGlfw = true;
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openglVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openglVersionMinor);

	mWnd = glfwCreateWindow(dimensions.x, dimensions.y, windowTitle.c_str(),
		fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

	if (!mWnd)
		throw ApplicationInitException();

	glfwSetWindowUserPointer(mWnd, this);
	glfwSetScrollCallback(mWnd, GlfwScrollCallback);
	glfwSetFramebufferSizeCallback(mWnd, GlfwFramebufferSizeCallback);

	glfwMakeContextCurrent(mWnd);
	glfwSwapInterval(0);
	mRenderer.init();
	mRenderer.setViewport(glm::tvec2<int32_t>{ dimensions.x, dimensions.y });
	gl::ClearColor(oceanColorMin.r, oceanColorMin.g, oceanColorMin.b, 1.0f);
	gl::Enable(gl::BLEND);
	gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);

	// Create font
	mFnt = make_shared<Font>("ComicSans.ttf", 16, 
		make_shared<ImageAtlas>(256, 256, Image::Format::R8), mRenderer);

	// Create Text vbo and vao
	mVaoText = make_shared<VertexArray>(
		make_shared<VertexBuffer<TextVertexLayout>>(1024 * 1024, mRenderer), mRenderer);
	
	// Create Sprite vbo and vao
	mVaoSprite = make_shared<VertexArray>(
		make_shared<VertexBuffer<TextureVertexLayout>>(1024, mRenderer), mRenderer);
	mVaoSpriteInstanced = make_shared<VertexArray>(
		make_shared<VertexBuffer<TextureVertexLayout>>(1024, mRenderer), mRenderer);

	setupWolfMaleSpriteSheet();
	setupWolfFemaleSpriteSheet();
	setupHareSpriteSheet();
	setupBoardSpriteSheet();

	// Sliders
	Image guiSpriteImg;
	ifstream guiSpriteFile{ guiSpriteSheetPath, ios_base::binary };
	PngCodec{}.decode(guiSpriteFile, guiSpriteImg);
	shared_ptr<Texture> guiSpriteTex = make_shared<Texture>(guiSpriteImg, mRenderer);
	guiSpriteTex->generateMipmaps(mRenderer);
	shared_ptr<Sprite> sliderSprite = make_shared<Sprite>(
		glm::vec2{ 208.0f, 15.0f }, glm::vec2{ 0 / 1024.0f, 0 / 1024.0f },
		glm::vec2{ 208.0f / 1024.0f, 15.0f / 1024.0f }, 1.0f, guiSpriteTex,
		mVaoSprite, mRenderer);
	shared_ptr<Sprite> buttonSprite = make_shared<Sprite>(
		glm::vec2{ 22.0f, 33.0f }, glm::vec2{ 0 / 1024.0f, 15.0f / 1024.0f },
		glm::vec2{ 22.0f / 1024.0f, 48.0f / 1024.0f }, 1.0f, guiSpriteTex,
		mVaoSprite, mRenderer);
	shared_ptr<Text> sliderWidthText = make_shared<Text>(string{}, mFnt, mVaoText, 0, mRenderer);
	shared_ptr<Text> sliderHeightText = make_shared<Text>(string{}, mFnt, mVaoText, 
		18 * TextVertexLayout::Size(), mRenderer);
	shared_ptr<Text> sliderWolfCountText = make_shared<Text>(string{}, mFnt, mVaoText, 
		36 * TextVertexLayout::Size(), mRenderer);
	shared_ptr<Text> sliderHareCountText = make_shared<Text>(string{}, mFnt, mVaoText, 
		48 * TextVertexLayout::Size(), mRenderer);

	mWidthSlider.create(sliderSprite, buttonSprite, sliderWidthText, 2, 200, 
		glm::vec2{ 0.0f, 40.0f }, mRenderer);
	mHeightSlider.create(sliderSprite, buttonSprite, sliderHeightText, 2, 200, 
		glm::vec2{ 0.0f, 20.0f }, mRenderer);
	mWolfCountSlider.create(sliderSprite, buttonSprite, sliderWolfCountText, 0, 50, 
		glm::vec2{ 0.0f, 0.0f }, mRenderer);
	mHareCountSlider.create(sliderSprite, buttonSprite, sliderHareCountText, 0, 50, 
		glm::vec2{ 0.0f, -20.0f }, mRenderer);

	// Create ortho matrix
	mOrthoMatrix = glm::ortho(-(dimensions.x / 2.0f), dimensions.x / 2.0f,
		-(dimensions.y / 2.0f), dimensions.y / 2.0f);
}


Application::~Application()
{
	if (mWnd)
		glfwDestroyWindow(mWnd);

	if (mIsGlfw)
		glfwTerminate();
}

void Application::run()
{
	const double updateTimeStep = 1.0 / 60.0;
	double accumulator = 0.0;

	auto previous = chrono::steady_clock::now();
	auto current = chrono::steady_clock::now();
	chrono::duration<double> diff;


	while (!glfwWindowShouldClose(mWnd))
	{
		current = chrono::steady_clock::now();
		diff = current - previous;
		previous = current;
		accumulator += mRealDeltaTime = diff.count();

		grabInput();

		while (accumulator > updateTimeStep)
		{
			accumulator -= updateTimeStep;

			calculateLogic(updateTimeStep);
		}

		animationUpdate(diff.count());

		renderScene();
		glfwSwapBuffers(mWnd);
	}
}

void Application::grabInput()
{
	glfwPollEvents();
	if (mState == State::MENU)
	{
		mWidthSlider.grabInput(mOrthoMatrix, *this);
		mHeightSlider.grabInput(mOrthoMatrix, *this);
		mWolfCountSlider.grabInput(mOrthoMatrix, *this);
		mHareCountSlider.grabInput(mOrthoMatrix, *this);

		if (getKeyState(GLFW_KEY_ENTER))
		{
			setupBoard();
			mState = State::SIMULATION;
		}
	}
	if (mState == State::SIMULATION)
	{
		mCameraMoveDir = { 0.0f, 0.0f };

		if (getKeyState(GLFW_KEY_UP) || getKeyState(GLFW_KEY_W))
			mCameraMoveDir += glm::vec2{ 0.0f, -1.0f };

		if (getKeyState(GLFW_KEY_DOWN) || getKeyState(GLFW_KEY_S))
			mCameraMoveDir += glm::vec2{ 0.0f, 1.0f };

		if (getKeyState(GLFW_KEY_LEFT) || getKeyState(GLFW_KEY_A))
			mCameraMoveDir += glm::vec2{ 1.0f, 0.0f };

		if (getKeyState(GLFW_KEY_RIGHT) || getKeyState(GLFW_KEY_D))
			mCameraMoveDir += glm::vec2{ -1.0f, 0.0f };

		if (getKeyState(GLFW_KEY_1))
			mCameraMoveMultiplier = 1.0f;

		if (getKeyState(GLFW_KEY_2))
			mCameraMoveMultiplier = 2.0f;

		if (getKeyState(GLFW_KEY_3))
			mCameraMoveMultiplier = 3.0f;

		if (getKeyState(GLFW_KEY_4))
			mCameraMoveMultiplier = 4.0f;

		mCameraZoom += getLastScrollAction() * cameraZoomUnit;
	}
}

void Application::calculateLogic(double deltaTime)
{
	if (mState == State::SIMULATION)
	{
		mCameraMoveDir = mCameraMoveDir == glm::vec2{ 0.0f, 0.0f } ? glm::vec2{ 0.0f, 0.0f } :
			glm::normalize(mCameraMoveDir);
		mCameraPos += static_cast<float>(deltaTime) * mCameraMoveDir * cameraMoveVelocity *
			mCameraMoveMultiplier;

		mTourTimer += static_cast<float>(deltaTime);

		if (mTourTimer >= tourTime)
		{
			mBoard.updateTurn(*this);

			// Update only active objects
			for (auto& obj : mBoard.getObjects())
			{
				if (!obj->isActive())
					continue;

				obj->saveCurrentPos();
			}

			for (auto& obj : mBoard.getObjects())
			{
				if (!obj->isActive())
					continue;

				obj->updateMove(mBoard);
			}

			for (auto& obj : mBoard.getObjects())
			{
				if (!obj->isActive())
					continue;

				obj->updateAction(mBoard);
			}

			mTourTimer = 0.0f;
		}

		mColorChange += deltaTime * colorChangeVelocity;
	}
}

void Application::animationUpdate(double deltaTime)
{
	if (mState == State::SIMULATION)
	{
		// Update all objects
		for (auto& obj : mBoard.getObjects())
			obj->update(deltaTime);

		auto color = glm::mix(oceanColorMin, oceanColorMax, (glm::sin(mColorChange) + 1.0f) / 2.0f);
		gl::ClearColor(color.r, color.g, color.b, 1.0f);
	}
}

void Application::renderScene()
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	if (mState == State::MENU)
	{
		mRenderer.bindOrthoMatrix(mOrthoMatrix);
		mWidthSlider.draw(mRenderer);
		mHeightSlider.draw(mRenderer);
		mWolfCountSlider.draw(mRenderer);
		mHareCountSlider.draw(mRenderer);
	}
	if (mState == State::SIMULATION)
	{
		auto cameraMatrix = mOrthoMatrix * glm::scale(glm::vec3{ mCameraZoom, mCameraZoom, 1.0f }) *
			glm::translate(glm::vec3{ mCameraPos, 0.0f });

		mRenderer.bindOrthoMatrix(cameraMatrix);

		mBoard.draw(mRenderer);

		// Render all objects
		for (auto& obj : mBoard.getObjects())
			obj->draw(mRenderer);
	}
}

Renderer& Application::getRenderer()
{
	return mRenderer;
}

glm::tvec2<int32_t> Application::getDimensions()
{
	int32_t width;
	int32_t height;

	glfwGetFramebufferSize(mWnd, &width, &height);

	return glm::tvec2<int32_t>{ width, height };
}

int32_t Application::getLastScrollAction()
{
	int32_t lastScroll = mVerticalScroll;
	mVerticalScroll = 0;
	return lastScroll;
}

bool Application::getKeyState(int keyCode)
{
	return glfwGetKey(mWnd, keyCode) == GLFW_PRESS;
}

bool Application::getMouseButtonState(int keyCode)
{
	return glfwGetMouseButton(mWnd, keyCode) == GLFW_PRESS;
}

glm::vec2 Application::getMousePosition()
{
	auto dim = getDimensions();

	glm::tvec2<double> pos;
	glfwGetCursorPos(mWnd, &pos.x, &pos.y);

	return glm::vec2{ static_cast<float>(pos.x), static_cast<float>(dim.y - pos.y) };
}

void Application::spawnWolf(glm::tvec2<int32_t> pos)
{
	uniform_int_distribution<int32_t> dist{ 0, 1 };

	if (dist(randomDev) == 1)
	{
		auto wolf = make_shared<WolfMale>(mWolfMaleSpriteSheet);
		wolf->setPos(pos);
		mBoard.addGameObject(dynamic_pointer_cast<GameObject>(wolf));
	}
	else
	{
		auto wolf = make_shared<WolfFemale>(mWolfFemaleSpriteSheet);
		wolf->setPos(pos);
		mBoard.addGameObject(dynamic_pointer_cast<GameObject>(wolf));
	}
}

void Application::spawnHare(glm::tvec2<int32_t> pos)
{
	auto hare = make_shared<Hare>(mHareSpriteSheet);
	hare->setPos(pos);
	mBoard.addGameObject(dynamic_pointer_cast<GameObject>(hare));
}

void Application::GlfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application* app{ static_cast<Application*>(glfwGetWindowUserPointer(window)) };

	app->mVerticalScroll = static_cast<int32_t>(yoffset);
}

void Application::GlfwFramebufferSizeCallback(GLFWwindow * window, int width, int height)
{
	Application* app{ static_cast<Application*>(glfwGetWindowUserPointer(window)) };


	app->mRenderer.setViewport(glm::tvec2<int32_t>{ width, height });
	app->mOrthoMatrix = glm::ortho(-(width / 2.0f), width / 2.0f,
			-(height / 2.0f), height / 2.0f);
}

void Application::setupBoard()
{
	auto boardWidth = mWidthSlider.getValue();
	auto boardHeight = mHeightSlider.getValue();
	auto wolfCount = mWolfCountSlider.getValue();
	auto hareCount = mHareCountSlider.getValue();

	// Board dimensions
	mBoard.create(boardWidth, boardHeight, mBoardSpriteSheet, mRenderer);
	mCameraPos = glm::vec2{ -(boardWidth * spriteSize / 2.0f), -(boardHeight * spriteSize / 2.0f) };
	mCameraZoom = 1.0f;

	// Spawn wolfs and hares
	uniform_int_distribution<int32_t> distWidth{ 0, static_cast<int32_t>(boardWidth) - 1 };
	uniform_int_distribution<int32_t> distHeight{ 0, static_cast<int32_t>(boardHeight) - 1 };

	for (int i = 0; i < wolfCount; i++)
		spawnWolf({ distWidth(randomDev), distHeight(randomDev) });

	for (int i = 0; i < hareCount; i++)
		spawnHare({ distWidth(randomDev), distHeight(randomDev) });
}

void Application::setupWolfMaleSpriteSheet()
{
	Image spriteImg;
	ifstream spriteFile{ wolfMaleSpriteSheetPath, ios_base::binary };
	PngCodec{}.decode(spriteFile, spriteImg);
	shared_ptr<Texture> spriteTex = make_shared<Texture>(spriteImg, mRenderer);
	spriteTex->generateMipmaps(mRenderer);

	mWolfMaleSpriteSheet = make_shared<SpriteSheet>();

	auto w = spriteImg.getWidth(), h = spriteImg.getHeight();
	glm::vec2 spriteSize{ Application::spriteSize, Application::spriteSize };

	// Data to specific image file
	// Don't change it

	// Forward #1
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize, 
		glm::vec2{ 0.0f / w, 0.0f / h }, glm::vec2{ 48.0f / w, 48.0f / h }, 
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Forward #2
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 0.0f / h }, glm::vec2{ 96.0f / w, 48.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Backward #1
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 48.0f / h }, glm::vec2{ 48.0f / w, 96.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Backward #2
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 48.0f / h }, glm::vec2{ 96.0f / w, 96.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Left #1
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 96.0f / h }, glm::vec2{ 48.0f / w, 144.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Left #2
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 96.0f / h }, glm::vec2{ 96.0f / w, 144.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Left #3
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 96.0f / h }, glm::vec2{ 144.0f / w, 144.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Left #4
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 144.0f / w, 96.0f / h }, glm::vec2{ 192.0f / w, 144.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Right #1
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 144.0f / h }, glm::vec2{ 48.0f / w, 192.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Right #2
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 144.0f / h }, glm::vec2{ 96.0f / w, 192.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Right #3
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 144.0f / h }, glm::vec2{ 144.0f / w, 192.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Right #4
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 144.0f / w, 144.0f / h }, glm::vec2{ 192.0f / w, 192.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// IdleFront #1
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 192.0f / h }, glm::vec2{ 48.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleFront #2
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 192.0f / h }, glm::vec2{ 96.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleFront #3
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 192.0f / h }, glm::vec2{ 144.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleFront #4
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 144.0f / w, 192.0f / h }, glm::vec2{ 192.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleFront #5
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 192.0f / w, 192.0f / h }, glm::vec2{ 240.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// IdleBack #1
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 240.0f / h }, glm::vec2{ 48.0f / w, 288.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleBack #2
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 240.0f / h }, glm::vec2{ 96.0f / w, 288.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// IdleLeft #1
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 240.0f / h }, glm::vec2{ 144.0f / w, 288.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleLeft #2
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 144.0f / w, 240.0f / h }, glm::vec2{ 192.0f / w, 288.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// IdleRight #1
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 192.0f / w, 240.0f / h }, glm::vec2{ 240.0f / w, 288.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleRight #2
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 240.0f / w, 240.0f / h }, glm::vec2{ 288.0f / w, 288.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Eat #1
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 240.0f / w, 192.0f / h }, glm::vec2{ 288.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Eat #2
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 288.0f / w, 192.0f / h }, glm::vec2{ 336.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Eat #3
	mWolfMaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 336.0f / w, 192.0f / h }, glm::vec2{ 384.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));
}

void Application::setupWolfFemaleSpriteSheet()
{
	Image spriteImg;
	ifstream spriteFile{ wolfFemaleSpriteSheetPath, ios_base::binary };
	PngCodec{}.decode(spriteFile, spriteImg);
	shared_ptr<Texture> spriteTex = make_shared<Texture>(spriteImg, mRenderer);
	spriteTex->generateMipmaps(mRenderer);

	mWolfFemaleSpriteSheet = make_shared<SpriteSheet>();

	auto w = spriteImg.getWidth(), h = spriteImg.getHeight();
	glm::vec2 spriteSize{ Application::spriteSize, Application::spriteSize };

	// Data to specific image file
	// Don't change it

	// Forward #1
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 0.0f / h }, glm::vec2{ 48.0f / w, 48.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Forward #2
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 0.0f / h }, glm::vec2{ 96.0f / w, 48.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Backward #1
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 48.0f / h }, glm::vec2{ 48.0f / w, 96.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Backward #2
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 48.0f / h }, glm::vec2{ 96.0f / w, 96.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Left #1
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 96.0f / h }, glm::vec2{ 48.0f / w, 144.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Left #2
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 96.0f / h }, glm::vec2{ 96.0f / w, 144.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Left #3
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 96.0f / h }, glm::vec2{ 144.0f / w, 144.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Left #4
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 144.0f / w, 96.0f / h }, glm::vec2{ 192.0f / w, 144.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Right #1
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 144.0f / h }, glm::vec2{ 48.0f / w, 192.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Right #2
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 144.0f / h }, glm::vec2{ 96.0f / w, 192.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Right #3
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 144.0f / h }, glm::vec2{ 144.0f / w, 192.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Right #4
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 144.0f / w, 144.0f / h }, glm::vec2{ 192.0f / w, 192.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// IdleFront #1
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 192.0f / h }, glm::vec2{ 48.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleFront #2
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 192.0f / h }, glm::vec2{ 96.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleFront #3
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 192.0f / h }, glm::vec2{ 144.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleFront #4
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 144.0f / w, 192.0f / h }, glm::vec2{ 192.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleFront #5
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 192.0f / w, 192.0f / h }, glm::vec2{ 240.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// IdleBack #1
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 240.0f / h }, glm::vec2{ 48.0f / w, 288.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleBack #2
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 240.0f / h }, glm::vec2{ 96.0f / w, 288.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// IdleLeft #1
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 240.0f / h }, glm::vec2{ 144.0f / w, 288.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleLeft #2
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 144.0f / w, 240.0f / h }, glm::vec2{ 192.0f / w, 288.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// IdleRight #1
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 192.0f / w, 240.0f / h }, glm::vec2{ 240.0f / w, 288.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// IdleRight #2
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 240.0f / w, 240.0f / h }, glm::vec2{ 288.0f / w, 288.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Eat #1
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 240.0f / w, 192.0f / h }, glm::vec2{ 288.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Eat #2
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 288.0f / w, 192.0f / h }, glm::vec2{ 336.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Eat #3
	mWolfFemaleSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 336.0f / w, 192.0f / h }, glm::vec2{ 384.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));
}

void Application::setupHareSpriteSheet()
{
	Image spriteImg;
	ifstream spriteFile{ hareSpriteSheetPath, ios_base::binary };
	PngCodec{}.decode(spriteFile, spriteImg);
	shared_ptr<Texture> spriteTex = make_shared<Texture>(spriteImg, mRenderer);
	spriteTex->generateMipmaps(mRenderer);

	mHareSpriteSheet = make_shared<SpriteSheet>();

	auto w = spriteImg.getWidth(), h = spriteImg.getHeight();
	glm::vec2 spriteSize{ Application::spriteSize, Application::spriteSize };

	// Data to specific image file
	// Don't change it

	// Forward #1
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 0.0f / h }, glm::vec2{ 48.0f / w, 48.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Forward #2
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 0.0f / h }, glm::vec2{ 96.0f / w, 48.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Forward #3
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 0.0f / h }, glm::vec2{ 144.0f / w, 48.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Backward #1
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 48.0f / h }, glm::vec2{ 48.0f / w, 96.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Backward #2
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 48.0f / h }, glm::vec2{ 96.0f / w, 96.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Backward #2
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 48.0f / h }, glm::vec2{ 144.0f / w, 96.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));



	// Left #1
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 96.0f / h }, glm::vec2{ 48.0f / w, 144.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Left #2
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 96.0f / h }, glm::vec2{ 96.0f / w, 144.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Left #3
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 96.0f / h }, glm::vec2{ 144.0f / w, 144.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Right #1
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 144.0f / h }, glm::vec2{ 48.0f / w, 192.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Right #2
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 144.0f / h }, glm::vec2{ 96.0f / w, 192.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Right #3
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 144.0f / h }, glm::vec2{ 144.0f / w, 192.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Eaten #1
	mHareSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 192.0f / h }, glm::vec2{ 48.0f / w, 240.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

}

void Application::setupBoardSpriteSheet()
{
	Image spriteImg;
	ifstream spriteFile{ boardSpriteSheetPath, ios_base::binary };
	PngCodec{}.decode(spriteFile, spriteImg);
	shared_ptr<Texture> spriteTex = make_shared<Texture>(spriteImg, mRenderer);
	spriteTex->generateMipmaps(mRenderer);

	mBoardSpriteSheet = make_shared<SpriteSheet>();

	auto w = spriteImg.getWidth(), h = spriteImg.getHeight();
	glm::vec2 spriteSize{ Application::spriteSize, Application::spriteSize };

	// Data to specific image file
	// Don't change it

	// Lower left tile
	mBoardSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 0.0f / h }, glm::vec2{ 48.0f / w, 48.0f / h }, 
		0.0f, spriteTex, mVaoSpriteInstanced, mRenderer));

	// Lower middle tile
	mBoardSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 0.0f / h }, glm::vec2{ 96.0f / w, 48.0f / h }, 
		0.0f, spriteTex, mVaoSpriteInstanced, mRenderer));

	// Lower right tile
	mBoardSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 0.0f / h }, glm::vec2{ 144.0f / w, 48.0f / h }, 
		0.0f, spriteTex, mVaoSpriteInstanced, mRenderer));


	// Middle left tile
	mBoardSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 48.0f / h }, glm::vec2{ 48.0f / w, 96.0f / h }, 
		0.0f, spriteTex, mVaoSpriteInstanced, mRenderer));

	// Center tile
	mBoardSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 48.0f / h }, glm::vec2{ 96.0f / w, 96.0f / h }, 
		0.0f, spriteTex, mVaoSpriteInstanced, mRenderer));

	// Middle right tile
	mBoardSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 48.0f / h }, glm::vec2{ 144.0f / w, 96.0f / h }, 
		0.0f, spriteTex, mVaoSpriteInstanced, mRenderer));


	// Upper left tile
	mBoardSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 0.0f / w, 96.0f / h }, glm::vec2{ 48.0f / w, 144.0f / h }, 
		0.0f, spriteTex, mVaoSpriteInstanced, mRenderer));

	// Upper middle tile
	mBoardSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 48.0f / w, 96.0f / h }, glm::vec2{ 96.0f / w, 144.0f / h }, 
		0.0f, spriteTex, mVaoSpriteInstanced, mRenderer));

	// Upper right tile
	mBoardSpriteSheet->addSprite(make_shared<Sprite>(spriteSize,
		glm::vec2{ 96.0f / w, 96.0f / h }, glm::vec2{ 144.0f / w, 144.0f / h }, 
		0.0f, spriteTex, mVaoSpriteInstanced, mRenderer));
}

void Application::setupGuiSpriteSheet()
{
}

