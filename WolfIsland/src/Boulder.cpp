#include "Boulder.hpp"
#include "Renderer.hpp"
#include "Application.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
using namespace std;

static const string objectType{ "boulder" };

Boulder::Boulder() 
	: GameObject{}
{
	mType = objectType;
}

Boulder::Boulder(std::shared_ptr<class Sprite> boulderSprite)
	: GameObject{}
{
	mType = objectType;
	create(boulderSprite);
}

void Boulder::create(std::shared_ptr<class Sprite> boulderSprite)
{
	mSprite = boulderSprite;
}


Boulder::~Boulder()
{
}

const glm::vec2& Boulder::getRealPos()
{
	return mRealPos;
}

void Boulder::draw(Renderer& renderer) const
{
	renderer.prepareDrawSprite();
	renderer.drawSprite(*mSprite, glm::translate(glm::vec3{ mRealPos.x, mRealPos.y, 0.0f }));
}

void Boulder::updateMove(Board & board)
{
	// Boulder can't move
}

void Boulder::updateAction(Board & board)
{
	// Boulder do nothing
}

void Boulder::update(float deltaTime)
{
	// Boulder has no animation
}

void Boulder::setPos(const glm::tvec2<int32_t>& pos)
{
	mPos = pos;
	mSavedPos = pos;
	mRealPos = glm::vec2{ pos.x * Application::spriteSize, pos.y * Application::spriteSize };
	mActive = true;
}
