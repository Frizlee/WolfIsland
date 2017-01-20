#pragma once
#include "Prerequisites.hpp"
#include "Sprite.hpp"
#include "VertexBuffer.hpp"
#include "gl_core_3_3.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

/// <summary>	Klasa przedstawiająca planszę symulacji. </summary>
class Board
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	Board();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor tworzący planszę. </summary>
	///
	/// <param name="width">	  	Szerokość planszy. </param>
	/// <param name="height">	  	Wysokość planszy. </param>
	/// <param name="spriteSheet">	Zestaw spritów planszy. </param>
	/// <param name="renderer">   	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Board(std::uint32_t width, std::uint32_t height, 
		std::shared_ptr<class SpriteSheet> spriteSheet, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja tworząca planszę. </summary>
	///
	/// <param name="width">	  	Szerokość planszy. </param>
	/// <param name="height">	  	Wysokość planszy. </param>
	/// <param name="spriteSheet">	Zestaw spritów planszy. </param>
	/// <param name="renderer">   	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t width, std::uint32_t height, 
		std::shared_ptr<class SpriteSheet> spriteSheet, class Renderer& renderer);
	
	/// <summary>	Destructor. </summary>
	~Board();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja rysująca planszę przy pomocy renderera. </summary>
	///
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void draw(class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja pobierająca obiekty na planszy. </summary>
	///
	/// <returns>	Tablica obiektów na planszy. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const std::vector<std::shared_ptr<class GameObject>>& getObjects() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja pobierająca obiekty z podanej pozycji. </summary>
	///
	/// <param name="pos">  	Pozycja obiektów. </param>
	/// <param name="saved">	
	///		[Opt] Prawda jeżeli pozycja jest tą zapisaną na początku klatki. 
	/// </param>
	///
	/// <returns>	Tablica obiektów na planszy. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::vector<std::shared_ptr<class GameObject>> getObjects(const glm::tvec2<std::int32_t>& pos, 
		bool saved = true);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja pobierająca obiekty na planszy otaczające daną pozycję. </summary>
	///
	/// <param name="pos">	Pozycja. </param>
	///
	/// <returns>	Tablica obiektów na planszy. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::vector<std::shared_ptr<class GameObject>> getSurroundingObjects(
		const glm::tvec2<std::int32_t>& pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja dodająca obiekt do planszy. </summary>
	///
	/// <param name="object">	Obiekt do dodania. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void addGameObject(std::shared_ptr<class GameObject>& object);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca szerokość planszy. </summary>
	///
	/// <returns>	Szerokość planszy. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getWidth() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca wysokość planszy. </summary>
	///
	/// <returns>	Wysokośc planszy. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getHeight() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja stawiająca obiekt wilka na podanej pozycji. </summary>
	///
	/// <param name="pos">	Pozycja. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void spawnWolf(glm::tvec2<std::int32_t> pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja stawiająca obiekt zająca na podanej pozycji. </summary>
	///
	/// <param name="pos">	Pozycja. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void spawnHare(glm::tvec2<std::int32_t> pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca liczniki obiektów na planszy. </summary>
	///
	/// <returns>	
	///		Tablica liczników obiektów. Kolejno: sance wilków, samice wilków,
	///		zające, głazy, krzaki. 
	/// </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const std::array<std::int32_t, 5>& getObjectCounters();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja sprawdzająca czy zmienił się stan liczników. </summary>
	///
	/// <returns>	Prawda jeżeli zmienił się stan liczników. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isCountersChanged();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizująca turę. </summary>
	///
	/// <param name="app">	Obiekt aplikacji. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateTurn(class Application& app);

private:
	/// <summary>	Szerokość planszy. </summary>
	std::uint32_t mWidth;

	/// <summary>	Wysokość planszy. </summary>
	std::uint32_t mHeight;
	
	/// <summary>	Tablica obiektów na planszy. </summary>
	std::vector<std::shared_ptr<class GameObject>> mObjects;

	/// <summary>	Stos ustawianych zająców. </summary>
	std::stack<glm::tvec2<std::int32_t>> mHareSpawnStack;

	/// <summary>	Stos ustawianych wilków. </summary>
	std::stack<glm::tvec2<std::int32_t>> mWolfSpawnStack;

	/// <summary>	Tablica liczników obiektów. </summary>
	std::array<std::int32_t, 5> mObjectCounters;

	/// <summary>	Prawda jeżeli zmieniły się wartości liczników. </summary>
	bool mIsCountersChanged;

	/// <summary>	Mapa kafelków w pamięci GPU. </summary>
	std::vector<std::shared_ptr<VertexBuffer<PositionVertexLayout>>> mTileMap;

	/// <summary>	Zestaw spriteów planszy. </summary>
	std::shared_ptr<SpriteSheet> mSpriteSheet;
};

