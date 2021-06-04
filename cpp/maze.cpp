#include "maze.h"
#include <unistd.h>

using std::cin;
using std::cout;
using std::vector;
using std::stack;
#define underline "\033[4;37m"

void Maze::Cell::init(const int r, const int c, const int walls, const bool v) {
    setPosition(r, c);
    setWalls(walls);
    setVisited(v);
}
Maze::Cell::Cell() { init(0, 0, 0); }
Maze::Cell::Cell(const int r, const int c) { init(r, c, 0); }
Maze::Cell::Cell(const int r, const int c, const int walls) { init(r, c, walls); }
bool Maze::Cell::visited() const { return visit; }
void Maze::Cell::setVisited(const bool v) { visit = v; }
int Maze::Cell::getRow() const { return row; }
int Maze::Cell::getColumn() const { return col; }
void Maze::Cell::removeWall(const int w) {
    if (w!=WALL_NORTH && w!=WALL_EAST && w!=WALL_SOUTH && w!=WALL_WEST)
        throw std::string("Illegal wall argument");
    walls &= ~w;
}
int Maze::Cell::getWalls() const { return walls & WALL_ALL; }
void Maze::Cell::setWalls(const int w) { walls = w & WALL_ALL; }
void Maze::Cell::setPosition(const int r, const int c) { row = r; col = c; }

std::ostream& operator<<(std::ostream& strm, const Maze::Cell& c) {
            if ((c.getWalls() & Maze::Cell::WALL_WEST) != 0) strm << '|';
            else strm << ' ';
            if ((c.getWalls() & Maze::Cell::WALL_SOUTH) != 0) strm << '_';
            else strm << ' ';

    return strm;
}

Maze::Maze(int _ROWS, int _COLS, int _solvation)
    : ROWS{ _ROWS }
    , COLS{ _COLS }
    , solvation{ _solvation }
{}

