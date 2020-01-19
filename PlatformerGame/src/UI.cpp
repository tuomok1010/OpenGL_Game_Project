#include "UI.h"

UI::UI(Window& window, SpriteRenderer& spriteRenderer, TextRenderer& textRenderer, Player& player)
	:
	window(window),
	spriteRenderer(spriteRenderer),
	textRenderer(textRenderer),
	player(player)
{
	coinIcon = new Texture2D("../assets/CoinsByLexassets/PNG/COPPER/BIG/BIG_0.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	lifeIcon = new Texture2D("../textures/heart.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
}

UI::~UI()
{
	delete coinIcon;
	delete lifeIcon;
}

void UI::Draw()
{
	DrawScore();
	DrawHealth();
	DrawPauseMenu();
}

void UI::DrawScore()
{
	glm::vec2 size = glm::vec2(20.0f);
	glm::vec2 pos{};
	pos.x = player.GetCameraPos().x;
	pos.y = player.GetCameraPos().y + window.GetWindowHeight() - size.y;
	spriteRenderer.Draw(*coinIcon, 0, glm::vec3(1.0f), pos, size, 0.0f);

	std::string playerScoreString = " x " + std::to_string(player.GetScore());

	textRenderer.RenderText(playerScoreString, pos.x + size.x, pos.y, 1, glm::vec3(1.0f));
}

void UI::DrawHealth()
{
	glm::vec2 lifeSize = glm::vec2(20.0f);
	glm::vec2 lifePos{};
	lifePos.x = player.GetCameraPos().x + window.GetWindowWidth();
	lifePos.y = player.GetCameraPos().y + window.GetWindowHeight()- lifeSize.y;

	std::string playerHealthString = std::to_string(player.GetHealth());

	for (unsigned int i = 1; i <= player.GetLives(); ++i)
	{
		spriteRenderer.Draw(*lifeIcon, 0, glm::vec3(1.0f), glm::vec2(lifePos.x - lifeSize.x * i, lifePos.y), lifeSize, 0.0f);
	}

	textRenderer.RenderText(playerHealthString, lifePos.x - 50.0f, lifePos.y - lifeSize.y, 1, glm::vec3(1.0f, 0.0f, 0.0f));
}

void UI::DrawPauseMenu()
{
	if (gamePaused)
	{
		glm::vec2 pos{};
		pos.x = player.GetCameraPos().x + window.GetWindowWidth() / 2.0f;
		pos.y = player.GetCameraPos().y + window.GetWindowHeight() / 2.0f;
		textRenderer.RenderText("PAUSED", pos.x - 50.0f, pos.y + 100.0f, 2);
		textRenderer.RenderText("press Q to quit", pos.x - 30.0f, pos.y + 100.0f - 30.0f, 1);
		textRenderer.RenderText("press ENTER to continue", pos.x - 80.0f, pos.y + 100.0f - 60.0f, 1);
	}
}
