#include "Menu.hpp"

Menu::Menu() {}

Menu::~Menu() {}

void Menu::addButton(int x, int y) {
	Button newButton(x, y);
	buttons.push_back(newButton);
}


int Menu::handleMouseClick(int mouseX, int mouseY) {
	SDL_Point mousePoint = { mouseX, mouseY };

	for (size_t i = 0; i < buttons.size(); i++) {
		if (SDL_PointInRect(&mousePoint, &buttons[i].pos)) {
			return i; // se returneaza indicele butonului
		}
	}

	return -1; // butonul nu este selectat
}

