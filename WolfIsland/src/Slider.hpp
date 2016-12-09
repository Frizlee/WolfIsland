#pragma once
#include "Prerequisites.hpp"
#include "GuiObject.hpp"
#include <glm/vec2.hpp>

template <typename T>
class Slider : public GuiObject
{
public:
	Slider();

	Slider(std::shared_ptr<class SpriteSheet> guiSpriteSheet, std::shared_ptr<class Text> text, 
		const T& minValue, const T& maxValue, const glm::vec2& pos, class Renderer& renderer);
	void create(std::shared_ptr<class SpriteSheet> guiSpriteSheet, std::shared_ptr<class Text> text,
		const T& minValue, const T& maxValue, const glm::vec2& pos, class Renderer& renderer);

	~Slider();

	void draw(class Renderer& renderer) const override;

	void grabInput(const glm::mat4& orthoMatrix, class Application& app) override;
	void update(float deltaTime) override;

	const T& getValue() const;


private:
	static constexpr std::uint32_t sliderIndex();
	static constexpr std::uint32_t  buttonIndex();

	glm::vec2 mPos;
	glm::vec2 mButtonPos;
	glm::vec2 mTextPos;

	T mValue;
	T mMinValue;
	T mMaxValue;

	bool mClicked;

	std::shared_ptr<class SpriteSheet> mGuiSpriteSheet;
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
	create(guiSpriteSheet, minValue, maxValue, pos);
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
	mPos = pos;

	auto sliderBounds = mGuiSpriteSheet->getSprite(sliderIndex()).lock()->getBounds();
	auto buttonBounds = mGuiSpriteSheet->getSprite(buttonIndex()).lock()->getBounds();

	mButtonPos = glm::vec2{ 0.0f, -(buttonBounds.y - sliderBounds.y) / 2.0f };
	mTextPos = glm::vec2{ sliderBounds.x + 7.0f, sliderBounds.y + 3.0f };

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
	auto pos{ app.getMouseNormalizedPosition() };
	pos = pos * glm::inverse(orthoMatrix);
	auto sliderBounds = mGuiSpriteSheet->getSprite(sliderIndex()).lock()->getBounds();
	auto buttonBounds = mGuiSpriteSheet->getSprite(buttonIndex()).lock()->getBounds();

	auto boundsLowerLeft = glm::vec4{ mPos + mButtonPos, 0.0f, 1.0f };
	auto boundsUpperRight = glm::vec4{ mPos + mButtonPos + buttonBounds, 0.0f, 1.0f };

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
		mButtonPos.x = glm::clamp(pos.x, mPos.x, (mPos + sliderBounds - buttonBounds).x);

		mValue = (mButtonPos.x - mPos.x) / (sliderBounds.x - buttonBounds.x) *
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
