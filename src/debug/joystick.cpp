#include "joystick.hpp"
#include <cassert>
#include <iostream>
namespace gamelib2{

  Joystick::~Joystick(){
    for(auto &s : sprites){
      delete s;
    }
  }

  void Joystick::init(std::vector<std::string> &in_filenames){

    assert(in_filenames.size() == 12);
    for(auto &s : in_filenames){
      std::cout << s << std::endl;
      sprites.emplace_back(new Sprite(s, 1, 1));
      sprites.back()->setOrigin(0, 0);
    }
    inited = true;
  }
  void Joystick::update(const int in_states[]){
    for(size_t i=0;i<InputState::Totalevents; ++i){
      states[i] = in_states[i];
    }
  }

  void Joystick::render(sf::RenderTarget &target){
    assert(inited);

    bool dpad_centered = true;
    sprites[BG]->setPosition(x,y);
    sprites[BG]->render(target);

    if(states[Up]){
      sprites[DPAD_UP]->setPosition(x,y);
      sprites[DPAD_UP]->render(target);
      dpad_centered = false;
    }if (states[Down]){
      sprites[DPAD_DOWN]->setPosition(x,y);
      sprites[DPAD_DOWN]->render(target);
      dpad_centered = false;

    }if (states[Left]){
      sprites[DPAD_LEFT]->setPosition(x,y);
      sprites[DPAD_LEFT]->render(target);
      dpad_centered = false;

    }if (states[Right]){
      sprites[DPAD_RIGHT]->setPosition(x,y);
      sprites[DPAD_RIGHT]->render(target);
      dpad_centered = false;
    }if(dpad_centered){
      sprites[DPAD_CENTERED]->setPosition(x,y);
      sprites[DPAD_CENTERED]->render(target);
    }

    // fire 1
    if (states[FireDown]){
      sprites[BUTTON_BLUE]->setPosition(x,y);
      sprites[BUTTON_BLUE]->render(target);
    }

    // fire 2
    if (states[FireDown2]){
      sprites[BUTTON_YELLOW]->setPosition(x,y);
      sprites[BUTTON_YELLOW]->render(target);
    }

    // fire 3
    if (states[FireDown3]){
      sprites[BUTTON_RED]->setPosition(x,y);
      sprites[BUTTON_RED]->render(target);
    }

    // fire 4
    if (states[FireDown4]){
      sprites[BUTTON_GREEN]->setPosition(x,y);
      sprites[BUTTON_GREEN]->render(target);
    }
  }

}
