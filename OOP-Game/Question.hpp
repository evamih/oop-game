#pragma once

#include "Label.hpp"
#include "Button.h"
#include <vector>
#include <sstream>

class Question : public Component
{
private:
	Label* question;
	std::vector<Label*> answers;
	Button* confirmButton;
	std::vector<Button*> buttons;
	int correctAnswerIdx;
	int selectedAnswerIdx = -1;
	SDL_Texture* buttonTexture;
	SDL_Texture* confirmTexture;
	Mouse& mouse;
	SDL_Event& event;
	bool correct = false;
	bool complete = false;

public:
	Question(std::string line, Mouse& _mouse, SDL_Event& _event, int xpos, int ypos) : mouse(_mouse), event(_event)
	{
		buttonTexture = TextureManager::loadTexture("assets/assets2/radio_button.png");
		confirmTexture = TextureManager::loadTexture("assets/assets2/checkButton.png");

		std::stringstream ss(line);
		std::string element;
		std::vector<std::string> row;

		while (std::getline(ss, element, '@'))
		{
			row.push_back(element);
		}
			
		SDL_Color green = { 0, 255, 0, 255 };

		question = new Label(xpos, ypos, row[0], green, 15, 936);

		answers.push_back(new Label(xpos + 100, ypos + 150, row[1], green, 12, 800));
		buttons.push_back(new Button(buttonTexture, xpos, ypos + 150));
		answers.push_back(new Label(xpos + 100, ypos + 250, row[2], green, 12, 800));
		buttons.push_back(new Button(buttonTexture, xpos, ypos + 250));
		answers.push_back(new Label(xpos + 100, ypos + 350, row[3], green, 12, 800));
		buttons.push_back(new Button(buttonTexture, xpos, ypos + 350));
		answers.push_back(new Label(xpos + 100, ypos + 450, row[4], green,12, 800));
		buttons.push_back(new Button(buttonTexture, xpos, ypos + 450));

		correctAnswerIdx = std::stoi(row[5]);

		confirmButton = new Button(confirmTexture, xpos + 850, ypos + 700, false);
	}

	void draw() override
	{
		question->draw();
		for (Label* l : answers)
		{
			l->draw();
		}
		for (Button* b : buttons)
		{
			b->draw();
		}
		confirmButton->draw();
	}

	void update() override
	{
		int idx = 0;
		for (Button* b : buttons)
		{
			b->update(mouse, 1);

			if (b->isSelected && event.type == SDL_MOUSEBUTTONDOWN)
			{

				selectedAnswerIdx = idx;
			}

			idx++;
		}

		if (selectedAnswerIdx > -1) {
			buttons[selectedAnswerIdx]->srect.x = 17;
		}

		confirmButton->update(mouse, 1);

		if (confirmButton->isSelected && event.type == SDL_MOUSEBUTTONDOWN)
		{
			complete = true;
			if (selectedAnswerIdx == correctAnswerIdx) {
				correct = true;
			}
		}

	}

	bool isCompleted()
	{
		return complete;
	}

	bool isCorrect()
	{
		return correct;
	}

};