#pragma once
#include "Prerequisites.hpp"
#include "GameObject.hpp"

/// <summary>	Klasa reprezentująca obiekt symulacji jakim jest krzak. Typ: "bush" </summary>
class Bush :	public GameObject
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	Bush();

	///--------------------------------------------------------------------------------------------
	/// <summary>	konstruktor tworzący krzak z podanych zasobów. </summary>
	///
	/// <param name="boulderSprite">	Obiekt sprite dla krzaka. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Bush(std::shared_ptr<class Sprite> bushSprite);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="boulderSprite">	Obiekt sprite dla krzaka. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class Sprite> bushSprite);

	/// <summary>	Domyślny destruktor. </summary>
	~Bush();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca rzeczywistą pozycję krzaka. </summary>
	///
	/// <returns>	Rzeczywista pozycja głazu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::vec2& getRealPos();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja rysująca krzak przy pomocy renderera. </summary>
	///
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void draw(class Renderer& renderer) const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	///		Funkcja aktualizacji poruszania się krzaka. Nie robi nic, ponieważ krzak nie 
	///		może sie poruszać.
	///</summary>
	///
	/// <param name="board">	Obiekt planszy. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void updateMove(class Board& board) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizacji akcji krzaka. </summary>
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
	/// <summary>	Rzeczywista pozycja krzaka. </summary>
	glm::vec2 mRealPos;

	/// <summary>	Obiekt sprite dla krzaka. </summary>
	std::shared_ptr<class Sprite> mSprite;
};

