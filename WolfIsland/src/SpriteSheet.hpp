#pragma once
#include "Prerequisites.hpp"
#include <glm/vec2.hpp>

class SpriteSheet
{
	friend class Renderer;

public:
	SpriteSheet();

	SpriteSheet(const std::vector<std::shared_ptr<class Sprite>>& sprites);
	void create(const std::vector<std::shared_ptr<class Sprite>>& sprites);
	
	~SpriteSheet();

	std::uint32_t addSprite(std::shared_ptr<class Sprite> sprite);

	std::weak_ptr<const class Texture> getTexture() const;
	std::weak_ptr<const class Sprite> getSprite(std::uint32_t index) const;
	std::weak_ptr<const class VertexArray> getVao() const;
	std::weak_ptr<class VertexArray> getVao();
	const glm::vec2& getBounds();

private:
	std::vector<std::shared_ptr<class Sprite>> mSprites;
};

