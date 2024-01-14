#include "Game.hpp"
#include "Map.hpp"
#include "Minimap.h"
#include "TextureManager.hpp"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"


Mouse mouseCollider;

Map* map;
Minimap* minimap;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::string Game::gameState = "menu1";
const char* Game::charTexFile = "";
int x, y;

std::vector<ColliderComponent*> Game::colliders;

auto& menu(manager.addEntity());
auto& menu2(manager.addEntity());
auto& player(manager.addEntity());
auto& wall1(manager.addEntity());
auto& wall2(manager.addEntity());
auto& wall3(manager.addEntity());
auto& wall4(manager.addEntity());
auto& door1(manager.addEntity());
auto& door2(manager.addEntity());
auto& mouse(manager.addEntity());
auto& startButton(manager.addEntity("startButton"));
auto& creditsButton(manager.addEntity("creditsButton"));
auto& credits(manager.addEntity());
auto& leoButton(manager.addEntity("leoButton"));
auto& cleoButton(manager.addEntity("cleoButton"));

enum groupLabels : std::size_t
{
	groupMenu,
	groupMenu2,
	groupMap,
	groupWall,
	groupPlayers,
	groupDoors,
	groupColliders,
	groupMinigames,
	groupMouse,
	groupButtons

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
		isRunning = false;
	}


	/*startButton.srect.y = 30;
	startButton.drect.x = 1280/2 - 1 / 2 * startButton.drect.w;
	startButton.drect.y = 800/2 - 1 / 2 * startButton.drect.h;*/

	map = new Map();

	Map::loadMap("assets/ground/map16x16.map", 16, 16, 0, 0);

	player.addComponent<TransformComponent>(500.0f, 500.0f);
	//player.addComponent<TransformComponent>(0.0f, 0.0f);
	//player.addComponent<SpriteComponent>("assets/boyplayer64x64.png");
	//player.addComponent<SpriteComponent>("assets/caraplayer64x64.png");
	player.addComponent<SpriteComponent>("assets/animatiiCara.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	wall1.addComponent<TransformComponent>(790.0f, 0.0f, 790, 1, 1);
	wall2.addComponent<TransformComponent>(0.0f, 790.0f, 1, 770, 1);
	wall3.addComponent<TransformComponent>(0.0f, 0.0f, 770, 1, 1);
	wall4.addComponent<TransformComponent>(0.0f, 0.0f, 1, 770, 1);
	wall1.addComponent<ColliderComponent>("wall");
	wall2.addComponent<ColliderComponent>("wall");
	wall3.addComponent<ColliderComponent>("wall");
	wall4.addComponent<ColliderComponent>("wall");
	wall1.addComponent<SpriteComponent>("assets/pink32.png");
	wall2.addComponent<SpriteComponent>("assets/pink32.png");
	wall3.addComponent<SpriteComponent>("assets/pink32.png");
	wall4.addComponent<SpriteComponent>("assets/pink32.png");
	wall1.addGroup(groupWall);
	wall2.addGroup(groupWall);
	wall3.addGroup(groupWall);
	wall4.addGroup(groupWall);

	menu.addComponent<TransformComponent>(0.0f, 0.0f, 800, 1300, 1);
	menu.addComponent<SpriteComponent>("assets/menu1.png");
	menu.addComponent<MenuController>();
	menu.addGroup(groupMenu);

	menu2.addComponent<TransformComponent>(0.0f, 0.0f, 800, 1300, 1);
	menu2.addComponent<SpriteComponent>("assets/menu2.png");
	menu2.addComponent<MenuController>();
	menu2.addGroup(groupMenu2);

	credits.addComponent<TransformComponent>(0.0f, 0.0f, 800, 1300, 1);
	credits.addComponent<SpriteComponent>("assets/menuex2.png");


	//wall.addComponent<SpriteComponent>("assets/ground/graytile.png");
	//wall.addGroup(groupMap);

	door1.addComponent<TransformComponent>(128.0f, 32.0f, 64, 64, 2);
	door1.addComponent<SpriteComponent>("assets/door.png");
	door1.addComponent<ColliderComponent>("door1");
	door1.addGroup(groupDoors);

	door2.addComponent<TransformComponent>(450.0f, 192.0f, 64, 64, 2);
	door2.addComponent<SpriteComponent>("assets/door.png");
	door2.addComponent<ColliderComponent>("door2");
	door2.addGroup(groupDoors);

	minimap = new Minimap();
	Minimap::loadMinimap("assets/ground/map10x10.map", 10, 10, 3, 3);

	startButton.addComponent<TransformComponent>(480.0f, 307.0f, 31, 51, 6);
	startButton.addComponent<SpriteComponent>("assets/startBut.png");
	startButton.addGroup(groupButtons);

	creditsButton.addComponent<TransformComponent>(8.0f, 695.0f, 31, 51, 3);
	creditsButton.addComponent<SpriteComponent>("assets/creditsBut.png");
	creditsButton.addGroup(groupButtons);

	leoButton.addComponent<TransformComponent>(250.0f, 500.0f, 31, 51, 4);
	leoButton.addComponent<SpriteComponent>("assets/leoBut.png");
	leoButton.addGroup(groupButtons);

	cleoButton.addComponent<TransformComponent>(800.0f, 500.0f, 31, 51, 4);
	cleoButton.addComponent<SpriteComponent>("assets/cleoBut.png");
	cleoButton.addGroup(groupButtons);

	mouse.addComponent<TransformComponent>(0.0f, 0.0f, 44, 25, 1);
	mouse.addComponent<MouseController>();
	mouse.addComponent<SpriteComponent>("assets/mouse.png");
	//mouse.addComponent<ColliderComponent>("mouse");
	mouse.addGroup(groupMouse);

	std::cout << gameState << std::endl;

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
	case SDL_KEYDOWN:
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			if (gameState == "creditsState")
			{
				gameState = "menu1";
				break;
			}
			else
			{
				isRunning = false;
				break;
			}
		}
	}
	
	}
}

