#pragma once
#include "GuiObject.hpp"
#include <glm/vec2.hpp>


/// <summary>	
///		Klasa panelu zawierającego informacje o stanie symulacji. Jest to element 
///		interfejsu użytkownika.
/// </summary>
class InformationPanel : public GuiObject
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	InformationPanel();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konsturktor tworzący panel informacyjny z podanych zasobów. </summary>
	///
	/// <param name="guiSpriteSheet">	   	Zestaw sprite interfejsu użytkownika. </param>
	/// <param name="wolfMaleCouterText">  	Obiekt tekstu dla licznika samców wilków. </param>
	/// <param name="woflFemaleCouterText">	Obiekt tekstu dla licznika samic wilków. </param>
	/// <param name="hareCouterText">	   	Obiekt tekstu dla licznika zająców. </param>
	/// <param name="boulderCouterText">   	Obiekt tekstu dla licznika głazów. </param>
	/// <param name="bushCouterText">	   	Obiekt tekstu dla licznika krzaków. </param>
	/// <param name="pos">				   	Pozycja panelu. </param>
	/// <param name="renderer">			   	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	InformationPanel(std::shared_ptr<class SpriteSheet> guiSpriteSheet, 
		std::shared_ptr<class Text> wolfMaleCouterText, 
		std::shared_ptr<class Text> woflFemaleCouterText,
		std::shared_ptr<class Text> hareCouterText,
		std::shared_ptr<class Text> boulderCouterText,
		std::shared_ptr<class Text> bushCouterText, 
		const glm::vec2& pos, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja tworząca panel informacyjny z podanych zasobów. </summary>
	///
	/// <param name="guiSpriteSheet">	   	Zestaw sprite interfejsu użytkownika. </param>
	/// <param name="wolfMaleCouterText">  	Obiekt tekstu dla licznika samców wilków. </param>
	/// <param name="woflFemaleCouterText">	Obiekt tekstu dla licznika samic wilków. </param>
	/// <param name="hareCouterText">	   	Obiekt tekstu dla licznika zająców. </param>
	/// <param name="boulderCouterText">   	Obiekt tekstu dla licznika głazów. </param>
	/// <param name="bushCouterText">	   	Obiekt tekstu dla licznika krzaków. </param>
	/// <param name="pos">				   	Pozycja panelu. </param>
	/// <param name="renderer">			   	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> guiSpriteSheet,
		std::shared_ptr<class Text> wolfMaleCouterText,
		std::shared_ptr<class Text> woflFemaleCouterText,
		std::shared_ptr<class Text> hareCouterText,
		std::shared_ptr<class Text> boulderCouterText,
		std::shared_ptr<class Text> bushCouterText,
		const glm::vec2& pos, class Renderer& renderer);

	/// <summary>	Domyślny destruktor. </summary>
	~InformationPanel();

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
	/// <summary>	Funkcja aktualizująca stan liczników. </summary>
	///
	/// <param name="counters">	
	///		Tablica wartości liczników. Kolejno: sance wilków, samice wilków,
	///		zające, głazy, krzaki. 
	///	</param>
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateCounters(const std::array<std::int32_t, 5>& counters, Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca pozycję panelu. </summary>
	///
	/// <param name="pos">	Nowa pozycja panelu. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPos(const glm::vec2& pos);

private:

	/// <summary>	Pozycja panelu. </summary>
	glm::vec2 mPos;

	/// <summary>	Zbiór spriteów interfejsu użytkownika. </summary>
	std::shared_ptr<class SpriteSheet> mGuiSpriteSheet;

	/// <summary>	Obiekt tekstu dla licznika samców wilków. </summary>
	std::shared_ptr<class Text> mWolfMaleCouterText;

	/// <summary>	Obiekt tekstu dla licznika samic wilków. </summary>
	std::shared_ptr<class Text> mWolfFemaleCouterText;

	/// <summary>	Obiekt tekstu dla licznika zająców. </summary>
	std::shared_ptr<class Text> mHareCouterText;

	/// <summary>	Obiekt tekstu dla licznika głazów. </summary>
	std::shared_ptr<class Text> mBoulderCouterText;

	/// <summary>	Obiekt tekstu dla licznika krzaków. </summary>
	std::shared_ptr<class Text> mBushCouterText;
};

