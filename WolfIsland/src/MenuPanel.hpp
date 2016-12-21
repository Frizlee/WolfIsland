#pragma once
#include "GuiObject.hpp"
#include "Slider.hpp"
#include <glm/vec2.hpp>


class MenuPanel : public GuiObject
{
public:
	MenuPanel();

	MenuPanel(std::shared_ptr<class SpriteSheet> guiSpriteSheet, 
		std::shared_ptr<class Text> heightSliderText, 
		std::shared_ptr<class Text> widthSliderText,
		std::shared_ptr<class Text> wolfSliderText,
		std::shared_ptr<class Text> hareSliderText, 
		const glm::vec2& pos, class Renderer& renderer);
	
	void create(std::shared_ptr<class SpriteSheet> guiSpriteSheet,
		std::shared_ptr<class Text> heightSliderText,
		std::shared_ptr<class Text> widthSliderText,
		std::shared_ptr<class Text> wolfSliderText,
		std::shared_ptr<class Text> hareSliderText,
		const glm::vec2& pos, class Renderer& renderer);

	~MenuPanel();

	void draw(class Renderer& renderer) const override;
	void grabInput(const glm::mat4& orthoMatrix, class Application& app) override;
	void update(double deltaTime) override;

	void setPos(const glm::vec2& pos);
	std::array<std::int32_t, 4> getValues() const;

private:

	glm::vec2 mPos;

	// Resources
	std::shared_ptr<class SpriteSheet> mGuiSpriteSheet;
	std::shared_ptr<Slider<std::int32_t>> mHeightSlider;
	std::shared_ptr<Slider<std::int32_t>> mWidthSlider;
	std::shared_ptr<Slider<std::int32_t>> mWolfSlider;
	std::shared_ptr<Slider<std::int32_t>> mHareSlider;
};

