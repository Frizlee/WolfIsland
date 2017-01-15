#pragma once
#include "Prerequisites.hpp"
#include "VertexLayout.hpp"
#include <glm/vec4.hpp>

/// <summary>	
///		Klasa reprezentująca tekst. Jest to jeden z primitywnych obiektów do rysowania.
///		Przedstawia zestaw płaskich prostokątów z nałożoną teksturą reprezentującą znaki.
/// </summary>
class Text
{
	friend class Renderer;

public:
	/// <summary>	Domyślny konstruktor. </summary>
	Text();

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Konstruktor tworzący tekst z podanego ciągu znaków. Utworzone prostokąty 
	///		przechowane będą w buforze wierzchołków podanej tablicy stanów OpenGL.
	/// </summary>
	///
	/// <param name="content">	  	Ciąg znaków. </param>
	/// <param name="fnt">		  	Obiekt czcionki. </param>
	/// <param name="vao">		  	Obiekt tablicy stanów OpenGL. </param>
	/// <param name="vboPosition">	Pozycja w buforze wierzchołków na GPU. </param>
	/// <param name="renderer">   	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Text(const std::string& content, std::shared_ptr<class Font> fnt, 
		std::shared_ptr<class VertexArray>& vao, std::uint32_t vboPosition, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja tworząca tekst z podanego ciągu znaków. Utworzone prostokąty 
	///		przechowane będą w buforze wierzchołków podanej tablicy stanów OpenGL.
	/// </summary>
	///
	/// <param name="content">	  	Ciąg znaków. </param>
	/// <param name="fnt">		  	Obiekt czcionki. </param>
	/// <param name="vao">		  	Obiekt tablicy stanów OpenGL. </param>
	/// <param name="vboPosition">	Pozycja w buforze wierzchołków na GPU. </param>
	/// <param name="renderer">   	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(const std::string& content, std::shared_ptr<class Font> fnt,
		std::shared_ptr<class VertexArray>& vao, std::uint32_t vboPosition, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizująca zapisane znaki. </summary>
	///
	/// <param name="content"> 	Ciąg znaków. </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateContent(const std::string& content, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca kolor tekstu. </summary>
	///
	/// <param name="color">	Kolor tekstu. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setColor(const glm::vec4& color);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca kolor tekstu. </summary>
	///
	/// <returns>	TKolor tekstu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::vec4& getColor() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca przypisaną teksturę. </summary>
	///
	/// <returns>	Wskaźnik na teksturę. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class Texture> getTexture() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca bufor wierzchołków tekstu w pamięci CPU. </summary>
	///
	/// <returns>	Bufor wierzchołków. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const std::vector<TextVertexLayout::Data>& getBuffer() const;

private:
	/// <summary>	Bufor wierzchołków w pamięci CPU. </summary>
	std::vector<TextVertexLayout::Data> mBuffer;

	/// <summary>	Kolor tekstu. </summary>
	glm::vec4 mColor;

	/// <summary>	Tablica stanów OpenGL. </summary>
	std::shared_ptr<class VertexArray> mVao;

	/// <summary>	Pozycja w buforze wierzchołków w pamięci GPU. </summary>
	std::uint32_t mVboPosition;

	/// <summary>	Wskaźnik na teksturę. </summary>
	std::shared_ptr<class Texture> mTexture;

	/// <summary>	Wskaźnik na czcionkę. </summary>
	std::shared_ptr<class Font> mFont;
};



