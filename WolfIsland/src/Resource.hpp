#pragma once
#include "Prerequisites.hpp"

/// <summary>	Klasa abstrakcyjna reprezentująca zasób w pamięci. </summary>
class Resource
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	Resource();
	
	/// <summary>	Domyślny destruktor. </summary>
	virtual ~Resource() = 0;

	/// <summary>	Czyści obiekt do stanu z przed inicializacji. </summary>
	virtual void clear() = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar obiektu w pamięci. </summary>
	///
	/// <returns>	Rozmiar obiektu w bajtach. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual std::uint32_t getSize() const = 0;
};

