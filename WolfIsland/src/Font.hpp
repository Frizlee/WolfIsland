#pragma once
#include "Prerequisites.hpp"
#include "Resource.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "VertexLayout.hpp"
#include <glm/vec2.hpp>

/// <summary>	Klasa wyjątku inicjalizacji obiektu Czcionki. </summary>
class FontInitializationException : public std::exception
{
	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca informację o błędzie. </summary>
	///
	/// <returns>	Informacja o błędzie. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual const char* what() const noexcept
	{
		return "Initialization of the Font object failed.";
	}
};

/// <summary>	Klasa reprezentująca czcionkę jako atlas obrazków. </summary>
class Font : public Resource
{
	friend class Text;

public:
	/// <summary>	Domyślny konstruktor. </summary>
	Font();

	///--------------------------------------------------------------------------------------------
	/// <summary>
	/// 	Konstruktor tworzący atlas obrazków zawierające podstawowe glify czcionki znajdującej 
	/// 	się	w podanej lokalizacji.
	/// </summary>
	///
	/// <param name="facePath">	Scieżka do pliku .ttf zawierającego informację o czciące. </param>
	/// <param name="size">	   	Rozmiar czcionki. </param>
	/// <param name="atlas">   	
	/// 	[in,out] Obiekt atlasu obrazków w którym zostaną przechowane 
	/// 	obrazki glifów. 
	/// </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	/// <param name="spacing"> 	[opt] Odstęp pomiędzy wierszami. Domyślnie 1.5 wiersza. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Font(const std::string& facePath, std::uint8_t size, 
		std::shared_ptr<class ImageAtlas>& atlas, class Renderer& renderer, float spacing = 1.5f);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 	Funkcja tworzą atlas obrazków zawierający podstawowe glify czcionki znajdującej się 
	/// 	w podanej lokalizacji. 
	/// </summary>
	///
	/// <param name="facePath">	Scieżka do pliku .ttf zawierającego informację o czciące. </param>
	/// <param name="size">	   	Rozmiar czcionki. </param>
	/// <param name="atlas">   	
	/// 	[in,out] Obiekt atlasu obrazków w którym zostaną przechowane 
	/// 	obrazki glifów. 
	/// </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	/// <param name="spacing"> 	[opt] Odstęp pomiędzy wierszami. Domyślnie 1.5 wiersza. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(const std::string& facePath, std::uint8_t size, 
		std::shared_ptr<class ImageAtlas> atlas, class Renderer& renderer, float spacing = 1.5f);

	/// <summary>	Destruktor. </summary>
	~Font();

	/// <summary>	Czyści obiekt czcionki do stanu z przed inicializacji. </summary>
	void clear() override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracając atlas obrazków glifów czcionki. </summary>
	///
	/// <returns>	Wskaźnik na atlas. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class ImageAtlas> getAtlas() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar obiektu czcionki w bajtach. </summary>
	///
	/// <returns>	Rozmiar obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getSize() const override;

private:
	/// <summary>	Struktura reprezentująca wymiary glifu. </summary>
	struct GlyphInfo
	{
		float ax, ay;
		float bw, bh;
		float bl, bt;
		uint32_t tx, ty;
	};

	/// <summary>	Obiekt wymagany prze bibliotekę FreeType. </summary>
	FT_Library FTLib; 
	/// <summary>	Obiekt reprezentujący aktualny krój czcionki. </summary>
	FT_Face mFace;
	/// <summary>	Wskaźnik na atlas obrazków glifów. </summary>
	std::shared_ptr<ImageAtlas> mAtlas;
	/// <summary>	Wskaźnik do tekstury utworzonej z atlasu glifów. </summary>
	std::shared_ptr<class Texture> mTexture;
	/// <summary>	Obiekt przechowujący wiadomośc o konieczności aktualizacji tekstury. </summary>
	bool mIsTextureChanged;

	/// <summary>	Rozmiar obiektu. </summary>
	std::uint8_t mSize;
	/// <summary>	Szerokośc tabulatora. </summary>
	std::uint32_t mTabWidth;
	/// <summary>	Odległość od linijki do górnego krańca glifów. </summary>
	std::int32_t mAscender;
	/// <summary>	Odległość od linijki do dolnego krańca glifów. </summary>
	std::int32_t mDescender;
	/// <summary>	Wysokość glifu. </summary>
	std::uint16_t mHeight;
	/// <summary>	Odstęp pomiędzy wierszami (w wierszach). </summary>
	float mSpacing;

	/// <summary>	Mapa wczytanych znaków. </summary>
	std::unordered_map<std::uint32_t, GlyphInfo> mChars;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja wczytująca glif znaku z czcionki. </summary>
	///
	/// <param name="charCode">	kod znaku w formacie utf32. </param>
	///
	/// <returns>	
	/// 	Prawda jeśli znaleziono znak i go wczytano, fałsz w przeciwnym wypadku. 
	/// </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool cacheChar(std::uint32_t charCode);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja wstawiająca znak o danym kodzie do buffora. </summary>
	///
	/// <param name="charCode">	Kod znaku w formacie utf32. </param>
	/// <param name="buffer">  	[in,out] Buffor wierzchołków. </param>
	/// <param name="penPos">  	Pozycja pisaka. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void putChar(std::uint32_t charCode, std::vector<TextVertexLayout::Data>& buffer, 
		glm::vec2 &penPos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca teksturę utworzoną z atlasu glifów. </summary>
	///
	/// <param name="renderer">	Obiekt renderera. </param>
	///
	/// <returns>	Wskaźnik na teksturę. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<class Texture> getTexture(class Renderer& renderer);
};



