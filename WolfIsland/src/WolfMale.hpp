#pragma once
#include "Prerequisites.hpp"
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include "gl_core_3_3.hpp"
#include "GameObject.hpp"
#include "FlipbookAnimation.hpp"


class WolfMale : public GameObject
{
public:
	WolfMale();
	WolfMale(std::shared_ptr<class SpriteSheet> spriteSheet);
	void create(std::shared_ptr<class SpriteSheet> spriteSheet);

	~WolfMale();
	
	const glm::vec2& getRealPos();

	void draw(class Renderer& renderer) const override;

	void updateMove(class Board& board) override;
	void updateAction(class Board& board) override;
	void update(float deltaTime) override;
	void setPos(const glm::tvec2<std::int32_t>& pos);

private:
	glm::vec2 mRealPos;
	glm::vec2 mRandomDisorder;

	// Animations
	std::array<FlipbookAnimation, 10> mAnimations;
	std::uint32_t mCurrentAnimation;
	std::uint32_t mCurrentIdle;
	glm::vec2 mTransitionStartPos;
	float mTransitionTimer;
	float mCorpseTimer;

	// Logic
	bool mChaseHare;
	float mFat;
	std::uint32_t mMateTourTimer;
};