//void Game::startMiniGame()
//{
//	minimap->loadMinimap("assets/ground/map10x10.map", 10, 10, 3, 3);
//}
//
//void Game::stopMiniGame()
//{
//	minimap->~Minimap();
//
//	Map::loadMap("assets/ground/map16x16.map", 16, 16, 0, 0);
//
//}

auto& buttons(manager.getGroup(groupButtons));
auto& walls(manager.getGroup(groupWall));
auto& menus(manager.getGroup(groupMenu));
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& doors(manager.getGroup(groupDoors));
auto& minigame(manager.getGroup(groupMinigames));
auto& mouses(manager.getGroup(groupMouse));
auto& menus2(manager.getGroup(groupMenu2));

void Game::update()
{
	manager.refresh();
	manager.update();
	mouseCollider.update();

	if (gameState == "menu1")
	{
		for (auto& b : buttons)
		{
			b->updateButton(mouseCollider, b->tag);
			
		}

	}
	else if (gameState == "menu2")
	{
		for (auto& b : buttons)
		{
			b->updateButton(mouseCollider, b->tag);
		}
	}
	else if (gameState == "mainGameState")
	{
		if (charTexFile == "assets/animatiiLeo.png") 
		{
			player.getComponent<SpriteComponent>().setTexture("assets/animatiiLeo.png");
		}
		else if(charTexFile == "assets/animatiiCleo.png")
		{
			player.getComponent<SpriteComponent>().setTexture("assets/animatiiCleo.png");
		}
	}


	bool collidingWithDoor = false;

	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);

		if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->tag == "wall")
		{
			player.getComponent<TransformComponent>().velocity* (-1);
		}

		if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
		{
			if (cc->tag == "door1")
			{
				collidingWithDoor = true;
				break;
			}
		}
	}

	if (collidingWithDoor)
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_x)
		{
			player.getComponent<TransformComponent>().position.x = 300.0f;
			player.getComponent<TransformComponent>().position.y = 300.0f;

			gameState = "mainGameState";
		}
		else gameState = "miniGameState";
	}
}



