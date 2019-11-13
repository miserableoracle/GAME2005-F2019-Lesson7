#pragma once
#ifndef __Detonator__
#define __Detonator__

#include <vector>

#include "DisplayObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"
#include "Scene.h"

class Detonator :
	public DisplayObject
{
public:
	Detonator();
	~Detonator();

	// Inherited via GameObject
	void draw() override;

	void update() override;

	void clean() override;

	void move();
};


#endif /* defined (__Detonator__) */

