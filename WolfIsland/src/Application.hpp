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

/// <summary>	Klasa wyjątku inicjalizacji obiektu aplikacji. </summary>
class ApplicationInitException : public std::exception 
{
	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca informację o błędzie. </summary>
	///
	/// <returns>	Informacja o błędzie. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual const char* what() const noexcept
	{
		return "Exception during initialization of the Application object occured.";
	}
};

/// <summary>	
///		Klasa reprezentująca obiekt główny aplikacji. Tworzy i przydziela zasoby poszczególnym 
///		obiektom.
///		ą, ć, ę, ł, ń, ó, ś, ź, ż
///		Ą, Ć, Ę, Ł, Ń, Ó, Ś, Ź, Ż
/// </summary>
class Application
{
public:
	/// <summary>	Domyślny konsturuktor. </summary>
	Application();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor initializujący aplikację. </summary>
	///
	/// <param name="windowTitle">	Tytuł okna aplikacji. </param>
	/// <param name="dimensions"> 	Rozmiary okna aplikacji. </param>
	/// <param name="fullscreen"> 	[Opt] Prawda jeżeli włączyć tryb fullscreen. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Application(const std::string& windowTitle, const glm::tvec2<std::int32_t>& dimensions,
		bool fullscreen = false);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja initializująca aplikację. </summary>
	///
	/// <param name="windowTitle">	Tytuł okna aplikacji. </param>
	/// <param name="dimensions"> 	Rozmiary okna aplikacji. </param>
	/// <param name="fullscreen"> 	[Opt] Prawda jeżeli włączyć tryb fullscreen. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void init(const std::string& windowTitle, const glm::tvec2<std::int32_t>& dimensions,
		bool fullscreen = false);

	/// <summary>	Domyślny destrukotor. </summary>
	~Application();

	/// <summary>	Punkt startowy aplikacji. </summary>
	void run();

	/// <summary>	Funkcja obsługująca wejście do aplikacji. </summary>
	void grabInput();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja licząca logikę w pętli stałokrokowej. </summary>
	///
	/// <param name="deltaTime">	Krok pomiędzy wywołaniami funkcji. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void calculateLogic(double deltaTime);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizująca animację raz na klatkę. </summary>
	///
	/// <param name="deltaTime">	Czas pomiędzy klatkami. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void animationUpdate(double deltaTime);

	/// <summary>	Funkcja rysująca aktualną scenę. </summary>
	void renderScene();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracajaca obiekt renderera. </summary>
	///
	/// <returns>	Obiekt renderera. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Renderer& getRenderer();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiary okna. </summary>
	///
	/// <returns>	Rozmiary okna. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	glm::tvec2<std::int32_t> getDimensions();

	/// <summary>	Funkcja ustawiająca położenie obiektów interfejsu użytkownika. </summary>
	void resetGuiPosition();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja pobierająca ostatnią akcję związaną z kółkiem myszy. </summary>
	///
	/// <returns>	Ostatnia akcaj kółka myszy. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::int32_t getLastScrollAction();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja pobierająca stan przycisku klawiatury. </summary>
	///
	/// <param name="keyCode">	Kod przycisku. </param>
	///
	/// <returns>	Prawda jeżeli wciśnięty. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool getKeyState(int keyCode);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja pobierająca stan przycisku myszki. </summary>
	///
	/// <param name="keyCode">		   	Kod przycisku. </param>
	/// <param name="clickedThisFrame">	
	///		[Opt] Prawda jeżeli ma reagować tylko na przycisk wciśnięty 
	///		podczas tej trwania tej klatki animacji. 
	///	</param>
	///
	/// <returns>	Prawda jeżeli wciśnięty. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool getMouseButtonState(int keyCode, bool clickedThisFrame = false);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja pobierająca pozycję myszki. </summary>
	///
	/// <returns>	Pozycja myszki. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	glm::vec2 getMousePosition();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja pobierająca znormalizowaną pozycję myszki. </summary>
	///
	/// <returns>	Znormalizowana pozycja myszki. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	glm::vec4 getMouseNormalizedPosition();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja dodająca wilka. </summary>
	///
	/// <param name="pos">	Pozycja. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void spawnWolf(glm::tvec2<std::int32_t> pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja dodająca zająca. </summary>
	///
	/// <param name="pos">	Pozycja. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void spawnHare(glm::tvec2<std::int32_t> pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja dodająca głaz. </summary>
	///
	/// <param name="pos">	Pozycja. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void spawnBoulder(glm::tvec2<std::int32_t> pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja dodająca krzak. </summary>
	///
	/// <param name="pos">	Pozycja. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void spawnBush(glm::tvec2<std::int32_t> pos);

	/// <summary>	Stała określająca rozmiar kafelka podłoża. </summary>
	static const float spriteSize;

	/// <summary>	Maszyna generująca liczby pseudolosowe. </summary>
	static std::random_device randomDev;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Callback GLFW reagujący na akcję kółka myszki. </summary>
	///
	/// <param name="window"> 	Obiekt okna przejmującego wywołanie. </param>
	/// <param name="xoffset">	Offset x. </param>
	/// <param name="yoffset">	Offset y. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	static void GlfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Callback GLFW reagujący na zmiany rozmiarów okna. </summary>
	///
	/// <param name="window">	Obiekt okan przejmującego wywołanie. </param>
	/// <param name="width"> 	Nowa szerokość bufora klatki. </param>
	/// <param name="height">	Nowa wysokość bufora klatki. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	static void GlfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);

