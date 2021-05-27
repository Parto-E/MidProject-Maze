#include "maze.h"
#include <iostream>

int main(void){


   int ROWS;
   int COLS;

   std::cout << "Please enter the number of ROWS and COLOUMNS respectively" << std::endl;
   std::cin >> ROWS >> COLS;

   Maze m{ROWS, COLS};

   m.start();

   return 0;
} 