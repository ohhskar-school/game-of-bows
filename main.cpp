// Misc. C++ includes
#include <iostream>

// User Defined
#include "Game.hpp"

int main(){
  try{
    Game game;
    game.run();   
  } catch (std::exception& e){
    std::cout << "\nException: " << e.what() << std::endl;
  }
}