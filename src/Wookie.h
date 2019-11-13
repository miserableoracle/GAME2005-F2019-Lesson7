#pragma once
#ifndef __Wookie__
#define __Wookie__

#include <vector>
#include "DisplayObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"
#include "Scene.h"

class Wookie :
	public DisplayObject
{
public:
	Wookie();
	Wookie(float, float);
	~Wookie();

	// Inherited via GameObject
	void draw() override;

	void update() override;

	void clean() override;

private:
	float m_locationX;
	float m_locationY;
};


#endif

