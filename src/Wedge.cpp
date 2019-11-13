#include "Wedge.h"
#include "Game.h"
#include "Util.h"
#include "GLM/gtx/rotate_vector.hpp"
#include "PlayScene.h"
#include "GLM/gtx/string_cast.hpp"


Wedge::Wedge() :
	m_friction(0.0f), m_run(4.0f), m_rise(3.0f), m_hyp(0.0f), m_locationX(200.0f), m_locationY(500.0f), m_riseAngle(0)
{
	setPosition(glm::vec2(m_locationX, m_locationY));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::WEDGE);
	setState(State::IDLE);
	calc_hyp(m_run, m_rise);
	find_angle(m_rise, m_hyp, 90.0f);
}

Wedge::Wedge(float locationX, float locationY, float run, float rise) :
	m_friction(0.0f), m_run(run), m_rise(rise), m_hyp(0.0f), m_locationX(locationX), m_locationY(locationY), m_riseAngle(0) 
{
	setPosition(glm::vec2(m_locationX, m_locationY));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::WEDGE);
	setState(State::IDLE);
	calc_hyp(m_run, m_rise);
	find_angle(m_rise, m_hyp, 90.0f);
}

Wedge::~Wedge()
{
}

void Wedge::draw()
{
	float xComponent = getPosition().x;
	float yComponent = getPosition().y;
	float PPM = 100.0f;
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
	// Taking one meter = 100 PPM
	// Drawing run
	SDL_RenderDrawLine(TheGame::Instance()->getRenderer(), xComponent, yComponent, xComponent + (m_run * PPM), yComponent);
	// Drawing rise
	SDL_RenderDrawLine(TheGame::Instance()->getRenderer(), xComponent + (m_run * PPM), yComponent, xComponent + (m_run * PPM), yComponent - (m_rise * PPM));
	// Drawing Hyp
	SDL_RenderDrawLine(TheGame::Instance()->getRenderer(), xComponent, yComponent, xComponent + (m_run * PPM), yComponent - (m_rise * PPM));
}

void Wedge::update()
{
	// I dont think we need update here
}

void Wedge::clean()
{
	// Nothing to clean as of now
}

void Wedge::calc_hyp(float run, float rise) {
	m_hyp = sqrt((run*run) + (rise*rise));
}

void Wedge::find_angle(float aSide, float bSide, float bAngle) {
	// Applying sin laws
	// a/Sin A = b/Sin B
	m_riseAngle = (aSide * sinf(bAngle)) / bSide;
}

float Wedge::getRiseAngle() {
	return m_riseAngle;
}

glm::vec2 Wedge::getWedgePosition() {
	float xComponent = getPosition().x;
	float yComponent = getPosition().y;
	return glm::vec2(xComponent, yComponent);
}