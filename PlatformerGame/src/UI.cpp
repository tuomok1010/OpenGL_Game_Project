#include "UI.h"

#define TEXTURE_COIN_ICON	0
#define TEXTURE_LIFE_ICON	1
#define TEXTURE_OK_ICON		2
#define TEXTURE_INFO_ICON	3
#define TEXTURE_CANCEL_ICON	4

UI::UI(Window& window, SpriteRenderer& spriteRenderer, TextRenderer& textRenderer, PrimitiveRenderer& primitiveRenderer, Player& player, Level& level)
	:
	window(window),
	spriteRenderer(spriteRenderer),
	textRenderer(textRenderer),
	primitiveRenderer(primitiveRenderer),
	player(player),
	level(level)
{
	textures.emplace_back(new Texture2D("../assets/CoinsByLexassets/PNG/COPPER/BIG/BIG_0.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));		// TEXTURE_COIN_ICON
	textures.emplace_back(new Texture2D("../textures/heart.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));										// TEXTURE_LIFE_ICON		
	textures.emplace_back(new Texture2D("../textures/Game icon Pack1/400px/ok.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));					// TEXTURE_OK_ICON
	textures.emplace_back(new Texture2D("../textures/Game icon Pack1/400px/info.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));				// TEXTURE_INFO_ICON
	textures.emplace_back(new Texture2D("../textures/Game icon Pack1/400px/cancel.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));				// TEXTURE_CANCEL_ICON
}

UI::UI(const UI& src)
	: UI(src.window, src.spriteRenderer, src.textRenderer, src.primitiveRenderer, src.player, src.level)
{
}

UI::~UI()
{
	for (auto& texture : textures)
	{
		if (texture != nullptr)
			delete texture;
	}
}

void UI::Draw()
{
	DrawScore();
	DrawHealth();

	if(gamePaused)
		DrawPauseMenu();
	if(viewObjectives)
		DrawObjectivesMenu();
}

void UI::DrawScore()
{
	glm::vec2 size = glm::vec2(20.0f);
	glm::vec2 pos{};
	pos.x = player.GetCameraPos().x;
	pos.y = player.GetCameraPos().y + window.GetWindowHeight() - size.y;
	spriteRenderer.Draw(*textures.at(TEXTURE_COIN_ICON), 0, glm::vec3(1.0f), pos, size, 0.0f);

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
		spriteRenderer.Draw(*textures.at(TEXTURE_LIFE_ICON), 0, glm::vec3(1.0f), glm::vec2(lifePos.x - lifeSize.x * i, lifePos.y), lifeSize, 0.0f);
	}

	textRenderer.RenderText(playerHealthString, lifePos.x - 50.0f, lifePos.y - lifeSize.y, 1, glm::vec3(1.0f, 0.0f, 0.0f));
}

void UI::DrawPauseMenu()
{

	glm::vec2 pos{};
	pos.x = player.GetCameraPos().x + window.GetWindowWidth() / 2.0f;
	pos.y = player.GetCameraPos().y + window.GetWindowHeight() / 2.0f;

	primitiveRenderer.Draw(Shape::RECTANGLE, glm::vec4(0.2f, 0.2f, 0.2f, 0.5f), glm::vec2(pos.x - 100.0f, pos.y), glm::vec2(310.0f, 180.0f), 0.0f);

	textRenderer.RenderText("PAUSED", pos.x - 50.0f, pos.y + 100.0f, 2);
	textRenderer.RenderText("press Q to quit", pos.x - 30.0f, pos.y + 100.0f - 30.0f, 1);
	textRenderer.RenderText("press ENTER to continue", pos.x - 80.0f, pos.y + 100.0f - 60.0f, 1);
}

void UI::DrawObjectivesMenu()
{
	// Draw primary objectives
	glm::vec2 posText{};
	posText.x = player.GetCameraPos().x + 30.0f;
	posText.y = player.GetCameraPos().y + window.GetWindowHeight() - 100.0f;

	if (!level.GetObjectivesList().GetPrimaryObjectives().empty())
	{
		textRenderer.RenderText("Primary objectives: ", posText.x, posText.y, 0.75f, glm::vec3(0.75f, 0.2f, 0.0f));
		posText.y -= 30.0f;

		for (unsigned int i = 0; i < level.GetObjectivesList().GetPrimaryObjectives().size(); ++i)
		{
			if (level.GetObjectivesList().GetPrimaryObjectives().at(i).GetState() == ObjectiveState::COMPLETED)
			{
				spriteRenderer.Draw(*textures.at(TEXTURE_OK_ICON), 0, glm::vec3(1.0f), glm::vec2(posText.x - 30.0f, posText.y), glm::vec2(20.0f), 0.0f);
			}
			else if (level.GetObjectivesList().GetPrimaryObjectives().at(i).GetState() == ObjectiveState::IN_PROGRESS)
			{
				spriteRenderer.Draw(*textures.at(TEXTURE_INFO_ICON), 0, glm::vec3(1.0f), glm::vec2(posText.x - 30.0f, posText.y), glm::vec2(20.0f), 0.0f);
			}
			else if (level.GetObjectivesList().GetPrimaryObjectives().at(i).GetState() == ObjectiveState::FAILED)
			{
				spriteRenderer.Draw(*textures.at(TEXTURE_CANCEL_ICON), 0, glm::vec3(1.0f), glm::vec2(posText.x - 30.0f, posText.y), glm::vec2(20.0f), 0.0f);
			}
			textRenderer.RenderText(std::to_string(i + 1) + ". " + level.GetObjectivesList().GetPrimaryObjectives().at(i).GetName(), posText.x, posText.y, 0.6f);
			posText.y -= 25.0f;
		}
	}

	// Draw secondary objectives
	if (!level.GetObjectivesList().GetSecondaryObjectives().empty())
	{
		posText.y -= 30.0f;
		textRenderer.RenderText("Secondary objectives: ", posText.x, posText.y, 0.75f, glm::vec3(0.75f, 0.2f, 0.0f));
		posText.y -= 30.0f;
		for (unsigned int i = 0; i < level.GetObjectivesList().GetSecondaryObjectives().size(); ++i)
		{
			if (level.GetObjectivesList().GetSecondaryObjectives().at(i).GetState() == ObjectiveState::COMPLETED)
			{
				spriteRenderer.Draw(*textures.at(TEXTURE_OK_ICON), 0, glm::vec3(1.0f), glm::vec2(posText.x - 30.0f, posText.y), glm::vec2(20.0f), 0.0f);
			}
			else if (level.GetObjectivesList().GetSecondaryObjectives().at(i).GetState() == ObjectiveState::IN_PROGRESS)
			{
				spriteRenderer.Draw(*textures.at(TEXTURE_INFO_ICON), 0, glm::vec3(1.0f), glm::vec2(posText.x - 30.0f, posText.y), glm::vec2(20.0f), 0.0f);
			}
			else if (level.GetObjectivesList().GetSecondaryObjectives().at(i).GetState() == ObjectiveState::FAILED)
			{
				spriteRenderer.Draw(*textures.at(TEXTURE_CANCEL_ICON), 0, glm::vec3(1.0f), glm::vec2(posText.x - 30.0f, posText.y), glm::vec2(20.0f), 0.0f);
			}

			textRenderer.RenderText(std::to_string(i + 1) + ". " + level.GetObjectivesList().GetSecondaryObjectives().at(i).GetName(), posText.x, posText.y, 0.6f);
			posText.y -= 25.0f;
		}
	}
}

void UI::DrawObjectivesMarkers()
{
}
