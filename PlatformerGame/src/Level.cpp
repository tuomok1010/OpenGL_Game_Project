#include "Level.h"

//*********** these are the indices used to access the asset textures vector(check the constructor)

// blocks
#define TEXTURE_BLOCK_00		0
#define TEXTURE_BLOCK_01		1
#define TEXTURE_BLOCK_02		2
#define TEXTURE_BLOCK_03		3
#define TEXTURE_BLOCK_04		4
#define TEXTURE_BLOCK_05		5
#define TEXTURE_BLOCK_06		6
#define TEXTURE_BLOCK_07		7
#define TEXTURE_BLOCK_08		8
#define TEXTURE_BLOCK_09		9

// objects
#define TEXTURE_TRAP_01			10
#define TEXTURE_MENU_SIGN_START	11
#define TEXTURE_MENU_SIGN_QUIT	12

//************

#define BLOCK_SIZE 50

Level::Level(SpriteRenderer& renderer, Player& player)
	:
	renderer(renderer),
	player(player),
	rng(rd())
{
	assetTextures.emplace_back(new Texture2D("../assets/2DPlatformStoneTiles/Ground&Stone/Stone/ground0.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));	// TEXTURE_BLOCK_00
	assetTextures.emplace_back(new Texture2D("../assets/2DPlatformStoneTiles/Ground&Stone/Stone/ground1.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));	// TEXTURE_BLOCK_01
	assetTextures.emplace_back(new Texture2D("../assets/2DPlatformStoneTiles/Ground&Stone/Stone/ground2.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));	// TEXTURE_BLOCK_02
	assetTextures.emplace_back(new Texture2D("../assets/2DPlatformStoneTiles/Ground&Stone/Stone/ground3.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));	// TEXTURE_BLOCK_03
	assetTextures.emplace_back(new Texture2D("../assets/2DPlatformStoneTiles/Ground&Stone/Stone/ground4.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));	// TEXTURE_BLOCK_04
	assetTextures.emplace_back(new Texture2D("../assets/2DPlatformStoneTiles/Ground&Stone/Stone/ground5.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));	// TEXTURE_BLOCK_05
	assetTextures.emplace_back(new Texture2D("../assets/2DPlatformStoneTiles/Ground&Stone/Stone/ground6.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));	// TEXTURE_BLOCK_06
	assetTextures.emplace_back(new Texture2D("../assets/2DPlatformStoneTiles/Ground&Stone/Stone/ground7.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));	// TEXTURE_BLOCK_07
	assetTextures.emplace_back(new Texture2D("../assets/2DPlatformStoneTiles/Ground&Stone/Stone/ground8.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));	// TEXTURE_BLOCK_08
	assetTextures.emplace_back(new Texture2D("../assets/2DPlatformStoneTiles/Ground&Stone/Stone/ground9.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));	// TEXTURE_BLOCK_09

	assetTextures.emplace_back(new Texture2D("../assets/accessories/accessories/spike.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));						// TEXTURE_TRAP_01
	assetTextures.emplace_back(new Texture2D("../assets/accessories/accessories/menusignstart.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));				// TEXTURE_MENU_SIGN_START
	assetTextures.emplace_back(new Texture2D("../assets/accessories/accessories/menusignquit.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));				// TEXTURE_MENU_SIGN_QUIT

	cloudTextures.emplace_back(new Texture2D("../textures/TexturesCom_Skies0380_3_masked_S.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	cloudTextures.emplace_back(new Texture2D("../textures/TexturesCom_Skies0370_3_masked_S.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
}

Level::~Level()
{
	for (unsigned int i = 0; i < assetTextures.size(); ++i)
		delete assetTextures.at(i);

	for (unsigned int i = 0; i < blocks.size(); ++i)
		delete blocks.at(i);

	for (unsigned int i = 0; i < assets.size(); ++i)
		delete assets.at(i);

	for (unsigned int i = 0; i < cloudTextures.size(); ++i)
		delete cloudTextures.at(i);
}

void Level::Load(const std::string& filePath, const std::string& backGroundPath)
{
	levelData.clear();

	if (backGroundPath != "")
		backGround = new Texture2D(backGroundPath, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE);

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
	assets.clear();

	for (unsigned int i = 0; i < levelData.size(); ++i)
	{
		for (unsigned int j = 0; j < levelData.at(i).size(); ++j)
		{
			GLchar symbol{ levelData.at(i).at(j) };
			switch (symbol)
			{
				case 'C':
				{
					std::uniform_int_distribution<int> randRange(0, cloudTextures.size() - 1);

					// The initial positions of the clouds. They will slowly drift from right to left in the draw function
					Cloud* cloud = new Cloud(*cloudTextures.at(randRange(rng)), glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					clouds.emplace_back(cloud);
					hasClouds = true;
					break;
				}
				case 'P':
				{
					player.SetPosition(glm::vec3(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0f));
					break;
				}
				case '^':
				{
					SpikeTrap* trap = new SpikeTrap(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_TRAP_01], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f), glm::vec2(1.0f, 0.2f));
					trap->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					assets.emplace_back(trap);
					break;
				}
				case 'S':
				{
					GameObject* sign = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_MENU_SIGN_START], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
					sign->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					sign->SetType(Type::SIGNSTART);
					assets.emplace_back(sign);
					break;
				}
				case 'Q':
				{
					GameObject* sign = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_MENU_SIGN_QUIT], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
					sign->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					sign->SetType(Type::SIGNQUIT);
					assets.emplace_back(sign);
					break;
				}
				case '0':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_BLOCK_00], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '1':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_BLOCK_01], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '2':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_BLOCK_02], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '3':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_BLOCK_03], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '4':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_BLOCK_04], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '5':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_BLOCK_05], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '6':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_BLOCK_06], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '7':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_BLOCK_07], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '8':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_BLOCK_08], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '9':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures[TEXTURE_BLOCK_09], glm::vec3(1.0f), glm::vec2(0.0f), glm::vec2(0.0f));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
			}
		}
	}
}

void Level::Draw(Window& window, float deltaTime)
{
	//TODO consider refactoring the background and clouds rendering parts because there is more than just drawing happening there.

	// render background
	if (backGround != nullptr)
	{
		glm::vec2 backGroundPos = player.GetPosition() - glm::vec3(window.GetBufferWidth() / 2, window.GetBufferHeight() / 2, 0);
		renderer.Draw(*backGround, 0, glm::vec3(1.0f), backGroundPos, glm::vec2(window.GetBufferWidth(), window.GetBufferHeight()), 0.0f);
	}

	// render clouds if there are any in level, also adjusts their position.
	if (hasClouds)
	{
		std::uniform_int_distribution<int> randRange(0, cloudTextures.size() - 1);

		for (unsigned int i = 0; i < clouds.size(); ++i)
		{
			renderer.Draw(clouds.at(i)->texture, 0, glm::vec3(1.0f), clouds.at(i)->position, glm::vec2(clouds.at(i)->texture.GetWidth(), clouds.at(i)->texture.GetHeight()), 0.0f);
			clouds.at(i)->position.x -= 5.0f * deltaTime;

			// if the clouds have moved beyond the screen + 300.0f, the clouds position gets reset and and appears again from the right
			if (clouds.at(i)->position.x + clouds.at(i)->texture.GetWidth() < (player.GetPosition().x - window.GetBufferWidth() / 2) - 300.0f)
			{
				clouds.at(i)->position.x = (player.GetPosition().x + window.GetBufferWidth() / 2) + 300.0f;
				clouds.at(i)->texture = *cloudTextures.at(randRange(rng));
			}
		}
	}

	// render all blocks
	for (unsigned int i = 0; i < blocks.size(); ++i)
	{
		blocks.at(i)->Draw(renderer, 0);
	}

	// render all assets(chests, traps, ladders etc)
	for (unsigned int i = 0; i < assets.size(); ++i)
	{
		assets.at(i)->Draw(renderer, 0);
	}

	// render player
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

		if (collisionX && collisionY)
		{
			player.SetHasCollided(true);
			return collisionX && collisionY;
		}
	}
	else
	{
		player.SetHasCollided(false);
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
		if (CollisionCheck(player, *block))
		{
			return true;
		}
	}
	return false;
}

void Level::handlePlayerCollisionWithAssets()
{
	for (auto& obj : assets)
	{
		if (CollisionCheck(player, *obj))
		{
			if (obj->GetType() == Type::SPIKETRAP)
			{
				dynamic_cast<SpikeTrap*>(obj)->DamagePlayer(player);
				if (player.GetHealth() <= 0.0f)
					player.SetIsDead(true);
			}
			else if (obj->GetType() == Type::SIGNSTART)
			{
				levelComplete = true;
			}
			else if (obj->GetType() == Type::SIGNQUIT)
			{
				quitGame = true;
			}
		}
	}
}