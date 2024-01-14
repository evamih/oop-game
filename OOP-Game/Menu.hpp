#pragma once

#include "Button.hpp"

class Button;
#include <vector>

class Menu {

private:
	std::vector<Button> buttons;

public:
	Menu();
	~Menu();

	void addButton(int x, int y);
	int handleMouseClick(int mouseX, int mouseY); // indicele butonului selectat
};