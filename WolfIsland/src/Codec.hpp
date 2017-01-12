#pragma once
#include "Prerequisites.hpp"

/// <summary>	
///		Tymczasowa skruktura służąca do kożystania z standardowych strumieni w odniesieniu 
/// 	do bufora znajdującego się w pamięci. 
/// </summary>
struct memorybuf : std::streambuf
{
	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor </summary>
	///
	/// <param name="base">	Wskaźnik do pamięci. </param>
	/// <param name="size">	Rozmiar danych. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	memorybuf(char *base, std::ptrdiff_t size)
	{
		setg(base, base, base + size);
	}
};


/// <summary>	Klasa bazowa reprezentująca reguły kodowania i dekodowania zasobów. </summary>
class Codec
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	Codec();

	/// <summary>	Domyślny destruktor virtualny. Czyni klasę w pełni abstrakcyjną </summary>
	virtual ~Codec() = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja dekodująca zasób z podanego strumienia wejścia. </summary>
	///
	/// <param name="input">	Strumień wejścia. </param>
	/// <param name="res">  	[out] Zdekodowany zasób. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void decode(std::istream &input, class Resource &res) = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja kodująca zasób do podanego strumienia wyjścia. </summary>
	///
	/// <param name="output">	[out] Strumień wyjścia. </param>
	/// <param name="res">   	Zasób. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void encode(std::ostream &output, class Resource &res) = 0;

private:

};



