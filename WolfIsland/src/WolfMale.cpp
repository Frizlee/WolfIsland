#include "WolfMale.hpp"
#include "Sprite.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include "Renderer.hpp"
#include "Application.hpp"
#include "Board.hpp"
#include "Hare.hpp"
#include "WolfFemale.hpp"
using namespace std;

static const float transitionTime{ 1.0f };
static const string objectType{ "wolf_male" };
static const uint32_t mateTourTime{ 5 };
static const float fatLoss{ 0.05f };
static const float corpseTime{ 5.0f };


WolfMale::WolfMale()
	: GameObject{}, mTransitionTimer { 1.0f }, mChaseHare{ false }, mFat{ 1.0f }, 
	mMateTourTimer{ mateTourTime }, mCorpseTimer{ corpseTime }
{
	mType = objectType;
}

WolfMale::WolfMale(shared_ptr<SpriteSheet> spriteSheet)
	: GameObject{}, mTransitionTimer { 1.0f }, mChaseHare{ false }, mFat{ 1.0f }, 
	mMateTourTimer{ mateTourTime }, mCorpseTimer{ corpseTime }
{
	mType = objectType;
	create(spriteSheet);
}

void WolfMale::create(shared_ptr<SpriteSheet> spriteSheet)
{
	// Move forward
	mAnimations[0].create(spriteSheet, { 0, 1 }, 0.5);

	// Move backwards
	mAnimations[1].create(spriteSheet, { 2, 3 }, 0.5);

	// Move left
	mAnimations[2].create(spriteSheet, { 4, 5, 6, 7 }, 1.0);

	// Move right
	mAnimations[3].create(spriteSheet, { 8, 9, 10, 11 }, 1.0);

	// Idle front
	mAnimations[4].create(spriteSheet, { 12, 13, 14, 15, 16, 15, 14, 13 }, 3.0); 

	// Idle back
	mAnimations[5].create(spriteSheet, { 17, 18 }, 1.0);

	// Idle left
	mAnimations[6].create(spriteSheet, { 19, 20 }, 4.0);

	// Idle right
	mAnimations[7].create(spriteSheet,	{ 21, 22 }, 4.0);

	// Idle Eat
	mAnimations[8].create(spriteSheet, { 23, 24, 23, 25 }, 2.0);
	mAnimations[8].setRepeat(false);

	// Idle Death
	mAnimations[9].create(spriteSheet, { 25 }, 1.0);

	mCurrentAnimation = 4;
	mCurrentIdle = 4;
	mAnimations[4].start();

	mActive = true;
}

WolfMale::~WolfMale()
{
}


const glm::vec2& WolfMale::getRealPos()
{
	return mRealPos;
}

void WolfMale::draw(Renderer& renderer) const
{
	auto pos = mRealPos + mRandomDisorder;

	renderer.prepareDrawSprite();
	renderer.drawSprite(*(mAnimations[mCurrentAnimation].getCurrentSprite().lock()), 
		glm::translate(glm::vec3{ pos.x, pos.y, 0.0f }));
}

void WolfMale::updateMove(Board& board)
{
	glm::tvec2<int32_t> maxPos{ board.getWidth() - 1, board.getHeight() - 1 };
	auto surrObjects{ board.getSurroundingObjects(mPos) };
	vector<glm::tvec2<int32_t>> movePosVec;
	int harePos = -1;
	int wolfFemalePos = -1;

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
					if (obj->getObjectType() == "boulder" || obj->getObjectType() == "bush")
					{
						canMove = false;
						harePos = -1;
						wolfFemalePos = -1;
						break;
					}
					else if (obj->getObjectType() == "hare")
						harePos = movePosVec.size();
					else if (mMateTourTimer == 0 && obj->getObjectType() == "wolf_female")
					{
						if (dynamic_pointer_cast<WolfFemale>(obj)->canPup())
							wolfFemalePos = movePosVec.size();
					}					
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

	glm::tvec2<int32_t> newPos;

	if (harePos != -1)
	{
		newPos = movePosVec.at(harePos);
		mChaseHare == true;
	}
	else
		newPos = movePosVec.at(wolfFemalePos != -1 ? wolfFemalePos : dist(Application::randomDev));

	// Avoid animation change
	if (newPos == mPos)
		return;

	mPos = newPos;

	// Animation controling
	auto direction = glm::vec2{ mPos.x * Application::spriteSize, 
		mPos.y * Application::spriteSize } - mTransitionStartPos;
	
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

void WolfMale::updateAction(Board& board)
{
	shared_ptr<Hare> hare;
	shared_ptr<WolfFemale> wolfFemale;

	for (auto& obj : board.getObjects(mPos))
	{
		if (obj->getObjectType() == "hare")
		{
			hare = dynamic_pointer_cast<Hare>(obj);
			if (!hare->isEaten())
			{
				hare->setEaten(true);
				mChaseHare = false;
				mFat = 1.0f;
				mCurrentIdle = 8;
			}
		}
		else if (mChaseHare)
			mFat -= fatLoss;
		else if (obj->getObjectType() == "wolf_female")
			wolfFemale = dynamic_pointer_cast<WolfFemale>(obj);
	}

	mFat -= fatLoss;

	if (!hare && wolfFemale)
	{
		wolfFemale->pup(board);
		mMateTourTimer = mateTourTime;
	}

	if (mFat <= 0.0f)
	{
		setActive(false);

		// TODO: death animation
		mCurrentIdle = 9;
	}

	if (mMateTourTimer > 0)
		mMateTourTimer--;
}

void WolfMale::update(float deltaTime)
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

void WolfMale::setPos(const glm::tvec2<std::int32_t>& pos)
{
	mPos = pos;
	mRealPos = glm::vec2{ pos.x * Application::spriteSize, pos.y * Application::spriteSize };

	uniform_real_distribution<float> dist{ 0.0f, Application::spriteSize / 4.0f };
	mRandomDisorder = glm::vec2{ dist(Application::randomDev) - Application::spriteSize / 4.0f, 
		dist(Application::randomDev) };
}