void Game::render()
{
	SDL_RenderClear(renderer);

	if (gameState == "menu1")
	{
		for (auto& n : menus)
		{
			n->draw();
		}
		for (auto& b : buttons)
		{
			if(b->tag == "startButton" || b->tag == "creditsButton") b->draw();
		}
		for (auto& mo : mouses)
		{
			mo->draw();
		}
	}
	else if (gameState == "creditsState")
	{
		credits.draw();
	}
	else if (gameState == "menu2")
	{
		for (auto& n : menus2)
		{
			n->draw();
		}
		for (auto& b : buttons)
		{
			if (b->tag == "leoButton" || b->tag == "cleoButton") b->draw();
		}
		for (auto& mo : mouses)
		{
			mo->draw();
		}
	}

	else if (gameState == "mainGameState")
	{
		for (auto& t : tiles)
		{
			t->draw();
		}
		for (auto& w : walls)
		{
			w->draw();
		}
		for (auto& d : doors)
		{
			d->draw();
		}
		for (auto& p : players)
		{
			p->draw();
		}
		for (auto& mo : mouses)
		{
			mo->draw();
		}
	}


	else if (gameState == "miniGameState")

	{
		//std::cout << gameState << std::endl;
		//if(condition minigame not finished ex. count<nr questions
		//player.addComponent<TransformComponent>().velocity.zero(); to stop player movement

		for (auto& m : minigame)
		{
			m->draw();
		}
		for (auto& mo : mouses)
		{
			mo->draw();
		}
		gameState = "mainGameState";
	}

	//customMouse.draw();
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
	tile.addComponent<TileComponent>(x, y, 32, 32, id); //png width and height
	tile.addGroup(groupMap);
}

void Game::minigameBackground(int id, int x, int y)
{
	auto& minitile(manager.addEntity());
	minitile.addComponent<TileComponent>(x, y, 32, 32, id); //png width and height
	minitile.addGroup(groupMinigames);
}


