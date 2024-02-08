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
std::string Game::subject = "";
const char* Game::charTexFile = "";
int Game::count = 0;
Label* check;
int x, y;

std::vector<ColliderComponent*> Game::colliders;

auto& levelLabel1(manager.addEntity());
auto& levelLabel2(manager.addEntity());
auto& levelLabel3(manager.addEntity());
auto& m9Label(manager.addEntity());
auto& m10Label(manager.addEntity());

auto& help1(manager.addEntity("help1"));
auto& help2(manager.addEntity("help2"));
auto& help3(manager.addEntity("help3"));

std::vector<std::string> help1TextM9;
std::vector<std::string> help2TextM9;
std::vector<std::string> help3TextM9;

std::vector<std::string> help1TextM10;
std::vector<std::string> help2TextM10;
std::vector<std::string> help3TextM10;

std::vector <Label*> help1M9Label; // help labels for module 9
std::vector <Label*> help2M9Label;
std::vector <Label*> help3M9Label;

std::vector <Label*> help1M10Label; // help labels for module 10
std::vector <Label*> help2M10Label;
std::vector <Label*> help3M10Label;

std::vector <Label*> help1Label; // actual rendered help labels
std::vector <Label*> help2Label;
std::vector <Label*> help3Label;

auto& helpBg1(manager.addEntity());
auto& helpBg2(manager.addEntity());

auto& player(manager.addEntity());
auto& mouse(manager.addEntity());
auto& menu(manager.addEntity());
auto& startButton(manager.addEntity("startButton"));

auto& creditsButton(manager.addEntity("creditsButton"));
auto& credits(manager.addEntity());

auto& menu2(manager.addEntity());
auto& leoButton(manager.addEntity("leoButton"));
auto& cleoButton(manager.addEntity("cleoButton"));

auto& menu3(manager.addEntity());
auto& licencesButton(manager.addEntity("licences"));
auto& programmingButton(manager.addEntity("programming"));

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
auto& bomb(manager.addEntity("bomb"));
auto& labelStory(manager.addEntity("story"));

