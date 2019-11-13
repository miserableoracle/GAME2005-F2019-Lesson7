#pragma once
#ifndef __StormTrooper__
#define __StormTrooper__

#include <vector>
#include "DisplayObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"
#include "Scene.h"

class StormTrooper :
	public DisplayObject
{
public:
	StormTrooper();
	StormTrooper(float, float);
	~StormTrooper();

	// Inherited via GameObject
	void draw() override;

	void update() override;

	void clean() override;

private:
	float m_locationX;
	float m_locationY;
};


#endif

