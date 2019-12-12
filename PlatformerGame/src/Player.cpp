#include "Player.h"

Player::Player()
	:
	state(PlayerState::IDLE),
	textureOffset(glm::vec2(0.0f, 0.1f)),
	color(glm::vec3(1.0f)),
	position(glm::vec3(0.0f)),
	size(glm::vec2(75.0f, 100.0f)),
	rotation(0.0f),
	speed(250.0f)
{
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

	textureFall = new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Fall/jump_fall_000.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
}

Player::~Player()
{
	for (int i = 0; i < texturesIdle.size(); ++i)
	{
		texturesIdle.at(i)->Unbind();
		delete texturesIdle.at(i);
	}

	for (int i = 0; i < texturesRun.size(); ++i)
	{
		texturesRun.at(i)->Unbind();
		delete texturesRun.at(i);
	}

	for (int i = 0; i < texturesJump.size(); ++i)
	{
		texturesIdle.at(i)->Unbind();
		delete texturesJump.at(i);
	}
}

void Player::Draw(SpriteRenderer& renderer)
{
	// If the player is facing right, we do not need to rotate the sprite, if the sprite is facing left we set the axis of rotation to be the Y axis.
	glm::vec3 rotationAxiis = (orientation == PlayerOrientation::RIGHT) ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(0.0f, 1.0f, 0.0f);

	// If the player is facing right, set rotation to 0.0f, if the sprite is facing left set rotation to 180.0f.
	rotation = (orientation == PlayerOrientation::RIGHT) ? 0.0f : 180.0f;

	if (state == PlayerState::IDLE)
	{
		++textureIterator;

		if (textureIterator >= texturesIdle.size())
			textureIterator = 0;

		renderer.Draw(*texturesIdle.at(textureIterator), 0, color, position, size, rotation, glm::vec2(0.7f, 0.8f), textureOffset, rotationAxiis);
	}
	else if (state == PlayerState::RUN)
	{
		++textureIterator;

		if (textureIterator >= texturesRun.size())
			textureIterator = 0;

		renderer.Draw(*texturesRun.at(textureIterator), 0, color, position, size, rotation, glm::vec2(0.7f, 0.8f), textureOffset, rotationAxiis);
	}
	else if (state == PlayerState::JUMP)
	{
		++textureIterator;

		if (textureIterator >= texturesJump.size())
			textureIterator = 0;

		renderer.Draw(*texturesJump.at(textureIterator), 0, color, position, size, rotation, glm::vec2(0.7f, 0.8f), textureOffset, rotationAxiis);
	}
	else if (state == PlayerState::FALL)
	{
		renderer.Draw(*textureFall, 0, color, position, size, rotation, glm::vec2(0.7f, 0.8f), textureOffset, rotationAxiis);
	}
}

void Player::Move(float deltaTime)
{
	GLfloat velocity = speed * deltaTime;

	switch (orientation)
	{
	case PlayerOrientation::RIGHT:
		position += glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
		break;
	case PlayerOrientation::LEFT:
		position -= glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
		break;
	}
}

void Player::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Player::SetOrientation(PlayerOrientation newOrientation)
{
	orientation = newOrientation;
}

void Player::SetState(PlayerState newState)
{
	state = newState;
}
