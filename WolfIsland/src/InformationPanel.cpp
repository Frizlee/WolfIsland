#include "InformationPanel.hpp"
#include "Text.hpp"
#include "Renderer.hpp"
#include "SpriteSheet.hpp"
#include <glm/gtx/transform.hpp>
using namespace std;

static const glm::vec2 wolfMaleCounterOffset{ 166.0f, 108.0f + 30.0f };
static const glm::vec2 wolfFemaleCounterOffset{ 166.0f, 88.0f + 30.0f };
static const glm::vec2 hareCounterOffset{ 166.0f, 68.0f + 30.0f };
static const glm::vec2 boulderCounterOffset{ 166.0f, 48.0f + 30.0f };
static const glm::vec2 bushCounterOffset{ 166.0f, 28.0f + 30.0f };
static const int32_t panelIndex{ 2 };

InformationPanel::InformationPanel()
{
}

InformationPanel::InformationPanel(std::shared_ptr<class SpriteSheet> guiSpriteSheet, 
	shared_ptr<class Text> wolfMaleCouterText, shared_ptr<class Text> woflFemaleCouterText, 
	shared_ptr<class Text> hareCouterText, shared_ptr<class Text> boulderCouterText, 
	shared_ptr<class Text> bushCouterText, const glm::vec2& pos, Renderer& renderer)
{
	create(guiSpriteSheet, wolfMaleCouterText, woflFemaleCouterText, hareCouterText, 
		boulderCouterText, bushCouterText, pos, renderer);
}

void InformationPanel::create(shared_ptr<class SpriteSheet> guiSpriteSheet, 
	shared_ptr<class Text> wolfMaleCouterText, shared_ptr<class Text> woflFemaleCouterText, 
	shared_ptr<class Text> hareCouterText, shared_ptr<class Text> boulderCouterText, 
	shared_ptr<class Text> bushCouterText, const glm::vec2& pos, Renderer& renderer)
{
	mGuiSpriteSheet = guiSpriteSheet;
	mWolfMaleCouterText = wolfMaleCouterText;
	mWolfFemaleCouterText = woflFemaleCouterText;
	mHareCouterText = hareCouterText;
	mBoulderCouterText = boulderCouterText;
	mBushCouterText = bushCouterText;

	// initial values set to 0;
	string zeroStr = "0";
	mWolfMaleCouterText->updateContent(zeroStr, renderer);
	mWolfFemaleCouterText->updateContent(zeroStr, renderer);
	mHareCouterText->updateContent(zeroStr, renderer);
	mBoulderCouterText->updateContent(zeroStr, renderer);
	mBushCouterText->updateContent(zeroStr, renderer);

	setPos(pos);
}


InformationPanel::~InformationPanel()
{
}

void InformationPanel::draw(Renderer& renderer) const
{
	renderer.prepareDrawSprite();
	renderer.drawSprite(*mGuiSpriteSheet->getSprite(panelIndex).lock(),
		glm::translate(glm::vec3{ mPos.x, mPos.y, 0.0f }));

	renderer.prepareDrawText();
	auto pos = mPos + wolfMaleCounterOffset;
	renderer.drawText(*mWolfMaleCouterText, glm::translate(glm::vec3{ pos.x, pos.y, 0.0f }));
	pos = mPos + wolfFemaleCounterOffset;
	renderer.drawText(*mWolfFemaleCouterText, glm::translate(glm::vec3{ pos.x, pos.y, 0.0f }));
	pos = mPos + hareCounterOffset;
	renderer.drawText(*mHareCouterText, glm::translate(glm::vec3{ pos.x, pos.y, 0.0f }));
	pos = mPos + boulderCounterOffset;
	renderer.drawText(*mBoulderCouterText, glm::translate(glm::vec3{ pos.x, pos.y, 0.0f }));
	pos = mPos + bushCounterOffset;
	renderer.drawText(*mBushCouterText, glm::translate(glm::vec3{ pos.x, pos.y, 0.0f }));
}

void InformationPanel::grabInput(const glm::mat4& orthoMatrix, Application& app)
{
}

void InformationPanel::update(double deltaTime)
{
}

void InformationPanel::updateCounters(const std::array<std::int32_t, 5>& counters, Renderer& renderer)
{
	stringstream str;
	str << counters[0];
	mWolfMaleCouterText->updateContent(str.str(), renderer);
	str.str(string{});
	str << counters[1];
	mWolfFemaleCouterText->updateContent(str.str(), renderer);
	str.str(string{});
	str << counters[2];
	mHareCouterText->updateContent(str.str(), renderer);
	str.str(string{});
	str << counters[3];
	mBoulderCouterText->updateContent(str.str(), renderer);
	str.str(string{});
	str << counters[4];
	mBushCouterText->updateContent(str.str(), renderer);
}

void InformationPanel::setPos(const glm::vec2& pos)
{
	mPos = pos;
}
