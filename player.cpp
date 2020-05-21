#include "player.h"


player::player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight):
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.0f,150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);
}


player::~player(void)
{
}

void player::Update(float deltaTime)
{
	velocity.x *= 0.3f;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
	}
	velocity.y += 981.0f * deltaTime;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;

	if(velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if(velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}	
void player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void player::OnCollision(sf::Vector2f direction)
{
	if(direction.x < 0.0f)
	{
		//collision on the left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//collision of the right
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//collision on the bottom
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//collision on the top
		velocity.y = 0.0f;
	}
}