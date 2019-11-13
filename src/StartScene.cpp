#include "StartScene.h"
#include "Game.h"
#include <ctime>
#include "GLM/gtx/string_cast.hpp"
#include <algorithm>
#include "TileComparators.h"
#include <iomanip>
#include <string>

StartScene::StartScene() : m_stormtroop(550, 500), m_stormtroop2(590, 500), m_stormtroop3(630, 500), m_stormtroop4(670, 500), m_stormtroop5(710, 500)
{
	StartScene::start();
}

StartScene::~StartScene()
{
}

void StartScene::draw()
{
	m_wookie.draw();
	m_stormtroop.draw();
	m_stormtroop2.draw();
	m_stormtroop3.draw();
	m_stormtroop4.draw();
	m_stormtroop5.draw();
	//m_platform.draw();
	m_detonator->draw();
	m_pLabels[0]->draw();
	m_pLabels[1]->draw();
	m_pLabels[2]->draw();
	m_pLabels[3]->draw();
	
	// ImGui Rendering section - DO NOT MOVE OR DELETE
	if (m_displayUI)
	{
		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());
		SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 255, 255, 255, 255);
	}
}

void StartScene::update()
{
	if (m_isGravityEnabled) {
		m_move();
		//SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0x00, 0xFF, 0xFF, 0xFF);
		//SDL_RenderDrawPoint(TheGame::Instance()->getRenderer(), (int)m_detonator->getPosition().x, (int)m_detonator->getPosition().y);
		if (m_finalPosition.y > 510) {
			m_isGravityEnabled = false;
			glm::vec2 fPos = m_finalPosition - m_initialPos;
			std::string hdisp = "H-Displacement = ";
			hdisp += std::to_string(fPos.x);
			hdisp += " m";
			m_pLabels[3] = new Label(hdisp, "Consolas", 20, blue, glm::vec2(400.0f, 110.0f));
		}
		std::string text = "Initial Velocity(Vo) = ";
		text += std::to_string(m_velocity);
		text += " m/s";
		m_pLabels[0] = new Label(text, "Consolas", 20, blue, glm::vec2(450.0f, 20.0f));

		text = "X-Component(Vox) = ";
		text += std::to_string(m_velocityX/m_PPM);
		text += " m/s";
		m_pLabels[1] = new Label(text, "Consolas", 16, blue, glm::vec2(400.0f, 50.0f));

		text = "Y-Component(Voy) = ";
		text += std::to_string(m_velocityY/m_PPM);
		text += " m/s";
		m_pLabels[2] = new Label(text, "Consolas", 16, blue, glm::vec2(400.0f, 80.0f));
	}

	if (m_displayUI)
	{
		m_updateUI();
	}
}

void StartScene::clean()
{
	/*delete m_pStartLabel;
	delete m_pInstructionsLabel;*/

	// Delete all the label pointers
	for (int i = 0; i < 10; i++)
	{
		delete m_pLabels[i];
	}

	removeAllChildren();
}


void StartScene::handleEvents()
{
	ImGuiIO& io = ImGui::GetIO();
	int wheel = 0;

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_MOUSEWHEEL:
			wheel = event.wheel.y;
			break;
		case SDL_TEXTINPUT:
			io.AddInputCharactersUTF8(event.text.text);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_BACKQUOTE:
				m_displayUI = (m_displayUI) ? false : true;
				break;
				/************************************************************************/
			case SDLK_w:
				
				break;
			case SDLK_s:
				
				break;
			case SDLK_a:
				
				break;
			case SDLK_d:
				
				break;
			}
			{
				int key = event.key.keysym.scancode;
				IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
				io.KeysDown[key] = (event.type == SDL_KEYDOWN);
				io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
				io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
				io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
				io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				
				break;

			case SDLK_s:
				
				break;

			case SDLK_a:
				
				break;
			case SDLK_d:
				
				break;
			}
			{
				int key = event.key.keysym.scancode;
				IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
				io.KeysDown[key] = (event.type == SDL_KEYDOWN);
				io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
				io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
				io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
				io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
			}
			break;
		default:
			break;
		}
	}

	io.DeltaTime = 1.0f / 60.0f;
	int mouseX, mouseY;
	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseWheel = static_cast<float>(wheel);

	io.DisplaySize.x = 1280;
	io.DisplaySize.y = 720;

	m_ImGuiKeyMap();
	m_ImGuiSetStyle();
}

