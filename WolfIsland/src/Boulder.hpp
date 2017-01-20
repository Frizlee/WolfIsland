#pragma once
#include "Prerequisites.hpp"
#include "GameObject.hpp"

/// <summary>	Klasa reprezentująca obiekt symulacji jakim jest głaz. Typ: "boulder" </summary>
class Boulder :	public GameObject
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	Boulder();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor tworzący głaz z podanych zasobów. </summary>
	///
	/// <param name="boulderSprite">	Obiekt sprite dla głazu. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Boulder(std::shared_ptr<class Sprite> boulderSprite);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja tworząca głaz z podanych zasobów. </summary>
	///
	/// <param name="boulderSprite">	Obiekt sprite dla głazu. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class Sprite> boulderSprite);

	/// <summary>	Domyślny destruktor. </summary>
	~Boulder();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rzeczywistą pozycję głazu. </summary>
	///
	/// <returns>	Rzeczywista pozycja głazu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::vec2& getRealPos();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja rysująca głaz przy pomocy renderera. </summary>
	///
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void draw(class Renderer& renderer) const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja aktualizacji poruszania się głazu. Nie robi nic, ponieważ głaz nie 
	///		może się poruszać.
	/// </summary>
	///
	/// <param name="board">	Obiekt planszy. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateMove(class Board& board) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizacji akcji głazu. </summary>
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

private:
	/// <summary>	Rzeczywista pozycja głazu. </summary>
	glm::vec2 mRealPos;

	/// <summary>	Obiekt sprite dla głazu. </summary>
	std::shared_ptr<class Sprite> mSprite;
};

