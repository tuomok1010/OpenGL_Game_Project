#include "Level.h"

#define TEXTURE_BLOCK_01 0

#define BLOCK_SIZE 50

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
				GameObject blck(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *textures[TEXTURE_BLOCK_01], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f), glm::vec2(0.2f, 0.2f));
				blck.SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
				blocks.emplace_back(blck);
			}

			if (levelData.at(i).at(j) == 'P')
			{
				player.SetPosition(glm::vec3((j + 0.2f) * BLOCK_SIZE, (i + 0.2f) * BLOCK_SIZE, 0.0f));
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

GLboolean Level::CollisionCheck(Player& player, GameObject& obj)
{
	if (obj.isCollisionEnabled())
	{
		glm::vec3 playerPos = player.GetPosition();
		glm::vec2 playerSize = player.GetSize();
		glm::vec2 objPos = obj.GetPosition();
		glm::vec2 objSize = obj.GetSize();

		// Check if overlapping
		bool collisionX = playerPos.x + playerSize.x > objPos.x && objPos.x + objSize.x > playerPos.x;
		bool collisionY = playerPos.y + playerSize.y > objPos.y && objPos.y + objSize.y > playerPos.y;
		return collisionX && collisionY;
	}
	else
	{
		return false;
	}
}

GLboolean Level::CollisionCheck(GameObject& obj1, GameObject& obj2)
{
	if (obj1.isCollisionEnabled() && obj2.isCollisionEnabled())
	{
		glm::vec2 obj1Pos = obj1.GetPosition();
		glm::vec2 obj1Size = obj1.GetSize();
		glm::vec2 obj2Pos = obj2.GetPosition();
		glm::vec2 ob2Size = obj2.GetSize();

		bool collisionX = obj1Pos.x + obj1Size.x > obj2Pos.x && obj2Pos.x + ob2Size.x > obj1Pos.x;
		bool collisionY = obj1Pos.y + obj1Size.y > obj2Pos.y && obj2Pos.y + ob2Size.y > obj1Pos.y;
		return collisionX && collisionY;
	}
	else
	{
		return false;
	}
}

GLboolean Level::isPlayerCollidingWithBlocks()
{
	for (auto& block : blocks)
	{
		if (CollisionCheck(player, block))
		{
			return true;
		}
	}
	return false;
}

