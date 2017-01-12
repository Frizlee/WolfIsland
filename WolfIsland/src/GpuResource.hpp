#pragma once
#include "Prerequisites.hpp"
#include "gl_core_3_3.hpp"
#include "Resource.hpp"

/// <summary>	
/// 	Klasa abstrakcyjna reprezentująca zasób przechowywany w pamięci karty graficznej. 
/// </summary>
class GpuResource : public Resource
{
	friend class Renderer;

public:	
	/// <summary>	Domyślny konstruktor. </summary>
	GpuResource();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony konstruktor kopiujący. </summary>
	///
	/// <param name="lhs">	Obiekt do skopiowania. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuResource(const GpuResource& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor przenoszący. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuResource(GpuResource&& rhs);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Niedozwolony operator przypisania. </summary>
	///
	/// <param name="lhs">	Obiekt do przypisania. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuResource& operator=(const GpuResource& lhs) = delete;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Operator przeniesienia. </summary>
	///
	/// <param name="rhs">	Obiekt do przeniesienia. </param>
	///
	/// <returns>	Referencja do aktualnego obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	GpuResource& operator=(GpuResource&& rhs);

	/// <summary>	Domyślny destruktor. </summary>
	virtual ~GpuResource() = 0;

protected:
	/// <summary>	Identyfikator OpenGL zasobu. </summary>
	GLuint mID;

private:

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca identyfikator obiektu. </summary>
	///
	/// <returns>	Identyfikator OpenGL. </returns>
	///--------------------------------------------------------------------------------------------
	GLuint getID() const;
};

