#include "Game.hpp"
#include "Map.hpp"
#include "Minimap.h"
#include "TextureManager.hpp"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Minigame.hpp"
#include "CsvManager.hpp"


Mouse mouseCollider;

Minimap* minimap;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::string Game::gameState = "menu1";
const char* Game::charTexFile = "";
int x, y;

std::vector<ColliderComponent*> Game::colliders;

auto& levelLabel1(manager.addEntity());
auto& levelLabel2(manager.addEntity());
auto& levelLabel3(manager.addEntity());
auto& m9Label(manager.addEntity());
auto& m10Label(manager.addEntity());

auto& help1(manager.addEntity("help1"));
auto& help2(manager.addEntity("help2"));


auto& player(manager.addEntity());
auto& mouse(manager.addEntity());
auto& menu(manager.addEntity());
auto& startButton(manager.addEntity("startButton"));
auto& creditsButton(manager.addEntity("creditsButton"));
auto& credits(manager.addEntity());
auto& menu2(manager.addEntity());
auto& leoButton(manager.addEntity("leoButton"));
auto& cleoButton(manager.addEntity("cleoButton"));
auto& labelCC(manager.addEntity());
auto& map1(manager.addEntity());
auto& map2(manager.addEntity());
auto& alarmBlinker(manager.addEntity());
auto& map3(manager.addEntity());
auto& map3Light(manager.addEntity());
auto& minigameBg(manager.addEntity());
auto& minigame1Col(manager.addEntity());
auto& minigame2Col(manager.addEntity());
auto& minigame3Col(manager.addEntity());
auto& minigame4Col(manager.addEntity());
auto& minigame5Col(manager.addEntity());
auto& minigame6Col(manager.addEntity());
auto& label1Credits(manager.addEntity());
auto& label2Credits(manager.addEntity());
auto& label3Credits(manager.addEntity());
auto& label4Credits(manager.addEntity());
auto& label5Credits(manager.addEntity());
auto& label6Credits(manager.addEntity());
auto& label7Credits(manager.addEntity());

auto& labelStory(manager.addEntity("story"));

auto& endLabel(manager.addEntity("end"));

auto& wall1(manager.addEntity());
auto& wall2(manager.addEntity());
auto& wall3(manager.addEntity());
auto& wall4(manager.addEntity());
auto& wall5(manager.addEntity());
auto& wall6(manager.addEntity());
auto& wall7(manager.addEntity());
auto& wall8(manager.addEntity());
auto& wall9(manager.addEntity());
auto& wall10(manager.addEntity());



std::vector<std::string> quest;
Minigame* mini1;
Minigame* mini2;
Minigame* mini3;
Minigame* mini4;
Minigame* mini5;
Minigame* mini6;

enum groupLabels : std::size_t
{
	groupMenu,
	groupMenu2,
	groupMap1,
	groupMap2,
	groupMap3,
	groupPlayers,
	groupMouse,
	groupButtons,
	groupMini1,
	groupMini2,
	groupMini3,
	groupMini4,
	groupMini5,
	groupMini6,
	groupHelp
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

	if (TTF_Init() == -1) {
		std::cout << "ERROR_TTF\n";
	}

	SDL_Color white = { 255, 255, 255, 255 };

	levelLabel1.addComponent<Label>(40, 100, "LEVEL 1", white, 30);
	levelLabel1.addGroup(groupMap1);
	levelLabel2.addComponent<Label>(40, 100, "LEVEL 2", white, 30);
	levelLabel2.addGroup(groupMap2);
	levelLabel3.addComponent<Label>(40, 100, "LEVEL 3", white, 30);
	levelLabel3.addGroup(groupMap3);

	SDL_Color green = { 0,128,0,255 };
	SDL_Color blue = { 0, 0, 128, 255 };

	m9Label.addComponent<Label>(20, 800, "Licences", green, 20);
	m9Label.addGroup(groupMap1);
	m9Label.addGroup(groupMap2);
	m9Label.addGroup(groupMap3);

