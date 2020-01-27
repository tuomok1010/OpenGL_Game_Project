#include "UI.h"

UI::UI(Window& window, SpriteRenderer& spriteRenderer, TextRenderer& textRenderer, PrimitiveRenderer& primitiveRenderer, Player& player, Level& level)
	:
	window(window),
	spriteRenderer(spriteRenderer),
	textRenderer(textRenderer),
	primitiveRenderer(primitiveRenderer),
	player(player),
	level(level)
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
	DrawObjectivesMenu();
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

		primitiveRenderer.Draw(Shape::RECTANGLE, glm::vec4(0.2f, 0.2f, 0.2f, 0.5f), glm::vec2(pos.x - 100.0f, pos.y), glm::vec2(310.0f, 180.0f), 0.0f);

		textRenderer.RenderText("PAUSED", pos.x - 50.0f, pos.y + 100.0f, 2);
		textRenderer.RenderText("press Q to quit", pos.x - 30.0f, pos.y + 100.0f - 30.0f, 1);
		textRenderer.RenderText("press ENTER to continue", pos.x - 80.0f, pos.y + 100.0f - 60.0f, 1);
	}
}

void UI::DrawObjectivesMenu()
{
	// Draw primary objectives
	glm::vec2 pos{};
	pos.x = player.GetCameraPos().x;
	pos.y = player.GetCameraPos().y + window.GetWindowHeight() - 100.0f;

	if (!level.GetPrimaryObjectives().empty())
	{
		textRenderer.RenderText("Primary objectives: ", pos.x, pos.y, 0.75f, glm::vec3(0.75f, 0.2f, 0.0f));
		pos.y -= 30.0f;

		for (unsigned int i = 0; i < level.GetPrimaryObjectives().size(); ++i)
		{
			textRenderer.RenderText(std::to_string(i + 1) + ". " + level.GetPrimaryObjectives().at(i).GetName(), pos.x, pos.y, 0.6f);
			pos.y -= 25.0f;
		}
	}

	// Draw secondary objectives
	if (!level.GetSecondaryObjectives().empty())
	{
		pos.y -= 30.0f;
		textRenderer.RenderText("Secondary objectives: ", pos.x, pos.y, 0.75f, glm::vec3(0.75f, 0.2f, 0.0f));
		pos.y -= 30.0f;
		for (unsigned int i = 0; i < level.GetSecondaryObjectives().size(); ++i)
		{
			textRenderer.RenderText(std::to_string(i + 1) + ". " + level.GetSecondaryObjectives().at(i).GetName(), pos.x, pos.y, 0.6f);
			pos.y -= 25.0f;
		}
	}
}

void UI::DrawObjectivesMarkers()
{
}
