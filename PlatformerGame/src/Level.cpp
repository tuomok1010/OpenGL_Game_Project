#include "Level.h"

#define TEXTURE_BLOCK_01 0

Level::Level(SpriteRenderer& renderer, Player& player)
	:
	renderer(renderer),
	player(player)
{
	textures.emplace_back(new Texture2D("../textures/TexturesCom_Brick_Rustic2_512_albedo.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	
}

Level::~Level()
{

}

void Level::Load(const std::string& filePath)
{
	levelData.clear();

	std::fstream stream;

	stream.open(filePath, stream.in);
	if (!stream.is_open())
	{
		std::cerr << "Error opening file " << filePath << std::endl;
	}

	stream.seekp(0);
	while (!stream.eof())
	{
		std::vector<GLchar> levelRowVec;
		std::string levelRowString{};
		std::getline(stream, levelRowString);

		for (unsigned int i = 0; i < levelRowString.size(); ++i)
		{
			if (levelRowString.at(i) != ' ')
				levelRowVec.emplace_back(levelRowString.at(i));
		}

		levelData.emplace_back(levelRowVec);
	}
	stream.close();

	// Need to reverse the vec, otherwise level gets drawn upside down. Alternatively could probably play around with the matrices
	std::reverse(levelData.begin(), levelData.end());

	ProcessLevelData();
}

void Level::ProcessLevelData()
{
	blocks.clear();

	for (unsigned int i = 0; i < levelData.size(); ++i)
	{
		for (int j = 0; j < levelData.at(i).size(); ++j)
		{
			if (levelData.at(i).at(j) == '#')
			{
				// using a magic number 50 here, TODO fix!
				GameObject blck(glm::vec2(j * 50, i * 50), glm::vec2(50.0f), *textures[TEXTURE_BLOCK_01], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f), glm::vec2(0.2f, 0.2f));
				blocks.emplace_back(blck);
			}

			if (levelData.at(i).at(j) == 'P')
			{
				player.SetPosition(glm::vec3(j * 50, i * 50, 0.0f));
			}
		}
	}
}

void Level::Draw()
{
	// Render all blocks
	for (unsigned int i = 0; i < blocks.size(); ++i)
	{
		blocks.at(i).Draw(renderer, 0);
	}

	// Render player
	player.Draw(renderer);
}