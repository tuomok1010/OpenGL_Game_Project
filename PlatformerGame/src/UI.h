#pragma once

#include "Window.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "PrimitiveRenderer.h"
#include "Player.h"
#include "Level.h"

class UI
{
public:
	UI(Window& window, SpriteRenderer& spriteRenderer, TextRenderer& textRenderer, PrimitiveRenderer& primitiveRenderer, Player& player, Level& level);
	UI(const UI& src);
	~UI();

	void Draw();

	GLboolean GetGamePaused()const { return gamePaused; }
	GLboolean GetViewObjectives()const { return viewObjectives; }

	void SetGamePaused(GLboolean newVal) { gamePaused = newVal; }
	void SetViewObjectives(GLboolean newVal) { viewObjectives = newVal; }

private:
	void DrawScore();
	void DrawHealth();
	void DrawPauseMenu();
	void DrawObjectivesMenu();
	void DrawObjectivesMarkers();

private:
	Window& window;
	Player& player;
	Level& level;
	SpriteRenderer& spriteRenderer;
	TextRenderer& textRenderer;
	PrimitiveRenderer& primitiveRenderer;
	std::vector<Texture2D*> textures{};
	GLboolean gamePaused{ false };
	GLboolean viewObjectives{ false };
};