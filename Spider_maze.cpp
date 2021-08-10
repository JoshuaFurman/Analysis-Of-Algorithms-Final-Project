#include <iostream>
#include <map>
#include <fstream>
#include "Graph.h"

using namespace std;

int main()
{
    // These variables hold the data read in from the input file.
    int num_of_mazes;
    int levels, rows, columns;
    int start_level, start_row, start_column;
    int end_level, end_row, end_column;

    // Declares the name for the output file.
    string output_file_name = "output.txt";

    // An fstream object is created and the user is asked for the input file name.
    string input_file_name;
    ifstream input_file;

    while(true)
    {
        cout << "Please enter file name: " << endl;
        cin >> input_file_name;

        // The file is opened here.
        input_file.open(input_file_name);
        if(input_file.is_open())
        {
            break;
        }
        else
        {
            cout << "Had some trouble opening the file... Try again" << endl << endl;
            continue;
        }
    }

    // This reads the first number in the file which is the number of mazes and
    // creates a for loop that iterates through all the mazes in the input file.
    input_file >> num_of_mazes;
    for(int i = 0; i < num_of_mazes; i++)
    {
        // The graph is created here for the following maze.
        GameBoard game;

        // Information about the current maze is read in and saved.
        input_file >> levels >> rows >> columns;
        input_file >> start_level >> start_row >> start_column;
        input_file >> end_level >> end_row >> end_column;

        // This nested for loop is used to loop through the cells in the maze
        // and a new node/cell is created and added to the graph each time.
        for(int i = 0; i < levels; i++)
        {
            for(int j = 0; j < rows; j++)
            {
                for(int k = 0; k < columns; k++)
                {
                    GameCell *cell = new GameCell;
                    input_file >> cell->moves;
                    cell->level = i;
                    cell->row = j;
                    cell->column = k;

                    // This if/else block sets the flags used for identifying
                    // the start and end cell in the maze.
                    if(i == start_level && j == start_row && k == start_column)
                    {
                        cell->start = true;
                    }
                    else if(i == end_level && j == end_row && k == end_column)
                    {
                        cell->end = true;
                    }
                    game.addCell(*cell);
                }
            }
        }

        // This for loop loops through all the cells in the graph and creates
        // the proper edges connecting it to other cells.
        for(GameCell* cell : game.cells)
        {
            game.addNeighbors(cell);
        }

        // A DFS is called on the graph starting from the start node.
        game.DFS(game.findCell(start_level, start_row, start_column));

        // The output file is opened here and the path saved by DFS is appened to
        // the file.
        ofstream output_file;
        output_file.open(output_file_name, ios::app);
        for(int i = game.start_to_goal.size()-1; i > 0;i--)
        {
            output_file << game.start_to_goal[i] << ' ';
        }
        output_file << '\n';
        output_file.close();
    }
    input_file.close();

    cout << "The solution paths have been written to the file: output.txt" << endl;

    return 0;
}