auto& label8(manager.addEntity());
auto& yesButton(manager.addEntity("yes"));
//auto& noButton(manager.addEntity("no"));

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
auto& wall11(manager.addEntity());
auto& wall12(manager.addEntity());
auto& wall13(manager.addEntity());
auto& wall14(manager.addEntity());
auto& wall15(manager.addEntity());
auto& wall16(manager.addEntity());
auto& wall17(manager.addEntity());
auto& wall18(manager.addEntity());
auto& wall19(manager.addEntity());
auto& wall20(manager.addEntity());
auto& wall21(manager.addEntity());
auto& wall22(manager.addEntity());

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
	groupMenu3,
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
	groupHelp,
	groupHelp2,
	groupHelpScreen,
	groupEnd
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

	SDL_Color green = { 30, 128, 0, 100 };
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

	mouse.addComponent<TransformComponent>(0.0f, 0.0f, 46, 30, 1);
	mouse.addComponent<MouseController>();
	mouse.addComponent<SpriteComponent>("assets/assets2/mouse.png");
	mouse.addGroup(groupMouse);

	menu.addComponent<TransformComponent>(0.f, 0.f, 768, 1024, 1.5f);
	menu.addComponent<SpriteComponent>("assets/assets2/start.png");
	menu.addGroup(groupMenu);

	menu2.addComponent<TransformComponent>(0.f, 0.f, 768, 1024, 1.5f);
	menu2.addComponent<SpriteComponent>("assets/assets2/leoCleo.png");
	menu2.addGroup(groupMenu2);

	menu3.addComponent<TransformComponent>(0.0f, 0.0f, 768, 1024, 1.5f);
	menu3.addComponent<SpriteComponent>("assets/assets2/start.png");
	menu3.addGroup(groupMenu3);

	licencesButton.addComponent<TransformComponent>(340.0f, 400.0f, 31, 51, 4);
	licencesButton.addComponent<SpriteComponent>("assets/leoBut.png");
	licencesButton.addGroup(groupButtons);

	programmingButton.addComponent<TransformComponent>(985.0f, 400.0f, 31, 51, 4);
	programmingButton.addComponent<SpriteComponent>("assets/cleoBut.png");
	programmingButton.addGroup(groupButtons);

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
	map3Light.addComponent<SpriteComponent>("assets/assets2/level3_light.png", true, 1200);
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

	minigame1Col.addComponent<TransformComponent>(1.5 * 606.0f, 418.5f, 33, 33, 1.5f);
	minigame1Col.addComponent<ColliderComponent>("mini1");
	minigame1Col.addGroup(groupMap1);

	minigame2Col.addComponent<TransformComponent>(1.5 * 606.0f, 694.0f, 33, 33, 1.5f);
	minigame2Col.addComponent<ColliderComponent>("mini2");
	minigame2Col.addGroup(groupMap1);
	
	minigame3Col.addComponent<TransformComponent>(1.5 * 606.0f, 550.0f, 33, 33, 1.5f);
	minigame3Col.addComponent<ColliderComponent>("mini3");
	minigame3Col.addGroup(groupMap2);

	bomb.addComponent<TransformComponent>(900.0f, 556.0f, 70, 33, 1.5f);
	bomb.addComponent<SpriteComponent>("assets/cleoBut.png");
	bomb.addGroup(groupButtons);

	SDL_Color black = { 0, 0, 0, 255 };

	label1Credits.addComponent<Label>(200, 200, "National University of Science and Technology Politehnica of Bucharest (NUSTPB)", black, 26, 900);
	label2Credits.addComponent<Label>(200, 400, "Project carried out in accordance with the initiatives of the Erasmus+ programs", black, 20, 1200);
	label4Credits.addComponent<Label>(200, 600, "Fostering Transversal Digital Competences in Higher Education", black, 20, 1200);
	label5Credits.addComponent<Label>(200, 700, "Coordinating Professors: Mihail Caramihai, Daniel Chis", black, 20, 1200);
	label6Credits.addComponent<Label>(200, 800, "Developed by: Mihai Eva-Elena, Serban Eva-Maria, Tomescu Robert-Iulian, Preda Sergiu-Adrian, Tomescu Adriana-Marinela", black, 20, 1200);
	label7Credits.addComponent<Label>(200, 1000, "PRESS [ESC] TO EXIT", black, 20, 1200);

	labelStory.addComponent<Label>(200, 400, "In a secret and isolated laboratory, there lived a mad scientist named Dr. Hackerstein. Known for his brilliance in the field of programming, as well as for his eccentricities, Dr. Hackerstein invented a hack that could control any electronic system in the world. Eccentric and malevolent, Hackerstein decided to use his discovery to subjugate the entire digital network, turning it into an extension of his own will. One day, Dr.Hackerstein mysteriously disappeared from his laboratory, leaving behind an encrypted message.Much later, it was revealed that the doctor had created a digital bomb, an explosive device threatening to destroy the entire digital network of the city. With your talent and programming experience, you find yourself in a race against time to save the city from the imminent explosion.Don't forget! With each passing second, the pressure on you and the city increases, placing you in imminent danger.", black, 20, 1200);

	endLabel.addComponent<Label>(200, 400, "You've outwitted me this time... My digital empire crumbles, and my chaotic dreams are extinguished. The code of your skill has proven mightier than my darkest creation. Farewell to my malevolent aspirations, at least for now.....", black, 20, 1200);

	label8.addComponent<Label>(200, 600, "If you would like to play the other subject, press the button!", black, 20, 1200);

	yesButton.addComponent<TransformComponent>(340.0f, 800.0f, 31, 51, 4);
	yesButton.addComponent<SpriteComponent>("assets/leoBut.png");
	yesButton.addGroup(groupButtons);

	//noButton.addComponent<TransformComponent>(985.0f, 200.0f, 31, 51, 4);
	//noButton.addComponent<SpriteComponent>("assets/cleoBut.png");
	//noButton.addGroup(groupButtons);

	wall1.addComponent<TransformComponent>(0.f, 0.f, 270, 1600, 1.f);
	wall1.addComponent<ColliderComponent>("wall");
	wall1.addComponent<SpriteComponent>("assets/pink32.png");

	wall2.addComponent<TransformComponent>(215.f, 260.f, 165, 55, 1.f);
	wall2.addComponent<ColliderComponent>("wall");
	wall2.addComponent<SpriteComponent>("assets/pink32.png");

	wall3.addComponent<TransformComponent>(0.f, 260.f, 465, 20, 1.f);
	wall3.addComponent<ColliderComponent>("wall");
	wall3.addComponent<SpriteComponent>("assets/pink32.png");

	wall4.addComponent<TransformComponent>(215.f, 640.f, 560, 55, 1.f);
	wall4.addComponent<ColliderComponent>("wall");
	wall4.addComponent<SpriteComponent>("assets/pink32.png");

	wall5.addComponent<TransformComponent>(0.f, 715.f, 485, 225, 1.f);
	wall5.addComponent<ColliderComponent>("wall");
	wall5.addComponent<SpriteComponent>("assets/pink32.png");

	wall6.addComponent<TransformComponent>(260.f, 840.f, 360, 165, 1.f);
	wall6.addComponent<ColliderComponent>("wall1");
	wall6.addComponent<SpriteComponent>("assets/pink32.png");

	wall7.addComponent<TransformComponent>(415.f, 1110.f, 90, 925, 1.f);
	wall7.addComponent<ColliderComponent>("wall1");
	wall7.addComponent<SpriteComponent>("assets/pink32.png");

	wall8.addComponent<TransformComponent>(1330.f, 950.f, 250, 270, 1.f);
	wall8.addComponent<ColliderComponent>("wall1");
	wall8.addComponent<SpriteComponent>("assets/pink32.png");

	wall9.addComponent<TransformComponent>(1515.f, 260.f, 700, 85, 1.f);
	wall9.addComponent<ColliderComponent>("wall");
	wall9.addComponent<SpriteComponent>("assets/pink32.png");

	wall10.addComponent<TransformComponent>(1080.f, 480.f, 125, 520, 1.f);
	wall10.addComponent<ColliderComponent>("wall1");
	wall10.addComponent<SpriteComponent>("assets/pink32.png");

	wall11.addComponent<TransformComponent>(1280.f, 595.f, 130, 520, 1.f);
	wall11.addComponent<ColliderComponent>("wall1");
	wall11.addComponent<SpriteComponent>("assets/pink32.png");

	wall12.addComponent<TransformComponent>(260.f, 765.f, 360, 165, 1.f);
	wall12.addComponent<ColliderComponent>("wall2");
	wall12.addComponent<SpriteComponent>("assets/pink32.png");

	wall13.addComponent<TransformComponent>(660.f, 1010.f, 360, 300, 1.f);
	wall13.addComponent<ColliderComponent>("wall2");
	wall13.addComponent<SpriteComponent>("assets/pink32.png");

	wall14.addComponent<TransformComponent>(1270.f, 950.f, 250, 270, 1.f);
	wall14.addComponent<ColliderComponent>("wall2");
	wall14.addComponent<SpriteComponent>("assets/pink32.png");

	wall15.addComponent<TransformComponent>(1340.f, 595.f, 130, 520, 1.f);
	wall15.addComponent<ColliderComponent>("wall2");
	wall15.addComponent<SpriteComponent>("assets/pink32.png");

	wall16.addComponent<TransformComponent>(1080.f, 480.f, 125, 520, 1.f);
	wall16.addComponent<ColliderComponent>("wall2");
	wall16.addComponent<SpriteComponent>("assets/pink32.png");

	wall17.addComponent<TransformComponent>(415.f, 1110.f, 90, 925, 1.f);
	wall17.addComponent<ColliderComponent>("wall2");
	wall17.addComponent<SpriteComponent>("assets/pink32.png");

	wall18.addComponent<TransformComponent>(250.f, 1110.f, 90, 1200, 1.f);
	wall18.addComponent<ColliderComponent>("wall3");
	wall18.addComponent<SpriteComponent>("assets/pink32.png");

	wall19.addComponent<TransformComponent>(1355.f, 835.f, 300, 270, 1.f);
	wall19.addComponent<ColliderComponent>("wall3");
	wall19.addComponent<SpriteComponent>("assets/pink32.png");

	wall20.addComponent<TransformComponent>(1080.f, 480.f, 125, 520, 1.f);
	wall20.addComponent<ColliderComponent>("wall3");
	wall20.addComponent<SpriteComponent>("assets/pink32.png");

	wall21.addComponent<TransformComponent>(630.f, 980.f, 300, 140, 1.f);
	wall21.addComponent<ColliderComponent>("wall3");
	wall21.addComponent<SpriteComponent>("assets/pink32.png");

	wall22.addComponent<TransformComponent>(1345.f, 100.f, 500, 520, 1.f);
	wall22.addComponent<ColliderComponent>("wall3");
	wall22.addComponent<SpriteComponent>("assets/pink32.png");

	/*wall1.addGroup(groupMap1);
	wall1.addGroup(groupMap2);
	wall1.addGroup(groupMap3);

	wall2.addGroup(groupMap1);
	wall2.addGroup(groupMap2);
	wall2.addGroup(groupMap3);
	
	wall3.addGroup(groupMap1);
	wall3.addGroup(groupMap2);
	wall3.addGroup(groupMap3);

	wall4.addGroup(groupMap1);
	wall4.addGroup(groupMap2);
	wall4.addGroup(groupMap3);

	wall5.addGroup(groupMap1);
	wall5.addGroup(groupMap2);
	wall5.addGroup(groupMap3);

	wall6.addGroup(groupMap1);

	wall7.addGroup(groupMap1);

	wall8.addGroup(groupMap1);

	wall9.addGroup(groupMap1);
	wall9.addGroup(groupMap2);
	wall9.addGroup(groupMap3);

	wall10.addGroup(groupMap1);

	wall11.addGroup(groupMap1);

	wall12.addGroup(groupMap2);

	wall13.addGroup(groupMap2);

	wall14.addGroup(groupMap2);
	
	wall15.addGroup(groupMap2);

	wall16.addGroup(groupMap2);

	wall17.addGroup(groupMap2);

	wall18.addGroup(groupMap3);

	wall19.addGroup(groupMap3);

	wall20.addGroup(groupMap3);

	wall21.addGroup(groupMap3);

	wall22.addGroup(groupMap3);*/

	help1.addComponent<TransformComponent>(1000.f, 80.f, 45, 45, 2.f);
	help1.addComponent<SpriteComponent>("assets/help/helpButGood1.png");
	help1.addGroup(groupHelp);
	
	help2.addComponent<TransformComponent>(1150.f, 80.f, 45, 45, 2.f);
	help2.addComponent<SpriteComponent>("assets/help/helpButGood2.png");
	help2.addGroup(groupHelp);
	
	help3.addComponent<TransformComponent>(1000.f, 80.f, 45, 45, 2.f);
	help3.addComponent<SpriteComponent>("assets/help/helpButGood1.png");
	help3.addGroup(groupHelp2);

	//--------------Module 9 help text -------------------

	std::ifstream fin1("assets/help/M9L3Help.txt", std::ios::in);
	std::string line;
	while (std::getline(fin1, line)) {
		help1TextM9.push_back(line);
		help1M9Label.push_back(new Label(200, 200, line, black, 20, 900));
	}
	fin1.close();
	
	std::ifstream fin2("assets/help/M9L4Help.txt", std::ios::in);
	line = "";
	while (std::getline(fin2, line)) {
		help2TextM9.push_back(line);
		help2M9Label.push_back(new Label(200, 200, line, black, 20, 900));
	}
	fin2.close();
	
	std::ifstream fin3("assets/help/M9L5Help.txt", std::ios::in);
	line = "";
	while (std::getline(fin3, line)) {
		help3TextM9.push_back(line);
		help3M9Label.push_back(new Label(200, 200, line, black, 20, 900));
	}
	fin3.close();

	//--------------Module 10 help text -------------------
	
	std::ifstream fin4("assets/help/M10L3Help.txt", std::ios::in);
	line = "";
	while (std::getline(fin4, line)) {
		help1TextM10.push_back(line);
		help1M10Label.push_back(new Label(200, 200, line, black, 20, 900));
		
	}
	fin4.close();
	
	std::ifstream fin5("assets/help/M10L4Help.txt", std::ios::in);
	line = "";
	while (std::getline(fin5, line)) {
		help2TextM10.push_back(line);
		help2M10Label.push_back(new Label(200, 200, line, black, 20, 900));
	}
	fin5.close();
	
	std::ifstream fin6("assets/help/M10L5Help.txt", std::ios::in);
	line = "";
	while (std::getline(fin6, line)) {
		help3TextM10.push_back(line);
		help3M10Label.push_back(new Label(200, 200, line, black, 20, 900));
	}
	fin6.close();

	//----------------------------------------------

	helpBg1.addComponent<TransformComponent>(0.f, 0.f, 768, 1024, 1.5f);
	helpBg1.addComponent<SpriteComponent>("assets/help/helpBg1.png");
	
	
	helpBg2.addComponent<TransformComponent>(0.f, 0.f, 768, 1024, 1.5f);
	helpBg2.addComponent<SpriteComponent>("assets/help/helpBg2.png");


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

	quest = CsvManager::readData("assets/files/M9_L4.txt");
	mini2 = new Minigame(quest, 300, 250, mouseCollider, event);

	quest = CsvManager::readData("assets/files/M9_L5.txt");
	mini3 = new Minigame(quest, 300, 250, mouseCollider, event);

	quest = CsvManager::readData("assets/files/M10_L3.txt");
	mini4 = new Minigame(quest, 300, 250, mouseCollider, event);

	quest = CsvManager::readData("assets/files/M10_L4.txt");
	mini5 = new Minigame(quest, 300, 250, mouseCollider, event);

	quest = CsvManager::readData("assets/files/M10_L5.txt");
	mini6 = new Minigame(quest, 300, 250, mouseCollider, event);

	check = new Label(337 + 840, 270 + 715, "CHECK", green, 32, 800);
}