	m10Label.addComponent<Label>(20, 900, "Classical Programming", blue, 20, 300);
	m10Label.addGroup(groupMap1);
	m10Label.addGroup(groupMap2);
	m10Label.addGroup(groupMap3);

	player.addComponent<TransformComponent>(500.0f, 500.0f, 64, 64, 1.75f);
	player.addComponent<SpriteComponent>("assets/animatiiLeo.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	mouse.addComponent<TransformComponent>(0.0f, 0.0f, 44, 25, 1);
	mouse.addComponent<MouseController>();
	mouse.addComponent<SpriteComponent>("assets/assets2/mouse.png");
	mouse.addGroup(groupMouse);

	menu.addComponent<TransformComponent>(0.f, 0.f, 768, 1024, 1.5f);
	menu.addComponent<SpriteComponent>("assets/assets2/start.png");
	menu.addGroup(groupMenu);

	menu2.addComponent<TransformComponent>(0.f, 0.f, 768, 1024, 1.5f);
	menu2.addComponent<SpriteComponent>("assets/assets2/leoCleo.png");
	menu2.addGroup(groupMenu2);

	startButton.addComponent<TransformComponent>(630.0f, 400.0f, 31, 51, 6);
	startButton.addComponent<SpriteComponent>("assets/startBut.png");
	startButton.addGroup(groupButtons);

	creditsButton.addComponent<TransformComponent>(10.0f, 1014.0f, 31, 51, 3);
	creditsButton.addComponent<SpriteComponent>("assets/creditsBut.png");
	creditsButton.addGroup(groupButtons);

	credits.addComponent<TransformComponent>(0.0f, 0.0f, 768, 1024, 1.5f);
	credits.addComponent<SpriteComponent>("assets/assets2/credits.png");

	map1.addComponent<TransformComponent>(0.f, 0.f, 768, 1024, 1.5f);
	map1.addComponent<SpriteComponent>("assets/assets2/level1.png");
	map1.addGroup(groupMap1);

	map2.addComponent<TransformComponent>(0.f, 0.f, 768, 1024, 1.5f);
	map2.addComponent<SpriteComponent>("assets/assets2/level2.png");
	map2.addGroup(groupMap2);

	alarmBlinker.addComponent<TransformComponent>(0.f, 0.f, 768, 1024, 1.5f);
	alarmBlinker.addComponent<SpriteComponent>("assets/assets2/level2_light.png", true, 1200);
	alarmBlinker.addGroup(groupMap2);

	map3.addComponent<TransformComponent>(0.f, 0.f, 768, 1024, 1.5f);
	map3.addComponent<SpriteComponent>("assets/assets2/level3_a.png");
	map3.addGroup(groupMap3);

	map3Light.addComponent<TransformComponent>(0.f, 0.f, 768, 1024, 1.5f);
	map3Light.addComponent<SpriteComponent>("assets/assets2/level3_light.png");
	map3Light.addGroup(groupMap3);

	minigameBg.addComponent<TransformComponent>(0.f, 0.f, 768, 1024, 1.5f);
	minigameBg.addComponent<SpriteComponent>("assets/assets2/minigame.png");
	minigameBg.addGroup(groupMini1);
	minigameBg.addGroup(groupMini2);
	minigameBg.addGroup(groupMini3);
	minigameBg.addGroup(groupMini4);
	minigameBg.addGroup(groupMini5);
	minigameBg.addGroup(groupMini6);

	leoButton.addComponent<TransformComponent>(340.0f, 850.0f, 31, 51, 4);
	leoButton.addComponent<SpriteComponent>("assets/leoBut.png");
	leoButton.addGroup(groupButtons);

	cleoButton.addComponent<TransformComponent>(985.0f, 850.0f, 31, 51, 4);
	cleoButton.addComponent<SpriteComponent>("assets/cleoBut.png");
	cleoButton.addGroup(groupButtons);

	minigame1Col.addComponent<TransformComponent>(1.5 * 606.0f, 1.5 * 279.0f, 33, 33, 1.5f);
	minigame1Col.addComponent<ColliderComponent>("mini1");
	minigame1Col.addGroup(groupMap1);

	minigame2Col.addComponent<TransformComponent>(1.5 * 606.0f, 694.0f, 33, 33, 1.5f);
	minigame2Col.addComponent<ColliderComponent>("mini2");
	minigame2Col.addGroup(groupMap1);

	minigame3Col.addComponent<TransformComponent>(1.5 * 606.0f, 694.0f, 33, 33, 1.5f);
	minigame3Col.addComponent<ColliderComponent>("mini3");
	minigame3Col.addGroup(groupMap2);

	minigame4Col.addComponent<TransformComponent>(1.5 * 606.0f, 694.0f, 33, 33, 1.5f);
	minigame4Col.addComponent<ColliderComponent>("mini4");
	minigame4Col.addGroup(groupMap2);

	minigame5Col.addComponent<TransformComponent>(1.5 * 606.0f, 694.0f, 33, 33, 1.5f);
	minigame5Col.addComponent<ColliderComponent>("mini5");
	minigame5Col.addGroup(groupMap3);

	minigame6Col.addComponent<TransformComponent>(1.5 * 606.0f, 694.0f, 33, 33, 1.5f);
	minigame6Col.addComponent<ColliderComponent>("mini6");
	minigame6Col.addGroup(groupMap3);

	SDL_Color black = { 0, 0, 0, 255 };



	label1Credits.addComponent<Label>(200, 200, "National University of Science and Technology Politehnica of Bucharest (NUSTPB)", black, 20, 900);
	label2Credits.addComponent<Label>(200, 400, "Project carried out in accordance with the initiatives of the Erasmus+ programs", black, 16, 1200);
	label3Credits.addComponent<Label>(200, 500, "Gender, Digitalization, Green: Ensuring a Sustainable Future for All in Europe", black, 16, 1200);
	label4Credits.addComponent<Label>(200, 600, "Fostering Transversal Digital Competences in Higher Education", black, 16, 1200);
	label5Credits.addComponent<Label>(200, 700, "Coordinating Professors: Mihail Caramihai, Daniel Chis", black, 16, 1200);
	label6Credits.addComponent<Label>(200, 800, "Developed by: Mihai Eva-Elena, Serban Eva-Maria, Tomescu Robert-Iulian, Preda Sergiu-Adrian, Tomescu Adriana-Marinela", black, 16, 1200);
	label7Credits.addComponent<Label>(200, 1000, "PRESS [ESC] TO EXIT", black, 16, 1200);

	labelStory.addComponent<Label>(200, 400, "In a secret and isolated laboratory, there lived a mad scientist named Dr. Hackerstein. Known for his brilliance in the field of programming, as well as for his eccentricities, Dr. Hackerstein invented a hack that could control any electronic system in the world. Eccentric and malevolent, Hackerstein decided to use his discovery to subjugate the entire digital network, turning it into an extension of his own will. One day, Dr.Hackerstein mysteriously disappeared from his laboratory, leaving behind an encrypted message.Much later, it was revealed that the doctor had created a digital bomb, an explosive device threatening to destroy the entire digital network of the city. With your talent and programming experience, you find yourself in a race against time to save the city from the imminent explosion.Don't forget! With each passing second, the pressure on you and the city increases, placing you in imminent danger.", black, 16, 1200);


	endLabel.addComponent<Label>(200, 400, "You've outwitted me this time... My digital empire crumbles, and my chaotic dreams are extinguished. The code of your skill has proven mightier than my darkest creation. Farewell to my malevolent aspirations, at least for now.....", black, 16, 1200);

	wall1.addComponent<TransformComponent>(0.f, 0.f, 355, 270, 1.f);
	wall1.addComponent<ColliderComponent>("wall");
	wall1.addComponent<SpriteComponent>("../assets/assets2/leoCleo.png");

	wall2.addComponent<TransformComponent>(0.f, 0.f, 270, 871, 1.f);
	wall2.addComponent<ColliderComponent>("wall");
	wall2.addComponent<SpriteComponent>("../assets/assets2/leoCleo.png");

	wall3.addComponent<TransformComponent>(0.f, 636.f, 500, 270, 1.f);
	wall3.addComponent<ColliderComponent>("wall");
	wall3.addComponent<SpriteComponent>("../assets/assets2/leoCleo.png");

	wall4.addComponent<TransformComponent>(0.f, 0.f, 2000, 20, 1.f);
	wall4.addComponent<ColliderComponent>("wall");

	help1.addComponent<TransformComponent>(1000.f, 80.f, 20, 20, 1.f);
	//help1.addComponent<SpriteComponent>("assets/assets2/checkButton.png");
	help1.addGroup(groupHelp);

	help2.addComponent<TransformComponent>(1140.f, 80.f, 20, 20, 1.f);
	//help2.addComponent<SpriteComponent>("assets/assets2/checkButton.png");
	help2.addGroup(groupHelp);

	//wall5.addComponent<TransformComponent>(0.f, 1560.f, 50, 1600, 1.f);
	//wall5.addComponent<ColliderComponent>("wall");

	//wall6.addComponent<TransformComponent>(1300.f, 0.f, 50, 1700, 1.f);
	//wall6.addComponent<ColliderComponent>("wall");

	/*wall7.addComponent<TransformComponent>(0.f, 0.f, 270, 355);
	wall7.addComponent<ColliderComponent>("wall");

	wall8.addComponent<TransformComponent>(0.f, 0.f, 270, 355);
	wall8.addComponent<ColliderComponent>("wall");*/



	quest = CsvManager::readData("assets/files/M9_L3.txt");
	mini1 = new Minigame(quest, 300, 250, mouseCollider, event);	
	quest = CsvManager::readData("assets/files/M10_L3.txt");
	mini2 = new Minigame(quest, 300, 250, mouseCollider, event);	
	quest = CsvManager::readData("assets/files/M9_L4.txt");
	mini3 = new Minigame(quest, 300, 250, mouseCollider, event);	
	quest = CsvManager::readData("assets/files/M10_L4.txt");
	mini4 = new Minigame(quest, 300, 250, mouseCollider, event);	
	quest = CsvManager::readData("assets/files/M9_L5.txt");
	mini5 = new Minigame(quest, 300, 250, mouseCollider, event);	
	quest = CsvManager::readData("assets/files/M10_L5.txt");
	mini6 = new Minigame(quest, 300, 250, mouseCollider, event);

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
			else if (gameState == "storyState")
			{
				gameState = "menu2";
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

auto& map1Group(manager.getGroup(groupMap1));
auto& map2Group(manager.getGroup(groupMap2));
auto& map3Group(manager.getGroup(groupMap3));
auto& buttons(manager.getGroup(groupButtons));
auto& menus(manager.getGroup(groupMenu));
auto& players(manager.getGroup(groupPlayers));
auto& mouses(manager.getGroup(groupMouse));
auto& menus2(manager.getGroup(groupMenu2));
auto& minigame1(manager.getGroup(groupMini1));
auto& minigame2(manager.getGroup(groupMini2));
auto& helpl1(manager.getGroup(groupHelp));

void Game::update()
{
	if (gameState != "creditsState" && gameState != "storyState") {
		

		if (mini1->getScore() >= 5 && mini2->getScore() >= 5 && mini1->questions[6]->isCompleted() && mini2->questions[6]->isCompleted())
		{
			gameState = "mainGameState2";
			mini1 = mini3;
			mini2 = mini4;
			player.getComponent<TransformComponent>().position.x = 300;
			player.getComponent<TransformComponent>().position.y = 300;
			mini1->countdown.start(300);
			mini2->countdown.start(300);
		}
		if (mini3->getScore() >= 5 && mini4->getScore() >= 5 && mini3->questions[6]->isCompleted() && mini4->questions[6]->isCompleted())
		{
			gameState = "mainGameState3";
			mini1 = mini5;
			mini2 = mini6;
			player.getComponent<TransformComponent>().position.x = 500;
			player.getComponent<TransformComponent>().position.y = 500;
			mini1->countdown.start(300);
			mini2->countdown.start(300);
		}
		if (mini5->getScore() >= 5 && mini6->getScore() >= 5 && mini5->questions[6]->isCompleted() && mini6->questions[6]->isCompleted())
		{
			gameState = "endState";
		}

		manager.refresh();
		manager.update();
		mouseCollider.update();

		int collidingWithDoor = 0;

		for (auto cc : colliders)
		{
			Collision::AABB(player.getComponent<ColliderComponent>(), *cc);

			if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->tag == "wall")
			{
				player.getComponent<TransformComponent>().velocity* (-1);
			}

			if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
			{
				if (cc->tag == "mini1")
				{
					collidingWithDoor = 1;
					break;
				}
				if (cc->tag == "mini2")
				{
					collidingWithDoor = 2;
					break;
				}
			}
			else if (gameState != "menu1" && gameState != "menu2" && gameState != "mainGameState2" && gameState != "mainGameState3") {
				gameState = "mainGameState";
			}
		}

		if (mini1->getScore() >= 5 && mini2->getScore() >= 5)
		{
			gameState = "mainGameState2";
		}
		if (mini3->getScore() >= 5 && mini4->getScore() >= 5)
		{
			gameState = "mainGameState3";
		}

		switch (collidingWithDoor)
		{
		case 1:
			gameState = "miniGameState1";
			break;
		case 2:
			gameState = "miniGameState2";
			break;
		default:
			break;
		}

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
			if (charTexFile == "assets/animatiiLeo.png")
			{
				player.getComponent<SpriteComponent>().setTexture("assets/animatiiLeo.png");
			}
			else if (charTexFile == "assets/animatiiCleo.png")
			{
				player.getComponent<SpriteComponent>().setTexture("assets/animatiiCleo.png");
			}
		}

		if (gameState == "miniGameState1")
		{
			mini1->update();
		}
		if (gameState == "miniGameState2")
		{
			mini2->update();
		}



		mini1->countdown.update();
		mini2->countdown.update();
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
			if (b->tag == "startButton" || b->tag == "creditsButton") b->draw();
		}
		for (auto& mo : mouses)
		{
			mo->draw();
		}
	}
	else if (gameState == "creditsState")
	{
		credits.draw();
		label1Credits.draw();
		label2Credits.draw();
		label3Credits.draw();
		label4Credits.draw();
		label5Credits.draw();
		label6Credits.draw();
	}
	else if (gameState == "storyState")
	{
		credits.draw();
		labelStory.draw();
	}
	else if (gameState == "endState")
	{
		credits.draw();
		endLabel.draw();
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
		for (auto& m : map1Group)
		{
			m->draw();
		}
		for (auto& h : helpl1)
		{
			h->draw();
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
	else if (gameState == "mainGameState2")
	{
		for (auto& m : map2Group)
		{
			m->draw();
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
	else if (gameState == "mainGameState3")
	{
		for (auto& m : map3Group)
		{
			m->draw();
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

	else if (gameState == "miniGameState1")
	{

		for (auto& m : minigame1)
		{
			m->draw();
		}
		mini1->draw();

		mouse.draw();
		//gameState = "mainGameState";
	}
	else if (gameState == "miniGameState2")
	{

		for (auto& m : minigame2)
		{
			m->draw();
		}
		mini2->draw();
		mouse.draw();
		//gameState = "mainGameState";
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
	tile.addGroup(groupMap1);
}

void Game::minigameBackground(int id, int x, int y)
{
	auto& minitile(manager.addEntity());
	minitile.addComponent<TileComponent>(x, y, 32, 32, id); //png width and height
}

