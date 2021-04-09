#include <iostream>
#include <fstream>
#include "astar.h"

using namespace std;

// Read the start and goal position as well as the flags
// Construct the world as a 2D matrix. 0 (traversable), 1 (obstacle)
vector<vector<int>> parseCSV()
{
    ifstream data("../input.csv");
    if(!data.good()){
    	cerr << "Input csv file not found! " << endl;
        abort();
    }
    string line;
    vector<vector<int>> input;

    // Read the start, goal points and flags
    // Construct the regtangular world
    int col_size = 0;
    int cunt_line = 0;
    while(getline(data,line)){
        stringstream lineStream(line);
        string cell;
        vector<int> parsedRow;
        while(getline(lineStream,cell,',')){
            parsedRow.push_back(stoi(cell));
        }
        // Check the input size for start and goal points
        if(cunt_line == 0 && parsedRow.size() != 4){
            cerr << "Invalid start or goal points, please check the input size. " << endl;
        }
        // Check the input size for flags
        if(cunt_line == 1 && parsedRow.size() != 2){
            cerr << "Invalid falgs, please check the input size. " << endl;
        }
        // Ensure the map is a rectangular
        if(cunt_line > 1){
            if(col_size == 0)
                col_size = parsedRow.size();
            else if(parsedRow.size() != col_size){
                cerr << "Map is not a rectangular. " << endl;
                abort();
            }
        }
        cunt_line++;
        input.push_back(parsedRow);
    }
    return input;
}

int main(){
	vector<vector<int>> input = parseCSV();
    // Set the start and goal points
    astar::Point start = {input[0][0], input[0][1]};
    astar::Point goal = {input[0][2], input[0][3]};

	// Set flags
	int flag_directions = input[1][0]; 
	int flag_distance = input[1][1];
	
    // Set up world
    vector<vector<int>> world;
    for(int i=2; i<input.size(); i++){
        world.push_back(input[i]);
    }

	astar::Astar astar(world, flag_directions, flag_distance);
	stack<astar::Point> path = astar.findPath(start, goal);
	astar.printPath(path);
	return 0;
}