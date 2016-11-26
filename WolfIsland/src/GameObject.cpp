#include "GameObject.hpp"


GameObject::GameObject()
	: mReadyToDelete{ false }
{
}


GameObject::~GameObject()
{
}

void GameObject::saveCurrentPos()
{
	mSavedPos = mPos;
}

const glm::tvec2<std::int32_t>& GameObject::getPos() const
{
	return mPos;
}

const glm::tvec2<std::int32_t>& GameObject::getSavedPos() const
{
	return mSavedPos;
}

const std::string& GameObject::getObjectType()
{
	return mType;
}

void GameObject::setActive(bool state)
{
	mActive = state;
}

bool GameObject::isActive() const
{
	return mActive;
}

bool GameObject::isReadyToDelete() const
{
	return mReadyToDelete;
}

