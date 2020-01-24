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

	cloudTextures.emplace_back(new Texture2D("../textures/TexturesCom_Skies0380_3_masked_S.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	cloudTextures.emplace_back(new Texture2D("../textures/TexturesCom_Skies0370_3_masked_S.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

	levelNumber = levelNumCounter;
	levelNumCounter += 1;
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

	for (unsigned int i = 0; i < enemies.size(); ++i)
		delete enemies.at(i);

	for (unsigned int i = 0; i < coins.size(); ++i)
		delete coins.at(i);
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
					enemies.emplace_back(spearman);
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
					assets.emplace_back(trap);
					break;
				}
				case 'S':
				{
					GameObject* sign = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_MENU_SIGN_START));
					sign->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					sign->SetType(Type::SIGNSTART);
					assets.emplace_back(sign);
					break;
				}
				case 'Q':
				{
					GameObject* sign = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_MENU_SIGN_QUIT));
					sign->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					sign->SetType(Type::SIGNQUIT);
					assets.emplace_back(sign);
					break;
				}
				case 'T':
				{
					GameObject* chest = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(BLOCK_SIZE), *assetTextures.at(TEXTURE_CHEST_GOLD));
					chest->SetPosition(glm::vec2(j * BLOCK_SIZE, i * BLOCK_SIZE));
					chest->SetType(Type::CHEST);
					assets.emplace_back(chest);
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
	//for (auto& enemy : enemies)
	//{
	//	if (enemy->GetPosition().x > player.GetPosition().x)
	//		enemy->SetOrientation(EnemyOrientation::LEFT);
	//	else if(enemy->GetPosition().x < player.GetPosition().x)
	//		enemy->SetOrientation(EnemyOrientation::RIGHT);
	//}
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
		blocks.at(i)->Draw(renderer);

	// render all assets(chests, traps, ladders etc)
	for (unsigned int i = 0; i < assets.size(); ++i)
		assets.at(i)->Draw(renderer);

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
		if(!enemies.at(i)->GetShouldDespawn())
			dynamic_cast<Spearman*>(enemies.at(i))->DrawBloodEffect(renderer);
	}

	 //if level number is 0(we are in the tutorial level), render the player controls instructions
	if (levelNumber == 0)
	{
		Texture2D* menuTexture = new Texture2D("../textures/playerControls.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
		glm::vec2 menuPos = glm::vec2(player.GetPosition().x, player.GetPosition().y + player.GetSize().y);
		GameObject* controlsMenu = new GameObject(menuPos, glm::vec2(200.0f), *menuTexture);
		controlsMenu->Draw(renderer);
		delete menuTexture;
		delete controlsMenu;
	}
}

GLboolean Level::SimpleCollisionCheck(GameObject& obj1, GameObject& obj2)
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

/* need to optimize. slow fps causes collision to not work properly*/
void Level::ProcessCollisions()
{
	player.SetIsOnGround(false);

	for (auto& block : blocks)
	{
		ProcessPlayerCollisions(*block);

		for(auto& enemy : enemies)
			ProcessEnemyCollisions(*enemy, *block);
	}
}

void Level::ProcessPlayerCollisions(GameObject& obj)
{
	glm::vec3 playerPos = player.GetPosition();
	glm::vec3 playerPrevPos = player.GetPreviousPosition();
	glm::vec2 playerSize = player.GetSize();
	glm::vec2 playerVelocity = player.GetVelocity();

	glm::vec2 objPos = obj.GetPosition();
	glm::vec2 objSize = obj.GetSize();

	// ignore objs that are far from the player
	if (abs(objPos.x - playerPos.x) >= 500.0f || abs(objPos.y - playerPos.y) >= 500.0f)
		return;

	GLint collisionResult = player.AdvancedCollisionCheck(obj);

	if (collisionResult == 1)
	{
		player.SetIsOnGround(true);
		player.SetPosition(glm::vec3(playerPos.x, objPos.y + objSize.y, playerPos.z));
		player.SetVelocityY(0.0f);
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

void Level::ProcessEnemyCollisions(Enemy& enemy, GameObject& obj)
{
	if (enemy.GetIsDead())
		return;

	glm::vec3 enemyPos = enemy.GetPosition();
	glm::vec3 enemyPrevPos = enemy.GetPreviousPosition();
	glm::vec2 enemySize = enemy.GetSize();
	glm::vec2 enemyVelocity = enemy.GetVelocity();

	glm::vec2 objPos = obj.GetPosition();
	glm::vec2 objSize = obj.GetSize();

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

void Level::UpdateAssets(float deltaTime)
{
	for (auto& obj : assets)
	{
		switch (obj->GetType())
		{
			case Type::SPIKETRAP:
			{
				if (player.SimpleCollisionCheck(*obj))
				{
					dynamic_cast<SpikeTrap*>(obj)->DamagePlayer(player);

					if (!player.GetIsDead())
						player.SetShouldBleed(true);

					if (player.GetHealth() <= 0.0f)
					{
						player.SetIsDead(true);
					}
				}
				break;
			}
			case Type::SIGNSTART:
			{
				if (player.SimpleCollisionCheck(*obj))
				{
					levelComplete = true;
				}
				break;
			}
			case Type::SIGNQUIT:
			{
				if (player.SimpleCollisionCheck(*obj))
				{
					quitGame = true;
				}
				break;
			}
			case Type::CHEST:
			{
				if (player.SimpleCollisionCheck(*obj))
				{
					levelComplete = true;
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
				if (!enemy->GetIsDead())
				{
					Spearman* spearman = dynamic_cast<Spearman*>(enemy);

					spearman->Update(deltaTime);

					if (!spearman->CheckIfHasSeenPlayer(player))
						spearman->MoveTowardsNextPatrolPoint(deltaTime);
					else
					{
						if (spearman->MoveTowardsPlayer(player, deltaTime)) // MoveTowardsPlayer returns true when enemy is in melee range
						{
							spearman->MeleeAttack();

							if (spearman->DamagePlayer(player)) // returns true after the final melee attackanimation has been drawn
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
					if (spearman->IsInPlayerMeleeRange(player))
					{
						if (player.IsMeleeAttackFinished())	// returns false when the animation is in it's last frame // TODO this causes player to automatically attack: FIX!
						{
							spearman->TakeDamage(player.GetDamage());
							spearman->SetShouldBleed(true);
							spearman->ResetBloodAnimation();
						}
					}
				}
			}
		}
		if(player.GetIsDead())
			enemy->SetState(EnemyState::IDLE);

		if (enemy->GetIsDead())
			enemy->SetState(EnemyState::DEATH);
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