//#include "Game.hpp"
//#include "Map.hpp"
//#include "TextureManager.hpp"
//#include "Components.h"
//#include "Vector2D.h"
//#include "Collision.h"
//
//
//Map* map;
//Map* minimap;
//Manager manager;
//SDL_Renderer* Game::renderer = nullptr;
//SDL_Event Game::event;
//std::string Game::gameState = "mainGameState";
//
//std::vector<ColliderComponent*> Game::colliders;
//
//auto& player(manager.addEntity());
//auto& wall(manager.addEntity());
//auto& door1(manager.addEntity());
//auto& door2(manager.addEntity());
//
//enum groupLabels : std::size_t
//{
//	groupMap,
//	groupPlayers,
//	groupDoors,
//	groupColliders,
//	groupMinigames
//};
//
//bool Game::isRunning = false;
//
//void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
//{
//	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
//	{
//		std::cout << "Initialise...\n";
//
//		int flag = 0;
//
//		if (fullscreen)
//		{
//			flag = SDL_WINDOW_FULLSCREEN;
//		}
//
//		window = SDL_CreateWindow(title, xPos, yPos, width, height, flag);
//
//		if (window)
//		{
//			std::cout << "Window created!\n";
//		}
//
//		renderer = SDL_CreateRenderer(window, -1, 0);
//
//		if (renderer)
//		{
//			std::cout << "Renderer created!\n";
//		}
//
//
//		isRunning = true;
//	 }
//	else
//	 {
//		isRunning  = false;
//	 }
//
//
//	map = new Map();
//	minimap = new Map();
//	Map::loadMap("assets/ground/map16x16.map", 16, 16, 0, 0);
//
//	player.addComponent<TransformComponent>(0.0f, 0.0f);
//	//player.addComponent<SpriteComponent>("assets/boyplayer64x64.png");
//	//player.addComponent<SpriteComponent>("assets/caraplayer64x64.png");
//	player.addComponent<SpriteComponent>("assets/animatii3.png", true);
//	player.addComponent<KeyboardController>();
//	player.addComponent<ColliderComponent>("player");
//	player.addGroup(groupPlayers);
//
//	/*wall.addComponent<TransformComponent>(800.0f, 800.0f, 40, 80, 2);
//	wall.addComponent<SpriteComponent>("assets/ground/graytile.png");
//	wall.addComponent<ColliderComponent>("wall");
//	wall.addGroup(groupMap);*/
//
//	door1.addComponent<TransformComponent>(256.0f, 64.0f, 64, 64, 2);
//	door1.addComponent<SpriteComponent>("assets/door.png");
//	door1.addComponent<ColliderComponent>("door1");
//	door1.addGroup(groupDoors);
//
//	door2.addComponent<TransformComponent>(900.0f, 384.0f, 64, 64, 2);
//	door2.addComponent<SpriteComponent>("assets/door.png");
//	door2.addComponent<ColliderComponent>("door2");
//	door2.addGroup(groupDoors);
//
//	//space between walls/doors has to be bigger than the player
//}
//
//void Game::openWindow()
//{
//	std::cout << "open window" << std::endl;
//}
//
//void Game::handleEvents()
//{
//	SDL_PollEvent(&event);
//
//	switch (event.type)
//	{
//	case SDL_QUIT:
//		isRunning = false;
//		break;
//	default:
//		break; 
//	}
//}
//
//void startMiniGame()
//{
//	minimap->FilePath="assets/ground/map10x10.map";
//	minimap->loadMap(minimap->FilePath, 10, 10, 3, 3);
//	
//	//if (Game::event.type == SDL_KEYDOWN)
//	//{
//	//	if(Game::event.key.keysym.sym  == SDLK_x)
//	//		Map::loadMap("assets/ground/map10x10tiles.map", 10, 10, 3, 3);
//	//		// destroy window !!
//	//}
//
//	//Game::gameState = "mainGameState";
//	//std::cout << Game::gameState << std::endl;
//	// collision = false
//}
//
//void stopMiniGame()
//{
//	minimap->~Map();
//
//	Map::loadMap("assets/ground/map16x16.map", 16, 16, 0, 0);
//	
//}
//
//void Game::update()
//{
//	manager.refresh();
//	manager.update();
//
//	for (auto cc : colliders) 
//	{
//		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
//		if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->tag == "door1") //door1 as an example
//		{
//			//player.addComponent<TransformComponent>().velocity * -1;
//			if(gameState == "mainGameState")
//			{
//				startMiniGame();
//				gameState = "miniGameState";
//			}
//			std::cout << gameState << std::endl; 		
//		}
//	}
//	if(gameState == "miniGameState")
//	{
//		if (Game::event.type == SDL_KEYDOWN)
//		{
//			if (Game::event.key.keysym.sym == SDLK_x)
//			{
//				stopMiniGame();
//				gameState = "mainGameState";
//			}
//		}
//	}
//}
//
//auto& tiles(manager.getGroup(groupMap));
//auto& players(manager.getGroup(groupPlayers));
//auto& doors(manager.getGroup(groupDoors));
//auto& minigame(manager.getGroup(groupMinigames));
//
//void Game::render()
//{
//	SDL_RenderClear(renderer);
//
//	for (auto& t : tiles) 
//	{
//		t->draw();
//	}
//	for (auto& d : doors)
//	{
//		d->draw();
//	}
//	for (auto& p : players)
//	{
//		p->draw();
//	}
//	for (auto& m : minigame)
//	{
//		m->draw();
//	}
//	
//	SDL_RenderPresent(renderer);
//
//}
//
//void Game::clean()
//{
//	SDL_DestroyWindow(window);
//	SDL_DestroyRenderer(renderer);
//	SDL_Quit();
//	std::cout << "Game cleaned!\n";
//}
//
//bool Game::running()
//{
//	return isRunning;
//}
//
//void Game::addTile(int id, int x, int y)
//{
//	auto& tile(manager.addEntity());
//	tile.addComponent<TileComponent>(x, y, 32, 32, id);//png width and height
//	tile.addGroup(groupMap);
//}
//
//void Game::minigameBackground(int id, int x, int y)
//{
//	auto& minitile(manager.addEntity());
//	minitile.addComponent<TileComponent>(x, y, 32, 32, id);//png width and height
//	minitile.addGroup(groupMinigames);
//}
//
