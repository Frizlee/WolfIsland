#pragma once
#include "Prerequisites.hpp"
#include "gl_core_3_3.hpp"

/// <summary>	
///		Struktura reprezentująca format jednego atrybutu wierzchołka w pamięci GPU. 
/// </summary>
struct VertexFormat
{
	/// <summary>	Prawda jeżeli atrybut jest pusty. </summary>
	bool empty;

	/// <summary>	Ilość komponentów danego typu. </summary>
	GLint size;

	/// <summary>	Typ danych komponentu. </summary>
	GLenum type;

	/// <summary>	Prawda jeżeli dane powinny zostać znormalizowane. </summary>
	GLboolean normalized;

	/// <summary>	Offset pomiędzy kolejnymi atrybutami tego typu. </summary>
	GLsizei stride;

	/// <summary>	Położenie atrybutu. </summary>
	std::uint32_t pointer;

	/// <summary>	Domyślny destruktor. </summary>
	VertexFormat();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor tworzący format. </summary>
	///
	/// <param name="size">		 	Ilość komponentów danego typu. </param>
	/// <param name="type">		 	Typ danych komponentu. </param>
	/// <param name="normalized">	Prawda jeżeli dane powinny zostać znormalizowane. </param>
	/// <param name="stride">	 	Offset pomiędzy kolejnymi atrybutami tego typu. </param>
	/// <param name="pointer">   	Położenie atrybutu. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	VertexFormat(GLint size, GLenum type, GLboolean normalized, GLsizei stride, 
		std::uint32_t pointer);
};

/// <summary>	Klasa abstrakcyjna reprezentująca format wierzchołków w pamięci. </summary>
class VertexLayout
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	VertexLayout();

	/// <summary>	Domyślny dekstruktor. </summary>
	virtual ~VertexLayout() = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca formaty kolejnych atrybutów wierzchołka. </summary>
	///
	/// <returns>	Tablica atrybutów wierzchołków. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const std::vector<VertexFormat>& getFormats();

protected:
	/// <summary>	Tablica atrybutów wierzchołków.. </summary>
	std::vector<VertexFormat> mFormats;
};

/// <summary>	Format wierzchołków używany przy rysowaniu tekstu. </summary>
class TextVertexLayout : public VertexLayout
{
public:
	/// <summary>	Struktura reprezentująca dane wierzchołka. </summary>
	struct Data
	{
		/// <summary>	Współżędna x. </summary>
		float x;

		/// <summary>	Współżędna y. </summary>
		float y;

		/// <summary>	Współżędna tekstury u. </summary>
		float u; 

		/// <summary>	Współżędna tekstury v. </summary>
		float v;

		/// <summary>	Domyślny konstruktor. </summary>
		Data();

		///----------------------------------------------------------------------------------------
		/// <summary>	Konstruktor tworzący wierzchołek. </summary>
		///
		/// <param name="x">	Współżędna x. </param>
		/// <param name="y">	Współżędna y. </param>
		/// <param name="u">	Współżędna tekstury u. </param>
		/// <param name="v">	Współżędna tekstury y. </param>
		/// 
		///----------------------------------------------------------------------------------------
		Data(float x, float y, float u, float v);
	};
	
	/// <summary>	Domyślny konstruktor. </summary>
	TextVertexLayout();

	/// <summary>	Domyślny destruktor. </summary>
	~TextVertexLayout();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar wierzchołka. </summary>
	///
	/// <returns>	Rozmiar wierzchołka w bajtach. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static std::uint32_t Size();
};

/// <summary>	Format wierzchołków używany przy rysowaniu obiektu z teksturą. </summary>
class TextureVertexLayout : public VertexLayout
{
public:
	/// <summary>	Struktura reprezentująca dane wierzchołka. </summary>
	struct Data
	{
		/// <summary>	Współżędna x. </summary>
		float x;

		/// <summary>	Współżędna y. </summary>
		float y;

		/// <summary>	Współżędna z. </summary>
		float z;

		/// <summary>	Współżędna tekstury u. </summary>
		float u;

		/// <summary>	Współżędna tekstury v. </summary>
		float v;

		/// <summary>	Domyślny konstruktor. </summary>
		Data();

		///----------------------------------------------------------------------------------------
		/// <summary>	Konstruktor tworzący wierzchołek. </summary>
		///
		/// <param name="x">	Współżędna x. </param>
		/// <param name="y">	Współżędna y. </param>
		/// <param name="z">	Współżędna z. </param>
		/// <param name="u">	Współżędna tekstury u. </param>
		/// <param name="v">	Współżędna tekstury y. </param>
		/// 
		///----------------------------------------------------------------------------------------
		Data(float x, float y, float z, float u, float v);
	};

	/// <summary>	Domyślny konstruktor. </summary>
	TextureVertexLayout();
	/// <summary>	Domyślny destruktor. </summary>
	~TextureVertexLayout();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar wierzchołka. </summary>
	///
	/// <returns>	Rozmiar wierzchołka w bajtach. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static std::uint32_t Size();
};

/// <summary>	Format wierzchołków używany przy rysowaniu obiektu z kolorem. </summary>
class ColorVertexLayout : public VertexLayout
{
public:
	/// <summary>	Struktura reprezentująca dane wierzchołka. </summary>
	struct Data
	{
		/// <summary>	Współżędna x. </summary>
		float x;

		/// <summary>	Współżędna y. </summary>
		float y;

		/// <summary>	Współżędna z. </summary>
		float z;

		/// <summary>	Kolor wierzchołka. </summary>
		std::uint32_t color;

		/// <summary>	Domyślny konstruktor. </summary>
		Data();

		///----------------------------------------------------------------------------------------
		/// <summary>	Konstruktor tworzący wierzchołek. </summary>
		///
		/// <param name="x">		Współżędna x. </param>
		/// <param name="y">		Współżędna y. </param>
		/// <param name="z">		Współżędna z. </param>
		/// <param name="color">	Kolor wierzchołka. </param>
		/// 
		///----------------------------------------------------------------------------------------
		Data(float x, float y, float z, std::uint32_t color);
	};

	/// <summary>	Domyślny konstruktor. </summary>
	ColorVertexLayout();
	/// <summary>	Domyślny destruktor. </summary>
	~ColorVertexLayout();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar wierzchołka. </summary>
	///
	/// <returns>	Rozmiar wierzchołka w bajtach. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static std::uint32_t Size();
};

/// <summary>	Format wierzchołków używany przy rysowaniu samej pozycji. </summary>
class PositionVertexLayout : public VertexLayout
{
public:
	/// <summary>	Struktura reprezentująca dane wierzchołka. </summary>
	struct Data
	{
		/// <summary>	Współżędna x. </summary>
		float x;

		/// <summary>	Współżędna y. </summary>
		float y;

		/// <summary>	Współżędna z. </summary>
		float z;

		/// <summary>	Domyślny konstruktor. </summary>
		Data();

		///----------------------------------------------------------------------------------------
		/// <summary>	Konstruktor tworzący wierzchołek. </summary>
		///
		/// <param name="x">	Współżędna x. </param>
		/// <param name="y">	Współżędna y. </param>
		/// <param name="z">	Współżędna z. </param>
		/// 
		///----------------------------------------------------------------------------------------
		Data(float x, float y, float z);
	};

	/// <summary>	Domyślny konstruktor. </summary>
	PositionVertexLayout();
	/// <summary>	Domyślny destruktor. </summary>
	~PositionVertexLayout();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar wierzchołka. </summary>
	///
	/// <returns>	Rozmiar wierzchołka w bajtach. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static std::uint32_t Size();
};

