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
#define TEXTURE_CHEST_GOLD		13
#define TEXTURE_PLATOFORM_01	14

//************

#define BLOCK_SIZE 50

static GLuint levelNumCounter{ 0 };

Level::Level(SpriteRenderer& renderer, PrimitiveRenderer& primitiveRenderer, Player& player)
	:
	renderer(renderer),
	primitiveRenderer(primitiveRenderer),
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
	assetTextures.emplace_back(new Texture2D("../assets/accessories/accessories/chest3.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));						// TEXTURE_CHEST_GOLD
	assetTextures.emplace_back(new Texture2D("../assets/accessories/accessories/shelf.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));						// TEXTURE_PLATOFORM_01

	cloudTextures.emplace_back(new Texture2D("../textures/TexturesCom_Skies0380_3_masked_S.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	cloudTextures.emplace_back(new Texture2D("../textures/TexturesCom_Skies0370_3_masked_S.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

	levelNumber = levelNumCounter;
	levelNumCounter += 1;
}

Level::~Level()
{
	for (unsigned int i = 0; i < assetTextures.size(); ++i)
	{
		if(assetTextures.at(i) != nullptr)
			delete assetTextures.at(i);
	}


	for (unsigned int i = 0; i < blocks.size(); ++i)
	{
		if(blocks.at(i) != nullptr)
			delete blocks.at(i);
	}

	for (unsigned int i = 0; i < assets.size(); ++i)
	{
		if(assets.at(i) != nullptr)
			delete assets.at(i);
	}

	for (unsigned int i = 0; i < cloudTextures.size(); ++i)
	{
		if(cloudTextures.at(i) != nullptr)
			delete cloudTextures.at(i);
	}

	for (unsigned int i = 0; i < enemies.size(); ++i)
	{
		if(enemies.at(i) != nullptr)
			delete enemies.at(i);
	}

	for (unsigned int i = 0; i < coins.size(); ++i)
	{
		if(coins.at(i) != nullptr)
			delete coins.at(i);
	}
}

void Level::Load(const std::string& filePath, const std::string& backGroundPath)
{
	levelData.clear();

	if (backGroundPath != "")
		backGround = new Texture2D(backGroundPath, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);

	if (backGround->loadFailed)
	{
		delete backGround;
		// loads the default backGround if current level doesn't have a unique background
		backGround = new Texture2D("../textures/backGroundDefault.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	}

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
	enemies.clear();
	coins.clear();

	for (unsigned int i = 0; i < levelData.size(); ++i)
	{
		for (unsigned int j = 0; j < levelData.at(i).size(); ++j)
		{
			GLchar symbol{ levelData.at(i).at(j) };
			switch (symbol)
			{
				case '!':
				{
					Spearman* spearman = new Spearman();
					spearman->SetPosition(glm::vec3((j * BLOCK_SIZE) - (spearman->GetSize().x / 2.0f), i * BLOCK_SIZE, 0.0f));
					spearman->AddPatrolPoint(spearman->GetPosition());
					enemies.emplace_back(spearman);
					break;
				}
				case 't':
				{
					Target* target = new Target();
					target->SetPosition(glm::vec3((j * BLOCK_SIZE), i * BLOCK_SIZE, 0.0f));
					enemies.emplace_back(target);
					break;
				}
				case 'C':
				{
					std::uniform_int_distribution<int> randRange(0, cloudTextures.size() - 1);

					// The initial positions of the clouds. They will slowly drift from right to left in the draw function
					Cloud* cloud = new Cloud(*cloudTextures.at(randRange(rng)), glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					clouds.emplace_back(cloud);
					hasClouds = true;
					break;
				}
				case 'c':
				{
					Coin* coin = new Coin(CoinType::COPPER, glm::vec3(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0f));
					coins.emplace_back(coin);
					break;
				}
				case 's':
				{
					Coin* coin = new Coin(CoinType::SILVER, glm::vec3(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0f));
					coins.emplace_back(coin);
					break;
				}
				case 'g':
				{
					Coin* coin = new Coin(CoinType::GOLD, glm::vec3(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0f));
					coins.emplace_back(coin);
					break;
				}
				case 'P':
				{
					player.SetPosition(glm::vec3(j * BLOCK_SIZE - (player.GetSize().x / 2.0f), i * BLOCK_SIZE + 1.05f, 0.0f));
					break;
				}
				case '^':
				{
					SpikeTrap* trap = new SpikeTrap(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_TRAP_01), glm::vec3(1.0f), 100.0f, glm::vec2(0.0f), glm::vec2(1.0f, 0.2f));
					trap->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					trap->SetIsCollisionEnabled(false);
					assets.emplace_back(trap);
					break;
				}
				case 'S':
				{
					GameObject* sign = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_MENU_SIGN_START));
					sign->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					sign->SetType(Type::SIGNSTART);
					sign->SetIsCollisionEnabled(false);
					assets.emplace_back(sign);
					break;
				}
				case 'Q':
				{
					GameObject* sign = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_MENU_SIGN_QUIT));
					sign->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					sign->SetType(Type::SIGNQUIT);
					sign->SetIsCollisionEnabled(false);
					assets.emplace_back(sign);
					break;
				}
				case 'T':
				{
					GameObject* chest = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_CHEST_GOLD));
					chest->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					chest->SetType(Type::CHEST);
					chest->SetIsCollisionEnabled(false);
					assets.emplace_back(chest);
					break;
				}
				case 'p':
				{
					GameObject* platform = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_PLATOFORM_01));
					platform->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					platform->SetType(Type::PLATFORM);
					platform->SetCollisionBoxSize(glm::vec2(platform->GetSize().x, platform->GetSize().y / 4.0f));
					platform->SetVelocity(glm::vec2(-1.0f, 0.0f));
					assets.emplace_back(platform);
					break;
				}
				case '0':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_BLOCK_00));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '1':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_BLOCK_01));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '2':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_BLOCK_02));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '3':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_BLOCK_03));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '4':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_BLOCK_04));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '5':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_BLOCK_05));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '6':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_BLOCK_06));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '7':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_BLOCK_07));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '8':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_BLOCK_08));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
				case '9':
				{
					GameObject* block = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_BLOCK_09));
					block->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					blocks.emplace_back(block);
					break;
				}
			}
		}
	}

	 //initializes the enemy orientation so that at the start of the level they face the player
	for (auto& enemy : enemies)
	{
		if (enemy->GetPosition().x > player.GetPosition().x)
			enemy->SetOrientation(EnemyOrientation::LEFT);
		else if(enemy->GetPosition().x < player.GetPosition().x)
			enemy->SetOrientation(EnemyOrientation::RIGHT);
	}
}

