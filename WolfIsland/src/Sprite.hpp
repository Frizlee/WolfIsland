#pragma once
#include "Prerequisites.hpp"
#include "VertexLayout.hpp"
#include <glm/vec2.hpp>

/// <summary>	
///		Klasa reprezentująca sprite. Jest to jeden z primitywnych obiektów do rysowania. 
///		Przedstawia płaski wielokąt z nałożoną teksturą.
/// </summary>
class Sprite
{
	friend class Renderer;

public:
	/// <summary>	Domyślny konstruktor. </summary>
	Sprite();

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Konstruktor tworzący obiekt sprite w buforze wierzchołków podanej tablicy 
	///		stanów OpenGL. 
	///	</summary>
	///
	/// <param name="topRight">  	
	///		Wektor o punkcie zaczepienia (0, 0) i końcowi w prawym górnym rogu prostokąta 
	///		reprezentowanego przez obiekt sprite. 
	/// </param>
	/// <param name="uvDownLeft">	Lewy dolny róg koordynatów tekstury. </param>
	/// <param name="uvTopRight">	Prawy górny róg koordynatów tekstury. </param>
	/// <param name="z">		 	Koordynat z przypisany do każdego wierzchołka. </param>
	/// <param name="tex">		 	Obiekt tekstury. </param>
	/// <param name="vao">		 	Tablica stanów OpenGL. </param>
	/// <param name="renderer">  	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Sprite(const glm::vec2& topRight, const glm::vec2& uvDownLeft,
		const glm::vec2& uvTopRight, float z, std::shared_ptr<class Texture>& tex,
		std::shared_ptr<class VertexArray>& vao, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja tworząca obiekt sprite w buforze wierzchołków podanej tablicy 
	///		stanów OpenGL. 
	///	</summary>
	///
	/// <param name="topRight">  	
	///		Wektor o punkcie zaczepienia (0, 0) i końcowi w prawym górnym rogu prostokąta 
	///		reprezentowanego przez obiekt sprite. 
	/// </param>
	/// <param name="uvDownLeft">	Lewy dolny róg koordynatów tekstury. </param>
	/// <param name="uvTopRight">	Prawy górny róg koordynatów tekstury. </param>
	/// <param name="z">		 	Koordynat z przypisany do każdego wierzchołka. </param>
	/// <param name="tex">		 	Obiekt tekstury. </param>
	/// <param name="vao">		 	Tablica stanów OpenGL. </param>
	/// <param name="renderer">  	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(const glm::vec2& topRight, const glm::vec2& uvDownLeft, 
		const glm::vec2& uvTopRight, float z, std::shared_ptr<class Texture>& tex,
		std::shared_ptr<class VertexArray>& vao, class Renderer& renderer);
	
	
	/// <summary>	Domyslny destruktor. </summary>
	~Sprite();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca przypisaną teksturę. </summary>
	///
	/// <returns>	Przypisana tekstura. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class Texture> getTexture() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca bufor wierzchołków sprite w pamięci CPU. </summary>
	///
	/// <returns>	Bufor wierzchołków. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const std::vector<TextureVertexLayout::Data>& getBuffer() const;

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
	const glm::vec2& getBounds() const;

private:
	/// <summary>	Obiekt bufora wierzchołków na CPU. </summary>
	std::vector<TextureVertexLayout::Data> mBuffer;

	/// <summary>	Wskaźnik na tablicę stanów OpenGL. </summary>
	std::shared_ptr<class VertexArray> mVao;

	/// <summary>	Pozycja w buforze wierzchołków na GPU. </summary>
	std::uint32_t mVboPosition;

	/// <summary>	Wskaźnik na obiekt tekstury. </summary>
	std::shared_ptr<class Texture> mTexture;

	/// <summary>	Rozmiar prostokąta w który jest wpisany sprite. </summary>
	glm::vec2 mBounds;
};

