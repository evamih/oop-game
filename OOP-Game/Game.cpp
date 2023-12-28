#include "Game.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"


Map* map;
Map* minimap;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::string Game::gameState = "mainGameState";

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());
auto& door1(manager.addEntity());
auto& door2(manager.addEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupDoors,
	groupColliders,
	groupMinigames
};

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
	minimap = new Map();
	Map::loadMap("assets/ground/map16x16.map", 16, 16, 0, 0);

	player.addComponent<TransformComponent>(0.0f, 0.0f);
	//player.addComponent<SpriteComponent>("assets/boyplayer64x64.png");
	//player.addComponent<SpriteComponent>("assets/caraplayer64x64.png");
	player.addComponent<SpriteComponent>("assets/girlplayer64x64.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	/*wall.addComponent<TransformComponent>(800.0f, 800.0f, 40, 80, 2);
	wall.addComponent<SpriteComponent>("assets/ground/graytile.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);*/

	door1.addComponent<TransformComponent>(256.0f, 64.0f, 64, 64, 2);
	door1.addComponent<SpriteComponent>("assets/door.png");
	door1.addComponent<ColliderComponent>("door1");
	door1.addGroup(groupDoors);

	door2.addComponent<TransformComponent>(900.0f, 384.0f, 64, 64, 2);
	door2.addComponent<SpriteComponent>("assets/door.png");
	door2.addComponent<ColliderComponent>("door2");
	door2.addGroup(groupDoors);

	//space between walls/doors has to be bigger than the player
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

void startMiniGame()
{
	minimap->FilePath="assets/ground/map10x10.map";
	minimap->loadMap(minimap->FilePath, 10, 10, 3, 3);
	
	//if (Game::event.type == SDL_KEYDOWN)
	//{
	//	if(Game::event.key.keysym.sym  == SDLK_x)
	//		Map::loadMap("assets/ground/map10x10tiles.map", 10, 10, 3, 3);
	//		// destroy window !!
	//}

	//Game::gameState = "mainGameState";
	//std::cout << Game::gameState << std::endl;
	// collision = false
}

void stopMiniGame()
{
	minimap->~Map();

	Map::loadMap("assets/ground/map16x16.map", 16, 16, 0, 0);
	
}

void Game::update()
{
	manager.refresh();
	manager.update();

	for (auto cc : colliders) 
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
		if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->tag == "door1") //door1 as an example
		{
			//player.addComponent<TransformComponent>().velocity * -1;
			if(gameState == "mainGameState")
			{
				startMiniGame();
				gameState = "miniGameState";
			}
			std::cout << gameState << std::endl; 		
		}
	}
	if(gameState == "miniGameState")
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			if (Game::event.key.keysym.sym == SDLK_x)
			{
				stopMiniGame();
				gameState = "mainGameState";
			}
		}
	}
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& doors(manager.getGroup(groupDoors));
auto& minigame(manager.getGroup(groupMinigames));

void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles) 
	{
		t->draw();
	}
	for (auto& d : doors)
	{
		d->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& m : minigame)
	{
		m->draw();
	}
	
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
	tile.addComponent<TileComponent>(x, y, 32, 32, id);//png width and height
	tile.addGroup(groupMap);
}

void Game::minigameBackground(int id, int x, int y)
{
	auto& minitile(manager.addEntity());
	minitile.addComponent<TileComponent>(x, y, 32, 32, id);//png width and height
	minitile.addGroup(groupMinigames);
}

