#include "Player.h"

Player::Player()
	:
	state(PlayerState::IDLE),
	textureOffset(glm::vec2(-0.22f, 0.07f)), // old values -0.2f, 0.07f
	textureScale(glm::vec2(1.25f, 0.9f)),
	color(glm::vec3(1.0f)),
	position(glm::vec3(0.0f)),
	size(glm::vec2(160.0f, 100.0f)),
	rotation(0.0f),
	velocity(0.0f),
	speed(200.0f),
	gravity(5.0f),
	health(100),
	damage(50.0f),
	score(0),
	lives(3),
	colBoxOffsetBottom(glm::vec2(0.0f)),
	colBoxOffsetTop(glm::vec2(0.0f)),
	colBoxOffsetRight(glm::vec2(0.0f)),
	colBoxOffsetLeft(glm::vec2(0.0f)),
	colBoxOffsetSimple(glm::vec2(0.0f))
{
	for (unsigned int i = 0; i < 12; ++i)
		texturesIdle.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Idle/idle_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

	for(unsigned int i = 0; i < 16; ++i)
		texturesRun.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Run/run_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

	for(unsigned int i = 0; i < 10; ++i)
		texturesJump.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Start/jump_start_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

	for(unsigned int i = 0; i < 15; ++i)
		texturesDeath.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Death/death_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE));

	for(unsigned int i = 0; i < 10; ++i)
		texturesMeleeAttack.emplace_back(new Texture2D("../player/The Black Thief Slim Version/Animations/Attack Sword/sword_attack_" + std::to_string(i) + ".png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, GL_CLAMP_TO_EDGE));

	textureFall = new Texture2D("../player/The Black Thief Slim Version/Animations/Jump Fall/jump_fall_000.png", GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);

	camera = Camera(position);

	// Initialise collision boxes
	colBoxOffsetSimple.x = size.x / 2.0f - collisionBoxHorizontalLength / 2.0f;
	collisionBoxSimple = CollisionBox(glm::vec2(position.x + colBoxOffsetSimple.x + 200, position.y), glm::vec2(collisionBoxHorizontalLength, collisionBoxVerticalLength), glm::vec4(1.0f, 1.0f, 0.0f, 0.5f));

	colBoxOffsetBottom.x = size.x / 2.0f - collisionBoxSimple.size.x / 2.0f + collisionBoxThickness;
	collisionBottom = CollisionBox(glm::vec2(position.x + colBoxOffsetBottom.x, position.y), glm::vec2(collisionBoxSimple.size.x - 2 * collisionBoxThickness, collisionBoxThickness), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	colBoxOffsetTop.x = size.x / 2.0f - collisionBoxSimple.size.x / 2.0f + collisionBoxThickness;
	colBoxOffsetTop.y = collisionBoxSimple.size.y - collisionBoxThickness + 1.0f;
	collisionTop = CollisionBox(glm::vec2(position.x + colBoxOffsetTop.x, position.y + colBoxOffsetTop.y), glm::vec2(collisionBoxSimple.size.x - 2 * collisionBoxThickness, collisionBoxThickness), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	colBoxOffsetLeft.x = size.x / 2.0f - collisionBoxSimple.size.x / 2.0f - 1.0f;
	collisionLeft = CollisionBox(glm::vec2(position.x + colBoxOffsetLeft.x, collisionBoxSimple.position.y + collisionBottom.size.y), glm::vec2(collisionBoxThickness, collisionBoxSimple.size.y - collisionBoxThickness * 2), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	colBoxOffsetRight.x = size.x / 2.0f + collisionBoxSimple.size.x / 2.0f - collisionBoxThickness + 1.0f;
	collisionRight = CollisionBox(glm::vec2(position.x + colBoxOffsetRight.x, collisionBoxSimple.position.y + collisionBottom.size.y), glm::vec2(collisionBoxThickness, collisionBoxSimple.size.y - collisionBoxThickness * 2), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
}

Player::Player(const Player& src)
	: Player()
{
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

void Player::Draw(SpriteRenderer& renderer, PrimitiveRenderer& collisionBoxRenderer, GLboolean drawCollisionBoxes)
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
		{
			readyToDespawn = true;
			deathTexIterator = texturesDeath.size() - 1;
		}

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

	if (drawCollisionBoxes)
	{
		collisionBottom.Draw(collisionBoxRenderer);
		collisionTop.Draw(collisionBoxRenderer);
		collisionLeft.Draw(collisionBoxRenderer);
		collisionRight.Draw(collisionBoxRenderer);
		collisionBoxSimple.Draw(collisionBoxRenderer);
	}
}

void Player::Update(float deltaTime)
{
	// Update movement
	previousPosition = position;

	position.x += velocity.x * speed * deltaTime;
	position.y += velocity.y * speed * deltaTime;
	velocity.y -= gravity * deltaTime;

	// Update collision box positions
	collisionBoxSimple.position = glm::vec2(position.x + colBoxOffsetSimple.x, position.y);
	collisionBottom.position = glm::vec2(position.x + colBoxOffsetBottom.x, position.y - 1.0f);
	collisionTop.position = glm::vec2(position.x + colBoxOffsetTop.x, position.y + colBoxOffsetTop.y);
	collisionRight.position = glm::vec2(position.x + colBoxOffsetRight.x, collisionBoxSimple.position.y + collisionBottom.size.y);
	collisionLeft.position = glm::vec2(position.x + colBoxOffsetLeft.x, collisionBoxSimple.position.y + collisionBottom.size.y);

	camera.SetPosition(position + cameraOffset);
	//////////////////////////////

	// Update melee attack state
	if (IsMeleeAttackFinished())
	{
		isAttacking = false;
		ResetAnimation(PlayerState::ATTACK);
	}
	/////////////////////////////

	// Reset Jump animation if necessary
	if (state != PlayerState::JUMP && isOnGround)
		ResetAnimation(PlayerState::JUMP);
	/////////////////////////////
}

GLboolean Player::IsMeleeAttackFinished()
{
	if (meleeAttackIterator == texturesMeleeAttack.size() - 1)
		return true;
	else
		return false;
}

void Player::DrawBloodEffect(SpriteRenderer& renderer)
{
	if (shouldBleed)
	{
		bloodEffect.SetPosition(glm::vec3(position.x + size.x / 2.0f - bloodEffect.GetSize().x / 2.0f, position.y + size.y / 2.0f - bloodEffect.GetSize().y / 2.0f, position.z));
		bloodEffect.Draw(renderer);
	}

	if (bloodEffect.GetShouldStop())
		shouldBleed = false;
	else
		shouldBleed = true;
}

void Player::ResetBloodAnimation()
{
	bloodEffect.ResetAnimation();
}

void Player::ResetPuffAnimation()
{
	puffEffect.ResetAnimation();
	puffEffect.SetShouldStop(false);
}

void Player::DrawPuffEffect(SpriteRenderer& renderer)
{
	GLfloat yOffset = 50.0f;

	puffEffect.SetPosition(glm::vec3(position.x + size.x / 2.0f - puffEffect.GetSize().x / 2.0f, position.y - yOffset, position.z));

	if(!puffEffect.GetShouldStop())
		puffEffect.Draw(renderer);
}

// retuns an int based on which collision box is colliding. 0 = no collision, 1 = bottom, 2 = right, 3 = left, 4 = top
GLint Player::AdvancedCollisionCheck(GameObject& obj)
{
	CollisionBox objColBox = obj.GetCollisionBox();

	GLboolean collisionX = collisionBottom.position.x + collisionBottom.size.x > objColBox.position.x && objColBox.position.x + objColBox.size.x > collisionBottom.position.x;
	GLboolean collisionY = collisionBottom.position.y + collisionBottom.size.y > objColBox.position.y && objColBox.position.y + objColBox.size.y > collisionBottom.position.y;
	if (collisionX && collisionY && velocity.y < 0.0f)
	{
		return 1;
	}

	collisionX = collisionRight.position.x + collisionRight.size.x > objColBox.position.x&& objColBox.position.x + objColBox.size.x > collisionRight.position.x;
	collisionY = collisionRight.position.y + collisionRight.size.y > objColBox.position.y&& objColBox.position.y + objColBox.size.y > collisionRight.position.y;
	if (collisionX && collisionY && velocity.x > 0.0f)
	{
		return 2;
	}

	collisionX = collisionLeft.position.x + collisionLeft.size.x > objColBox.position.x&& objColBox.position.x + objColBox.size.x > collisionLeft.position.x;
	collisionY = collisionLeft.position.y + collisionLeft.size.y > objColBox.position.y&& objColBox.position.y + objColBox.size.y > collisionLeft.position.y;
	if (collisionX && collisionY && velocity.x < 0.0f)
	{
		return 3;
	}

	collisionX = collisionTop.position.x + collisionTop.size.x > objColBox.position.x&& objColBox.position.x + objColBox.size.x > collisionTop.position.x;
	collisionY = collisionTop.position.y + collisionTop.size.y > objColBox.position.y&& objColBox.position.y + objColBox.size.y > collisionTop.position.y;
	if (collisionX && collisionY && velocity.y > 0.0f)
	{
		return 4;
	}

	return 0;
}

GLboolean Player::SimpleCollisionCheck(GameObject& obj)
{
	CollisionBox objColBox = obj.GetCollisionBox();

	GLboolean collisionX = collisionBoxSimple.position.x + collisionBoxSimple.size.x > objColBox.position.x && objColBox.position.x + objColBox.size.x > collisionBoxSimple.position.x;
	GLboolean collisionY = collisionBoxSimple.position.y + collisionBoxSimple.size.y > objColBox.position.y && objColBox.position.y + objColBox.size.y > collisionBoxSimple.position.y;
	return collisionX && collisionY;

	return false;
}

GLboolean Player::SimpleCollisionCheck(Coin& coin)
{
	glm::vec3 objPos = coin.GetPosition();
	glm::vec2 objSize = coin.GetSize();

	GLboolean collisionX = collisionBoxSimple.position.x + collisionBoxSimple.size.x > objPos.x&& objPos.x + objSize.x > collisionBoxSimple.position.x;
	GLboolean collisionY = collisionBoxSimple.position.y + collisionBoxSimple.size.y > objPos.y&& objPos.y + objSize.y > collisionBoxSimple.position.y;
	return collisionX && collisionY;

	return false;
}

GLboolean Player::SimpleCollisionCheck(CollisionBox& colBox)
{
	GLboolean collisionX = collisionBoxSimple.position.x + collisionBoxSimple.size.x > colBox.position.x && colBox.position.x + colBox.size.x > collisionBoxSimple.position.x;
	GLboolean collisionY = collisionBoxSimple.position.y + collisionBoxSimple.size.y > colBox.position.y && colBox.position.y + colBox.size.y > collisionBoxSimple.position.y;
	return collisionX && collisionY;

	return false;
}

void Player::SetPosition(glm::vec3 newPosition)
{
	previousPosition = position;
	position = newPosition;
	camera.SetPosition(position + cameraOffset);

	// Update collision box positions
	collisionBoxSimple.position = glm::vec2(position.x + colBoxOffsetSimple.x, position.y);
	collisionBottom.position = glm::vec2(position.x + colBoxOffsetBottom.x, position.y - 1.0f);
	collisionTop.position = glm::vec2(position.x + colBoxOffsetTop.x, position.y + colBoxOffsetTop.y);
	collisionRight.position = glm::vec2(position.x + colBoxOffsetRight.x, collisionBoxSimple.position.y + collisionBottom.size.y);
	collisionLeft.position = glm::vec2(position.x + colBoxOffsetLeft.x, collisionBoxSimple.position.y + collisionBottom.size.y);
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

void Player::SetHealth(GLint newHealth)
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
