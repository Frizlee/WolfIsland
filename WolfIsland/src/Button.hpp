#pragma once
#include "GuiObject.hpp"
#include <glm/vec2.hpp>

/// <summary>	
///		Klasa przyciku - elementu interfejsu użytkownika rysowanego za pomocą OpenGL. 
/// </summary>
class Button :	public GuiObject
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	Button();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor tworzący przycisk z podanych spriteów. </summary>
	///
	/// <param name="guiSpriteSheet">	 	Zbiór spriteów interfejsu użytkownika. </param>
	/// <param name="spriteIndex">		 	Indeks nie wciśniętego sprite. </param>
	/// <param name="pressedSpriteIndex">	Indeks wciśniętego sprite. </param>
	/// <param name="pos">				 	Pozycja przycisku. </param>
	/// <param name="renderer">			 	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Button(std::shared_ptr<class SpriteSheet> guiSpriteSheet, std::int32_t spriteIndex,
		std::int32_t pressedSpriteIndex, const glm::vec2& pos, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja tworząc przycisk z podanych spriteów. </summary>
	///
	/// <param name="guiSpriteSheet">	 	Zbiór spriteów interfejsu użytkownika. </param>
	/// <param name="spriteIndex">		 	Indeks nie wciśniętego sprite. </param>
	/// <param name="pressedSpriteIndex">	Indeks wciśniętego sprite. </param>
	/// <param name="pos">				 	Pozycja przycisku. </param>
	/// <param name="renderer">			 	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> guiSpriteSheet, std::int32_t spriteIndex,
		std::int32_t pressedSpriteIndex, const glm::vec2& pos, class Renderer& renderer);

	/// <summary>	Domyślny destruktor. </summary>
	~Button();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja rysująca przycisk przy pomocy renderera. </summary>
	///
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void draw(class Renderer& renderer) const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja obsługująca wejście do przycisku. </summary>
	///
	/// <param name="orthoMatrix">	
	///		Macierz ortagonalna przedstawiająca skalę i położenię 
	///		interfejsu urzytkownika. 
	/// </param>
	/// <param name="app">		  	Obiekt aplikcaji. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void grabInput(const glm::mat4& orthoMatrix, class Application& app) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizująca stan przycisku. </summary>
	///
	/// <param name="deltaTime">	Czas pomiędzy kolejnymi krokami pętli stałokrokowej. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void update(double deltaTime) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca pozycję przycisku. </summary>
	///
	/// <param name="pos">	Pozycja przycisku. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPos(const glm::vec2& pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca czy przycisk ma zostać automatycznie wyłączany. </summary>
	///
	/// <param name="state">	Prawda jeśli przycisk ma być automatycznie wyłączany. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setAutoUnpress(bool state);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja sprawdzająca czy przycisk został wciśnięty. </summary>
	///
	/// <returns>	Prawda jężeli przycisk jest wciśnięty. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isPressed() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca wciśnięcie przycisku. </summary>
	///
	/// <param name="state">	Prawda - załączony. Fałsz - wyłączony. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPress(bool state);

private:
	/// <summary>	Prawda jeżeli przycisk jest załączony. </summary>
	bool mPressed;

	/// <summary>	Prawda jeśli przycisk ma być automatycznie wyłączany. </summary>
	bool mAutoUnpress;

	/// <summary>	Pozycja przycisku. </summary>
	glm::vec2 mPos;
	
	/// <summary>	Indeks sprite nie wciśniętego przycisku. </summary>
	std::int32_t mSpriteIndex;

	/// <summary>	Indeks sprite wciśniętego przycisku. </summary>
	std::int32_t mPressedSpriteIndex;

	/// <summary>	Zbiór sprite interfejsu użytkownika. </summary>
	std::shared_ptr<class SpriteSheet> mGuiSpriteSheet;
};

