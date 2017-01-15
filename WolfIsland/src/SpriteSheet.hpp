#pragma once
#include "Prerequisites.hpp"
#include <glm/vec2.hpp>

/// <summary>	Klasa reprezentująca zestaw spriteów. </summary>
class SpriteSheet
{
	friend class Renderer;

public:
	/// <summary>	Domyślny konstruktor. </summary>
	SpriteSheet();

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Konstruktor tworzący zestaw z podanej tablicy spriteów. Wszystkie muszą posiadać 
	///		tę samą przypisaną teksturę
	/// </summary>
	///
	/// <param name="sprites">	Tablica spriteów. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	SpriteSheet(const std::vector<std::shared_ptr<class Sprite>>& sprites);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja tworząca zestaw z podanej tablicy spriteów.Wszystkie muszą posiadać 
	///		tę samą przypisaną teksturę
	/// </summary>
	///
	/// <param name="sprites">	Tablica spriteów. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(const std::vector<std::shared_ptr<class Sprite>>& sprites);
	
	/// <summary>	Domyślny destruktor. </summary>
	~SpriteSheet();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja dodająca sprite do zestawu. </summary>
	///
	/// <param name="sprite">	Sprite do dodania. </param>
	///
	/// <returns>	Index dodanego sprite. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t addSprite(std::shared_ptr<class Sprite> sprite);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca teksturę przypisaną do zestawu. </summary>
	///
	/// <returns>	Wskaźnik na teksturę. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class Texture> getTexture() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca obiekt sprite znajdujący się w zestawie. </summary>
	///
	/// <param name="index">	Index sprite. </param>
	///
	/// <returns>	Wskaźnik na Sprite. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class Sprite> getSprite(std::uint32_t index) const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja zwracająca przypisaną tablicę stanów OpenGL. (postać niemodyfikowalna)
	/// </summary>
	///
	/// <returns>	Przypisana tablica stanów OpenGL. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class VertexArray> getVao() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja zwracająca przypisaną tablicę stanów OpenGL.
	/// </summary>
	///
	/// <returns>	Przypisana tablica stanów OpenGL. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<class VertexArray> getVao();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar prostokąta w który jest wpisany sprite. </summary>
	///
	/// <returns>	Rozmiar prostokąta. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::vec2& getBounds();

private:
	/// <summary>	Tablica spriteów. </summary>
	std::vector<std::shared_ptr<class Sprite>> mSprites;
};