void Game::openWindow()
{
	std::cout << "open window" << std::endl;
}

void Game::second()
{
	for (int i = 0; i < 7; i++)
	{
		mini1->clearQ();
		mini2->clearQ();
		mini3->clearQ();
		mini4->clearQ();
		mini5->clearQ();
		mini6->clearQ();
	}
	quest = CsvManager::readData("assets/files/M9_L3.txt");
	mini1 = new Minigame(quest, 300, 250, mouseCollider, event);

	quest = CsvManager::readData("assets/files/M9_L4.txt");
	mini2 = new Minigame(quest, 300, 250, mouseCollider, event);

	quest = CsvManager::readData("assets/files/M9_L5.txt");
	mini3 = new Minigame(quest, 300, 250, mouseCollider, event);

	quest = CsvManager::readData("assets/files/M10_L3.txt");
	mini4 = new Minigame(quest, 300, 250, mouseCollider, event);

	quest = CsvManager::readData("assets/files/M10_L4.txt");
	mini5 = new Minigame(quest, 300, 250, mouseCollider, event);

	quest = CsvManager::readData("assets/files/M10_L5.txt");
	mini6 = new Minigame(quest, 300, 250, mouseCollider, event);

	if (subject == "licences")
	{
		mini1 = mini1;
		mini2 = mini2;
		mini3 = mini3;
	}
	if (subject == "programming")
	{
		mini1 = mini4;
		mini2 = mini5;
		mini3 = mini6;
	}
	count++;
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
			/*else if (gameState == "endState")
			{
				gameState = "choice";
				break;
			}*/
			else if (gameState == "miniGameState1")
			{
				gameState = "mainGameState";
				player.getComponent<TransformComponent>().position.x = 300;
				player.getComponent<TransformComponent>().position.y = 300;

				break;

			}
			else if (gameState == "miniGameState2")
			{
				gameState = "mainGameState";
				player.getComponent<TransformComponent>().position.x = 300;
				player.getComponent<TransformComponent>().position.y = 300;
				break;
			}
			else if (gameState == "miniGameState3" || gameState == "help3GameState")
			{
				gameState = "mainGameState2";
				player.getComponent<TransformComponent>().position.x = 500;
				player.getComponent<TransformComponent>().position.y = 500;
				break;
			}
			else if (gameState == "help1GameState" || gameState == "help2GameState")
			{
				gameState = "mainGameState";
				player.getComponent<TransformComponent>().position.x = 500;
				player.getComponent<TransformComponent>().position.y = 500;

				break;

			}
			else
			{
				isRunning = false;
				break;
			}
		}
		else if (event.key.keysym.sym == SDLK_j)
		{
			if (gameState == "mainGameState")
			{
				gameState = "mainGameState2";
				mini1 = mini3;
				mini2 = mini3;
				break;
				
			}

			if (gameState == "mainGameState2")
			{
				gameState = "mainGameState3";
				mini1 = mini5;
				mini2 = mini6;
				break;
			}
		}
	}
	}
}

