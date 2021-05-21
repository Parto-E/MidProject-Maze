#include <iostream>
#include "cell.h"

int main(){
   
   int width, Height;
   std::cout << "Please enter width and height of the maze respectively:" << std::endl;
   std::cin>> width >> Height;

   Cell game{width, Height};
   game.Start();

   return 0;
}