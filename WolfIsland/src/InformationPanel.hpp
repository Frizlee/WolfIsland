#pragma once
#include "GuiObject.hpp"
#include <glm/vec2.hpp>


class InformationPanel : public GuiObject
{
public:
	InformationPanel();

	InformationPanel(std::shared_ptr<class SpriteSheet> guiSpriteSheet, 
		std::shared_ptr<class Text> wolfMaleCouterText, 
		std::shared_ptr<class Text> woflFemaleCouterText,
		std::shared_ptr<class Text> hareCouterText,
		std::shared_ptr<class Text> boulderCouterText,
		std::shared_ptr<class Text> bushCouterText, 
		const glm::vec2& pos, class Renderer& renderer);
	
	void create(std::shared_ptr<class SpriteSheet> guiSpriteSheet,
		std::shared_ptr<class Text> wolfMaleCouterText,
		std::shared_ptr<class Text> woflFemaleCouterText,
		std::shared_ptr<class Text> hareCouterText,
		std::shared_ptr<class Text> boulderCouterText,
		std::shared_ptr<class Text> bushCouterText,
		const glm::vec2& pos, class Renderer& renderer);

	~InformationPanel();

	void draw(class Renderer& renderer) const override;
	void grabInput(const glm::mat4& orthoMatrix, class Application& app) override;
	void update(double deltaTime) override;

	void updateCounters(const std::array<std::int32_t, 5>& counters, Renderer& renderer);

	void setPos(const glm::vec2& pos);

private:

	glm::vec2 mPos;

	// Resources
	std::shared_ptr<class SpriteSheet> mGuiSpriteSheet;
	std::shared_ptr<class Text> mWolfMaleCouterText;
	std::shared_ptr<class Text> mWolfFemaleCouterText;
	std::shared_ptr<class Text> mHareCouterText;
	std::shared_ptr<class Text> mBoulderCouterText;
	std::shared_ptr<class Text> mBushCouterText;
};