void Maze::start()
{
    // Randomize the random number function. 
    srand(time(NULL));

    // Create a 2-D array ([ROWS][COLS]) of Cell objects.
    Cell maze[ROWS][COLS];

    // For each Cell in the maze:
    for(int row = 0; row < ROWS; row++)
       for(int col = 0; col < COLS; col++) { 
          // set visited to false
          maze[row][col].setVisited(false);
          // set its position to its row and column in the maze
          maze[row][col].setPosition(row, col);
          // set the Cell's walls to Cell::WALL_ALL
          maze[row][col].setWalls(Cell::WALL_ALL);
    }

    //Create curX and curY variables and set them to a random position in the maze.
    int curX = 0;
    int curY = 0;

    // Create a vector of Cell objects named trail which will be used as a stack.
    vector<Cell> trail;

    // Create a vector of DIR values named live.
    vector<DIR> live;

    // Grab the Cell at the curX, curY position and push it on the trail stack.
    trail.push_back(maze[curX][curY]);
    ++visited;
    // While the trail stack is not empty do the following:
    while(trail.empty()==false) { // stay in here till display
        // Empty the live vector.

        live.clear();
        // Check the neighbors of the current cell to the north, east, south, and west.
        // If any of the neighbors have all four walls, add the direction to that 
        // neighbor to the live vector.
        if(curY)
            if(maze[curX][curY-1].getWalls()==Cell::WALL_ALL) // West has all walls
                live.push_back(WEST);
        if(curY<COLS-1)
            if(maze[curX][curY+1].getWalls()==Cell::WALL_ALL) // east has all walls
                live.push_back(EAST);
        if(curX)
            if(maze[curX-1][curY].getWalls()==Cell::WALL_ALL) // North has all walls
                live.push_back(NORTH);
        if(curX<ROWS-1)
            if(maze[curX+1][curY].getWalls()==Cell::WALL_ALL) // South has all walls
                live.push_back(SOUTH);
        // If the live vector is not empty:
        if(live.empty()==false) {
        // Choose one of the directions in the live vector at random
        // Remove the walls between the current cell and the neighbor in that direction
        // and Change curX and curY to refer to the neighbor
            maze[curX][curY].setVisited(true);
            switch(live[rand() % live.size()]) {
                case 0: //NORTH
                    maze[curX][curY].removeWall(Cell::WALL_NORTH);
                    maze[--curX][curY].removeWall(Cell::WALL_SOUTH);
                    visited++;
                    break;
                case 1: //SOUTH
                    maze[curX][curY].removeWall(Cell::WALL_SOUTH);
                    maze[++curX][curY].removeWall(Cell::WALL_NORTH);
                    visited++;
                    break;
                case 2: //EAST
                    maze[curX][curY].removeWall(Cell::WALL_EAST);
                    maze[curX][++curY].removeWall(Cell::WALL_WEST);
                    visited++;
                    break;
                case 3: //WEST
                    maze[curX][curY].removeWall(Cell::WALL_WEST);
                    maze[curX][--curY].removeWall(Cell::WALL_EAST);
                    visited++;
                    break;
            }
            // Push the new current cell onto the trail stack
            trail.push_back(maze[curX][curY]);
        }     //If the live vector was emtpy:
        else {
        // Pop the top item from the trail stack
        if(visited == ROWS*COLS){
            x_target = curX;
            y_target = curY;
            visited = 0;
        }
            trail.pop_back();
        // position of the top item in the trail stack.
            if(trail.empty()==false) {
               int n = trail.size();
               curX=trail[n-1].getRow();
               curY=trail[n-1].getColumn();
            }

        }
    }

    cout << y_target << "  " << x_target << std::endl;

    // Do the following to display the maze:
    int r, c;
    for (c=0; c<COLS; c++) {
        if (c == 0) cout << "\033[35m _";
        else cout << "__";
    }
    cout << '\n';
    for (r=0; r<ROWS; r++) {
        for (c=0; c<COLS; c++) {
            if(r == 0 && c == 0){
                if ((maze[r][c].getWalls() & Maze::Cell::WALL_WEST) != 0) 
                cout << '|';
                else cout << ' ';
                if ((maze[r][c].getWalls() & Maze::Cell::WALL_SOUTH) != 0) cout << underline << "\033[35m#\033[0m" << "\033[35m";
                else cout << "#";
            }
            else if(r == x_target && c == y_target){
                if ((maze[r][c].getWalls() & Maze::Cell::WALL_WEST) != 0) 
                cout << '|';
                else cout << ' ';
                if ((maze[r][c].getWalls() & Maze::Cell::WALL_SOUTH) != 0) cout << underline << "\033[35m*\033[0m" << "\033[35m";
                else cout << "*";
            }
            else
                cout << maze[r][c];
        }
        cout << "|\n";
    }
    cout << "\033[0m\n";

    usleep(5000000);

    if(solvation == 1){
        cout << "\033[1;32mNow you'll see the DFS algorithm for solving this maze\033[0m\n";
        cout << "\033[1;32mBut first remember:\033[0m\n";
        usleep(3000000);
        cout << "\033[1;36mFirst argument shows your horizontal movement\033[0m\n";
        cout << "\033[1;36mSecond argument shows your vertical movement\033[0m\n\n";
        usleep(3000000);
        for(int row = 0; row < ROWS; row++)
        for(int col = 0; col < COLS; col++) { 
            maze[row][col].setVisited(false);
            maze[row][col].setPosition(row, col);
        }

        int curX1 = 0;
        int curY1 = 0;

        vector<Cell> trail1;

        
        int size = trail1.size();

        vector<DIR> live1;

        trail1.push_back(maze[curX1][curY1]);
        
        maze[curX1][curY1].setVisited(true);
       
        while(maze[x_target][y_target].visited() == false) {
            live1.clear();
            //cout << "hi ..." <<std::endl;
            if(curY1)
                if((maze[curX1][curY1-1].getWalls() & Maze::Cell::WALL_EAST) == 0 && maze[curX1][curY1-1].visited() == false)
                    live1.push_back(WEST);
            if(curY1<COLS-1)
                if((maze[curX1][curY1+1].getWalls() & Maze::Cell::WALL_WEST) == 0 && maze[curX1][curY1+1].visited() == false)
                    live1.push_back(EAST);
            if(curX1)
                if((maze[curX1-1][curY1].getWalls() & Maze::Cell::WALL_SOUTH) == 0 && maze[curX1-1][curY1].visited() == false)
                    live1.push_back(NORTH);
            if(curX1<ROWS-1)
                if((maze[curX1+1][curY1].getWalls() & Maze::Cell::WALL_NORTH) == 0 && maze[curX1+1][curY1].visited() == false)
                    live1.push_back(SOUTH);

            if(live1.size() == 1) {
                switch(live1[0]) {
                    case 0: //NORTH
                        maze[--curX1][curY1].setVisited(true);
                        visited++;
                        break;
                    case 1: //SOUTH
                        maze[++curX1][curY1].setVisited(true);
                        visited++;
                        break;
                    case 2: //EAST
                        maze[curX1][++curY1].setVisited(true);
                        visited++;
                        break;
                    case 3: //WEST
                        maze[curX1][--curY1].setVisited(true);
                        visited++;
                        break;
                    }
                trail1.push_back(maze[curX1][curY1]); 
            }
            else if(live1.size() > 1){
                for (size_t i = 0; i < live1.size(); i++)
                {
                    if (live1[i])
                        switch(live1[i]) {
                            case 0: //NORTH
                                maze[--curX1][curY1].setVisited(true);
                                visited++;
                                break;
                            case 1: //SOUTH
                                maze[++curX1][curY1].setVisited(true);
                                visited++;
                                break;
                            case 2: //EAST
                                maze[curX1][++curY1].setVisited(true);
                                visited++;
                                break;
                            case 3: //WEST
                                maze[curX1][--curY1].setVisited(true);
                                visited++;
                                break;
                    }
                trail1.push_back(maze[curX1][curY1]);
                    }
                    
                }
                
            }
            else if(live1.empty() == true){
                if(visited < ROWS*COLS){
                    trail1.pop_back();
                    if(trail1.empty()==false) {
                    int n = trail1.size();
                    curX1=trail1[n-1].getRow();
                    curY1=trail1[n-1].getColumn();
                    }
                }
                else if(visited == ROWS*COLS){
                    trail1.pop_back();
                    if(trail1.empty()==false) {
                    int n = trail1.size();
                    curX1=trail1[n-1].getRow();
                    curY1=trail1[n-1].getColumn();
                    }
                    visited = 0;
                }
            }
            size = trail1.size();
        } 
        for (size_t i = 0; i < trail1.size(); i++)
        {
            cout << trail1[i].getColumn() << " " << trail1[i].getRow() << std::endl;
            usleep(10000);
        }
        
    }
}
