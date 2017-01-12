#pragma once
#include "Codec.hpp"
#include <png.h>

/// <summary>	Klasa reprezentująca kodek plików PNG. </summary>
class PngCodec : public Codec
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	PngCodec();

	/// <summary>	Domyślny destruktor. </summary>
	~PngCodec();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja dekodująca plik PNG z podanego strumienia wejścia. </summary>
	///
	/// <param name="input">	Strumień wejścia. </param>
	/// <param name="res">  	[out] Zdekodowany zasób. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void decode(std::istream &input, Resource &res);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja kodująca plik PNG do podanego strumienia wyjścia. </summary>
	///
	/// <param name="output">	[out] Strumień wyjścia. </param>
	/// <param name="res">   	Zasób. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void encode(std::ostream &output, Resource &res);
	
private:

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja typu callback. Specyficzna dla biblioteko libPng. </summary>
	///
	/// <param name="pngPtr">		  	PNG pointer. </param>
	/// <param name="outBytes">		  	[out] Wskaźnik na wyjściowe bajty. </param>
	/// <param name="byteCountToRead">	Ilość bajtów do przeczytania. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	static void PngReadCallback(png_structp pngPtr, png_bytep outBytes, png_size_t byteCountToRead);
};



