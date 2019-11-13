#include "Detonator.h"
#include "Game.h"
#include "Util.h"
#include "GLM/gtx/rotate_vector.hpp"
#include "PlayScene.h"
#include "GLM/gtx/string_cast.hpp"


Detonator::Detonator()
{
	TheTextureManager::Instance()->load("../Assets/textures/detonator.png",
		"detonator", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("detonator");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(50.0f, 500.0f));
}

Detonator::~Detonator()
{
}

void Detonator::draw()
{
	float xComponent = getPosition().x;
	float yComponent = getPosition().y;
	TheTextureManager::Instance()->draw("detonator", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0.0f, 255, true);
}

void Detonator::update()
{
	// Will be handled in move - StartScene
}

void Detonator::clean()
{
	// Nothing to clean as of now
}
