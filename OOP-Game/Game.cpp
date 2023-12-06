#include "Game.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"


Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Initialise...\n";

		int flag = 0;

		if (fullscreen)
		{
			flag = SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flag);

		if (window)
		{
			std::cout << "Window created!\n";
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			std::cout << "Renderer created!\n";
		}


		isRunning = true;
	 }
	else
	 {
		isRunning  = false;
	 }


	map = new Map();
	/*tile0.addComponent<TileComponent>(400.0f, 30.0f, 64, 64, 0);//tile
	tile1.addComponent<TileComponent>(400.0f, 200.0f, 64, 64, 1);//greentile
	tile1.addComponent<ColliderComponent>("purple"); // tagurile pe culori nu au f mult sens
	tile2.addComponent<TileComponent>(400.0f, 400.0f, 64, 64, 2);//bluetile
	tile2.addComponent<ColliderComponent>("blue");*/

	Map::loadMap("assets/ground/map10x10.map", 10, 10);

	player.addComponent<TransformComponent>(200.0f, 200.0f);
	player.addComponent<SpriteComponent>("assets/colliderTestPlayer.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(80.0f, 30.0f, 40, 80, 2);
	wall.addComponent<SpriteComponent>("assets/ground/graytile.png");
	wall.addComponent<ColliderComponent>("wall");

	//intre componentele astea sa fie mereu spatiu mai mare decat personajul nostru si nu prea imi convine
}

void Game::openWindow()
{
	std::cout << "open window" << std::endl;
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break; 
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	for (auto cc : colliders) //care este vectorul de pointeri de colliders initializati
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
		/* {
			player.getComponent<TransformComponent>().velocity * -1;
			std::cout << "Wall hit!" << std::endl;
			
			//personajul trebuie sa fie de 64x64 in tot fisierul / sa luam alt rectangle / sa aiba o toleranta de cativa pixeli stanga dreapta astfel incat sa nu se blocheze intre colliders
		}*/
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	manager.draw();

	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned!\n";
}

bool Game::running()
{
	return isRunning;
}

void Game::addTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
}