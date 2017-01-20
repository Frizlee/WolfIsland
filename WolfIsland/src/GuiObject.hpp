#pragma once
#include "Prerequisites.hpp"
#include <glm/mat4x4.hpp>
#include "gl_core_3_3.hpp"

/// <summary>	Klasa abstrakcyjna reprezentująca element interfejsu użytkownika. </summary>
class GuiObject
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	GuiObject();

	/// <summary>	Domyślny destruktor. </summary>
	virtual ~GuiObject() = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja rysująca element przy pomocy renderera. </summary>
	///
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void draw(class Renderer& renderer) const = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja obsługująca wejście do elementu. </summary>
	///
	/// <param name="orthoMatrix">	
	///		Macierz ortagonalna przedstawiająca skalę i położenię 
	///		interfejsu urzytkownika. 
	/// </param>
	/// <param name="app">		  	Obiekt aplikacji. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void grabInput(const glm::mat4& orthoMatrix, class Application& app) = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizująca stan elementu. </summary>
	///
	/// <param name="deltaTime">	Czas pomiędzy kolejnymi krokami pętli stałokrokowej. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void update(double deltaTime) = 0;

protected:
};

