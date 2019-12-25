#include "Player.h"

Player::Player()
	:
	state(PlayerState::IDLE),
	textureOffset(glm::vec2(-0.2f, 0.07f)),
	textureScale(glm::vec2(1.25f, 0.9f)),
	color(glm::vec3(1.0f)),
	position(glm::vec3(0.0f)),
	size(glm::vec2(160.0f, 100.0f)),
	rotation(0.0f),
	speed(250.0f),
	maxJumpHeight(75.0f),
	heightJumped(0.0f),
	health(100.0f)
{
	// TODO put these in loops
	texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_000.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_001.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_002.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_003.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_004.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_005.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_006.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_007.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_008.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_009.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_010.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_011.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_000.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_001.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_002.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_003.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_004.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_005.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_006.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_007.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_008.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_009.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_010.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_011.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_012.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_013.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_014.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_015.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

	texturesJump.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Start/jump_start_000.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesJump.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Start/jump_start_001.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesJump.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Start/jump_start_002.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesJump.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Start/jump_start_003.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesJump.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Start/jump_start_004.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesJump.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Start/jump_start_005.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesJump.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Start/jump_start_006.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesJump.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Start/jump_start_007.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesJump.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Start/jump_start_008.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesJump.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Start/jump_start_009.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_000.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_001.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_002.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_003.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_004.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_005.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_006.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_007.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_008.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_009.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_010.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_011.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_012.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_013.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));
	texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_014.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

	texturesMeleeAttack.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Attack Sword/sword_attack_000.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));
	texturesMeleeAttack.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Attack Sword/sword_attack_001.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));
	texturesMeleeAttack.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Attack Sword/sword_attack_002.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));
	texturesMeleeAttack.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Attack Sword/sword_attack_003.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));
	texturesMeleeAttack.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Attack Sword/sword_attack_004.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));
	texturesMeleeAttack.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Attack Sword/sword_attack_005.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));
	texturesMeleeAttack.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Attack Sword/sword_attack_006.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));
	texturesMeleeAttack.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Attack Sword/sword_attack_007.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));
	texturesMeleeAttack.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Attack Sword/sword_attack_008.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));
	texturesMeleeAttack.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Attack Sword/sword_attack_009.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));

	textureFall = new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Fall/jump_fall_000.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);

	camera = Camera(position);
}

Player::~Player()
{
	for (unsigned int i = 0; i < texturesIdle.size(); ++i)
	{
		texturesIdle.at(i)->Unbind();
		delete texturesIdle.at(i);
	}

	for (unsigned int i = 0; i < texturesRun.size(); ++i)
	{
		texturesRun.at(i)->Unbind();
		delete texturesRun.at(i);
	}

	for (unsigned int i = 0; i < texturesJump.size(); ++i)
	{
		texturesJump.at(i)->Unbind();
		delete texturesJump.at(i);
	}

	for (unsigned int i = 0; i < texturesDeath.size(); ++i)
	{
		texturesDeath.at(i)->Unbind();
		delete texturesDeath.at(i);
	}

	textureFall->Unbind();
	delete textureFall;
}

void Player::Draw(SpriteRenderer& renderer)
{
	// If the player is facing right, we do not need to rotate the sprite, if the sprite is facing left we set the axis of rotation to be the Y axis.
	glm::vec3 rotationAxiis = (orientation == PlayerOrientation::RIGHT) ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(0.0f, 1.0f, 0.0f);

	// If the player is facing right, set rotation to 0.0f, if the sprite is facing left set rotation to 180.0f.
	rotation = (orientation == PlayerOrientation::RIGHT) ? 0.0f : 180.0f;

	if (state == PlayerState::IDLE)
	{
		if (idleTexIterator >= texturesIdle.size())
			idleTexIterator = 0;

		renderer.Draw(*texturesIdle.at(idleTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++idleTexIterator;
	}
	else if (state == PlayerState::RUN)
	{
		if (runTexIterator >= texturesRun.size())
			runTexIterator = 0;

		renderer.Draw(*texturesRun.at(runTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++runTexIterator;
	}
	else if (state == PlayerState::JUMP)
	{
		if (jumpTexIterator >= texturesJump.size())
			jumpTexIterator = texturesJump.size() - 1;
		
		renderer.Draw(*texturesJump.at(jumpTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++jumpTexIterator;
	}
	else if (state == PlayerState::FALL)
	{
		renderer.Draw(*textureFall, 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
	}
	else if (state == PlayerState::DEATH)
	{
		if (deathTexIterator >= texturesDeath.size())
			deathTexIterator = texturesDeath.size() - 1;

		renderer.Draw(*texturesDeath.at(deathTexIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++deathTexIterator;
	}
	else if (state == PlayerState::ATTACK)
	{
		if (meleeAttackIterator >= texturesMeleeAttack.size())
			meleeAttackIterator = 0;

		renderer.Draw(*texturesMeleeAttack.at(meleeAttackIterator), 0, color, position, size, rotation, textureScale, textureOffset, rotationAxiis);
		++meleeAttackIterator;
	}
}

void Player::Move(float deltaTime)
{
	GLfloat velocity = speed * deltaTime;
	state = PlayerState::RUN;

	switch (orientation)
	{
	case PlayerOrientation::RIGHT:
		previousPosition = position;
		position += glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
		camera.SetPosition(position + cameraOffset);
		break;
	case PlayerOrientation::LEFT:
		previousPosition = position;
		position -= glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
		camera.SetPosition(position + cameraOffset);
		break;
	}
}

// TODO fix: there is a bug when player jumps and hits a block above him. This will cause the player to freeze in place and other weird behaviour
GLboolean Player::Jump(float deltaTime, GLboolean& gravityEnabled)
{
	GLfloat velocity = speed * deltaTime;
	state = PlayerState::JUMP;
	previousPosition = position;
	gravityEnabled = false;

	if (heightJumped >= maxJumpHeight)
	{
		heightJumped = 0.0f;
		gravityEnabled = true;
		return false;
	}
	else
	{
		position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
		camera.SetPosition(position + cameraOffset);

		heightJumped += position.y - previousPosition.y;
	}
	return true;
}

void Player::MeleeAttack()
{
	state = PlayerState::ATTACK;
}

void Player::MoveDown(float deltaTime)
{
	GLfloat velocity = speed * deltaTime;
	previousPosition = position;
	position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
	camera.SetPosition(position + cameraOffset);
}

void Player::SetPosition(glm::vec3 newPosition)
{
	previousPosition = position;
	position = newPosition;
	camera.SetPosition(position + cameraOffset);
}

void Player::SetOrientation(PlayerOrientation newOrientation)
{
	orientation = newOrientation;
}

void Player::SetState(PlayerState newState)
{
	state = newState;
}

void Player::SetHasCollided(GLboolean hasCollided)
{
	this->hasCollided = hasCollided;
}

void Player::SetHealth(GLfloat newHealth)
{
	health = newHealth;
}

void Player::SetIsDead(GLboolean isDead)
{
	this->isDead = isDead;
}

void Player::ResetAnimation(PlayerState animationToReset)
{
	switch (animationToReset)
	{
	case PlayerState::IDLE:
		idleTexIterator = 0;
		break;
	case PlayerState::RUN:
		runTexIterator = 0;
		break;
	case PlayerState::JUMP:
		jumpTexIterator = 0;
		break;
	case PlayerState::DEATH:
		deathTexIterator = 0;
		break;
	case PlayerState::ATTACK:
		meleeAttackIterator = 0;
		break;
	}
}