void StartScene::start()
{
	/*SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("START SCENE", "Dock51", 80, blue, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press 1 to Play", "Dock51", 40, blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel)*/

	// Initial Velocity 
	m_pLabels[0] = new Label("Initial Velocity(Vo) = 100.0 m/s", "Consolas", 20, blue, glm::vec2(400.0f, 20.0f));
	m_pLabels[0]->setParent(this);
	addChild(m_pLabels[0]);

	// Velocity X-component
	m_pLabels[1] = new Label("X-Component(Vox) = (?)", "Consolas", 16, blue, glm::vec2(400.0f, 50.0f));
	m_pLabels[1]->setParent(this);
	addChild(m_pLabels[1]);

	// Velocity Y-component
	m_pLabels[2] = new Label("Y-Component(Voy) = (?)", "Consolas", 16, blue, glm::vec2(400.0f, 80.0f));
	m_pLabels[2]->setParent(this);
	addChild(m_pLabels[2]);

	// Horizontal Displacement
	m_pLabels[3] = new Label("H-Displacement = (?)", "Consolas", 20, blue, glm::vec2(400.0f, 110.0f));
	m_pLabels[3]->setParent(this);
	addChild(m_pLabels[3]);

	m_detonator = new Detonator();
	//m_detonator->setPosition(glm::vec2(50.0f, 500.0f));
	addChild(m_detonator);
	addChild(&m_wookie);
	addChild(&m_stormtroop);
	addChild(&m_stormtroop2);
	addChild(&m_stormtroop3);
	addChild(&m_stormtroop4);
	addChild(&m_stormtroop5);

	m_initialPos = m_detonator->getPosition();
}

// ImGui functions ***********************************************

void StartScene::m_ImGuiKeyMap()
{
	ImGuiIO& io = ImGui::GetIO();

	// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
	io.KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
	io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
	io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
	io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
	io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
	io.KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
	io.KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
	io.KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
	io.KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;

	io.KeyMap[ImGuiKey_A] = SDL_SCANCODE_A;
	io.KeyMap[ImGuiKey_C] = SDL_SCANCODE_C;
	io.KeyMap[ImGuiKey_V] = SDL_SCANCODE_V;
	io.KeyMap[ImGuiKey_X] = SDL_SCANCODE_X;
	io.KeyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;
	io.KeyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;
}

