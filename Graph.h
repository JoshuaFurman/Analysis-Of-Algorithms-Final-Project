#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <string>
#include <sstream>
#include <map>

using namespace std;

// This structure is for storing the data for a cell in the maze.
struct GameCell
{
    // This holds the binary string read in from the input file.
    string moves;

    vector<pair<GameCell*, char> > neighbors;
    bool discovered = false;
    bool start = false;
    bool end = false;
    int level;
    int row;
    int column;
};

 // This class is for representing the whole maze.
class GameBoard
{
public:
    // This vector holds pointers to each cell.
    vector<GameCell*> cells;
    // This vector is used for storing the path from the start cell to the end cell.
    vector<char> start_to_goal;
    // This flag is used in the DFS function for determining when you've reached the end.
    bool reached_end = false;

    // This function adds a new cell to the graph.
    void addCell(GameCell &new_cell)
    {
        cells.push_back(&new_cell);
    }

    // This is a utility function for finding a specific cell in the graph and
    // returning a pointer to that cell.
    GameCell* findCell(int level_, int row_, int column_)
    {
        for(GameCell* cell : cells)
        {
            if(cell->level == level_ && cell->row == row_ && cell->column == column_)
            {
                return cell;
            }
        }
        throw("Cell not found!");
    }

    // This function connects a cell to all the cells that it can move to by
    // iterating through the binary string read in from the input.
    void addNeighbors(GameCell* cell)
    {
        if(cell->moves[0] == '1')
        {
            cell->neighbors.push_back(make_pair(findCell(cell->level, cell->row-1, cell->column), 'N'));
        }
        if(cell->moves[1] == '1')
        {
            cell->neighbors.push_back(make_pair(findCell(cell->level, cell->row, cell->column+1), 'E'));
        }
        if(cell->moves[2] == '1')
        {
            cell->neighbors.push_back(make_pair(findCell(cell->level, cell->row+1, cell->column), 'S'));
        }
        if(cell->moves[3] == '1')
        {
            cell->neighbors.push_back(make_pair(findCell(cell->level, cell->row, cell->column-1), 'W'));
        }
        if(cell->moves[4] == '1')
        {
            cell->neighbors.push_back(make_pair(findCell(cell->level+1, cell->row, cell->column), 'U'));
        }
        if(cell->moves[5] == '1')
        {
            cell->neighbors.push_back(make_pair(findCell(cell->level-1, cell->row, cell->column), 'D'));
        }
    }

    // Here is a variation of DFS that ends when it reaches a specific node/cell.
    // It also stores the path from the start to the end in the start_to_goal vector. 
    void DFS(GameCell* cell)
    {
        cell->discovered = true;

        if(cell->end == true)
        {
            reached_end = true;
        }

        for(auto neighbor : cell->neighbors)
        {
            if(neighbor.first->discovered == false)
            {
                DFS(neighbor.first);
            }
            if(reached_end == true)
            {
                start_to_goal.push_back(neighbor.second);
                return;
            }
        }
    }
};
#endif
