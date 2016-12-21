#include "MenuPanel.hpp"
#include "Text.hpp"
#include "Renderer.hpp"
#include "SpriteSheet.hpp"
#include "Application.hpp"
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>
using namespace std;

static const glm::vec2 heightSliderOffset{ 92.0f, 200.0f };
static const glm::vec2 widthSliderOffset{ 92.0f, 150.0f };
static const glm::vec2 wolfSliderOffset{ 92.0f, 100.0f };
static const glm::vec2 hareSliderOffset{ 92.0f, 50.0f };
static const int32_t panelIndex{ 3 };

MenuPanel::MenuPanel()
{
}

MenuPanel::MenuPanel(shared_ptr<SpriteSheet> guiSpriteSheet, 
	shared_ptr<Text> heightSliderText, shared_ptr<Text> widthSliderText, 
	shared_ptr<Text> wolfSliderText, shared_ptr<Text> hareSliderText, 
	const glm::vec2& pos, Renderer& renderer)
{
	create(guiSpriteSheet, heightSliderText, widthSliderText, wolfSliderText, hareSliderText,
		pos, renderer);
}

void MenuPanel::create(shared_ptr<SpriteSheet> guiSpriteSheet,
	shared_ptr<Text> heightSliderText, shared_ptr<Text> widthSliderText,
	shared_ptr<Text> wolfSliderText, shared_ptr<Text> hareSliderText,
	const glm::vec2& pos, Renderer& renderer)
{
	mGuiSpriteSheet = guiSpriteSheet;

	mHeightSlider = make_shared<Slider<int32_t>>(mGuiSpriteSheet, heightSliderText, 2, 200,
		glm::vec2{}, renderer);
	mWidthSlider = make_shared<Slider<int32_t>>(mGuiSpriteSheet, widthSliderText, 2, 200,
		glm::vec2{}, renderer);
	mWolfSlider = make_shared<Slider<int32_t>>(mGuiSpriteSheet, wolfSliderText, 0, 50,
		glm::vec2{}, renderer);
	mHareSlider = make_shared<Slider<int32_t>>(mGuiSpriteSheet, hareSliderText, 0, 50,
		glm::vec2{}, renderer);

	setPos(pos);
}

MenuPanel::~MenuPanel()
{
}

void MenuPanel::draw(Renderer& renderer) const
{
	renderer.prepareDrawSprite();
	renderer.drawSprite(*mGuiSpriteSheet->getSprite(panelIndex).lock(),
		glm::translate(glm::vec3{ mPos.x, mPos.y, 0.0f }));

	mHeightSlider->draw(renderer);
	mWidthSlider->draw(renderer);
	mWolfSlider->draw(renderer);
	mHareSlider->draw(renderer);
}

void MenuPanel::grabInput(const glm::mat4& orthoMatrix, Application& app)
{
	mHeightSlider->grabInput(orthoMatrix, app);
	mWidthSlider->grabInput(orthoMatrix, app);
	mWolfSlider->grabInput(orthoMatrix, app);
	mHareSlider->grabInput(orthoMatrix, app);
}

void MenuPanel::update(double deltaTime)
{
	mHeightSlider->update(deltaTime);
	mWidthSlider->update(deltaTime);
	mWolfSlider->update(deltaTime);
	mHareSlider->update(deltaTime);
}

void MenuPanel::setPos(const glm::vec2& pos)
{
	mPos = pos;
	mHeightSlider->setPos(pos + heightSliderOffset);
	mWidthSlider->setPos(pos + widthSliderOffset);
	mWolfSlider->setPos(pos + wolfSliderOffset);
	mHareSlider->setPos(pos + hareSliderOffset);
}

array<int32_t, 4> MenuPanel::getValues() const
{
	return { mHeightSlider->getValue(), mWidthSlider->getValue(), 
		mWolfSlider->getValue(), mHareSlider->getValue() };
}
