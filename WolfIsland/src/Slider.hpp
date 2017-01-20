#pragma once
#include "Prerequisites.hpp"
#include "GuiObject.hpp"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

///------------------------------------------------------------------------------------------------
/// <summary>	
///		Klasa slidera (suwaka) - elementu interfejsu użytkownika rysowanego za pomocą OpenGL. 
/// </summary>
///
/// <typeparam name="T">	
/// 	Typ danych jakie na jakich operuje suwak.
/// </typeparam>
/// 
///------------------------------------------------------------------------------------------------
template <typename T>
class Slider : public GuiObject
{
public:
	/// <summary>	Domyślny konsturktor. </summary>
	Slider();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Konstruktor tworzący slider z podanych zasobów. </summary>
	///
	/// <param name="guiSpriteSheet">	Zestaw spriteów interfejsu użytkownika. </param>
	/// <param name="text">			 	Obiekt tekstu dla slidera. </param>
	/// <param name="minValue">		 	Wartość maksymalna. </param>
	/// <param name="maxValue">		 	Wartość minimalna. </param>
	/// <param name="pos">			 	Pozycja slidera. </param>
	/// <param name="renderer">		 	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Slider(std::shared_ptr<class SpriteSheet> guiSpriteSheet, std::shared_ptr<class Text> text,
		const T& minValue, const T& maxValue, const glm::vec2& pos, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja tworząca slider z podanych zasobów. </summary>
	///
	/// <param name="guiSpriteSheet">	Zestaw spriteów interfejsu użytkownika. </param>
	/// <param name="text">			 	Obiekt tekstu dla slidera. </param>
	/// <param name="minValue">		 	Wartość maksymalna. </param>
	/// <param name="maxValue">		 	Wartość minimalna. </param>
	/// <param name="pos">			 	Pozycja slidera. </param>
	/// <param name="renderer">		 	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> guiSpriteSheet, std::shared_ptr<class Text> text,
		const T& minValue, const T& maxValue, const glm::vec2& pos, class Renderer& renderer);

	/// <summary>	Domyślny destruktor. </summary>
	~Slider();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja rysująca slider przy pomocy renderera. </summary>
	///
	/// <param name="renderer">	Obiekt renderera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void draw(class Renderer& renderer) const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja obsługująca wejście do slidera. </summary>
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
	/// <summary>	Funkcja aktualizująca stan slidera. </summary>
	///
	/// <param name="deltaTime">	Czas pomiędzy kolejnymi krokami pętli stałokrokowej. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void update(double deltaTime) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja zwracająca aktualną wartość slidera. </summary>
	///
	/// <returns>	Aktualna wartość. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const T& getValue() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca pozycję slidera. </summary>
	///
	/// <param name="pos">	Nowa pozycja slidera. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPos(const glm::vec2& pos);


private:

	///--------------------------------------------------------------------------------------------
	/// <summary>	Indeks sprite slidera. </summary>
	///
	/// <returns>	Indeks. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static constexpr std::uint32_t sliderIndex();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Indeks sprite przycisku. </summary>
	///
	/// <returns>	Indeks. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static constexpr std::uint32_t buttonIndex();

	/// <summary>	Pozycja slidera. </summary>
	glm::vec2 mPos;

	/// <summary>	Pozycja przycisku. </summary>
	glm::vec2 mButtonPos;

	/// <summary>	Pozycja tekstu. </summary>
	glm::vec2 mTextPos;

	/// <summary>	Aktualna wartość. </summary>
	T mValue;

	/// <summary>	Minimalna wartość. </summary>
	T mMinValue;

	/// <summary>	Maksymalna wartość. </summary>
	T mMaxValue;

	/// <summary>	Prawda jeżeli naciśnięto przycisk slidera. </summary>
	bool mClicked;
	
	/// <summary>	Zbiór spriteów interfejsu użytkownika. </summary>
	std::shared_ptr<class SpriteSheet> mGuiSpriteSheet;

	/// <summary>	Obiekt tekstu. </summary>
	std::shared_ptr<class Text> mText;
};

template<typename T>
inline Slider<T>::Slider()
{
}

