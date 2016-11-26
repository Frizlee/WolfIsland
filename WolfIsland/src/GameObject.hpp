#pragma once
#include "Prerequisites.hpp"
#include "gl_core_3_3.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = 0;


	virtual void draw(class Renderer& renderer) const = 0;

	virtual void updateMove(class Board& board) = 0;
	virtual void updateAction(class Board& board) = 0;
	virtual void update(float deltaTime) = 0;

	void saveCurrentPos();
	const glm::tvec2<std::int32_t>& getPos() const;
	const glm::tvec2<std::int32_t>& getSavedPos() const;
	virtual void setPos(const glm::tvec2<std::int32_t>& pos) = 0;
	const std::string& getObjectType();
	void setActive(bool state);
	bool isActive() const;
	bool isReadyToDelete() const;

protected:
	std::string mType;
	glm::tvec2<std::int32_t> mPos;
	glm::tvec2<std::int32_t> mSavedPos;
	bool mActive;
	bool mReadyToDelete;
};

