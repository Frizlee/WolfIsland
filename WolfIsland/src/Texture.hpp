#pragma once
#include "Prerequisites.hpp"
#include "Image.hpp"
#include "GpuResource.hpp"

/// <summary>	Klasa reprezentująca teksturę w pamięci karty graficznej </summary>
class Texture : public GpuResource
{
public:
	/// <summary>	Wartości reprezentujące typ tekstury. </summary>
	enum class Type
	{
		UNCOMPRESSED_2D,
		COMPRESSED_2D,
		UNCOMPRESSED_2D_ARRAY,
		COMPRESSED_2D_ARRAY
	};

	/// <summary>	Domyślny konstruktor. </summary>
	Texture();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony konstruktor kopiujący. </summary>
	///
	/// <param name="lhs">	Obiekt do skopiowania. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Texture(const Texture& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor przenoszący. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Texture(Texture&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony operator przypisania. </summary>
	///
	/// <param name="lhs">	Obiekt do przypisania </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Texture& operator=(const Texture& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Operator przeniesienia </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Texture& operator=(Texture&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor tworzący teksturę z gotowego obrazka. </summary>
	///
	/// <param name="img">	   	Obrazek do przypisania do tekstury. </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Texture(const Image& img, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja tworząca teksturę z gotowego obrazka. </summary>
	///
	/// <param name="img">	   	Obrazek do przypisania do tekstury. </param>
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(const Image& img, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 	Konstruktor tworzący tablicę tekstur z gotowych obrazków. Muszą one byæ
	/// 	tego samego rozmiaru i typu. 
	/// </summary>
	///
	/// <param name="imgs">	   	Tablica obrazków. </param>
	/// <param name="renderer">	Obiekt renderera </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Texture(std::vector<Image>& imgs, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>
	/// 	Funkcja tworząca tablicę tekstur z gotowych obrazków. Muszą one byæ
	/// 	tego samego rozmiaru i typu.
	/// </summary>
	///
	/// <param name="imgs">	   	Tablica obrazków. </param>
	/// <param name="renderer">	Obiekt renderera </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::vector<Image>& imgs, Renderer& renderer);
	
	/// <summary>	Destruktor. Woła funkcję clear(). </summary>
	~Texture();

	/// <summary>	Czyści obiekt tekstury do stanu z przed inicializacji. </summary>
	void clear() override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja generująca mipmapy tekstury. </summary>
	///
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void generateMipmaps(class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja zwracająca format tekstury. Format rozróżnialny jest przez sposób reprezentacji
	///		kolorów w pamięci. 
	///	</summary>
	///
	/// <returns>	Format tekstury. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Image::Format getFormat() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja pytająca czy dana tekstura posiada wygenerowane mipmapy. </summary>
	///
	/// <returns>	Prawda jeśli posiada mipmapy, fałsz jeśli nie posiada. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool hasMipmap() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 	Zwraca typ tekstury. Typ rozróżnialny jest przez sposób kompresji, ilośæ 
	/// 	wymiarów oraz czy tekstura jest typu tablicowego czy też nie.
	/// </summary>
	///
	/// <returns>	Typ tekstury. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Type getType() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 	Funkcja pytająca o rozmiar obiektu tekstury w bajtach przechowywanych w pamięci karty 
	/// 	graficznej.
	/// </summary>
	///
	/// <returns>	Rozmiar obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::uint32_t getSize() const override;

private:
	/// <summary>	Określa format tekstury. </summary>
	Image::Format mFormat;
	/// <summary>	Określa typ tekstury. </summary>
	Type mType;
	/// <summary>	Przechowuje rozmiar tekstury w pamięci karty graficznej. </summary>
	std::uint32_t mSize;
	/// <summary>	Prawda jeśli tekstura posiada mipmapy, fałsz jeśli nie posiada. </summary>
	bool mHasMipmap;

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 			Funkcja analizująca format obrazku i zwracająca format rozumiany przez OpenGL. 
	/// </summary>
	///
	/// <param name="imgFormat">			   	Format obrazka </param>
	/// <param name="format">				   	[out] Format poszczególnych pixeli. </param>
	/// <param name="internalFormat">		   	[out] Format przechowywanych danych. </param>
	/// <param name="dataType">				   	[out] Typ przechowywanych danych. </param>
	/// <param name="compressedInternalFormat">	
	/// 	[out] Format kompresji. 0 jeśli format jest nieskompresowany. 
	/// </param>
	/// 
	///--------------------------------------------------------------------------------------------
	static void ParseFormat(Image::Format imgFormat, GLint &format, 
		GLint &internalFormat, GLenum &dataType, GLenum &compressedInternalFormat);
};