private:
	/// <summary>	Wartości reprezentujące stan aplikacji. </summary>
	enum class State
	{
		MENU,
		SIMULATION
	};

	/// <summary>	Obiekt okna GLFW </summary>
	GLFWwindow *mWnd;

	/// <summary>	Prawda jeżeli GLFW jest już zinicjalizowane. </summary>
	bool mIsGlfw;

	/// <summary>	Prawdziwy czas pomiędzy kolejnymi klatkami. </summary>
	double mRealDeltaTime;

	/// <summary>	Obiekt renderera. </summary>
	Renderer mRenderer;

	/// <summary>	Współczynnik zmiany koloru wody. </summary>
	float mColorChange;
	
	/// <summary>	Obiekt czcionki. </summary>
	std::shared_ptr<Font> mFnt;

	/// <summary>	Zbiór spriteów dla samca wilka. </summary>
	std::shared_ptr<SpriteSheet> mWolfMaleSpriteSheet;

	/// <summary>	Zbiór spriteów dla samicy wilka. </summary>
	std::shared_ptr<SpriteSheet> mWolfFemaleSpriteSheet;

	/// <summary>	Zbiór spriteów dla zająca. </summary>
	std::shared_ptr<SpriteSheet> mHareSpriteSheet;

	/// <summary>	Zbiór spriteów dla planszy. </summary>
	std::shared_ptr<SpriteSheet> mBoardSpriteSheet;

	/// <summary>	Zbiór spriteów dla interfejzu użytkownika. </summary>
	std::shared_ptr<SpriteSheet> mGuiSpriteSheet;

	/// <summary>	Zbiór spriteów dla głazu. </summary>
	std::shared_ptr<Sprite> mBoulderSprite;

	/// <summary>	Zbiór spriteów dla krzaka. </summary>
	std::shared_ptr<Sprite> mBushSprite;

	/// <summary>	Obiekt planszy. </summary>
	Board mBoard;

	/// <summary>	Panel początkowy symulacji. </summary>
	MenuPanel mMenuPanel;

	/// <summary>	Panel zawierający informacjię o stanie symulacji. </summary>
	InformationPanel mInfoPanel;

	/// <summary>	Przycisk startowy. </summary>
	Button mStartButton;

	/// <summary>	Przycisk stawiania niczego. </summary>
	Button mNoneButton;

	/// <summary>	Przycisk stawiania wilka. </summary>
	Button mWolfButton;

	/// <summary>	Przycisk stawiania zająca. </summary>
	Button mHareButton;

	/// <summary>	Przycisk stawiania głazu. </summary>
	Button mBoulderButton;

	/// <summary>	Przycisk stawiania krzaka. </summary>
	Button mBushButton;
	
	/// <summary>	Tablica stanów OpenGL dla obiektów tekstu. </summary>
	std::shared_ptr<VertexArray> mVaoText;

	/// <summary>	Tablica stanów OpenGL dla obiektów sprite. </summary>
	std::shared_ptr<VertexArray> mVaoSprite;

	/// <summary>	Tablica stanów OpenGL dla instancjonowanych obiektów sprite. </summary>
	std::shared_ptr<VertexArray> mVaoSpriteInstanced;

	/// <summary>	Macierz ortagonalna. </summary>
	glm::mat4 mOrthoMatrix;

	/// <summary>	Macierz kamery. </summary>
	glm::mat4 mCameraMatrix;

	/// <summary>	Pozycja kółka myszy. </summary>
	std::int32_t mVerticalScroll;

	/// <summary>	Ostatnie stany przycisków myszy. </summary>
	std::array<bool, 8> mMouseLastState;

	/// <summary>	Pozycja kamery. </summary>
	glm::vec2 mCameraPos;

	/// <summary>	Kierunek poruszania się kamery. </summary>
	glm::vec2 mCameraMoveDir;

	/// <summary>	Mnożnik szybkości poruszania się kamery. </summary>
	float mCameraMoveMultiplier;

	/// <summary>	Przybliżenie kamery. </summary>
	float mCameraZoom;

	/// <summary>	Czas tury. </summary>
	float mTourTimer;

	/// <summary>	Typ aktualnie stawianego obiektu. </summary>
	char mSpawnObjectTypeKey;

	/// <summary>	Prawda jeżeli postawiono już obiekt na tym miejscu. </summary>
	bool mObjectAlreadySpawned;

	/// <summary>	Pozycja do postawienia obiektu. </summary>
	glm::tvec2<std::int32_t> mSpawnPos;

	/// <summary>	Aktualny stan aplikacji. </summary>
	State mState;

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Pobieranie pozycji myszy i przekształcanie jej na pozycję do postawienia nowego 
	///		obiektu. 
	///	</summary>
	///
	/// <returns>	Pozycja do postawienia obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	glm::tvec2<std::int32_t> getMouseoverSpawnPosition();

	/// <summary>	Ustawienie rozmiarów planszy. </summary>
	void setupBoard();

	/// <summary>	Wczytanie zasobów samca wilka. </summary>
	void setupWolfMaleSpriteSheet();

	/// <summary>	Wczytanie zasobów samicy wilka. </summary>
	void setupWolfFemaleSpriteSheet();

	/// <summary>	Wczytanie zasobów zająca. </summary>
	void setupHareSpriteSheet();

	/// <summary>	Wczytanie zasobów planszy. </summary>
	void setupBoardSpriteSheet();

	/// <summary>	Wczytanie zasobów interfejsu użytkownika. </summary>
	void setupGuiSpriteSheet();
};

