#pragma once
#include "Prerequisites.hpp"
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include "gl_core_3_3.hpp"
#include "GameObject.hpp"
#include "FlipbookAnimation.hpp"


/// <summary>	
///		Klasa reprezentująca obiekt symulacji jakim jest samica wilka. Typ: "wolf_female" 
/// </summary>
class WolfFemale : public GameObject
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	WolfFemale();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor tworzący wilka z podanych zasobów. </summary>
	///
	/// <param name="spriteSheet">	Zestaw spriteów dla wilka. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	WolfFemale(std::shared_ptr<class SpriteSheet> spriteSheet);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja tworząca wilka z podanych zasobów. </summary>
	///
	/// <param name="spriteSheet">	Zestaw spriteów dla wilka. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> spriteSheet);

	/// <summary>	Domyślny destruktor. </summary>
	~WolfFemale();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rzeczywistą pozycję wilka. </summary>
	///
	/// <returns>	Rzeczywista pozycja wilka. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::vec2& getRealPos();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja rysująca wilka przy pomocy renderera. </summary>
	///
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void draw(class Renderer& renderer) const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizacji poruszania się wilka. </summary>
	///
	/// <param name="board">	Obiekt planszy. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateMove(class Board& board) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizacji akcji wilka. </summary>
	///
	/// <param name="board">	Obiekt planszy. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateAction(class Board& board) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizująca animację raz na klatkę. </summary>
	///
	/// <param name="deltaTime">	Czas pomiędzy klatkami animacji. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void update(float deltaTime) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca pozycję. </summary>
	///
	/// <param name="pos">	Nowa pozycja. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPos(const glm::tvec2<std::int32_t>& pos);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja powodująca oszczenienie się wilczycy i ustawienie nowego wilka na 
	///		planszy. 
	///	</summary>
	///
	/// <param name="board">	Obiekt planszy. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void pup(class Board& board);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja sprawdzająca czy wilczyca może się oszczenić. </summary>
	///
	/// <returns>	Prawda jeśli wilczyca może się oszczenić. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool canPup();

private:
	/// <summary>	Rzeczywista pozycja wilka. </summary>
	glm::vec2 mRealPos;

	/// <summary>	Losowy odchył o pozycji. </summary>
	glm::vec2 mRandomDisorder;

	/// <summary>	Tablica obiekt animacji typu Flipbook dla wilka. </summary>
	std::array<FlipbookAnimation, 10> mAnimations;

	/// <summary>	Aktualna animacja wilka. </summary>
	std::uint32_t mCurrentAnimation;

	/// <summary>	Aktualna animacja spoczynkowa. </summary>
	std::uint32_t mCurrentIdle;

	/// <summary>	Punkt rozpoczęcia przemieszczania. </summary>
	glm::vec2 mTransitionStartPos;

	/// <summary>	Czas przemieszczania. </summary>
	float mTransitionTimer;

	/// <summary>	Czas wyświetlania ciała wilka. </summary>
	float mCorpseTimer;

	/// <summary>	Prawda jeżeli wilk goni zająca. </summary>
	bool mChaseHare;

	/// <summary>	Tłuszcz wilka, jeżeli spadnie do 0 to wilk umrze. </summary>
	float mFat;

	/// <summary>	Licznik czasu po którym wilczyca może się oszczenić. </summary>
	std::uint32_t mPupTourTimer;
};

