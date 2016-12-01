#pragma once
#include "Prerequisites.hpp"
#include "GuiObject.hpp"
#include <glm/vec2.hpp>

template <typename T>
class Slider : public GuiObject
{
public:
	Slider();

	Slider(std::shared_ptr<class Sprite> sliderSprite, std::shared_ptr<class Sprite> buttonSprite,
		std::shared_ptr<class Text> text, const T& minValue, const T& maxValue, 
		const glm::vec2& pos, class Renderer& renderer);
	void create(std::shared_ptr<class Sprite> sliderSprite, 
		std::shared_ptr<class Sprite> buttonSprite, std::shared_ptr<class Text> text,
		const T& minValue, const T& maxValue, const glm::vec2& pos, class Renderer& renderer);

	~Slider();

	void draw(class Renderer& renderer) const override;

	void grabInput(const glm::mat4& orthoMatrix, class Application& app) override;
	void update(float deltaTime) override;

	const T& getValue() const;


private:
	glm::vec2 mPos;
	glm::vec2 mButtonPos;
	glm::vec2 mTextPos;

	T mValue;
	T mMinValue;
	T mMaxValue;

	bool mClicked;

	std::shared_ptr<class Sprite> mSlider;
	std::shared_ptr<class Sprite> mButton;
	std::shared_ptr<class Text> mText;
};

template<typename T>
inline Slider<T>::Slider()
{
}

template<typename T>
inline Slider<T>::Slider(std::shared_ptr<class Sprite> sliderSprite, 
	std::shared_ptr<class Sprite> buttonSprite, std::shared_ptr<class Text> text, const T& minValue,
	const T& maxValue, const glm::vec2& pos, class Renderer& renderer)
{
	create(sliderSprite, buttonSprite, minValue, maxValue, pos);
}

template<typename T>
inline void Slider<T>::create(std::shared_ptr<class Sprite> sliderSprite, 
	std::shared_ptr<class Sprite> buttonSprite, std::shared_ptr<class Text> text, const T& minValue,
	const T& maxValue, const glm::vec2& pos, class Renderer& renderer)
{
	mSlider = sliderSprite;
	mButton = buttonSprite;
	mText = text;
	mMinValue = minValue;
	mMaxValue = maxValue;
	mValue = minValue;
	mPos = pos;
	mButtonPos = glm::vec2{ 0.0f, -(mButton->getBounds().y - mSlider->getBounds().y) / 2.0f };
	mTextPos = glm::vec2{ mSlider->getBounds().x + 7.0f, mSlider->getBounds().y + 3.0f };

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
	renderer.drawSprite(*mSlider, glm::translate(glm::vec3{ mPos.x, mPos.y, 0.0f }));

	auto pos = mPos + mButtonPos;
	renderer.drawSprite(*mButton, glm::translate(glm::vec3{ pos.x, pos.y, 0.0f }));

	renderer.prepareDrawText();
	pos = mPos + mTextPos;
	renderer.drawText(*mText, glm::translate(glm::vec3{ pos.x, pos.y, 0.0f }));
}

template<typename T>
inline void Slider<T>::grabInput(const glm::mat4& orthoMatrix, Application& app)
{
	auto dim = app.getDimensions();
	auto pos{ app.getMousePosition() };
	auto normPos = glm::vec4{ 2 * pos.x / dim.x - 1.0f, 
		2 * pos.y / dim.y - 1.0f, 0.0f, 1.0f };

	auto boundsLowerLeft = orthoMatrix * glm::vec4{ mPos + mButtonPos, 0.0f, 1.0f };
	auto boundsUpperRight = orthoMatrix * glm::vec4{ mPos + mButtonPos + mButton->getBounds(), 
		0.0f, 1.0f };

	if (app.getMouseButtonState(GLFW_MOUSE_BUTTON_1))
	{
		if (normPos.x >= boundsLowerLeft.x && normPos.y >= boundsLowerLeft.y &&
			normPos.x <= boundsUpperRight.x && normPos.y <= boundsUpperRight.y)
			mClicked = true;
	}
	else
		mClicked = false;

	if (mClicked)
	{
		mButtonPos.x = glm::clamp((normPos * glm::inverse(orthoMatrix)).x, mPos.x, 
			(mPos + mSlider->getBounds() - mButton->getBounds()).x);

		mValue = (mButtonPos.x - mPos.x) / (mSlider->getBounds().x - mButton->getBounds().x) * 
			(mMaxValue - mMinValue) + mMinValue;

		std::stringstream str;
		str << mValue;
		mText->updateContent(str.str(), app.getRenderer());
	}
}

template<typename T>
inline void Slider<T>::update(float deltaTime)
{
}

template<typename T>
inline const T& Slider<T>::getValue() const
{
	return mValue;
}
