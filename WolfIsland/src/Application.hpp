///-------------------------------------------------------------------------------------------------
// file:	src\Application.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
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
#include <glm/vec2.hpp>
#include <glm/gtx/transform.hpp>
#include "Board.hpp"
#include "InformationPanel.hpp"
#include "MenuPanel.hpp"
#include "Button.hpp"

/// <summary>	Exception for signalling application init errors. </summary>
class ApplicationInitException : public std::exception 
{
	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the what. </summary>
	///
	/// <returns>	Null if it fails, else a pointer to a const char. </returns>
	///--------------------------------------------------------------------------------------------
	virtual const char* what() const noexcept
	{
		return "Exception during initialization of the Application object occured.";
	}
};

/// <summary>	An application. </summary>
class Application
{
public:
	/// <summary>	Default constructor, which doesn't do anything special. </summary>
	Application();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor which calls function "init". </summary>
	///
	/// <param name="windowTitle">	The window title. </param>
	/// <param name="dimensions"> 	The dimensions. </param>
	/// <param name="fullscreen"> 	(Optional) True to fullscreen. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Application(const std::string& windowTitle, const glm::tvec2<std::int32_t>& dimensions,
		bool fullscreen = false);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Function which initializes application data and creates window. </summary>
	///
	/// <param name="windowTitle">	The window title. </param>
	/// <param name="dimensions"> 	The dimensions. </param>
	/// <param name="fullscreen"> 	(Optional) True to fullscreen. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void init(const std::string& windowTitle, const glm::tvec2<std::int32_t>& dimensions,
		bool fullscreen = false);

	/// <summary>	Default destructor. </summary>
	~Application();

	/// <summary>	Application starting point, creates main loop. </summary>
	void run();

	/// <summary>	Gets input from keyboard and mouse in every frame. </summary>
	void grabInput();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Calculates logic of all entities in every fixed time step. </summary>
	///
	/// <param name="deltaTime">	The delta time. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void calculateLogic(double deltaTime);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates animation once in every frame. </summary>
	///
	/// <param name="deltaTime">	The delta time. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void animationUpdate(double deltaTime);

	/// <summary>	Renders all visible entities and hud elements. </summary>
	void renderScene();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the renderer. </summary>
	///
	/// <returns>	The renderer. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Renderer& getRenderer();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the dimensions. </summary>
	///
	/// <returns>	The dimensions. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	glm::tvec2<std::int32_t> getDimensions();

	/// <summary>	Resets the graphical user interface position. </summary>
	void resetGuiPosition();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the last scroll action. </summary>
	///
	/// <returns>	The last scroll action. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::int32_t getLastScrollAction();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets key state. </summary>
	///
	/// <param name="keyCode">	The key code. </param>
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool getKeyState(int keyCode);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets mouse button state. </summary>
	///
	/// <param name="keyCode">		   	The key code. </param>
	/// <param name="clickedThisFrame">	(Optional) True to clicked this frame. </param>
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool getMouseButtonState(int keyCode, bool clickedThisFrame = false);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets mouse position. </summary>
	///
	/// <returns>	The mouse position. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	glm::vec2 getMousePosition();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets mouse normalized position. </summary>
	///
	/// <returns>	The mouse normalized position. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	glm::vec4 getMouseNormalizedPosition();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Spawn wolf. </summary>
	///
	/// <param name="pos">	The position. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void spawnWolf(glm::tvec2<std::int32_t> pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Spawn hare. </summary>
	///
	/// <param name="pos">	The position. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void spawnHare(glm::tvec2<std::int32_t> pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Spawn boulder. </summary>
	///
	/// <param name="pos">	The position. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void spawnBoulder(glm::tvec2<std::int32_t> pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Spawn bush. </summary>
	///
	/// <param name="pos">	The position. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void spawnBush(glm::tvec2<std::int32_t> pos);

	/// <summary>	Size of the sprite. </summary>
	static const float spriteSize;
	/// <summary>	The random development. </summary>
	static std::random_device randomDev;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Callback, called when the glfw scroll. </summary>
	///
	/// <param name="window"> 	[in,out] If non-null, the window. </param>
	/// <param name="xoffset">	The xoffset. </param>
	/// <param name="yoffset">	The yoffset. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	static void GlfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Callback, called when the glfw framebuffer size. </summary>
	///
	/// <param name="window">	[in,out] If non-null, the window. </param>
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	static void GlfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);

