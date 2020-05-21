#include <SFML\Graphics.hpp>
#include "Platform.h"
#include <iostream>
#include <vector>
#include "player.h"
using namespace std;
using namespace sf;

static const float VIEW_HEIGHT = 512.0f;

void ResizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	RenderWindow window(sf::VideoMode(512, 512), "SFML Tutorial", Style::Close | Style::Resize);
	View view(Vector2f(0.0f,0.0f),Vector2f(VIEW_HEIGHT , VIEW_HEIGHT ));
	Texture playerTexture;
	playerTexture.loadFromFile("tux_from_linux.png");

	player player(&playerTexture, Vector2u(3,9), 0.3f, 100.0f, 200);

	vector<Platform> platforms;

	platforms.push_back(Platform(nullptr,Vector2f(400.0f,100.0f),Vector2f(500.0f,370.0f)));
	platforms.push_back(Platform(nullptr,Vector2f(400.0f,200.0f),Vector2f(500.0f,0.0f)));
	platforms.push_back(Platform(nullptr,Vector2f(1000.0f,170.0f),Vector2f(500.0f,500.0f)));
	
	float deltaTime = 0.0f;
	Clock clock;

	while(window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if(deltaTime >1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		Event evnt;
		while(window.pollEvent(evnt))
			switch (evnt.type)
		{
			case Event::Closed:
				window.close();
				break;
			case Event::Resized:
				ResizeView(window, view);
				break;
		}
		player.Update(deltaTime);

		Vector2f direction;
		
		for(Platform& platform: platforms)
			if(platform.GetCollider().CheckCollision(player.GetCollider(),direction,1.0f))
				player.OnCollision(direction);

		view.setCenter(player.GetPosition());
		window.clear(Color(150,150,150));
		window.setView(view);
		player.Draw(window);
		for(Platform& platform: platforms)
			platform.Draw(window);
		window.display();
	}
	

	return 0;
}