#pragma once
#include "GuiObject.hpp"
#include <glm/vec2.hpp>

class Button :	public GuiObject
{
public:
	Button();

	Button(std::shared_ptr<class SpriteSheet> guiSpriteSheet, std::int32_t spriteIndex,
		std::int32_t pressedSpriteIndex, const glm::vec2& pos, class Renderer& renderer);
	void create(std::shared_ptr<class SpriteSheet> guiSpriteSheet, std::int32_t spriteIndex,
		std::int32_t pressedSpriteIndex, const glm::vec2& pos, class Renderer& renderer);

	~Button();

	void draw(class Renderer& renderer) const override;
	void grabInput(const glm::mat4& orthoMatrix, class Application& app) override;
	void update(double deltaTime) override;

	void setPos(const glm::vec2& pos);
	void setAutoUnpress(bool state);
	bool isPressed() const;
	void setPress(bool state);

private:
	bool mPressed;
	bool mAutoUnpress;

	glm::vec2 mPos;
	
	// Resources
	std::int32_t mSpriteIndex;
	std::int32_t mPressedSpriteIndex;
	std::shared_ptr<class SpriteSheet> mGuiSpriteSheet;
};