void StartScene::m_ImGuiSetStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 0.8f;
	style.FrameRounding = 3.0f;
	style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void StartScene::m_updateUI()
{
	// Prepare Window Frame
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow(); // use for debug purposes

	std::string windowString = "Physics Settings";

	ImGui::Begin(&windowString[0], NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar);

	// set window to top left corner
	ImGui::SetWindowPos(ImVec2(0, 0), true);

	/*************************************************************************************************/
	/* MENU                                                                                          */
	/*************************************************************************************************/

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::Separator();
			ImGui::MenuItem("Exit", NULL, &m_exitApp);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			ImGui::Separator();
			ImGui::MenuItem("About", NULL, &m_displayAbout);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (m_exitApp)
	{
		TheGame::Instance()->quit();
	}

	if (m_displayAbout)
	{
		ImGui::Begin("About Pathfinding Simulator", &m_displayAbout, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Separator();
		ImGui::Text("Authors:");
		ImGui::Text("Hiren Pandya");
		ImGui::End();
	}

	/*************************************************************************************************/
	if (ImGui::Button("Fire!"))
	{
		m_isGravityEnabled = (m_isGravityEnabled) ? false : true;
		m_detonator->draw();
	}

	ImGui::SameLine();

	if (ImGui::Button("Reset All"))
	{
		m_isGravityEnabled = false;
		m_detonator->setPosition(glm::vec2(50.0f, 500.0f));
		m_gravity = 9.8f;
		m_PPM = 10.01f;
		m_Atime = 0.016667f;
		m_angle = 14.67f;
		m_velocity = 100.0f;
		m_velocityX = 0.0f;
		m_velocityY = 0.0f;

		for (int i = 0; i < 4; i++)
		{
			delete m_pLabels[i];
		}
		
		// Initial Velocity 
		m_pLabels[0] = new Label("Initial Velocity(Vo) = 100.0 m/s", "Consolas", 20, blue, glm::vec2(400.0f, 20.0f));
		// Velocity X-component
		m_pLabels[1] = new Label("X-Component(Vox) = (?)", "Consolas", 16, blue, glm::vec2(400.0f, 50.0f));
		// Velocity Y-component
		m_pLabels[2] = new Label("Y-Component(Voy) = (?)", "Consolas", 16, blue, glm::vec2(400.0f, 80.0f));
		// Horizontal Displacement
		m_pLabels[3] = new Label("H-Displacement = (?)", "Consolas", 20, blue, glm::vec2(400.0f, 110.0f));
	}

	ImGui::PushItemWidth(80);
	if (ImGui::SliderFloat("Gravity", &m_gravity, 0.1f, 30.0f, "%.1f"))
	{
		
	}

	if (ImGui::SliderFloat("Pixels Per Meter", &m_PPM, 1.0f, 30.0f, "%.1f"))
	{

	}

	if (ImGui::SliderFloat("Kicking Angle", &m_angle, 0.0f, 90.0f, "%.1f"))
	{

	}

	if (ImGui::SliderFloat("Velocity", &m_velocity, 0.0f, 200.0f, "%.1f"))
	{

	}

	/*if (ImGui::SliderFloat("Time Factor", &m_time, 0.000001f, 0.20f, "%.001f"))
	{

	}

	if (ImGui::SliderFloat("Time Accumulation", &m_Atime, 0.000001f, 0.20f, "%.001f"))
	{

	}*/


	//ImGui::SameLine();

	//if (ImGui::Button("Respawn Planet"))
	//{
	//	m_respawnPlanet();
	//	m_moveAlongPath = false;
	//}

	//ImGui::SameLine();

	//if (ImGui::Button("Respawn Mines"))
	//{
	//	m_respawnMines();
	//	m_moveAlongPath = false;
	//}

	//ImGui::SameLine();

	//if (ImGui::Button("Toggle Grid"))
	//{
	//	m_debugMode = (m_debugMode) ? false : true;
	//}

	//ImGui::SameLine();

	//if (ImGui::Button("Reset All"))
	//{
	//	m_resetAll();
	//}

	//ImGui::PushItemWidth(80);
	//if (ImGui::SliderFloat("Manhattan Factor", m_grid[0][0]->getManhanttanFactor(), 0.1f, 10.0f, "%.1f"))
	//{
	//	float newFactor = *m_grid[0][0]->getManhanttanFactor();

	//	for (size_t row = 0; row < m_rowSize; row++)
	//	{
	//		for (size_t col = 0; col < m_colSize; col++)
	//		{
	//			m_grid[col][row]->setManhanttanFactor(newFactor);
	//		}
	//	}
	//}

	//ImGui::SameLine();

	//if (ImGui::SliderFloat("Euclidean Factor", m_grid[0][0]->getEuclideanFactor(), 0.1f, 10.0f, "%.1f"))
	//{
	//	float newFactor = *m_grid[0][0]->getEuclideanFactor();

	//	for (size_t row = 0; row < m_rowSize; row++)
	//	{
	//		for (size_t col = 0; col < m_colSize; col++)
	//		{
	//			m_grid[col][row]->setEuclideanFactor(newFactor);
	//		}
	//	}
	//}

	//ImGui::SameLine();

	//if (ImGui::SliderFloat("Mine Factor", m_grid[0][0]->getMineFactor(), 0.1f, 10.0f, "%.1f"))
	//{
	//	float newFactor = *m_grid[0][0]->getMineFactor();

	//	for (size_t row = 0; row < m_rowSize; row++)
	//	{
	//		for (size_t col = 0; col < m_colSize; col++)
	//		{
	//			m_grid[col][row]->setMineFactor(newFactor);
	//		}
	//	}
	//}
	//ImGui::PopItemWidth();

	//if (ImGui::CollapsingHeader("Ship Locations"))
	//{
	//	ImGui::PushItemWidth(80);
	//	int count = 0;

	//	std::string shipText;
	//	shipText = "Ship " + count;
	//	shipText += " Position: ";
	//	ImGui::Text(shipText.c_str());
	//	ImGui::SameLine();
	//	glm::vec2 pos = m_ship.getPosition();
	//	ImGui::InputFloat2("", &pos[0], 0, ImGuiInputTextFlags_ReadOnly);
	//	count++;
	//	ImGui::PopItemWidth();
	//}

	//if (ImGui::CollapsingHeader("Planet Location"))
	//{
	//	ImGui::PushItemWidth(80);
	//	std::string planetText;
	//	planetText = "Planet Position: ";
	//	ImGui::Text(planetText.c_str());
	//	ImGui::SameLine();
	//	glm::vec2 pos = m_planet.getPosition();
	//	ImGui::InputFloat2("", &pos[0], 0, ImGuiInputTextFlags_ReadOnly);
	//	ImGui::PopItemWidth();
	//}

	//if (ImGui::CollapsingHeader("Mine Locations"))
	//{
	//	ImGui::PushItemWidth(80);
	//	int count = 0;
	//	for (Mine mine : m_pMines)
	//	{
	//		std::string mineText;
	//		mineText = "Mine " + count;
	//		mineText += " Position: ";
	//		ImGui::Text(mineText.c_str());
	//		ImGui::SameLine();
	//		glm::vec2 pos = mine.getPosition();
	//		ImGui::InputFloat2("", &pos[0], 0, ImGuiInputTextFlags_ReadOnly);
	//		count++;
	//	}
	//	ImGui::PopItemWidth();
	//}

	//ImGui::Separator();

	//ImGui::PushItemWidth(80);
	//glm::vec2 targetPosition = getTargetPosition();
	//if (ImGui::SliderFloat("Target X Position", &targetPosition.x, 0.0f, 800.0f, "%.0f"))
	//{
	//	setTargetPosition(targetPosition);
	//}
	//ImGui::SameLine();
	//if (ImGui::SliderFloat("Target Y Position", &targetPosition.y, 0.0f, 600.0f, "%.0f"))
	//{
	//	setTargetPosition(targetPosition);
	//}
	//ImGui::PopItemWidth();

	//ImGui::Separator();

	//if (ImGui::Button("Find Path"))
	//{
	//	//std::cout << "**** NEW PATH ****" << std::endl;

	//	findShortestPath();
	//	m_moveAlongPath = false;
	//}

	//if (ImGui::CollapsingHeader("Open Tiles"))
	//{
	//	ImGui::PushItemWidth(80);
	//	int count = 0;
	//	for (Tile* tile : m_pOpen)
	//	{
	//		std::string tileText;
	//		tileText = "Tile ";
	//		tileText += std::to_string(count);
	//		tileText += " Position: ";
	//		ImGui::Text(tileText.c_str());
	//		ImGui::SameLine();
	//		glm::vec2 pos = tile->getPosition();
	//		ImGui::InputFloat2("", &pos[0], 0, ImGuiInputTextFlags_ReadOnly);
	//		count++;
	//	}
	//	ImGui::PopItemWidth();
	//}

	//if (ImGui::CollapsingHeader("Closed Tiles"))
	//{
	//	ImGui::PushItemWidth(80);
	//	int count = 0;
	//	for (Tile* tile : m_pClosed)
	//	{
	//		std::string tileText;
	//		tileText = "Tile ";
	//		tileText += std::to_string(count);
	//		tileText += " Position: ";
	//		ImGui::Text(tileText.c_str());
	//		ImGui::SameLine();
	//		glm::vec2 pos = tile->getPosition();
	//		ImGui::InputFloat2("", &pos[0], 0, ImGuiInputTextFlags_ReadOnly);
	//		count++;
	//	}
	//	ImGui::PopItemWidth();
	//}

	//if (!m_pOpen.empty())
	//{
	//	if (ImGui::Button("Move Ship Along Path"))
	//	{
	//		m_moveAlongPath = true;
	//		m_pathLength = 0;
	//	}
	//}

	// Main Window End
	ImGui::End();
}

void StartScene::m_move()
{
	// Pf = Pi + Vi*T + 1/2*A*T*T
	// Pfx = Pix + VixCos(theta)T + 1/2AxT^2
	// Pfx = Piy + ViySin(theta)T + 1/2AyT^2

	m_velocityX = (m_velocity * m_PPM) * cos(m_angle * Deg2Rad);					// Velocity Components
	m_velocityY = (m_velocity * m_PPM) * -sin(m_angle * Deg2Rad);
	glm::vec2 velocity_vector = glm::vec2(m_velocityX, m_velocityY);	// Final velocity vector	

	m_acceleration = glm::vec2(0.0f, m_gravity) * m_PPM;

	// Physics equation
	m_finalPosition = m_detonator->getPosition() 
		+ (velocity_vector * m_time)
		+ ((m_acceleration * 0.5f) * (m_Atime * m_Atime));

	m_Atime += m_time;

	m_detonator->setPosition(m_finalPosition);
}
