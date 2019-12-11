#include "Player.h"

Player::Player()
	:
	state(PlayerState::IDLE),
	color(glm::vec3(1.0f)),
	position(glm::vec2(0.0f)),
	size(glm::vec2(150.0f, 120.0f)),
	rotation(0.0f)
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
}

void Player::Draw(SpriteRenderer& renderer)
{

	if (state == PlayerState::IDLE)
	{
		++textureIterator;

		if (textureIterator >= texturesIdle.size())
			textureIterator = 0;

		renderer.Draw(*texturesIdle.at(textureIterator), 0, color, position, size, rotation, 1.0f);
	}
}

void Player::SetPosition(glm::vec2 newPosition)
{
	position = newPosition;
}
