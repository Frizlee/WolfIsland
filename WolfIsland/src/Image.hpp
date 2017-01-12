#pragma once
#include "Prerequisites.hpp"
#include "Resource.hpp"


/// <summary>	Klasa reprezentująca obrazek. </summary>
class Image : public Resource
{
	friend class Texture;
	friend class ImageAtlas;

public:
	/// <summary>	Format jaki może przyjąć obrazek w pamięci. </summary>
	enum class Format
	{
		UNKNOWN = 0,

		R8,
		RG8,
		RGB8,
		RGBA8,
		R3G3B2,
		R5G6B5,
		RGBA4,
		RGB5A1,
		RGB10A2,
		
		SRGB8,
		SRGB8A8,

		// Compressed formats.
		BC1_RGB,
		BC1_RGBA,
		BC2_RGBA,
		BC3_RGBA,
		BC4_R,
		BC4_SIGNED_R,
		BC5_RG,
		BC5_SIGNED_RG,

		// Aliases.
		R = R8,
		RG = RG8,
		RGB = RGB8,
		RGBA = RGBA8,
	};	
	
	/// <summary>	Domyślny konstruktor. </summary>
	Image();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor kopiujący. </summary>
	///
	/// <param name="lhs">	Obiekt do skopiowania. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Image(const Image &lhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor przenoszący. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Image(Image &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Operator przypisania. </summary>
	///
	/// <param name="lhs">	Obiekt do przypisania. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Image& operator=(Image cas);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Operator przeniesienia. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Image& operator=(Image &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Konstruktor tworzący obrazek o podanym rozmiarze oraz kopiujący wartości danych obrazka
	///		z podanego bufora. 
	///	</summary>
	///
	/// <param name="width"> 	Szerokość obrazka. </param>
	/// <param name="height">	Wysokość obrazka. </param>
	/// <param name="format">	Format obrazka w pamięci. </param>
	/// <param name="bytes"> 	Bufor danych obrazka. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Image(std::uint32_t width, std::uint32_t height, Format format, 
		const std::vector<std::uint8_t> &bytes);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja tworząca obrazek o podanym rozmiarze oraz kopiująca wartości danych obrazka
	///		z podanego bufora. 
	///	</summary>
	///
	/// <param name="width"> 	Szerokość obrazka. </param>
	/// <param name="height">	Wysokość obrazka. </param>
	/// <param name="format">	Format obrazka w pamięci. </param>
	/// <param name="bytes"> 	Bufor danych obrazka. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t width, std::uint32_t height, Format format,
		const std::vector<std::uint8_t> &bytes);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Konstruktor tworzący obrazek o podanym rozmiarze oraz przenoszący wartości danych 
	///		obrazka	z podanego bufora. 
	///	</summary>
	///
	/// <param name="width"> 	Szerokość obrazka. </param>
	/// <param name="height">	Wysokość obrazka. </param>
	/// <param name="format">	Format obrazka w pamięci. </param>
	/// <param name="bytes"> 	Bufor danych obrazka. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Image(std::uint32_t width, std::uint32_t height, Format format,
		std::vector<std::uint8_t> &&bytes);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja tworząca obrazek o podanym rozmiarze oraz przenosząca wartości danych 
	///		obrazka	z podanego bufora. 
	///	</summary>
	///
	/// <param name="width"> 	Szerokość obrazka. </param>
	/// <param name="height">	Wysokość obrazka. </param>
	/// <param name="format">	Format obrazka w pamięci. </param>
	/// <param name="bytes"> 	Bufor danych obrazka. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t width, std::uint32_t height, Format format,
		std::vector<std::uint8_t> &&bytes);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Konstruktor tworzący czysty obrazek o podanym rozmiarze.
	///	</summary>
	///
	/// <param name="width"> 	Szerokość obrazka. </param>
	/// <param name="height">	Wysokość obrazka. </param>
	/// <param name="format">	Format obrazka w pamięci. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Image(std::uint32_t width, std::uint32_t height, Format format);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja tworząca czysty obrazek o podanym rozmiarze.
	///	</summary>
	///
	/// <param name="width"> 	Szerokość obrazka. </param>
	/// <param name="height">	Wysokość obrazka. </param>
	/// <param name="format">	Format obrazka w pamięci. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::uint32_t width, std::uint32_t height, Format format);
	
	/// <summary>	Domyślny destruktor. </summary>
	virtual ~Image();

	/// <summary>	Funkcja czyszcząca obiekt obrazka do stanu z przed inicializacji. </summary>
	void clear() override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca format obrazka. </summary>
	///
	/// <returns>	Format obrazka. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Format getFormat() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca szerokość obrazka. </summary>
	///
	/// <returns>	Szerokość obrazka. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getWidth() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca wysokość obrazka. </summary>
	///
	/// <returns>	Wysokość obrazka. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getHeight() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja pytająca czy obiekt obrazka jest skompresowany. </summary>
	///
	/// <returns>	Prawda jeżeli obiekt jest skompresowany, fałsz w przeciwnym wypadku. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isCompressed() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 	Zwraca ilość bajtów na pixel lub jeżeli obiekt jest skompresowany rozmiar bloku (blok 
	/// 	odnosi się do metody kompresji). 
	/// </summary>
	///
	/// <returns>	Ilość bajtów na pixel albo rozmiar bloku. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint8_t getBytesPerPixel() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 	Funkcja obliczająca ilość bajtów na pixel lub wielkość bloku (jeżeli obiekt 
	/// 	skompresowany) z podanego formatu obrazka. 
	/// </summary>
	///
	/// <param name="format">	Format obrazka. </param>
	///
	/// <returns>	Ilość bajtów na pixel albo rozmiar bloku. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static std::uint8_t CalculateBytesPerPixel(Format format);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Ustawia wartość jednego pixela w pamięci o podanych koordynatach.
	/// 	Muszą one być z zakresu: x - [0, mWidth], y - [0, mHeight]. 
	/// </summary>
	///
	/// <param name="x">		Koordynat x pixela. </param>
	/// <param name="y">		Koordynat y pixela. </param>
	/// <param name="bytes">	Dane pixela w odpowiednim formacie. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPixel(std::uint32_t x, std::uint32_t y, const std::vector<std::uint8_t> &bytes);

	/// <summary>	Funkcja odwracająca obrazek w pionie. </summary>
	void flipVerticaly();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar danych obrazka w pamięci. </summary>
	///
	/// <returns>	Rozmiar w bajtach. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getSize() const override;

protected:
	/// <summary>	Dane obrazka w pamięci. </summary>
	std::vector<std::uint8_t> mBytes;

private:
	/// <summary>	Szerokość obrazka. </summary>
	std::uint32_t mWidth;
	/// <summary>	Wysokość obrazka. </summary>
	std::uint32_t mHeight;
	/// <summary>	Format obrazka. </summary>
	Format mFormat;
};

