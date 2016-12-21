#include "Application.hpp"
#include "WolfMale.hpp"
#include "WolfFemale.hpp"
#include "Hare.hpp"
#include "Boulder.hpp"
#include "Bush.hpp"
#include <glm/gtx/transform.hpp>
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
static const string boulderSpritePath{ "BoulderSprite.png" };
static const string bushSpritePath{ "BushSprite.png" };
static const string fontPath{ "TimesNewRoman.ttf" };
static const glm::vec4 textColor{ 160 / 256.0f, 160 / 256.0f, 160 / 256.0f, 1.0f };
const float Application::spriteSize{ 48.0f };
random_device Application::randomDev;

Application::Application()
	: mWnd{ nullptr }, mIsGlfw{ false }, mTourTimer{ 0.0f }, mCameraMoveMultiplier{ 1.0f },
	mState{ State::MENU }, mColorChange{ 0.0f }, mObjectAlreadySpawned{ false },
	mSpawnObjectTypeKey{ 'n' }, mMouseLastState{ false }
{
}

Application::Application(const std::string& windowTitle, const glm::tvec2<int32_t>& dimensions,
	bool fullscreen)
	: mWnd{ nullptr }, mIsGlfw{ false }, mTourTimer{ 0.0f }, mCameraMoveMultiplier{ 1.0f },
	mState{ State::MENU }, mColorChange{ 0.0f }, mObjectAlreadySpawned{ false }, 
	mSpawnObjectTypeKey{ 'n' }, mMouseLastState{ false }
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
	mFnt = make_shared<Font>(fontPath, 18, 
		make_shared<ImageAtlas>(256, 256, Image::Format::R8), mRenderer);

	// Create Text vbo and vao
	mVaoText = make_shared<VertexArray>(
		make_shared<VertexBuffer<TextVertexLayout>>(1024 * 1024, mRenderer), mRenderer);
	
	// Create Sprite vbo and vao
	mVaoSprite = make_shared<VertexArray>(
		make_shared<VertexBuffer<TextureVertexLayout>>(1024, mRenderer), mRenderer);
	mVaoSpriteInstanced = make_shared<VertexArray>(
		make_shared<VertexBuffer<TextureVertexLayout>>(1024, mRenderer), mRenderer);

	// Resources
	setupWolfMaleSpriteSheet();
	setupWolfFemaleSpriteSheet();
	setupHareSpriteSheet();
	setupBoardSpriteSheet();
	setupGuiSpriteSheet();

	// Boulder sprite
	{
		Image spriteImg;
		ifstream spriteFile{ boulderSpritePath, ios_base::binary };
		PngCodec{}.decode(spriteFile, spriteImg);
		shared_ptr<Texture> spriteTex = make_shared<Texture>(spriteImg, mRenderer);
		spriteTex->generateMipmaps(mRenderer);

		glm::vec2 spriteSize{ Application::spriteSize, Application::spriteSize };
		
		mBoulderSprite = make_shared<Sprite>(spriteSize, glm::vec2{ 0.0f, 0.0f }, 
			glm::vec2{ 1.0f, 1.0f }, 0.0f, spriteTex, mVaoSprite, mRenderer);
	}

	// Bush sprite
	{
		Image spriteImg;
		ifstream spriteFile{ bushSpritePath, ios_base::binary };
		PngCodec{}.decode(spriteFile, spriteImg);
		shared_ptr<Texture> spriteTex = make_shared<Texture>(spriteImg, mRenderer);
		spriteTex->generateMipmaps(mRenderer);

		glm::vec2 spriteSize{ Application::spriteSize, Application::spriteSize };

		mBushSprite = make_shared<Sprite>(spriteSize, glm::vec2{ 0.0f, 0.0f },
			glm::vec2{ 1.0f, 1.0f }, 0.0f, spriteTex, mVaoSprite, mRenderer);
	}

	// Sliders
	shared_ptr<Text> widthSliderText = make_shared<Text>(string{}, mFnt, mVaoText, 0, mRenderer);
	widthSliderText->setColor(textColor);
	shared_ptr<Text> heightSliderText = make_shared<Text>(string{}, mFnt, mVaoText, 
		18 * TextVertexLayout::Size(), mRenderer);
	heightSliderText->setColor(textColor);
	shared_ptr<Text> wolfSliderText = make_shared<Text>(string{}, mFnt, mVaoText, 
		36 * TextVertexLayout::Size(), mRenderer);
	wolfSliderText->setColor(textColor);
	shared_ptr<Text> hareSliderText = make_shared<Text>(string{}, mFnt, mVaoText, 
		48 * TextVertexLayout::Size(), mRenderer);
	hareSliderText->setColor(textColor);

	mMenuPanel.create(mGuiSpriteSheet, heightSliderText, widthSliderText, wolfSliderText, 
		hareSliderText, glm::vec2{}, mRenderer);
	
	// Start button
	mStartButton.create(mGuiSpriteSheet, 4, 5, glm::vec2{}, mRenderer);

	// Spawn buttons
	mNoneButton.create(mGuiSpriteSheet, 6, 7, glm::vec2{}, mRenderer);
	mNoneButton.setAutoUnpress(false);
	mWolfButton.create(mGuiSpriteSheet, 8, 9, glm::vec2{}, mRenderer);
	mWolfButton.setAutoUnpress(false);
	mHareButton.create(mGuiSpriteSheet, 10, 11, glm::vec2{}, mRenderer);
	mHareButton.setAutoUnpress(false);
	mBoulderButton.create(mGuiSpriteSheet, 12, 13, glm::vec2{}, mRenderer);
	mBoulderButton.setAutoUnpress(false);
	mBushButton.create(mGuiSpriteSheet, 14, 15, glm::vec2{}, mRenderer);
	mBushButton.setAutoUnpress(false);

	mNoneButton.setPress(true);
	
	// Info panel
	shared_ptr<Text> wolfMaleCountText = make_shared<Text>(string{}, mFnt, mVaoText,
		60 * TextVertexLayout::Size(), mRenderer);
	wolfMaleCountText->setColor(textColor);
	shared_ptr<Text> wolfFemaleCountText = make_shared<Text>(string{}, mFnt, mVaoText,
		90 * TextVertexLayout::Size(), mRenderer);
	wolfFemaleCountText->setColor(textColor);
	shared_ptr<Text> hareCountText = make_shared<Text>(string{}, mFnt, mVaoText,
		120 * TextVertexLayout::Size(), mRenderer);
	hareCountText->setColor(textColor);
	shared_ptr<Text> boulderCountText = make_shared<Text>(string{}, mFnt, mVaoText,
		150 * TextVertexLayout::Size(), mRenderer);
	boulderCountText->setColor(textColor);
	shared_ptr<Text> bushCountText = make_shared<Text>(string{}, mFnt, mVaoText,
		180 * TextVertexLayout::Size(), mRenderer);
	bushCountText->setColor(textColor);

	mInfoPanel.create(mGuiSpriteSheet, wolfMaleCountText, wolfFemaleCountText, hareCountText,
		boulderCountText, bushCountText, glm::vec2{}, mRenderer);
	
	resetGuiPosition();

	// Create ortho matrix
	mOrthoMatrix = glm::ortho(-dimensions.x / 2.0f, dimensions.x / 2.0f,
		-dimensions.y / 2.0f, dimensions.y / 2.0f);
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

	switch (mState)
	{
	case State::MENU:
		{
			if (getKeyState(GLFW_KEY_ENTER))
				mStartButton.setPress(true);

			if (mStartButton.isPressed())
			{
				setupBoard();
				mState = State::SIMULATION;
			}

			mMenuPanel.grabInput(mOrthoMatrix, *this);
			mStartButton.grabInput(mOrthoMatrix, *this);	

			break;
		}

	case State::SIMULATION:
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
			
			mNoneButton.grabInput(mOrthoMatrix, *this);

			if (mNoneButton.isPressed() || getKeyState(GLFW_KEY_N))
			{
				mNoneButton.setPress(true);
				mWolfButton.setPress(false);
				mHareButton.setPress(false);
				mBoulderButton.setPress(false);
				mBushButton.setPress(false);

				mSpawnObjectTypeKey = 'n'; // no object
			}

			mWolfButton.grabInput(mOrthoMatrix, *this);

			if (mWolfButton.isPressed() || getKeyState(GLFW_KEY_V))
			{
				mNoneButton.setPress(false);
				mWolfButton.setPress(true);
				mHareButton.setPress(false);
				mBoulderButton.setPress(false);
				mBushButton.setPress(false);

				mSpawnObjectTypeKey = 'v'; // wolf
			}

			mHareButton.grabInput(mOrthoMatrix, *this);

			if (mHareButton.isPressed() || getKeyState(GLFW_KEY_H))
			{
				mNoneButton.setPress(false);
				mWolfButton.setPress(false);
				mHareButton.setPress(true);
				mBoulderButton.setPress(false);
				mBushButton.setPress(false);

				mSpawnObjectTypeKey = 'h'; // hare
			}

			mBoulderButton.grabInput(mOrthoMatrix, *this);

			if (mBoulderButton.isPressed() || getKeyState(GLFW_KEY_B))
			{
				mNoneButton.setPress(false);
				mWolfButton.setPress(false);
				mHareButton.setPress(false);
				mBoulderButton.setPress(true);
				mBushButton.setPress(false);

				mSpawnObjectTypeKey = 'b'; // boulder
			}

			mBushButton.grabInput(mOrthoMatrix, *this);

			if (mBushButton.isPressed() || getKeyState(GLFW_KEY_G))
			{
				mNoneButton.setPress(false);
				mWolfButton.setPress(false);
				mHareButton.setPress(false);
				mBoulderButton.setPress(false);
				mBushButton.setPress(true);

				mSpawnObjectTypeKey = 'g'; // bush
			}

			if (getMouseButtonState(GLFW_MOUSE_BUTTON_1))
			{
				auto pos = getMouseoverSpawnPosition();
				auto boardDim =  glm::tvec2<int32_t>(mBoard.getWidth(), mBoard.getHeight());

				if (mSpawnPos != pos)
					mObjectAlreadySpawned = false;
				if (pos.x < 0 || pos.x >= boardDim.x ||
					pos.y < 0 || pos.y >= boardDim.y ||
					!mBoard.getObjects(pos, false).empty())
					mObjectAlreadySpawned = true;

				mSpawnPos = pos;
			}

			mCameraZoom += getLastScrollAction() * cameraZoomUnit;
			mCameraZoom = glm::clamp(mCameraZoom, 0.3f, 3.0f);

			mInfoPanel.grabInput(mOrthoMatrix, *this);

			break;
		}
	}
}

