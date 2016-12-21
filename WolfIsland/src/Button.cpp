#include "Button.hpp"
#include "Renderer.hpp"
#include "SpriteSheet.hpp"
#include "Application.hpp"
#include <glm/gtx/transform.hpp>
using namespace std;

Button::Button()
	: mAutoUnpress{ false }
{
}

Button::Button(shared_ptr<SpriteSheet> guiSpriteSheet, int32_t spriteIndex, 
	int32_t pressedSpriteIndex, const glm::vec2& pos, Renderer& renderer)
	: mAutoUnpress{ false }
{
	create(guiSpriteSheet, spriteIndex, pressedSpriteIndex, pos, renderer);
}

void Button::create(shared_ptr<SpriteSheet> guiSpriteSheet, int32_t spriteIndex, 
	int32_t pressedSpriteIndex, const glm::vec2& pos, Renderer& renderer)
{
	mGuiSpriteSheet = guiSpriteSheet;
	setPos(pos);
	mSpriteIndex = spriteIndex;
	mPressedSpriteIndex = pressedSpriteIndex;
}


Button::~Button()
{
}

void Button::draw(Renderer& renderer) const
{
	renderer.prepareDrawSprite();
	renderer.drawSprite(
		*mGuiSpriteSheet->getSprite(mPressed ? mPressedSpriteIndex : mSpriteIndex).lock(),
		glm::translate(glm::vec3{ mPos.x, mPos.y, 0.0f }));
}

void Button::grabInput(const glm::mat4& orthoMatrix, Application& app)
{
	auto pos{ app.getMouseNormalizedPosition() * glm::inverse(orthoMatrix) };
	auto bounds{ mGuiSpriteSheet->getSprite(mSpriteIndex).lock()->getBounds() };
	
	auto boundsLowerLeft = mPos;
	auto boundsUpperRight = mPos + bounds;

	if (app.getMouseButtonState(GLFW_MOUSE_BUTTON_1, !mAutoUnpress))
	{
		if (pos.x >= boundsLowerLeft.x && pos.y >= boundsLowerLeft.y &&
			pos.x <= boundsUpperRight.x && pos.y <= boundsUpperRight.y)
			mPressed = true;
	}
	else if (!app.getMouseButtonState(GLFW_MOUSE_BUTTON_1) && mAutoUnpress)
		mPressed = false;
}

void Button::update(double deltaTime)
{
}

void Button::setPos(const glm::vec2& pos)
{
	mPos = pos;
}

void Button::setAutoUnpress(bool state)
{
	mAutoUnpress = state;
}

bool Button::isPressed() const
{
	return mPressed;
}

void Button::setPress(bool state)
{
	mPressed = state;
}