private:
	/// <summary>	Window and rendering. </summary>
	GLFWwindow *mWnd;
	/// <summary>	Stores information about glfw init state. </summary>
	bool mIsGlfw;
	/// <summary>	Stores real time difference between two frames. </summary>
	double mRealDeltaTime;
	/// <summary>	The renderer. </summary>
	Renderer mRenderer;
	/// <summary>	The color change. </summary>
	float mColorChange;
	
	/// <summary>	Resources. </summary>
	std::shared_ptr<Font> mFnt;
	/// <summary>	The wolf male sprite sheet. </summary>
	std::shared_ptr<SpriteSheet> mWolfMaleSpriteSheet;
	/// <summary>	The wolf female sprite sheet. </summary>
	std::shared_ptr<SpriteSheet> mWolfFemaleSpriteSheet;
	/// <summary>	The hare sprite sheet. </summary>
	std::shared_ptr<SpriteSheet> mHareSpriteSheet;
	/// <summary>	The board sprite sheet. </summary>
	std::shared_ptr<SpriteSheet> mBoardSpriteSheet;
	/// <summary>	The graphical user interface sprite sheet. </summary>
	std::shared_ptr<SpriteSheet> mGuiSpriteSheet;
	/// <summary>	The boulder sprite. </summary>
	std::shared_ptr<Sprite> mBoulderSprite;
	/// <summary>	The bush sprite. </summary>
	std::shared_ptr<Sprite> mBushSprite;

	/// <summary>	Simulation objects. </summary>
	Board mBoard;

	/// <summary>	Menu controls. </summary>
	MenuPanel mMenuPanel;
	/// <summary>	The information panel. </summary>
	InformationPanel mInfoPanel;
	/// <summary>	The start button. </summary>
	Button mStartButton;
	/// <summary>	The none control. </summary>
	Button mNoneButton;
	/// <summary>	The wolf control. </summary>
	Button mWolfButton;
	/// <summary>	The hare control. </summary>
	Button mHareButton;
	/// <summary>	The boulder control. </summary>
	Button mBoulderButton;
	/// <summary>	The bush control. </summary>
	Button mBushButton;
	
	/// <summary>	Gpu resources. </summary>
	std::shared_ptr<VertexArray> mVaoText;
	/// <summary>	The vao sprite. </summary>
	std::shared_ptr<VertexArray> mVaoSprite;
	/// <summary>	The vao sprite instanced. </summary>
	std::shared_ptr<VertexArray> mVaoSpriteInstanced;

	/// <summary>	The ortho matrix. </summary>
	glm::mat4 mOrthoMatrix;
	/// <summary>	The camera matrix. </summary>
	glm::mat4 mCameraMatrix;

	/// <summary>	Input related. </summary>
	std::int32_t mVerticalScroll;
	/// <summary>	State of the mouse last. </summary>
	std::array<bool, 8> mMouseLastState;
	/// <summary>	The camera position. </summary>
	glm::vec2 mCameraPos;
	/// <summary>	The camera move dir. </summary>
	glm::vec2 mCameraMoveDir;
	/// <summary>	The camera move multiplier. </summary>
	float mCameraMoveMultiplier;
	/// <summary>	The camera zoom. </summary>
	float mCameraZoom;
	/// <summary>	The tour timer. </summary>
	float mTourTimer;
	/// <summary>	The spawn object type key. </summary>
	char mSpawnObjectTypeKey;
	/// <summary>	True if object already spawned. </summary>
	bool mObjectAlreadySpawned;
	/// <summary>	The spawn position. </summary>
	glm::tvec2<std::int32_t> mSpawnPos;

	/// <summary>	Values that represent states. </summary>
	enum class State
	{
		MENU,
		SIMULATION
	} mState;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets mouseover spawn position. </summary>
	///
	/// <returns>	The mouseover spawn position. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	glm::tvec2<std::int32_t> getMouseoverSpawnPosition();

	/// <summary>	Sets up the board. </summary>
	void setupBoard();
	/// <summary>	Sets up the wolf male sprite sheet. </summary>
	void setupWolfMaleSpriteSheet();
	/// <summary>	Sets up the wolf female sprite sheet. </summary>
	void setupWolfFemaleSpriteSheet();
	/// <summary>	Sets up the hare sprite sheet. </summary>
	void setupHareSpriteSheet();
	/// <summary>	Sets up the board sprite sheet. </summary>
	void setupBoardSpriteSheet();
	/// <summary>	Sets up the graphical user interface sprite sheet. </summary>
	void setupGuiSpriteSheet();
};

