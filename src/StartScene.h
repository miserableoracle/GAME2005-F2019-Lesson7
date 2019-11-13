#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "ship.h"
#include "Wedge.h"
#include "Wookie.h"
#include "StormTrooper.h"
#include "Detonator.h"
#include <cmath>

class StartScene : public Scene
{
public:
	StartScene();
	~StartScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	/*Label* m_pStartLabel;
	Label* m_pInstructionsLabel;*/

	Ship* m_pShip;
	Wedge m_platform;
	Wookie m_wookie;
	
	StormTrooper m_stormtroop;
	StormTrooper m_stormtroop2;
	StormTrooper m_stormtroop3;
	StormTrooper m_stormtroop4;
	StormTrooper m_stormtroop5;

	Detonator* m_detonator;
	Label* m_pInstructionsLabel;
	Label* m_pLabels[10];
	// ----------- IMGUI ---------------
	glm::vec2 m_mousePosition;
	glm::vec2 m_initialPos;
	SDL_Color blue = { 0, 0, 255, 255 };

	// ImGui utility functions
	void m_ImGuiKeyMap();
	void m_ImGuiSetStyle();
	void m_updateUI();

	// ImGui menu variables
	bool m_exitApp = false;
	bool m_displayAbout = false;
	bool m_displayUI = true;

	// Physics variables
	const float Deg2Rad = 0.0174532925f;
	const float Rad2Deg = 57.2957795130f;
	bool m_isGravityEnabled = false;
	float m_gravity = 9.8f;
	float m_PPM = 10.01f;	// Pixels per meter - scale

	glm::vec2 m_finalPosition = glm::vec2(0.0f, 0.0f);
	float m_velocity = 100.0f;
	float m_velocityX = 0.0f;
	float m_velocityY = 0.0f;
	glm::vec2 m_acceleration = glm::vec2(0.0f, 0.0f);

	float m_time = 0.016667f;		// Approx. 16 ms
	float m_Atime = 0.016667f;		// Accumulated time

	float m_angle = 14.67f;	// The "kicking" Angle
	// Physics Functions
	void m_move();
};	

#endif /* defined (__START_SCENE__) */