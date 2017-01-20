#pragma once
#include "Prerequisites.hpp"
#include "GameObject.hpp"
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include "gl_core_3_3.hpp"
#include "FlipbookAnimation.hpp"

/// <summary>	
///		Klasa reprezentująca obiekt symulacji jakim jest zając. Typ: "hare" 
/// </summary>
class Hare : public GameObject
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	Hare();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor tworzący zająca z podanych zasobów. </summary>
	///
	/// <param name="spriteSheet">	Zestaw spriteow dla zajaca. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Hare(std::shared_ptr<class SpriteSheet> spriteSheet);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja tworząca zająca z podanych zasobów. </summary>
	///
	/// <param name="spriteSheet">	Zestaw spriteow dla zajaca. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> spriteSheet);

	/// <summary>	Domyślny destruktor. </summary>
	~Hare();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rzeczywistą pozycję zająca. </summary>
	///
	/// <returns>	Rzeczywista pozycja zająca. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::vec2& getRealPos();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja rysująca zająca przy pomocy renderera. </summary>
	///
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void draw(class Renderer& renderer) const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizacji poruszania się zająca. </summary>
	///
	/// <param name="board">	Obiekt planszy. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateMove(class Board& board) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizacji akcji zająca. </summary>
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
	/// <summary>	Funkcja ustawiająca czy zając został zjedzony. </summary>
	///
	/// <param name="state">	Prawda jeżeli zając ma zostać zjedzony. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setEaten(bool state);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja sprawdzająca czy zając został zjedzony. </summary>
	///
	/// <returns>	Prawda jeżeli zając został zjedzony. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isEaten();

private:
	/// <summary>	Rzeczywista pozycja zająca. </summary>
	glm::vec2 mRealPos;

	/// <summary>	Losowy odchył o pozycji. </summary>
	glm::vec2 mRandomDisorder;

	/// <summary>	Tablica obiekt animacji typu Flipbook dla zająca. </summary>
	std::array<FlipbookAnimation, 9> mAnimations;

	/// <summary>	Aktualna animacja zająca. </summary>
	std::uint32_t mCurrentAnimation;

	/// <summary>	Aktualna animacja spoczynkowa. </summary>
	std::uint32_t mCurrentIdle;

	/// <summary>	Punkt rozpoczęcia przemieszczania. </summary>
	glm::vec2 mTransitionStartPos;

	/// <summary>	Czas przemieszczania. </summary>
	float mTransitionTimer;

	/// <summary>	Czas wyświetlania ciała zająca. </summary>
	float mCorpseTimer;

	/// <summary>	Licznik czasu do kolejnej możliwości podziału zająca. </summary>
	std::uint32_t mSplitTourTimer;

	/// <summary>	Liczba pozostałych tur życia. </summary>
	std::uint32_t mLifeTours;

	/// <summary>	Prawda jeżeli zając został zjedzony. </summary>
	bool mIsEaten;
};

