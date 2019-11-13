#include "Wookie.h"
#include "Game.h"
#include "Util.h"
#include "GLM/gtx/rotate_vector.hpp"
#include "PlayScene.h"
#include "GLM/gtx/string_cast.hpp"


Wookie::Wookie() :
	m_locationX(50.0f), m_locationY(500.0f)
{
	TheTextureManager::Instance()->load("../Assets/textures/wookie.png",
		"wookie", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("wookie");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(m_locationX, m_locationY));
}

Wookie::Wookie(float locationX, float locationY) :
	m_locationX(locationX), m_locationY(locationY)
{
	TheTextureManager::Instance()->load("../Assets/textures/wookie.png",
		"wookie", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("wookie");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(m_locationX, m_locationY));
}

Wookie::~Wookie()
{
}

void Wookie::draw()
{
	float xComponent = getPosition().x;
	float yComponent = getPosition().y;
	TheTextureManager::Instance()->draw("wookie", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0.0f, 255, true);
}

void Wookie::update()
{
	// I dont think we need update here
}

void Wookie::clean()
{
	// Nothing to clean as of now
}
