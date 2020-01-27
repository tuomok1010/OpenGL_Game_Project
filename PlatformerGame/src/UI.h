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
	~UI();

	void Draw();

	GLboolean GetGamePaused()const { return gamePaused; }

	void SetGamePaused(GLboolean newVal) { gamePaused = newVal; }

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
	Texture2D* coinIcon{};
	Texture2D* lifeIcon{};
	GLboolean gamePaused{};
};