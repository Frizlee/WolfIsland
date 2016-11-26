#include "SpriteSheet.hpp"
#include "Sprite.hpp"
using namespace std;

SpriteSheet::SpriteSheet()
{
}

SpriteSheet::SpriteSheet(const vector<shared_ptr<Sprite>>& sprites)
{
	create(sprites);
}

void SpriteSheet::create(const vector<shared_ptr<Sprite>>& sprites)
{
	if (sprites.empty())
		return;

	auto tex = sprites[0]->getTexture();

	for (auto& i : sprites)
	{
		if (i->getTexture().lock() != tex.lock())
			return;
	}

	mSprites = sprites;
}

SpriteSheet::~SpriteSheet()
{
}

uint32_t SpriteSheet::addSprite(shared_ptr<Sprite> sprite)
{
	if (mSprites.empty() || mSprites[0]->getTexture().lock() == sprite->getTexture().lock())
		mSprites.push_back(sprite);

	return mSprites.size() - 1;
}

weak_ptr<const class Texture> SpriteSheet::getTexture() const
{
	if (mSprites.empty())
		return shared_ptr<Texture>{};

	return mSprites[0]->getTexture();
}

std::weak_ptr<const class Sprite> SpriteSheet::getSprite(std::uint32_t index) const
{
	return mSprites.at(index);
}

weak_ptr<const VertexArray> SpriteSheet::getVao() const
{
	if (mSprites.empty())
		return shared_ptr<VertexArray>{};

	return mSprites[0]->getVao();
}

weak_ptr<VertexArray> SpriteSheet::getVao()
{
	if (mSprites.empty())
		return shared_ptr<VertexArray>{};

	return mSprites[0]->getVao();
}

const glm::vec2& SpriteSheet::getBounds()
{
	if (mSprites.empty())
		return glm::vec2{ 0.0f, 0.0f };

	return mSprites[0]->getBounds();
}
