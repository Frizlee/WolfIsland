#include "Bush.hpp"
#include "Renderer.hpp"
#include "Application.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
using namespace std;

static const string objectType{ "bush" };

Bush::Bush() 
	: GameObject{}
{
	mType = objectType;
}

Bush::Bush(std::shared_ptr<class Sprite> bushSprite)
	: GameObject{}
{
	mType = objectType;
	create(bushSprite);
}

void Bush::create(std::shared_ptr<class Sprite> bushSprite)
{
	mSprite = bushSprite;
}


Bush::~Bush()
{
}

const glm::vec2& Bush::getRealPos()
{
	return mRealPos;
}

void Bush::draw(Renderer& renderer) const
{
	renderer.prepareDrawSprite();
	renderer.drawSprite(*mSprite, glm::translate(glm::vec3{ mRealPos.x, mRealPos.y, 0.0f }));
}

void Bush::updateMove(Board & board)
{
	// Bush can't move
}

void Bush::updateAction(Board & board)
{
	// Bush do nothing
}

void Bush::update(float deltaTime)
{
	// Bush has no animation
}

void Bush::setPos(const glm::tvec2<int32_t>& pos)
{
	mPos = pos;
	mSavedPos = pos;
	mRealPos = glm::vec2{ pos.x * Application::spriteSize, pos.y * Application::spriteSize };
	mActive = true;
}
