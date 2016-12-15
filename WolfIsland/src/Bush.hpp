#pragma once
#include "Prerequisites.hpp"
#include "GameObject.hpp"

class Bush :	public GameObject
{
public:
	Bush();
	Bush(std::shared_ptr<class Sprite> boulderSprite);
	void create(std::shared_ptr<class Sprite> boulderSprite);

	~Bush();

	const glm::vec2& getRealPos();

	void draw(class Renderer& renderer) const override;

	void updateMove(class Board& board) override;
	void updateAction(class Board& board) override;
	void update(float deltaTime) override;
	void setPos(const glm::tvec2<std::int32_t>& pos);

private:
	glm::vec2 mRealPos;

	// Resources
	std::shared_ptr<class Sprite> mSprite;
};