template<typename T>
inline Slider<T>::Slider(std::shared_ptr<class SpriteSheet> guiSpriteSheet, 
	std::shared_ptr<class Text> text, const T& minValue, const T& maxValue, const glm::vec2& pos, 
	class Renderer& renderer)
{
	create(guiSpriteSheet, text, minValue, maxValue, pos, renderer);
}

template<typename T>
inline void Slider<T>::create(std::shared_ptr<class SpriteSheet> guiSpriteSheet,
	std::shared_ptr<class Text> text, const T& minValue, const T& maxValue, const glm::vec2& pos, 
	class Renderer& renderer)
{
	mGuiSpriteSheet = guiSpriteSheet;
	mText = text;
	mMinValue = minValue;
	mMaxValue = maxValue;
	mValue = minValue;

	setPos(pos);

	std::stringstream str;
	str << mValue;

	mText->updateContent(str.str(), renderer);
}

template<typename T>
inline Slider<T>::~Slider()
{
}

template<typename T>
inline void Slider<T>::draw(Renderer& renderer) const
{
	renderer.prepareDrawSprite();
	renderer.drawSprite(*mGuiSpriteSheet->getSprite(sliderIndex()).lock(), 
		glm::translate(glm::vec3{ mPos.x, mPos.y, 0.0f }));

	auto pos = mPos + mButtonPos;
	renderer.drawSprite(*mGuiSpriteSheet->getSprite(buttonIndex()).lock(), 
		glm::translate(glm::vec3{ pos.x, pos.y, 0.0f }));

	renderer.prepareDrawText();
	pos = mPos + mTextPos;
	renderer.drawText(*mText, glm::translate(glm::vec3{ pos.x, pos.y, 0.0f }));
}

template<typename T>
inline void Slider<T>::grabInput(const glm::mat4& orthoMatrix, Application& app)
{
	auto dim = app.getDimensions();
	auto pos{ app.getMouseNormalizedPosition() * glm::inverse(orthoMatrix) };
	auto sliderBounds = mGuiSpriteSheet->getSprite(sliderIndex()).lock()->getBounds();
	auto buttonBounds = mGuiSpriteSheet->getSprite(buttonIndex()).lock()->getBounds();

	auto boundsLowerLeft = mPos + mButtonPos;
	auto boundsUpperRight = mPos + mButtonPos + buttonBounds;

	if (app.getMouseButtonState(GLFW_MOUSE_BUTTON_1))
	{
		if (pos.x >= boundsLowerLeft.x && pos.y >= boundsLowerLeft.y &&
			pos.x <= boundsUpperRight.x && pos.y <= boundsUpperRight.y)
			mClicked = true;
	}
	else
		mClicked = false;

	if (mClicked)
	{
		mButtonPos.x = glm::clamp(pos.x - mPos.x, 0.0f, (sliderBounds - buttonBounds).x);

		mValue = mButtonPos.x / (sliderBounds.x - buttonBounds.x) *
			(mMaxValue - mMinValue) + mMinValue;

		std::stringstream str;
		str << mValue;
		mText->updateContent(str.str(), app.getRenderer());
	}
}

template<typename T>
inline void Slider<T>::update(double deltaTime)
{
}

template<typename T>
inline const T& Slider<T>::getValue() const
{
	return mValue;
}

template<typename T>
inline void Slider<T>::setPos(const glm::vec2 & pos)
{
	mPos = pos;
	auto sliderBounds = mGuiSpriteSheet->getSprite(sliderIndex()).lock()->getBounds();
	auto buttonBounds = mGuiSpriteSheet->getSprite(buttonIndex()).lock()->getBounds();
	mButtonPos = glm::vec2{ 0.0f, -(buttonBounds.y - sliderBounds.y) / 2.0f };
	mTextPos = glm::vec2{ sliderBounds.x + 7.0f, 30.0f };
}

template<typename T>
inline constexpr std::uint32_t Slider<T>::sliderIndex()
{
	return 0;
}

template<typename T>
inline constexpr std::uint32_t Slider<T>::buttonIndex()
{
	return 1;
}
