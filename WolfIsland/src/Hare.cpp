#include "Hare.hpp"
#include "Sprite.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include "Renderer.hpp"
#include "Application.hpp"
#include "Board.hpp"
using namespace std;

static const float transitionTime{ 0.5f };
static const int32_t splitChance{ 10 };
static const string objectType{ "hare" };
static const uint32_t splitTourTime{ 5 };
static const uint32_t maxLifeTours{ 20 };
static const uint32_t minLifeTours{ 15 };
static const float corpseTime{ 5.0f };


Hare::Hare()
	: GameObject{}, mTransitionTimer{ 0.5f }, mSplitTourTimer{ splitTourTime }, mIsEaten{ false },
	mCorpseTimer{ corpseTime }
{
	mType = objectType;
}

Hare::Hare(shared_ptr<SpriteSheet> spriteSheet)
	: GameObject{}, mTransitionTimer{ 0.5f }, mSplitTourTimer{ splitTourTime }, mIsEaten{ false },
	mCorpseTimer{ corpseTime }
{
	mType = objectType;
	create(spriteSheet);
}

void Hare::create(shared_ptr<SpriteSheet> spriteSheet)
{
	// Move forward
	mAnimations[0].create(spriteSheet, { 0, 1, 2 }, 1.0);

	// Move backwards
	mAnimations[1].create(spriteSheet, { 3, 4, 5 }, 1.0);

	// Move left
	mAnimations[2].create(spriteSheet, { 6, 7, 8 }, 1.0);

	// Move right
	mAnimations[3].create(spriteSheet, { 9, 10, 11 }, 1.0);

	// Idle front
	mAnimations[4].create(spriteSheet, { 0 }, 1.0);

	// Idle back
	mAnimations[5].create(spriteSheet, { 3 }, 1.0);

	// Idle left
	mAnimations[6].create(spriteSheet, { 7 }, 1.0);

	// Idle right
	mAnimations[7].create(spriteSheet, { 10 }, 1.0);

	// Idle eaten
	mAnimations[8].create(spriteSheet, { 12 }, 1.0);

	mCurrentAnimation = 4;
	mCurrentIdle = 4;
	mAnimations[4].start();
	mLifeTours = uniform_int_distribution<uint32_t>{ minLifeTours, maxLifeTours }(
		Application::randomDev);
	mActive = true;
}

Hare::~Hare()
{
}

const glm::vec2& Hare::getRealPos()
{
	return mRealPos;
}

void Hare::draw(Renderer& renderer) const
{
	auto pos = mRealPos + mRandomDisorder;

	renderer.prepareDrawSprite();
	renderer.drawSprite(*(mAnimations[mCurrentAnimation].getCurrentSprite().lock()),
		glm::translate(glm::vec3{ pos.x, pos.y, 0.0f }));
}

void Hare::updateMove(Board& board)
{
	glm::tvec2<int32_t> maxPos{ board.getWidth() - 1, board.getHeight() - 1 };
	auto surrObjects{ board.getSurroundingObjects(mPos) };
	vector<glm::tvec2<int32_t>> movePosVec;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			auto movePos{ mPos + glm::tvec2<int32_t>{i, j} };


			if (movePos.x < 0 || movePos.y < 0 || movePos.x > maxPos.x || movePos.y > maxPos.y)
				continue;

			bool canMove = true;

			for (auto& obj : surrObjects)
			{
				if (obj->getSavedPos() == movePos)
				{
					// Put other objects relations
				}
			}

			if (canMove)
				movePosVec.push_back(movePos);
		}
	}

	// Can't move.
	if (movePosVec.size() == 0)
		return;

	uniform_int_distribution<int32_t> dist{ 0, static_cast<int32_t>(movePosVec.size() - 1) };


	mTransitionStartPos = glm::vec2{ mPos.x * Application::spriteSize,
		mPos.y * Application::spriteSize };
	mTransitionTimer = 0.0f;

	auto newPos = movePosVec.at(dist(Application::randomDev));

	// Avoid animation change
	if (newPos == mPos)
		return;

	mPos = newPos;

	// Animation controling
	auto direction = glm::vec2{ mPos.x * Application::spriteSize,
		mPos.y * Application::spriteSize } -mTransitionStartPos;

	if (direction.x < 0.0f)
	{
		mAnimations[mCurrentAnimation].stop();
		mAnimations[2].reset();
		mAnimations[2].start();
		mCurrentAnimation = 2;
		mCurrentIdle = 6;
	}
	else if (direction.x > 0.0f)
	{
		mAnimations[mCurrentAnimation].stop();
		mAnimations[3].reset();
		mAnimations[3].start();
		mCurrentAnimation = 3;
		mCurrentIdle = 7;
	}
	else if (direction.y < 0.0f)
	{
		mAnimations[mCurrentAnimation].stop();
		mAnimations[0].reset();
		mAnimations[0].start();
		mCurrentAnimation = 0;
		mCurrentIdle = 4;
	}
	else if (direction.y > 0.0f)
	{
		mAnimations[mCurrentAnimation].stop();
		mAnimations[1].reset();
		mAnimations[1].start();
		mCurrentAnimation = 1;
		mCurrentIdle = 5;
	}
}

void Hare::updateAction(Board& board)
{
	uniform_int_distribution<int32_t> dist{ 0, 100 };

	if (mSplitTourTimer == 0 && dist(Application::randomDev) < splitChance)
	{
		board.spawnHare(mPos);
		mSplitTourTimer = splitTourTime;
	}

	if (mSplitTourTimer > 0)
		mSplitTourTimer--;

	mLifeTours--;

	if (mLifeTours == 0)
	{
		setActive(false);

		// TODO: death animation
		mCurrentIdle = 8;
	}
}

void Hare::update(float deltaTime)
{
	if (mActive)
	{
		if (mTransitionTimer < transitionTime)
		{
			glm::vec2 transitionEndPos{ mPos.x * Application::spriteSize,
				mPos.y * Application::spriteSize };

			mRealPos = glm::mix(mTransitionStartPos, transitionEndPos,
				mTransitionTimer / transitionTime);

			mTransitionTimer += deltaTime;

			if (mTransitionTimer >= transitionTime)
			{
				mAnimations[mCurrentAnimation].stop();
				mAnimations[mCurrentIdle].start();
				mCurrentAnimation = mCurrentIdle;
			}
		}
	}
	else
	{
		if (mCurrentAnimation != mCurrentIdle)
		{
			mAnimations[mCurrentAnimation].stop();
			mAnimations[mCurrentIdle].start();
			mCurrentAnimation = mCurrentIdle;
		}

		if (mCorpseTimer <= 0.0f)
			mReadyToDelete = true;

		mCorpseTimer -= deltaTime;
	}

	mAnimations[mCurrentAnimation].update(deltaTime);
}

void Hare::setPos(const glm::tvec2<int32_t>& pos)
{
	mPos = pos;
	mRealPos = glm::vec2{ pos.x * Application::spriteSize, pos.y * Application::spriteSize };

	uniform_real_distribution<float> dist{ 0.0f, Application::spriteSize / 4.0f };
	mRandomDisorder = glm::vec2{ dist(Application::randomDev) - Application::spriteSize / 4.0f,
		dist(Application::randomDev) };
}

void Hare::setEaten(bool state)
{
	mIsEaten = state;

	if (state)
	{
		mActive = false;
		/*mAnimations[mCurrentAnimation].stop();
		mAnimations[8].start();
		mCurrentAnimation = 8;*/
		mCurrentIdle = 8;
	}
}

bool Hare::isEaten()
{
	return mIsEaten;
}


