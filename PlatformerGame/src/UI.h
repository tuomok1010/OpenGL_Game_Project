#pragma once

#include "Window.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Player.h"

class UI
{
public:
	UI(Window& window, SpriteRenderer& spriteRenderer, TextRenderer& textRenderer, Player& player);
	~UI();

	void Draw();

	GLboolean GetGamePaused()const { return gamePaused; }

	void SetGamePaused(GLboolean newVal) { gamePaused = newVal; }

private:
	void DrawScore();
	void DrawHealth();
	void DrawPauseMenu();

private:
	Window& window;
	Player& player;
	SpriteRenderer& spriteRenderer;
	TextRenderer& textRenderer;
	Texture2D* coinIcon{};
	Texture2D* lifeIcon{};
	GLboolean gamePaused{};
};