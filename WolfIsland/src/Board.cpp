#include "Board.hpp"
#include "Renderer.hpp"
#include "Image.hpp"
#include "Texture.hpp"
#include "PngCodec.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexLayout.hpp"
#include "GameObject.hpp"
#include "Application.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
using namespace std;

static const string groundSpriteSheetName{ "GroundSpriteSheet.png" };


Board::Board()
{
}

Board::Board(uint32_t width, uint32_t height, shared_ptr<SpriteSheet> spriteSheet, 
	Renderer& renderer)
{
	create(width, height, spriteSheet, renderer);
}

void Board::create(uint32_t width, uint32_t height, shared_ptr<SpriteSheet> spriteSheet, 
	Renderer& renderer)
{
	mWidth = width;
	mHeight = height;
	mSpriteSheet = spriteSheet;

	vector<PositionVertexLayout::Data> vec;

	// lower left tile
	vec.clear();
	vec.push_back({ -Application::spriteSize, -Application::spriteSize, 0.0f });
	mTileMap.push_back(make_shared<VertexBuffer<PositionVertexLayout>>(
		vec.size(), renderer));
	mTileMap.back()->add(vec, renderer);
	

	// lower middle tile
	vec.clear();

	for (int x = 0; x < mWidth; x++)
		vec.push_back({ x * Application::spriteSize, -Application::spriteSize, 0.0f });

	mTileMap.push_back(make_shared<VertexBuffer<PositionVertexLayout>>(
		vec.size(), renderer));
	mTileMap.back()->add(vec, renderer);
	

	// lower right tile
	vec.clear();
	vec.push_back({ mWidth * Application::spriteSize, -Application::spriteSize, 0.0f });
	mTileMap.push_back(make_shared<VertexBuffer<PositionVertexLayout>>(
		vec.size(), renderer));
	mTileMap.back()->add(vec, renderer);


	// middle left tile
	vec.clear();

	for (int y = 0; y < mHeight; y++)
		vec.push_back({ -Application::spriteSize, y * Application::spriteSize, 0.0f });

	mTileMap.push_back(make_shared<VertexBuffer<PositionVertexLayout>>(
		vec.size(), renderer));
	mTileMap.back()->add(vec, renderer);


	// center tile
	vec.clear();

	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
			vec.push_back({ x * Application::spriteSize, y * Application::spriteSize, 0.0f });
	}
	
	mTileMap.push_back(make_shared<VertexBuffer<PositionVertexLayout>>(
		vec.size(), renderer));
	mTileMap.back()->add(vec, renderer);


	// middle right tile
	vec.clear();

	for (int y = 0; y < mHeight; y++)
		vec.push_back({ mWidth * Application::spriteSize, 
			y * Application::spriteSize, 0.0f });

	mTileMap.push_back(make_shared<VertexBuffer<PositionVertexLayout>>(
		vec.size(), renderer));
	mTileMap.back()->add(vec, renderer);


	// upper left tile
	vec.clear();
	vec.push_back({ -Application::spriteSize, mHeight * Application::spriteSize, 0.0f });
	mTileMap.push_back(make_shared<VertexBuffer<PositionVertexLayout>>(
		vec.size(), renderer));
	mTileMap.back()->add(vec, renderer);

	// upper middle tile
	vec.clear();

	for (int x = 0; x < mWidth; x++)
		vec.push_back({ x * Application::spriteSize, 
			mHeight * Application::spriteSize, 0.0f });

	mTileMap.push_back(make_shared<VertexBuffer<PositionVertexLayout>>(
		vec.size(), renderer));
	mTileMap.back()->add(vec, renderer);

	// upper right tile
	vec.clear();
	vec.push_back({ mWidth * Application::spriteSize, 
		mHeight * Application::spriteSize, 0.0f });
	mTileMap.push_back(make_shared<VertexBuffer<PositionVertexLayout>>(
		vec.size(), renderer));
	mTileMap.back()->add(vec, renderer);
}


Board::~Board()
{
}

void Board::draw(Renderer& renderer)
{
	renderer.prepareDrawSpriteInstanced();

	auto vao = mSpriteSheet->getVao().lock();

	for (int i = 0; i < mTileMap.size(); i++)
	{
		vao->addInstanceBuffer(mTileMap[i], renderer);
		renderer.drawSpriteInstanced(*mSpriteSheet->getSprite(i).lock(), glm::mat4{ 1.0f }, 
			mTileMap[i]->getElementsCount());
	}
}

const vector<shared_ptr<GameObject>>& Board::getObjects() const
{
	return mObjects;
}

void Board::addGameObject(shared_ptr<GameObject>& object)
{
	mObjects.push_back(object);
}

uint32_t Board::getWidth() const
{
	return mWidth;
}

uint32_t Board::getHeight() const
{
	return mHeight;
}

void Board::spawnWolf(glm::tvec2<int32_t> pos)
{
	mWolfSpawnStack.push(pos);
}

void Board::spawnHare(glm::tvec2<int32_t> pos)
{
	mHareSpawnStack.push(pos);
}

void Board::updateTurn(Application& app)
{
	for (auto it{ begin(mObjects) }; it != end(mObjects);)
	{
		if ((*it)->isReadyToDelete())
			it = mObjects.erase(it);
		else
			it++;
	}

	while (!mHareSpawnStack.empty())
	{
		app.spawnHare(mHareSpawnStack.top());
		mHareSpawnStack.pop();
	}

	while (!mWolfSpawnStack.empty())
	{
		app.spawnWolf(mWolfSpawnStack.top());
		mWolfSpawnStack.pop();
	}
}

vector<shared_ptr<GameObject>> Board::getSurroundingObjects(const glm::tvec2<int32_t>& pos)
{
	vector<shared_ptr<GameObject>> vec;

	for (auto& obj : mObjects)
	{
		auto absDiff{ glm::abs(obj->getPos() - pos) };

		if (obj->isActive() && (absDiff.x == 1 || absDiff.y == 1))
			vec.push_back(obj);
	}
	
	return vec;
}

vector<shared_ptr<GameObject>> Board::getObjects(const glm::tvec2<int32_t>& pos)
{
	vector<shared_ptr<GameObject>> vec;

	for (auto& obj : mObjects)
	{
		if (obj->isActive() && obj->getPos() == pos)
			vec.push_back(obj);
	}

	return vec;
}