auto& map1Group(manager.getGroup(groupMap1));
auto& map2Group(manager.getGroup(groupMap2));
auto& map3Group(manager.getGroup(groupMap3));
auto& buttons(manager.getGroup(groupButtons));
auto& menus(manager.getGroup(groupMenu));
auto& players(manager.getGroup(groupPlayers));
auto& mouses(manager.getGroup(groupMouse));
auto& menus2(manager.getGroup(groupMenu2));
auto& menus3(manager.getGroup(groupMenu3));
auto& minigame1(manager.getGroup(groupMini1));
auto& minigame2(manager.getGroup(groupMini2));
auto& minigame3(manager.getGroup(groupMini3));
auto& helpl1(manager.getGroup(groupHelp));
auto& helpl2(manager.getGroup(groupHelp2));
auto& helpscr(manager.getGroup(groupHelpScreen));

void Game::update()
{
	manager.refresh();
	manager.update();
	mouseCollider.update();
	//std::cout << mouseCollider.point.x << " " << mouseCollider.point.y << std::endl;
	
	
	//-------------Game test purposes-------------------

	if (SDL_KEYDOWN)
	{
		if(event.key.keysym.sym == SDLK_1)
			gameState = "mainGameState";
		else if (event.key.keysym.sym == SDLK_2)
			gameState = "mainGameState2";
		else if (event.key.keysym.sym == SDLK_3)
			gameState = "mainGameState3";
	}

	//---------------------------------------------------
	
	if (gameState == "menu1")
	{
		for (auto& b : buttons)
		{
			if (b->tag == "startButton" || b->tag == "creditsButton")
				b->updateButton(mouseCollider, b->tag);
		}	
	}
	else if (gameState == "menu2")
	{
		for (auto& b : buttons)
		{
			if (b->tag == "leoButton" || b->tag == "cleoButton")
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
	else if (gameState == "menu3")
	{
		for (auto& b : buttons)
		{
			if (b->tag == "licences" || b->tag == "programming")
				b->updateButton(mouseCollider, b->tag);
		}
		if (subject == "licences")
		{
			mini1 = mini1;
			mini2 = mini2;
			mini3 = mini3;

			help1Label = help1M9Label;
			help2Label = help2M9Label;
			help3Label = help3M9Label;

		}
		if (subject == "programming")
		{
			mini1 = mini4;
			mini2 = mini5;
			mini3 = mini6;

			help1Label = help1M10Label;
			help2Label = help2M10Label;
			help3Label = help3M10Label;
		}
	}
	else if (gameState == "mainGameState")
	{
		for (auto& h : helpl1)
		{
			if (h->tag == "help1")
			{
				h->updateButton(mouseCollider, h->tag);
			}
			if (h->tag == "help2")
			{
				h->updateButton(mouseCollider, h->tag);
			}
		}
		for (auto cc : colliders)
		{
			Collision::AABB(player.getComponent<ColliderComponent>(), *cc);

			if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->tag == "wall")
			{
				player.getComponent<TransformComponent>().velocity* (-1);
			}

			else if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->tag == "wall1")
			{
				player.getComponent<TransformComponent>().velocity* (-1);
			}

			if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
			{
				if (cc->tag == "mini1")
				{
					if (!mini1->questions[6]->isCompleted())
					{
						gameState = "miniGameState1";
						break;
					}
				}
				if (cc->tag == "mini2")
				{
					if (!mini2->questions[6]->isCompleted())
					{
						gameState = "miniGameState2";
						break;
					}
				}
			}
		}
	}
	else if (gameState == "mainGameState2")
	{
		for (auto& h : helpl2)
		{
			if (h->tag == "help3")
			{
				h->updateButton(mouseCollider, h->tag);
			}
		}
		for (auto cc : colliders)
		{
			Collision::AABB(player.getComponent<ColliderComponent>(), *cc);

			if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->tag == "wall")
			{
				player.getComponent<TransformComponent>().velocity* (-1);
			}
			
			else if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->tag == "wall2")
			{
				player.getComponent<TransformComponent>().velocity* (-1);
			}

			if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
			{
				if (cc->tag == "mini3")
				{
					if (!mini3->questions[6]->isCompleted())
					{
						gameState = "miniGameState3";
						break;
					}
				}
			}
		}
	}
	else if (gameState == "mainGameState3")
	{
		for (auto cc : colliders)
		{
			Collision::AABB(player.getComponent<ColliderComponent>(), *cc);

			if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->tag == "wall")
			{
				player.getComponent<TransformComponent>().velocity* (-1);
			}

			else if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->tag == "wall3")
			{
				player.getComponent<TransformComponent>().velocity* (-1);
			}
		}

		for (auto& b : buttons)
		{
			if (b->tag == "bomb")
				b->updateButton(mouseCollider, b->tag);
		}
	}
	else if (gameState == "miniGameState1")
	{
		mini1->update();
		mini1->countdown.update();
		if (mini1->questions[6]->isCompleted() && !mini2->questions[6]->isCompleted())
			gameState = "mainGameState";

	}
	else if (gameState == "miniGameState2")
	{
		mini2->update();
		mini2->countdown.update();
		if (!mini1->questions[6]->isCompleted() && mini2->questions[6]->isCompleted())
			gameState = "mainGameState";
		if (mini1->questions[6]->isCompleted() && mini2->questions[6]->isCompleted())
		{
			gameState = "mainGameState2";
			player.getComponent<TransformComponent>().position.x = 300;
			player.getComponent<TransformComponent>().position.y = 300;
		}
	}
	else if (gameState == "miniGameState3")
	{
		mini3->update();
		mini3->countdown.update();
		if (mini3->questions[6]->isCompleted())
		{
			gameState = "mainGameState3";
			player.getComponent<TransformComponent>().position.x = 300;
			player.getComponent<TransformComponent>().position.y = 300;
		}
	}
	else if (gameState == "endState")
	{
		for (auto& b : buttons)
		{
			if (b->tag == "yes")
				b->updateButton(mouseCollider, b->tag);
		}
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
		//label3Credits.draw();
		label4Credits.draw();
		label5Credits.draw();
		label6Credits.draw();
		label7Credits.draw();
	}
	else if (gameState == "storyState")
	{
		credits.draw();
		labelStory.draw();
		label7Credits.draw();
	}
	else if (gameState == "endState")
	{
		credits.draw();
		endLabel.draw();
		//label7Credits.draw();
		label8.draw();

		for (auto& b : buttons)
		{
			if (b->tag == "yes") b->draw();
		}

		mouse.draw();
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
	else if (gameState == "menu3")
	{
		for (auto& n : menus3)
		{
			n->draw();
		}
		for (auto& b : buttons)
		{
			if (b->tag == "licences" || b->tag == "programming") b->draw();
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
		for (auto& h : helpl2)
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
		bomb.draw();
	}

	else if (gameState == "miniGameState1")
	{

		for (auto& m : minigame1)
		{
			m->draw();
		}
		mini1->draw();
		check->draw();
		mouse.draw();
	}
	else if (gameState == "miniGameState2")
	{

		for (auto& m : minigame2)
		{
			m->draw();
		}
		mini2->draw();
		check->draw();
		mouse.draw();
	}
	else if (gameState == "miniGameState3")
	{
		for (auto& m : minigame3)
		{
			m->draw();
		}
		mini3->draw();
		check->draw();
		mouse.draw();
	}
	else if (gameState == "help1GameState")
	{
		helpBg1.draw();
		for (int i = 0; i < help1Label.size(); i++)
		{
			help1Label[i]->setPos(300, 160 + i * 150);
			help1Label[i]->draw();
		}
		mouse.draw();
	}
	else if (gameState == "help2GameState")
	{
		helpBg2.draw();
		for (int i = 0; i < help2Label.size(); i++)
		{
			help2Label[i]->setPos(300, 160 + i * 100);
			help2Label[i]->draw();
		}
		mouse.draw();
	}
	else if (gameState == "help3GameState")
	{
		helpBg1.draw();
		for (int i = 0; i < help3Label.size(); i++)
		{
			help3Label[i]->setPos(300, 160 + i * 150);
			help3Label[i]->draw();
		}
		mouse.draw();
	}
	//else if (gameState == "choice")
	//{
	//	credits.draw();
	//	label8.draw();
	//	for (auto& b : buttons)
	//	{
	//		if (b->tag == "yes") b->draw();
	//	}
	//	mouse.draw();
	//}
	else if (gameState == "endLast")
	{
		credits.draw();
		endLabel.draw();
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