void Application::calculateLogic(double deltaTime)
{
	switch (mState)
	{
	case State::MENU:
		{
			mMenuPanel.update(deltaTime);
			mStartButton.update(deltaTime);
			break;
		}

	case State::SIMULATION:
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

			mCameraMatrix = mOrthoMatrix * 
				glm::scale(glm::vec3{ mCameraZoom, mCameraZoom, 1.0f }) *
				glm::translate(glm::vec3{ mCameraPos, 0.0f });

			if (!mObjectAlreadySpawned)
			{
				switch (mSpawnObjectTypeKey)
				{
				case 'b':
					spawnBoulder(mSpawnPos);
					break;

				case 'g':
					spawnBush(mSpawnPos);
					break;

				case 'v':
					spawnWolf(mSpawnPos);
					break;

				case 'h':
					spawnHare(mSpawnPos);
					break;

				case 'n': // No object to spawn
					break;
				}

				mObjectAlreadySpawned = true;
			}

			mInfoPanel.update(deltaTime);
			mNoneButton.update(deltaTime);
			mWolfButton.update(deltaTime);
			mHareButton.update(deltaTime);
			mBoulderButton.update(deltaTime);
			mBushButton.update(deltaTime);

			if (mBoard.isCountersChanged())
				mInfoPanel.updateCounters(mBoard.getObjectCounters(), mRenderer);

			break;
		}
	}
}

