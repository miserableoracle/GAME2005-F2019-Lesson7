#include "StormTrooper.h"
#include "Game.h"
#include "Util.h"
#include "GLM/gtx/rotate_vector.hpp"
#include "PlayScene.h"
#include "GLM/gtx/string_cast.hpp"


StormTrooper::StormTrooper() :
	m_locationX(500.0f), m_locationY(500.0f)
{
	TheTextureManager::Instance()->load("../Assets/textures/stormtrooper.png",
		"stormtrooper", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("stormtrooper");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(m_locationX, m_locationY));
}

StormTrooper::StormTrooper(float locationX, float locationY) :
	m_locationX(locationX), m_locationY(locationY)
{
	TheTextureManager::Instance()->load("../Assets/textures/stormtrooper.png",
		"stormtrooper", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("stormtrooper");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(m_locationX, m_locationY));
}

StormTrooper::~StormTrooper()
{
}

void StormTrooper::draw()
{
	float xComponent = getPosition().x;
	float yComponent = getPosition().y;
	TheTextureManager::Instance()->draw("stormtrooper", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0.0f, 255, true);
}

void StormTrooper::update()
{
	// I dont think we need update here
}

void StormTrooper::clean()
{
	// Nothing to clean as of now
}
