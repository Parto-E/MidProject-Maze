#ifndef __CELL_H_
#define __CELL_H_

#include <iostream>
//#include <memory>
#include <stack>
#include <cstring>
#include <vector>

class Cell {
private:
    int m_nMazeWidth;
    int m_nMazeHeight;
    int m_nVisitedcells;
    std::stack<std::pair<int, int>> m_stack;
    //std::shared_ptr<int> m_maze = std::make_shared<int> ();
    int* m_maze;
public:
    enum
    {
        CELL_PATH_N = 0x01,
        CELL_PATH_E = 0x02,
        CELL_PATH_S = 0x04,
        CELL_PATH_W = 0x08,
        CELL_VISITED =0x10,
    };
    Cell(int Width, int Height);
    void Start();


};

#endif 