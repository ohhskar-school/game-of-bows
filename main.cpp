// // Misc. C++ includes
// #include <iostream>

// // User Defined
// #include "States/GameState.hpp"

// int main(){
//   try{
//     GameState game();
//     game.run();
//   } catch (std::exception& e){
//   }
// }

#include "Application.hpp"

#include <iostream>
#include <stdexcept>

int main() {
  try {
    Application app;
    app.run();
  } catch (std::exception& e) {
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }
}
