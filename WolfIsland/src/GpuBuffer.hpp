#pragma once
#include "Prerequisites.hpp"
#include "GpuResource.hpp"

/// <summary>	Wartości reprezentujące typ bufora. </summary>
enum class GpuBufferType
{
	VERTEX_BUFFER,
	COPY_WRITE_BUFFER,
	COPY_READ_BUFFER
};

/// <summary>	
/// 	Klasa abstrakcyjna obiektu bufora umieszczonego w pamięci karty graficznej.
/// </summary>
class GpuBuffer : public GpuResource
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	GpuBuffer() = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor zapisujący typ bufora. </summary>
	///
	/// <param name="type">	Typ bufora. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuBuffer(GpuBufferType type);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony konstruktor kopiujący. </summary>
	///
	/// <param name="lhs">	Obiekt do skopiowania. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuBuffer(const GpuBuffer &lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor przenoszący. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuBuffer(GpuBuffer &&rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony operator przypisania. </summary>
	///
	/// <param name="lhs">	Obiekt do przypisania. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuBuffer& operator=(const GpuBuffer &lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Operator przeniesienia. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuBuffer& operator=(GpuBuffer &&rhs);

	/// <summary>	Domyślny destruktor. </summary>
	virtual ~GpuBuffer() = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rozmiar jednej encji danych zapisanych w buforze. </summary>
	///
	/// <returns>	Rozmiar encji. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual std::uint32_t getEntitySize() const = 0;;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca typ bufora. </summary>
	///
	/// <returns>	Typ bufora. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuBufferType getType() const;

private:
	/// <summary>	Typ bufora. </summary>
	GpuBufferType mType;
	
};

