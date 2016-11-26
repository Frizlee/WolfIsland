#pragma once
#include "Prerequisites.hpp"
#include "gl_core_3_3.hpp"
#include <GLFW/glfw3.h>
#include "Renderer.hpp"
#include "Font.hpp"
#include "ImageAtlas.hpp"
#include "Texture.hpp"
#include "Text.hpp"
#include "Shader.hpp"
#include "VertexLayout.hpp"
#include "SpriteSheet.hpp"
#include "PngCodec.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include "Board.hpp"
#include "Slider.hpp"


class ApplicationInitException : public std::exception 
{
	virtual const char* what() const noexcept
	{
		return "Exception during initialization of the Application object occured.";
	}
};

class Application
{
public:
	// Default constructor, which doesn't do anything special
	Application();
	
	// Constructor which calls function "init"
	Application(const std::string& windowTitle,	bool fullscreen = false);

	// Function which initializes application data and creates window
	void init(const std::string& windowTitle, bool fullscreen = false);

	// Default destructor
	~Application();

	// Application starting point, creates main loop
	void run();

	// Gets input from keyboard and mouse in every frame
	void grabInput();

	// Calculates logic of all entities in every fixed time step
	void calculateLogic(double deltaTime);

	// Updates animation once in every frame.
	void animationUpdate(double deltaTime);

	// Renders all visible entities and hud elements
	void renderScene();

	Renderer& getRenderer();

	std::int32_t getLastScrollAction();
	bool getKeyState(int keyCode);
	bool getMouseButtonState(int keyCode);
	glm::vec2 getMousePosition();

	void spawnWolf(glm::tvec2<std::int32_t> pos);
	void spawnHare(glm::tvec2<std::int32_t> pos);

	static const float spriteSize;
	static const std::uint32_t windowWidth;
	static const std::uint32_t windowHeight;
	static std::random_device randomDev;
	static void GlfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
	// Window and rendering
	GLFWwindow *mWnd; // Pointer to glfw window
	bool mIsGlfw; // Stores information about glfw init state
	double mRealDeltaTime; // Stores real time difference between two frames
	Renderer mRenderer;
	float mColorChange;
	
	// Resources
	std::shared_ptr<Font> mFnt;
	std::shared_ptr<SpriteSheet> mWolfMaleSpriteSheet;
	std::shared_ptr<SpriteSheet> mWolfFemaleSpriteSheet;
	std::shared_ptr<SpriteSheet> mHareSpriteSheet;
	std::shared_ptr<SpriteSheet> mBoardSpriteSheet;

	// Simulation objects
	Board mBoard;

	// Menu controls
	Slider<std::int32_t> mWidthSlider;
	Slider<std::int32_t> mHeightSlider;
	Slider<std::int32_t> mWolfCountSlider;
	Slider<std::int32_t> mHareCountSlider;
	
	// Gpu resources
	std::shared_ptr<VertexArray> mVaoText;
	std::shared_ptr<VertexArray> mVaoSprite;
	std::shared_ptr<VertexArray> mVaoSpriteInstanced;

	glm::mat4 mOrthoMatrix;
	std::int32_t mVerticalScroll;
	glm::vec2 mCameraPos;
	glm::vec2 mCameraMoveDir;
	float mCameraMoveMultiplier;
	float mCameraZoom;
	float mTourTimer;

	enum class State
	{
		MENU,
		SIMULATION
	} mState;

	void setupBoard();
	void setupWolfMaleSpriteSheet();
	void setupWolfFemaleSpriteSheet();
	void setupHareSpriteSheet();
	void setupBoardSpriteSheet();
	void setupGuiSpriteSheet();
};
