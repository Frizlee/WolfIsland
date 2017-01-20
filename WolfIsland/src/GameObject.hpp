#pragma once
#include "Prerequisites.hpp"
#include "gl_core_3_3.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

/// <summary>	Klasa abstrakcyjna reprezentująca obiekt symulacji. </summary>
class GameObject
{
public:
	/// <summary>	Domyślny konsturktor. </summary>
	GameObject();

	/// <summary>	Domyślny destruktor. </summary>
	virtual ~GameObject() = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja rysująca obiekt przy pomocy renderera. </summary>
	///
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void draw(class Renderer& renderer) const = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizacji poruszania się obiektu. </summary>
	///
	/// <param name="board">	Obiekt planszy. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void updateMove(class Board& board) = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizacji akcji obiektu. </summary>
	///
	/// <param name="board">	Obiekt planszy. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void updateAction(class Board& board) = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizująca animację raz na klatkę. </summary>
	///
	/// <param name="deltaTime">	Czas pomiędzy klatkami animacji. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void update(float deltaTime) = 0;

	/// <summary>	Funkcja zapisująca aktualną pozycję. </summary>
	void saveCurrentPos();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca aktualną pozycję. </summary>
	///
	/// <returns>	Aktualna pozycja. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::tvec2<std::int32_t>& getPos() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca zapisaną pozycję. </summary>
	///
	/// <returns>	Zapisana pozycja. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const glm::tvec2<std::int32_t>& getSavedPos() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca pozycję. </summary>
	///
	/// <param name="pos">	Nowa pozycja. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	virtual void setPos(const glm::tvec2<std::int32_t>& pos) = 0;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca string przedstawiający typ obiektu. </summary>
	///
	/// <returns>	Ciąg specyficzny dla danego typu obiektu. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const std::string& getObjectType();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktywująca/dezaktywująca obiekt. </summary>
	///
	/// <param name="state">	Prawda aktywuje obiekt. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setActive(bool state);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja sprawdzająca czy obiekt jest aktywny. </summary>
	///
	/// <returns>	Prawda jeżeli obiekt jest aktywny. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isActive() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja sprawdzająca czy obiekt jest gotowy do usunięcia. </summary>
	///
	/// <returns>	Prawda jeżeli obiekt jest gotowy do usunięcia. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	bool isReadyToDelete() const;

protected:
	/// <summary>	Ciąg specyficzny dla danego typu obiektu. </summary>
	std::string mType;

	/// <summary>	Pozycja obiektu. </summary>
	glm::tvec2<std::int32_t> mPos;

	/// <summary>	Zapisana pozycja obiektu. </summary>
	glm::tvec2<std::int32_t> mSavedPos;

	/// <summary>	Prawda jeżeli obiekt jest aktywny. </summary>
	bool mActive;

	/// <summary>	Prawda jeżeli obiekt jest gotowy do usunięcia. </summary>
	bool mReadyToDelete;
};

