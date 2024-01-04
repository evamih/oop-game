#include "Button.hpp"

Button::Button(int xpos, int ypos){
  
    pos.x = xpos;
    pos.y = ypos;

    pos.w = 100;
    pos.h = 60;
}

Button::~Button() {
    
}

void Button::update(Mouse& mouse) {
    if (SDL_HasIntersection(&pos, &mouse.point)) {
        isSelected = true;
    }
    else {
        isSelected = false;
    }
}