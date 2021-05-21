#include "cell.h"

Cell::Cell(int Width, int Height)
    : m_nMazeWidth{ Width }
    , m_nMazeHeight{ Height }
{
    //m_maze = std::make_shared<int> (new int[m_nMazeWidth*m_nMazeHeight]);
    m_maze = new int[m_nMazeHeight*m_nMazeWidth];
    //std::memset( m_maze, 0x00, m_nMazeWidth*m_nMazeHeight*sizeof(int));

    m_stack.push(std::make_pair(0, 0));
    m_maze[0] = CELL_VISITED;
    m_nVisitedcells = 1;
}

void Cell::Start()
{
    std::cout<< "qable offset" <<std::endl;
    auto offset = [&](int x, int y)
    {
        return (m_stack.top().second + y) * m_nMazeWidth + (m_stack.top().first + x);
    };

    //while(m_stack.top().first != m_nMazeWidth - 1 && m_stack.top().second != m_nMazeHeight - 1){
        if(m_nVisitedcells < m_nMazeWidth*m_nMazeHeight)
        {
            std::cout<< "avale avalin if" <<std::endl;
            std::cout<< m_nVisitedcells <<std::endl;
            std::vector<int> neighbours;

            //North neighbour
            if(m_stack.top().second > 0 && (m_maze[offset(0, -1)]& CELL_VISITED) == 0)
                neighbours.push_back(0);
            std::cout<< "bade if north" <<std::endl;
            //East neighbour
            if(m_stack.top().first < m_nMazeWidth - 1 && (m_maze[offset(1, 0)]& CELL_VISITED) == 0)
                neighbours.push_back(1);
            std::cout<< "bade if east" <<std::endl;
            //South neighbour
            if(m_stack.top().second < m_nMazeHeight - 1 && (m_maze[offset(0, 1)]& CELL_VISITED) == 0)
                neighbours.push_back(2);
            //West neighbour
            if(m_stack.top().first > 0 && (m_maze[offset(-1, 0)]& CELL_VISITED) == 0)
                neighbours.push_back(3);
            
            if(!neighbours.empty())
            {
                int next_cell_direction = neighbours[rand() % neighbours.size()];
                std::cout<< "qable switch" << std::endl;
                switch(next_cell_direction)
                {
                    case 0: //NORTH
                        m_maze[offset(0, 0)] |= CELL_PATH_N;
                        m_maze[offset(0, -1)] |= CELL_PATH_S;
                        m_stack.push(std::make_pair((m_stack.top().first + 0), (m_stack.top().second - 1)));
                        break;
                    case 1: //EAST
                        m_maze[offset(0, 0)] |= CELL_PATH_E;
                        m_maze[offset(1, 0)] |= CELL_PATH_W;
                        m_stack.push(std::make_pair((m_stack.top().first + 1), (m_stack.top().second + 0)));
                        break;
                    case 2: //SOUTH
                        m_maze[offset(0, 0)] |= CELL_PATH_S;
                        m_maze[offset(0, 1)] |= CELL_PATH_N;
                        m_stack.push(std::make_pair((m_stack.top().first + 0), (m_stack.top().second + 1)));
                        break;
                    case 3: //WEST
                        m_maze[offset(0, 0)] |= CELL_PATH_W;
                        m_maze[offset(-1, 0)] |= CELL_PATH_E;
                        m_stack.push(std::make_pair((m_stack.top().first - 1), (m_stack.top().second + 0)));
                        break;
                }

                std::cout<< "bade switch" <<std::endl;
                //NEw Cell
                m_maze[offset(0, 0)] |= CELL_VISITED;
                m_nVisitedcells++;
            }
            else
            {
                std::cout<< "pop kardan" <<std::endl;
                m_stack.pop();
            }
        }
    //}

    std::cout<< "qable show" <<std::endl;
    for(int x = 0; x < m_nMazeWidth; x++)
    {
        for(int y = 0; y < m_nMazeHeight; y++)
        {
            if(m_maze[y*m_nMazeWidth + x]& CELL_VISITED)
            std::cout<< "_ ";
            else
            std::cout<< "| ";
        }
        std::cout<< std::endl;
    }

}