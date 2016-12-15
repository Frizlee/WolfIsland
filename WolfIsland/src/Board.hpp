#pragma once
#include "Prerequisites.hpp"
#include "Sprite.hpp"
#include "VertexBuffer.hpp"
#include "gl_core_3_3.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

class Board
{
public:
	Board();
	
	Board(std::uint32_t width, std::uint32_t height, 
		std::shared_ptr<class SpriteSheet> spriteSheet, class Renderer& renderer);
	void create(std::uint32_t width, std::uint32_t height, 
		std::shared_ptr<class SpriteSheet> spriteSheet, class Renderer& renderer);
	
	~Board();

	void draw(class Renderer& renderer);

	const std::vector<std::shared_ptr<class GameObject>>& getObjects() const;
	std::vector<std::shared_ptr<class GameObject>> getObjects(const glm::tvec2<std::int32_t>& pos, 
		bool saved = true);
	std::vector<std::shared_ptr<class GameObject>> getSurroundingObjects(
		const glm::tvec2<std::int32_t>& pos);
	void addGameObject(std::shared_ptr<class GameObject>& object);
	std::uint32_t getWidth() const;
	std::uint32_t getHeight() const;

	void spawnWolf(glm::tvec2<std::int32_t> pos);
	void spawnHare(glm::tvec2<std::int32_t> pos);

	const std::array<std::int32_t, 5>& getObjectCounters();
	bool isCountersChanged();

	void updateTurn(class Application& app);

private:
	std::uint32_t mWidth;
	std::uint32_t mHeight;
	
	std::vector<std::shared_ptr<class GameObject>> mObjects;
	std::stack<glm::tvec2<std::int32_t>> mHareSpawnStack;
	std::stack<glm::tvec2<std::int32_t>> mWolfSpawnStack;

	std::array<std::int32_t, 5> mObjectCounters;
	bool mIsCountersChanged;

	// Resources
	std::vector<std::shared_ptr<VertexBuffer<PositionVertexLayout>>> mTileMap;
	std::shared_ptr<SpriteSheet> mSpriteSheet;
};

