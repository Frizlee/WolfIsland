///-------------------------------------------------------------------------------------------------
// file:	src\Slider.hpp
//
// summary:	
///-------------------------------------------------------------------------------------------------
#pragma once
#include "Prerequisites.hpp"
#include "GuiObject.hpp"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

template <typename T>
/// <summary>	A slider. </summary>
class Slider : public GuiObject
{
public:
	/// <summary>	Default constructor. </summary>
	Slider();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="guiSpriteSheet">	The graphical user interface sprite sheet. </param>
	/// <param name="text">			 	The text. </param>
	/// <param name="minValue">		 	The minimum value. </param>
	/// <param name="maxValue">		 	The maximum value. </param>
	/// <param name="pos">			 	The position. </param>
	/// <param name="renderer">		 	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	Slider(std::shared_ptr<class SpriteSheet> guiSpriteSheet, std::shared_ptr<class Text> text,
		const T& minValue, const T& maxValue, const glm::vec2& pos, class Renderer& renderer);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Creates this object. </summary>
	///
	/// <param name="guiSpriteSheet">	The graphical user interface sprite sheet. </param>
	/// <param name="text">			 	The text. </param>
	/// <param name="minValue">		 	The minimum value. </param>
	/// <param name="maxValue">		 	The maximum value. </param>
	/// <param name="pos">			 	The position. </param>
	/// <param name="renderer">		 	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> guiSpriteSheet, std::shared_ptr<class Text> text,
		const T& minValue, const T& maxValue, const glm::vec2& pos, class Renderer& renderer);

	/// <summary>	Destructor. </summary>
	~Slider();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Draws the given renderer. </summary>
	///
	/// <param name="renderer">	[in,out] The renderer. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void draw(class Renderer& renderer) const override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Grab input. </summary>
	///
	/// <param name="orthoMatrix">	The ortho matrix. </param>
	/// <param name="app">		  	[in,out] The application. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void grabInput(const glm::mat4& orthoMatrix, class Application& app) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Updates the given deltaTime. </summary>
	///
	/// <param name="deltaTime">	The delta time. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void update(double deltaTime) override;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Gets the value. </summary>
	///
	/// <returns>	The value. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	const T& getValue() const;

	///--------------------------------------------------------------------------------------------
	/// <summary>	Sets a position. </summary>
	///
	/// <param name="pos">	The position. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setPos(const glm::vec2& pos);


private:

	///--------------------------------------------------------------------------------------------
	/// <summary>	Slider index. </summary>
	///
	/// <returns>	A std::uint32_t. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static constexpr std::uint32_t sliderIndex();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Button index. </summary>
	///
	/// <returns>	A std::uint32_t. </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	static constexpr std::uint32_t buttonIndex();

	/// <summary>	The position. </summary>
	glm::vec2 mPos;
	/// <summary>	The button position. </summary>
	glm::vec2 mButtonPos;
	/// <summary>	The text position. </summary>
	glm::vec2 mTextPos;

	/// <summary>	The value. </summary>
	T mValue;
	/// <summary>	The minimum value. </summary>
	T mMinValue;
	/// <summary>	The maximum value. </summary>
	T mMaxValue;

	/// <summary>	True if clicked. </summary>
	bool mClicked;
	
	/// <summary>	Resources. </summary>
	std::shared_ptr<class SpriteSheet> mGuiSpriteSheet;
	/// <summary>	The text. </summary>
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
