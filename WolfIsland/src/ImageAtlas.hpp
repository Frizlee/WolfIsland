#pragma once
#include "Prerequisites.hpp"
#include "Image.hpp"
#include <glm/vec4.hpp>


/// <summary>	Klasa reprezentująca atlas obrazków w pamięci. </summary>
class ImageAtlas : public Image
{
public:
	/// <summary>	Definicja typu reprezentującego prostokąt. </summary>
	typedef glm::tvec4<std::uint32_t> Rect;

	/// <summary>	Domyślny konstruktor. </summary>
	ImageAtlas();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony konstruktor kopiujący. </summary>
	///
	/// <param name="lhs">	Obiekt do skopiowania. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	ImageAtlas(const ImageAtlas& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor przenoszący. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	ImageAtlas(ImageAtlas &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony operator przypisania. </summary>
	///
	/// <param name="lhs">	Obiekt do przypisania. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	ImageAtlas& operator=(ImageAtlas cas) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Operator przeniesienia. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	ImageAtlas& operator=(ImageAtlas &&rhs);

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
	ImageAtlas(std::uint32_t width, std::uint32_t height, Format format,
		const std::vector<uint8_t> &bytes);

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
	ImageAtlas(std::uint32_t width, std::uint32_t height, Format format,
		std::vector<uint8_t> &&bytes);

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
	ImageAtlas(std::uint32_t width, std::uint32_t height, Format format);

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
	~ImageAtlas();

	/// <summary>	Funkcja czyszcząca obiekt atlasu do stanu z przed inicializacji. </summary>
	void clear();

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 	Umieszcza pojedyńczy obrazek wewnątrz atlasu. Dany obrazek musi mieć taki sam 
	/// 	format jak atlas.
	///  </summary>
	///
	/// <param name="img">	Obiekt obrazka. </param>
	///
	/// <returns>	Prostokąt opisujący położenie obrazka wewnątrz atlasu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	Rect insert(Image &img);

private:
	/// <summary>	Struktura opisująca węzeł służacy do bisekcji atlasu obrazków. </summary>
	struct Node
	{
		/// <summary>	Dzieci danego węzła. </summary>
		std::unique_ptr<Node> mChilds[2];
		/// <summary>	Prostokąt opisujący położenie węzła. </summary>
		Rect mRect;
		/// <summary>	Obiekt opisujący czy węzeł jest już zajęty przez obrazek. </summary>
		bool mFree;

		/// <summary>	Domyślny konstruktor. </summary>
		Node();

		///--------------------------------------------------------------------------------------------
		/// <summary>	Niedozwolony konstruktor kopiujący. </summary>
		///
		/// <param name="lhs">	Obiekt do skopiowania. </param>
		/// 
		///--------------------------------------------------------------------------------------------
		Node(const Node &lhs) = delete;

		///--------------------------------------------------------------------------------------------
		/// <summary>	Konstruktor przenoszący. </summary>
		///
		/// <param name="rhs">	Obiekt do przeniesienia. </param>
		/// 
		///--------------------------------------------------------------------------------------------
		Node(Node &&rhs);

		///--------------------------------------------------------------------------------------------
		/// <summary>	Niedozwolony operator przypisania. </summary>
		///
		/// <param name="lhs">	Obiekt do przypisania. </param>
		///
		/// <returns>	Referencja do aktualnego obiektu. </returns>
		/// 
		///--------------------------------------------------------------------------------------------
		Node& operator=(const Node &cas) = delete;

		///--------------------------------------------------------------------------------------------
		/// <summary>	Operator przeniesienia. </summary>
		///
		/// <param name="rhs">	Obiekt do przeniesienia. </param>
		///
		/// <returns>	Referencja do aktualnego obiektu. </returns>
		/// 
		///--------------------------------------------------------------------------------------------
		Node& operator=(Node &&rhs);

		///----------------------------------------------------------------------------------------
		/// <summary>	
		/// 	Przeładowany operator alokacji pamięci. Wymagany z powodu wyrównywania 
		/// 	bajtów 
		/// </summary>
		///
		/// <param name="i">	Ilość pamięci do alokacji. </param>
		/// 
		/// <returns> Wzkaźnik do zaalokowanej pamięci. </returns>
		/// 
		///----------------------------------------------------------------------------------------
		void* operator new(size_t i);

		///----------------------------------------------------------------------------------------
		/// <summary>	Dealokacja pamięci danej wskaźnikiem. </summary>
		///
		/// <param name="p">	Wskaźnik do pamięci. </param>
		/// 
		///----------------------------------------------------------------------------------------
		void operator delete(void *p);

		///----------------------------------------------------------------------------------------
		/// <summary>	Umieszczenie prostokątnego obiektu w drzewie. </summary>
		///
		/// <param name="width"> 	Szerokość. </param>
		/// <param name="height">	Wysokość. </param>
		///
		/// <returns>	Prostokąt opisujący położenie obiektu na atlasie. </returns>
		/// 
		///----------------------------------------------------------------------------------------
		Rect insert(std::uint32_t width, std::uint32_t height);
	};

	/// <summary>	Korzeń drzewa. </summary>
	std::unique_ptr<Node> mRoot;
};



