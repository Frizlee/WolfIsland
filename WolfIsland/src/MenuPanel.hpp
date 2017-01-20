#pragma once
#include "GuiObject.hpp"
#include "Slider.hpp"
#include <glm/vec2.hpp>


/// <summary>	
///		Klasa panelu zawierającego menu początkowe symulacji. Jest to element 
///		interfejsu użytkownika.
/// </summary>
class MenuPanel : public GuiObject
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	MenuPanel();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor tworzący panel z podanych zasobów. </summary>
	///
	/// <param name="guiSpriteSheet">  	Zbiór spriteów interfejsu użytkownika. </param>
	/// <param name="heightSliderText">	Obiekt tekstu dla slidera wysokości. </param>
	/// <param name="widthSliderText"> 	Obiekt tekstu dla slidera szerokości. </param>
	/// <param name="wolfSliderText">  	Obiekt tekstu dla slidera ilości wilków. </param>
	/// <param name="hareSliderText">  	Obiekt tekstu dla slidera ilości zająców. </param>
	/// <param name="pos">			   	Pozycja panelu. </param>
	/// <param name="renderer">		   	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	MenuPanel(std::shared_ptr<class SpriteSheet> guiSpriteSheet, 
		std::shared_ptr<class Text> heightSliderText, 
		std::shared_ptr<class Text> widthSliderText,
		std::shared_ptr<class Text> wolfSliderText,
		std::shared_ptr<class Text> hareSliderText, 
		const glm::vec2& pos, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja tworząca panel z podanych zasobów. </summary>
	///
	/// <param name="guiSpriteSheet">  	Zbiór spriteów interfejsu użytkownika. </param>
	/// <param name="heightSliderText">	Obiekt tekstu dla slidera wysokości. </param>
	/// <param name="widthSliderText"> 	Obiekt tekstu dla slidera szerokości. </param>
	/// <param name="wolfSliderText">  	Obiekt tekstu dla slidera ilości wilków. </param>
	/// <param name="hareSliderText">  	Obiekt tekstu dla slidera ilości zająców. </param>
	/// <param name="pos">			   	Pozycja panelu. </param>
	/// <param name="renderer">		   	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> guiSpriteSheet,
		std::shared_ptr<class Text> heightSliderText,
		std::shared_ptr<class Text> widthSliderText,
		std::shared_ptr<class Text> wolfSliderText,
		std::shared_ptr<class Text> hareSliderText,
		const glm::vec2& pos, class Renderer& renderer);

	/// <summary>	Domyślny destruktor. </summary>
	~MenuPanel();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja rysująca panel przy pomocy renderera. </summary>
	///
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void draw(class Renderer& renderer) const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja obsługująca wejście do panelu. </summary>
	///
	/// <param name="orthoMatrix">	
	///		Macierz ortagonalna przedstawiająca skalę i położenię 
	///		interfejsu urzytkownika. 
	/// </param>
	/// <param name="app">		  	Obiekt aplikacji. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void grabInput(const glm::mat4& orthoMatrix, class Application& app) override;
	
	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizująca stan panelu. </summary>
	///
	/// <param name="deltaTime">	Czas pomiędzy kolejnymi krokami pętli stałokrokowej. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void update(double deltaTime) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca pozycję panelu. </summary>
	///
	/// <param name="pos">	Nowa pozycja panelu. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPos(const glm::vec2& pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja pobierająca kolejne wratości sliderów. </summary>
	///
	/// <returns>	
	///		Tablica wartości sliderów. Kolejno: wysokość, szerokość, ilość wilków, ilość 
	///		zająców.
	/// </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::array<std::int32_t, 4> getValues() const;

private:

	/// <summary>	Pozycja panelu. </summary>
	glm::vec2 mPos;

	/// <summary>	Zbiór spriteów interfejsu użytkownika. </summary>
	std::shared_ptr<class SpriteSheet> mGuiSpriteSheet;

	/// <summary>	Obiekt slidera wysokości. </summary>
	std::shared_ptr<Slider<std::int32_t>> mHeightSlider;

	/// <summary>	Obiekt slidera szerokości. </summary>
	std::shared_ptr<Slider<std::int32_t>> mWidthSlider;

	/// <summary>	Obiekt slidera ilośći wilków. </summary>
	std::shared_ptr<Slider<std::int32_t>> mWolfSlider;

	/// <summary>	Obiekt slidera ilości zajaców. </summary>
	std::shared_ptr<Slider<std::int32_t>> mHareSlider;
};