void Level::Draw(Window& window, float deltaTime)
{
	//TODO consider refactoring the background and clouds rendering parts because there is more than just drawing happening there.

	// render background
	if (backGround != nullptr)
	{
		//glm::vec2 backGroundPos = player.GetPosition() - glm::vec3(window.GetWindowWidth() / 2, window.GetWindowHeight() / 2, 0);
		glm::vec2 backGroundPos = player.GetCameraPos();
		renderer.Draw(*backGround, 0, glm::vec3(1.0f), backGroundPos, glm::vec2(window.GetWindowWidth(), window.GetWindowHeight()), 0.0f);
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
		blocks.at(i)->Draw(renderer, primitiveRenderer);

	// render all assets(chests, traps, ladders etc)
	for (unsigned int i = 0; i < assets.size(); ++i)
	{
		assets.at(i)->Draw(renderer, primitiveRenderer, true);
	}

	for (unsigned int i = 0; i < coins.size(); ++i)
	{
		if(!coins.at(i)->GetShouldBeDestroyed())
			coins.at(i)->Draw(renderer);
	}

	// render all enemies
	for (unsigned int i = 0; i < enemies.size(); ++i)
	{
		if (!enemies.at(i)->GetShouldDespawn())
		{
			enemies.at(i)->Draw(renderer, primitiveRenderer, true);
		}
		else
		{
			enemies.at(i)->DrawPuffEffect(renderer);
		}
	}

	// render player
	if (!player.GetShouldDespawn())
	{
		player.Draw(renderer, primitiveRenderer, true);
		player.DrawBloodEffect(renderer);
	}
	else
	{
		player.DrawPuffEffect(renderer);
	}

	// render enemy effects
	for (unsigned int i = 0; i < enemies.size(); ++i)
	{
		if(enemies.at(i)->GetEnemyType() == EnemyType::SPEARMAN && !enemies.at(i)->GetShouldDespawn())
			dynamic_cast<Spearman*>(enemies.at(i))->DrawBloodEffect(renderer);
	}

	 //if level number is 0(we are in the tutorial level), render the player controls instructions
	if (levelNumber == 0)
	{
		Texture2D* menuTexture = new Texture2D("../textures/playerControls.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
		glm::vec2 menuPos = glm::vec2(player.GetPosition().x, player.GetPosition().y + player.GetSize().y);
		GameObject* controlsMenu = new GameObject(menuPos, glm::vec2(200.0f), *menuTexture);
		controlsMenu->Draw(renderer, primitiveRenderer);
		delete menuTexture;
		delete controlsMenu;
	}
}

void Level::ProcessCollisions()
{
	player.SetIsOnGround(false);
	player.SetIsOnMovingSurface(false);
	player.ResetSpeed();

	// process collisions with blocks
	for (auto& block : blocks)
	{
		ProcessPlayerCollisions(*block);

		for(auto& enemy : enemies)
			ProcessEnemyCollisions(*enemy, *block);
	}

	// process collisions with assets
	for (auto& asset : assets)
	{
		ProcessPlayerCollisions(*asset);

		for (auto& enemy : enemies)
			ProcessEnemyCollisions(*enemy, *asset);
	}

	for (auto& asset : assets)
	{
		if (asset->GetType() == Type::PLATFORM)
		{
			for (auto& block : blocks)
				ProcessGameObjectCollisions(*asset, *block);
		}
	}
}

void Level::ProcessPlayerCollisions(GameObject& obj)
{
	if (obj.isCollisionEnabled())
	{
		glm::vec3 playerPos = player.GetPosition();
		glm::vec3 playerPrevPos = player.GetPreviousPosition();
		glm::vec2 playerSize = player.GetSize();
		glm::vec2 playerVelocity = player.GetVelocity();

		glm::vec2 objPos = obj.GetCollisionBox().position;
		glm::vec2 objSize = obj.GetCollisionBox().size;

		// ignore objs that are far from the player
		if (abs(objPos.x - playerPos.x) >= 500.0f || abs(objPos.y - playerPos.y) >= 500.0f)
			return;

		GLint collisionResult = player.AdvancedCollisionCheck(obj);

		if (collisionResult == 1)
		{
			player.SetIsOnGround(true);
			player.SetPosition(glm::vec3(playerPos.x, objPos.y + objSize.y, playerPos.z));
			player.SetVelocityY(0.0f);

			if (obj.GetType() == Type::PLATFORM)
			{
				player.SetIsOnMovingSurface(true);

				if (player.GetState() == PlayerState::IDLE || player.GetState() == PlayerState::ATTACK)
				{
					player.SetSpeed(obj.GetSpeed());
					player.SetVelocityX(obj.GetVelocity().x);
				}
				else if (player.GetState() == PlayerState::RUN)
				{
					if (player.GetOrientation() == PlayerOrientation::LEFT && obj.GetVelocity().x < 0.0f)
						player.SetSpeed(200.0f + obj.GetSpeed());
					else if (player.GetOrientation() == PlayerOrientation::RIGHT && obj.GetVelocity().x > 0.0f)
						player.SetSpeed(200.0f + obj.GetSpeed());
				}
			}
		}
		else if (collisionResult == 2)
		{
			GLfloat xPos = objPos.x - playerSize.x / 2.0f - player.GetCollisionBoxBottom().size.x / 2.0f - player.GetCollisionBoxRight().size.x;
			player.SetPosition(glm::vec3(xPos, playerPos.y, playerPos.z));
			player.SetVelocityX(0.0f);
		}
		else if (collisionResult == 3)
		{
			GLfloat xPos = objPos.x + objSize.x - playerSize.x / 2.0f + player.GetCollisionBoxBottom().size.x / 2.0f + player.GetCollisionBoxLeft().size.x;
			player.SetPosition(glm::vec3(xPos, playerPos.y, playerPos.z));
			player.SetVelocityX(0.0f);
		}
		else if (collisionResult == 4)
		{
			GLfloat yPos = objPos.y - player.GetCollisionBoxBottom().size.y - player.GetCollisionBoxLeft().size.y - player.GetCollisionBoxTop().size.y;
			player.SetPosition(glm::vec3(playerPos.x, yPos, playerPos.z));
			if (!player.GetIsOnGround())
				player.SetVelocityY(playerVelocity.y - 2 * playerVelocity.y);
		}
	}
}

void Level::ProcessEnemyCollisions(Enemy& enemy, GameObject& obj)
{
	if (enemy.GetIsDead())
		return;

	if (obj.isCollisionEnabled())
	{
		glm::vec3 enemyPos = enemy.GetPosition();
		glm::vec3 enemyPrevPos = enemy.GetPreviousPosition();
		glm::vec2 enemySize = enemy.GetSize();
		glm::vec2 enemyVelocity = enemy.GetVelocity();

		glm::vec2 objPos = obj.GetCollisionBox().position;
		glm::vec2 objSize = obj.GetCollisionBox().size;

		// ignore objs that are far from the enemy
		if (abs(objPos.x - enemyPos.x) >= 500.0f || abs(objPos.y - enemyPos.y) >= 500.0f)
			return;

		GLint collisionResult = enemy.AdvancedCollisionCheck(obj);

		if (collisionResult == 1)
		{
			enemy.SetIsOnGround(true);
			enemy.SetPosition(glm::vec3(enemyPos.x, objPos.y + objSize.y, enemyPos.z));
			enemy.SetVelocityY(0.0f);
		}
		else if (collisionResult == 2)
		{
			GLfloat xPos = objPos.x - enemySize.x / 2.0f - enemy.GetCollisionBoxBottom().size.x / 2.0f - enemy.GetCollisionBoxRight().size.x - 5.0f;
			enemy.SetPosition(glm::vec3(xPos, enemyPos.y, enemyPos.z));
			enemy.SetVelocityX(0.0f);
		}
		else if (collisionResult == 3)
		{
			GLfloat xPos = objPos.x + objSize.x - enemySize.x / 2.0f + enemy.GetCollisionBoxBottom().size.x / 2.0f + enemy.GetCollisionBoxLeft().size.x;
			enemy.SetPosition(glm::vec3(xPos, enemyPos.y, enemyPos.z));
			enemy.SetVelocityX(0.0f);
		}
		else if (collisionResult == 4)
		{
			GLfloat yPos = objPos.y - enemy.GetCollisionBoxBottom().size.y - enemy.GetCollisionBoxLeft().size.y - enemy.GetCollisionBoxTop().size.y;
			enemy.SetPosition(glm::vec3(enemyPos.x, yPos, enemyPos.z));
			if (!enemy.GetIsOnGround())
				enemy.SetVelocityY(enemyVelocity.y - 2 * enemyVelocity.y);
		}
	}
}

void Level::ProcessGameObjectCollisions(GameObject& object, GameObject& otherObject)
{
	if (object.isCollisionEnabled() && otherObject.isCollisionEnabled())
	{
		glm::vec2 objectPos = object.GetPosition();
		glm::vec2 objectPrevPos = object.GetPreviousPosition();
		glm::vec2 objectSize = object.GetSize();
		glm::vec2 objectVelocity = object.GetVelocity();

		glm::vec2 otherObjectPos = otherObject.GetCollisionBox().position;
		glm::vec2 otherObjectSize = otherObject.GetCollisionBox().size;

		if (object.SimpleCollisionCheck(otherObject))
		{
			object.SetPosition(objectPrevPos);
		}
	}
}

void Level::Update(float deltaTime)
{
	for (auto& obj : assets)
	{
		obj->Update(deltaTime);

		switch (obj->GetType())
		{
			case Type::SPIKETRAP:
			{
				SpikeTrap* spikeTrap = dynamic_cast<SpikeTrap*>(obj);

				if (player.SimpleCollisionCheck(*obj))
				{					
					spikeTrap->DamagePlayer(player);
					if (!player.GetIsDead())
						player.SetShouldBleed(true);
					if (player.GetHealth() <= 0.0f)
						player.SetIsDead(true);
				}
				for (auto& enemy : enemies)
				{
					if (enemy->SimpleCollisionCheck(*obj))
					{
						Spearman* spearman = dynamic_cast<Spearman*>(enemy);
						spikeTrap->DamageEnemy(*spearman);
						std::cout << "Spiketrap damaging enemy" << std::endl;
						if (!spearman->GetIsDead())
						{
							spearman->SetShouldBleed(true);
							std::cout << "setting should bleed to true" << std::endl;
						}

						if (spearman->GetHealth() <= 0.0f)
						{
							std::cout << "setting is dead to true" << std::endl;
							spearman->SetIsDead(true);
						}
					}
				}
				break;
			}
			case Type::PLATFORM:
			{
				for (auto& block : blocks)
				{
					if (obj->SimpleCollisionCheck(*block))
						obj->ReverseVelocityX();
				}

				break;
			}
		}
	}

	for (auto& coin : coins)
	{
		if (player.SimpleCollisionCheck(*coin))
		{
			if (!coin->GetIsCollected())
			{
				player.IncrementScore(coin->GetValue());
				GLint newScore = player.GetScore();

				if (newScore >= 100)
				{
					player.SetLives(player.GetLives() + 1);
					GLint scoreLeftover = newScore - 100;
					player.SetScore(scoreLeftover);

					// let the player know he received a new life for 100 coins he collected
				}

				std::cout << "player score increased by " << coin->GetValue() << "! New score: " << player.GetScore() << std::endl;
			}
			coin->SetIsCollected(true);
		}
	}

	// if all primary objectives in the level are complete, the level is finished. TODO draw some kind of "level complete" menu (maybe in UI class) 
	// that shows how the player did

	levelComplete = CheckObjectives();
}

GLboolean Level::IsPlayerSpottedByEnemies()
{
	GLboolean hasBeenSpotted{ false };

	for (auto& enemy : enemies)
	{
		if (enemy->CheckIfHasSeenPlayer(player))
			hasBeenSpotted = true;
	}
	return hasBeenSpotted;
}

void Level::RunEnemyBehaviour(float deltaTime)
{
	for (auto& enemy : enemies)
	{
		switch (enemy->GetEnemyType())
		{
			case EnemyType::SPEARMAN:
			{
				Spearman* spearman = dynamic_cast<Spearman*>(enemy);
				RunSpearmanBehaviour(*spearman, deltaTime);
				break;
			}
			case EnemyType::TARGET:
			{
				Target* target = dynamic_cast<Target*>(enemy);
				RunTargetBehaviour(*target, deltaTime);
				break;
			}
		}
		if (player.GetIsDead())
			enemy->SetState(EnemyState::IDLE);

		if (enemy->GetIsDead())
			enemy->SetState(EnemyState::DEATH);

	}
}

void Level::RunSpearmanBehaviour(Spearman& enemy, float deltaTime)
{
	if (!enemy.GetIsDead())
	{
		enemy.Update(deltaTime);

		if (!enemy.CheckIfHasSeenPlayer(player))
			enemy.MoveTowardsNextPatrolPoint(deltaTime);
		else
		{
			if (enemy.MoveTowardsPlayer(player, deltaTime)) // MoveTowardsPlayer returns true when enemy is in melee range
			{
				enemy.MeleeAttack();

				if (enemy.DamagePlayer(player)) // returns true after the final melee attackanimation has been drawn
				{
					player.SetShouldBleed(true);
					player.ResetBloodAnimation();

					if (player.GetHealth() <= 0.0f)
					{
						player.SetLives(player.GetLives() - 1);
						if (player.GetLives() > 0)
							player.SetHealth(100.0f);
					}
				}
				if (player.GetLives() == 0 && player.GetHealth() <= 0)
					player.SetIsDead(true);
			}
		}
		if (enemy.IsInPlayerMeleeRange(player))
		{
			if (player.IsMeleeAttackFinished())	// returns false when the animation is in it's last frame // TODO this causes player to automatically attack: FIX!
			{
				enemy.TakeDamage(player.GetDamage());
				enemy.SetShouldBleed(true);
				enemy.ResetBloodAnimation();
			}
		}
	}
}

void Level::RunTargetBehaviour(Target& target, float deltaTime)
{
	if (!target.GetIsDead())
	{
		target.Update(deltaTime);

		if (target.IsInPlayerMeleeRange(player))
		{
			if (player.IsMeleeAttackFinished())	// returns false when the animation is in it's last frame // TODO this causes player to automatically attack: FIX!
			{
				target.TakeDamage(player.GetDamage());
			}
		}
	}
}

void Level::SetAnimationToAllAliveEnemies(EnemyState newState)
{
	for (auto& enemy : enemies)
	{
		if(!enemy->GetIsDead())
			enemy->SetState(newState);
	}
}

void Level::InitObjectives()
{
	switch (levelNumber)
	{
		case 0:
		{
			InitLevel0Objectives();
			break;
		}
		case 1:
		{
			InitLevel1Objectives();
			break;
		}
	}
}

void Level::InitLevel0Objectives()
{
	Objective objective1 = Objective(player, ObjectiveType::MOVE_TO_LOCATION, ObjectivePriority::PRIMARY);
	for (auto& asset : assets)
	{
		if (asset->GetType() == Type::SIGNSTART)
			objective1.AddLocationToMoveTo(glm::vec2(asset->GetPosition().x + asset->GetSize().x / 2.0f, asset->GetPosition().y));
		objective1.SetName("Move to the start sign to begin");
	}
	objectivesPrimary.emplace_back(objective1);

	Objective objective2 = Objective(player, ObjectiveType::KILL_TARGET, ObjectivePriority::SECONDARY);
	for (auto& target : enemies)
	{
		if (target->GetEnemyType() == EnemyType::TARGET)
			objective2.AddTargetToKill(target);
		objective2.SetName("Destroy the target");
	}
	objectivesSecondary.emplace_back(objective2);
}

void Level::InitLevel1Objectives()
{
	Objective objective1 = Objective(player, ObjectiveType::MOVE_TO_LOCATION, ObjectivePriority::PRIMARY);
	for (auto& asset : assets)
	{
		if (asset->GetType() == Type::CHEST)
			objective1.AddLocationToMoveTo(glm::vec2(asset->GetPosition().x + asset->GetSize().x / 2.0f, asset->GetPosition().y));
		objective1.SetName("Find the treasure chest!");
	}
	objectivesPrimary.emplace_back(objective1);

	Objective objective2 = Objective(player, ObjectiveType::COLLECT_COIN, ObjectivePriority::SECONDARY);
	for (auto& coin : coins)
	{
		objective2.AddCoin(coin);
		objective2.SetName("Collect all the coins in the level");
	}
	objectivesSecondary.emplace_back(objective2);
}

GLboolean Level::CheckObjectives()
{
	GLboolean allPrimaryObjectivesComplete{ true };

	if (!objectivesPrimary.empty())
	{
		for (auto& objective : objectivesPrimary)
		{
			objective.Update();
			if (objective.GetState() != ObjectiveState::COMPLETED)
			{
				allPrimaryObjectivesComplete = false;
			}
		}
	}
	else
	{
		return false;
	}

	if (!objectivesSecondary.empty())
	{
		for (auto& objective : objectivesSecondary)
		{
			objective.Update();
			if (objective.GetState() != ObjectiveState::COMPLETED)
			{
				// if the player has not finished all secondary objectives at the end of the level, do not give him full score for the level
			}
		}
	}

	return allPrimaryObjectivesComplete;
}
