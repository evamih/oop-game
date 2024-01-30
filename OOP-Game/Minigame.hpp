#pragma once
#include <vector>
#include "Question.hpp"
#include "Countdown.h"

class Minigame
{
private:
	int questionIdx = 0;
	SDL_Event eve;
	int rightAnswersCount = 0;
	Label* labelCompleted;
	Label* labelGameOver;
	SDL_Color white = { 255, 255, 255, 255 };
public:
	std::vector<Question*> questions;
	Countdown countdown;

public:
	Minigame(std::vector<std::string> _questions, int xpos, int ypos, Mouse& m, SDL_Event& e) : eve(e)
	{
		countdown.loadRects({1150, 800, 40, 40}, 2);
		countdown.start(300.f);

		for (auto& q : _questions)
		{
			questions.push_back(new Question(q, m, e, xpos, ypos));
		}
		labelCompleted = new Label(xpos+ 350, ypos+220, "COMPLETED", white, 30);
		labelGameOver = new Label(xpos + 350, ypos + 220, "GAME OVER", white, 30);
	}

	void update()
	{
		if (questionIdx - rightAnswersCount <= 2) {
			if (questionIdx < questions.size())
			{
				questions[questionIdx]->update();

				if (questions[questionIdx]->isCompleted()) {
					if (questions[questionIdx]->isCorrect())
					{
						rightAnswersCount++;
					}
					questionIdx++;
				}
			}
		}
		else {
			
		}
	}

	void draw()
	{	
		if (countdown.getTimeLeft() <= 0.0f)
		{
			labelGameOver->draw();
		}
		if (questionIdx - rightAnswersCount > 2)
		{
			labelGameOver->draw();
		}
		else if(questionIdx < questions.size())
		{
			questions[questionIdx]->draw();
			countdown.draw();
		}
		else
		{
			labelCompleted->draw();
		}
	}

	void setScore()
	{
		rightAnswersCount = 0;
	}

	int getScore() {
		return rightAnswersCount;
	}

	void clearQ()
	{
		questions.clear();
	}
	int sizeQ()
	{
		return questions.size();
	}
};