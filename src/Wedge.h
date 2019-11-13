#pragma once
#ifndef __Wedge__
#define __Wedge__

#include <vector>
#include "DisplayObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"
#include "Scene.h"

class Wedge :
	public DisplayObject
{
public:
	Wedge();
	Wedge(float, float, float, float);
	~Wedge();

	// Inherited via GameObject
	void draw() override;

	void update() override;

	void clean() override;

	float getRiseAngle();
	glm::vec2 getWedgePosition();

private:
	float m_friction;
	float m_run;
	float m_rise;
	float m_hyp;
	float m_locationX;
	float m_locationY;
	float m_riseAngle;

	void find_angle(float, float, float);
	void calc_hyp(float, float);
};


#endif