void Application::animationUpdate(double deltaTime)
{
	switch (mState)
	{
	case State::SIMULATION:
		{
			// Update all objects
			for (auto& obj : mBoard.getObjects())
				obj->update(deltaTime);

			auto color = glm::mix(oceanColorMin, oceanColorMax, 
				(glm::sin(mColorChange) + 1.0f) / 2.0f);
			gl::ClearColor(color.r, color.g, color.b, 1.0f);
		}
	}
}

void Application::renderScene()
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	switch (mState)
	{
	case State::MENU:
		{
			// Render menu interface 
			mRenderer.bindOrthoMatrix(mOrthoMatrix);
			
			mMenuPanel.draw(mRenderer);
			mStartButton.draw(mRenderer);
			break;
		}

	case State::SIMULATION:
		{
			// Render simulation objects
			mRenderer.bindOrthoMatrix(mCameraMatrix);

			mBoard.draw(mRenderer);

			for (auto& obj : mBoard.getObjects())
				obj->draw(mRenderer);

			// Render user interface
			mRenderer.bindOrthoMatrix(mOrthoMatrix);
			mInfoPanel.draw(mRenderer);
			mNoneButton.draw(mRenderer);
			mWolfButton.draw(mRenderer);
			mHareButton.draw(mRenderer);
			mBoulderButton.draw(mRenderer);
			mBushButton.draw(mRenderer);
			break;
		}
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

void Application::resetGuiPosition()
{
	auto dimensions = getDimensions();

	auto menuPanelBounds = mGuiSpriteSheet->getSprite(3).lock()->getBounds();
	mMenuPanel.setPos(glm::vec2{ -menuPanelBounds.x / 2.0f, -menuPanelBounds.y / 2.0f });
	
	auto startButtonBounds = mGuiSpriteSheet->getSprite(4).lock()->getBounds();
	mStartButton.setPos(glm::vec2{ -startButtonBounds.x / 2.0f, 
		-menuPanelBounds.y / 2.0f - startButtonBounds.y - 30.0f });
	
	auto infoPanelBounds = mGuiSpriteSheet->getSprite(2).lock()->getBounds();
	mInfoPanel.setPos(glm::vec2{ -dimensions.x / 2.0f, dimensions.y / 2.0f - infoPanelBounds.y });

	// Spawn buttons
	auto spawnButtonsBounds = mGuiSpriteSheet->getSprite(6).lock()->getBounds();
	glm::vec2 startPos{ -5.0f * spawnButtonsBounds.x / 2.0f, -dimensions.y / 2.0f };
	mNoneButton.setPos(startPos);
	startPos += glm::vec2{ spawnButtonsBounds.x, 0.0f };
	mWolfButton.setPos(startPos);
	startPos += glm::vec2{ spawnButtonsBounds.x, 0.0f };
	mHareButton.setPos(startPos);
	startPos += glm::vec2{ spawnButtonsBounds.x, 0.0f };
	mBoulderButton.setPos(startPos);
	startPos += glm::vec2{ spawnButtonsBounds.x, 0.0f };
	mBushButton.setPos(startPos);
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

bool Application::getMouseButtonState(int keyCode, bool clickedThisFrame)
{
	if (clickedThisFrame)
	{
		auto thisState = glfwGetMouseButton(mWnd, keyCode) == GLFW_PRESS;

		if (thisState && !mMouseLastState[keyCode])
			return true;
	}
	else 
		return glfwGetMouseButton(mWnd, keyCode) == GLFW_PRESS;

	return false;
}

glm::vec2 Application::getMousePosition()
{
	auto dim = getDimensions();

	glm::tvec2<double> pos;
	glfwGetCursorPos(mWnd, &pos.x, &pos.y);

	return glm::vec2{ static_cast<float>(pos.x), static_cast<float>(dim.y - pos.y) };
}

glm::vec4 Application::getMouseNormalizedPosition()
{
	auto dim = getDimensions();
	auto pos = getMousePosition();
	pos = 2.0f * pos / glm::vec2{ static_cast<float>(dim.x), static_cast<float>(dim.y) } - 1.0f;

	return glm::vec4{ pos.x, pos.y, 0.0f, 1.0f };
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

void Application::spawnBoulder(glm::tvec2<std::int32_t> pos)
{
	auto boulder = make_shared<Boulder>(mBoulderSprite);
	boulder->setPos(pos);
	mBoard.addGameObject(dynamic_pointer_cast<GameObject>(boulder));
}

void Application::spawnBush(glm::tvec2<std::int32_t> pos)
{
	auto bush = make_shared<Bush>(mBushSprite);
	bush->setPos(pos);
	mBoard.addGameObject(dynamic_pointer_cast<GameObject>(bush));
}

void Application::GlfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application* app{ static_cast<Application*>(glfwGetWindowUserPointer(window)) };

	app->mVerticalScroll = static_cast<int32_t>(yoffset);
}

void Application::GlfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Application* app{ static_cast<Application*>(glfwGetWindowUserPointer(window)) };


	app->mRenderer.setViewport(glm::tvec2<int32_t>{ width, height });
	app->mOrthoMatrix = glm::ortho(-(width / 2.0f), width / 2.0f,
			-(height / 2.0f), height / 2.0f);
	app->resetGuiPosition();
}

glm::tvec2<int32_t> Application::getMouseoverSpawnPosition()
{
	auto pos = getMouseNormalizedPosition() * glm::inverse(mCameraMatrix)
		- glm::vec4{ mCameraPos.x, mCameraPos.y, mCameraPos.x, 0.0f };
	pos /= spriteSize;
	
	return glm::tvec2<int32_t>{ static_cast<int32_t>(pos.x), static_cast<int32_t>(pos.y) };
}

void Application::setupBoard()
{
	// 0 - height, 1 - width, 2 - wolfCount, 3 - hareCount
	auto values = mMenuPanel.getValues();

	// Board dimensions
	mBoard.create(values[1], values[0], mBoardSpriteSheet, mRenderer);
	mCameraPos = glm::vec2{ -(values[1] * spriteSize / 2.0f), -(values[0] * spriteSize / 2.0f) };
	mCameraZoom = 1.0f;

	// Spawn wolfs and hares
	uniform_int_distribution<int32_t> distWidth{ 0, static_cast<int32_t>(values[1]) - 1 };
	uniform_int_distribution<int32_t> distHeight{ 0, static_cast<int32_t>(values[0]) - 1 };

	for (int i = 0; i < values[2]; i++)
		spawnWolf({ distWidth(randomDev), distHeight(randomDev) });

	for (int i = 0; i < values[3]; i++)
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
	Image spriteImg;
	ifstream spriteFile{ guiSpriteSheetPath, ios_base::binary };
	PngCodec{}.decode(spriteFile, spriteImg);
	shared_ptr<Texture> spriteTex = make_shared<Texture>(spriteImg, mRenderer);
	spriteTex->generateMipmaps(mRenderer);

	mGuiSpriteSheet = make_shared<SpriteSheet>();

	auto w = spriteImg.getWidth(), h = spriteImg.getHeight();
	glm::vec2 spriteSize{ Application::spriteSize, Application::spriteSize };

	// Data to specific image file
	// Don't change it

	// Slider
	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 176.0f, 15.0f },
		glm::vec2{ 0.0f / w, 0.0f / h }, glm::vec2{ 176.0f / w, 15.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Slider button
	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 22.0f, 33.0f },
		glm::vec2{ 0.0f / w, 15.0f / h }, glm::vec2{ 22.0f / w, 48.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Object list panel
	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 320.0f, 179.0f },
		glm::vec2{ 0.0f / w, 48.0f / h }, glm::vec2{ 320.0f / w, 227.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	// Menu panel
	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 319.0f, 310.0f },
		glm::vec2{ 0.0f / w, 229.0f / h }, glm::vec2{ 319.0f / w, 539.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Start button 
	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 84.0f, 84.0f },
		glm::vec2{ 0.0f / w, 539.0f / h }, glm::vec2{ 84.0f / w, 623.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 84.0f, 84.0f },
		glm::vec2{ 84.0f / w, 539.0f / h }, glm::vec2{ 168.0f / w, 623.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// None button 
	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 84.0f, 84.0f },
		glm::vec2{ 0.0f / w, 623.0f / h }, glm::vec2{ 84.0f / w, 707.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 84.0f, 84.0f },
		glm::vec2{ 84.0f / w, 623.0f / h }, glm::vec2{ 168.0f / w, 707.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Wolf button 
	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 84.0f, 84.0f },
		glm::vec2{ 0.0f / w, 707.0f / h }, glm::vec2{ 84.0f / w, 791.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 84.0f, 84.0f },
		glm::vec2{ 84.0f / w, 707.0f / h }, glm::vec2{ 168.0f / w, 791.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Hare button 
	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 84.0f, 84.0f },
		glm::vec2{ 0.0f / w, 791.0f / h }, glm::vec2{ 84.0f / w, 875.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 84.0f, 84.0f },
		glm::vec2{ 84.0f / w, 791.0f / h }, glm::vec2{ 168.0f / w, 875.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Boulder button 
	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 84.0f, 84.0f },
		glm::vec2{ 0.0f / w, 875.0f / h }, glm::vec2{ 84.0f / w, 959.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 84.0f, 84.0f },
		glm::vec2{ 84.0f / w, 875.0f / h }, glm::vec2{ 168.0f / w, 959.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));


	// Bush button 
	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 84.0f, 84.0f },
		glm::vec2{ 168.0f / w, 539.0f / h }, glm::vec2{ 252.0f / w, 623.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));

	mGuiSpriteSheet->addSprite(make_shared<Sprite>(glm::vec2{ 84.0f, 84.0f },
		glm::vec2{ 252.0f / w, 539.0f / h }, glm::vec2{ 336.0f / w, 623.0f / h },
		1.0f, spriteTex, mVaoSprite, mRenderer));
}

