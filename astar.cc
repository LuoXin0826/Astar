#include <iostream>
#include <algorithm>

#include "astar.h"

using namespace std;

namespace astar{

Astar::Astar(
	vector<vector<int>> world,
	int flag_directions, 
	int flag_distance)
	: world_(world),
	flag_directions_(flag_directions),
	flag_distance_(flag_distance),
    find_goal_(false){
  	length_ = world.size();
  	if(length_ != 0){
  		width_ = world[0].size();
  	}else{
  		cout << "Input world is empty. Please check input." << endl;
  	}

  	visit_queue_ = priority_queue<Node*, vector<Node*>, CompareScore>(); // reset the visit queue
  	visit_queue_map_.clear(); // reset visit queue map
  	visited_nodes_.clear(); // reset visited nodes
 }

stack<Point> Astar::findPath(Point start, Point goal){
    Node* start_node = new Node(start);
	Node* goal_node = new Node(goal);
	stack<Point> path;
	if(!isValid_(start_node) || !isValid_(goal_node)){
		cout << "Invalid start or goal point. " << endl;
		return path;
	}
	visit_queue_.push(start_node);
	visit_queue_map_[start] = start_node;

	while(!visit_queue_.empty()){
		Node* current_node = visit_queue_.top();
		visit_queue_.pop();
		if(current_node->p == goal){
			goal_node = current_node;
			find_goal_ = true;
			break;
		}

		visit_queue_map_.erase(current_node->p);
		visited_nodes_[current_node->p] = current_node;

		vector<Node*> neighbors = getNeighbors_(current_node->p);
		for(const auto nbr: neighbors){
			double total_cost = current_node->g + getDistance_(current_node->p, nbr->p);

			// If the neighbor is not in visit queue, enqueue it in the visit queue
			if(visit_queue_map_.find(nbr->p) == visit_queue_map_.end()){
				nbr-> g = total_cost;
				nbr-> h = sqrt(pow((nbr->p.x-goal.x),2) + pow((nbr->p.y - goal.y),2));
				nbr-> parent = current_node;
				visit_queue_.push(nbr);
				visit_queue_map_[nbr->p] = nbr;
			}else{ // If the neighbor is already in the visit queue, upload its cost and parent
				Node* n = visit_queue_map_[nbr->p];
				if (n-> g > total_cost){
					n-> parent = current_node;
					n-> g = total_cost;
				}
			} 
		}

		if(find_goal_){
			break;
		}
	}

	if(find_goal_){
		Node* temp_node = goal_node;
		cout << "Valid path found!" << endl;
		cout << "Path length is: " << temp_node->getScore() << endl;
		while(temp_node != nullptr){
			path.push(temp_node->p);
			temp_node = temp_node->parent;
		}
		cout << "Number of way points: " << path.size() << endl;
	}else{
		cout << "Valid path not found!" << endl;
	}

	// release dynamic memory
	for(auto n:visited_nodes_){
		delete n.second;
	}

	return path;
}

void Astar::printPath(stack<Point> path){
	fstream fout;
    // Open an existing csv file or creates a new file.
    // Store the way points in the csv file
    fout.open("../path.csv", ios::out);

	while(!path.empty()){
		cout << "x: " << path.top().x << "  y: " << path.top().y << endl;
		fout << path.top().x << ", "
             << path.top().y << ", "
             << "\n";
		path.pop();
	}
	fout.close();
}

double Astar::getDistance_(Point p1, Point p2){
	if(flag_distance_ == 1){
		//mannhattan distance
		return abs(p1.x-p2.x) + abs(p1.y-p2.y);
	}else if(flag_distance_ == 2){
		//euclidean distance
		return sqrt(pow((p1.x-p2.x),2) + pow((p1.y - p2.y),2));
	}else{
		cerr << "flag_distance type not recognized." << endl;
        abort();
	}
	return -1;
}

bool Astar::isValid_(Node* n){
	// check if out of world boundary
	if(n->p.x < 0 || n->p.x >= length_ || n->p.y < 0 || n->p.y >= width_){
		return false;
	}
	// check if blocked
	if(world_[n->p.x][n->p.y] == 1){
		return false;
	}

	// check if visited
	if(visited_nodes_.find(n->p) != visited_nodes_.end()){
		return false;
	}
	return true;
}

vector<Node*> Astar::getNeighbors_(Point p){
	if(flag_directions_ != 4 && flag_directions_ != 8){
		cerr << "flag_direction type is not recognized." << endl;
        abort();
	}
	vector<Node*> neighbors;
	vector<pair<int,int>> directions= {{1,0},{0,1},{-1,0},{0,-1}};
	for(const auto& direction : directions){
		Point new_p = {p.x + direction.first, p.y +direction.second};
		Node* new_node = new Node(new_p);
		if(isValid_(new_node)){
			neighbors.push_back(new_node);
		}
	}

	if (flag_directions_ == 8){
		vector<pair<int,int>> directions= {{1,1},{1,-1},{-1,1},{-1,-1}};
		for(const auto& direction : directions){
			Point new_p = {p.x + direction.first, p.y +direction.second};
			Node* new_node = new Node(new_p);
			if(isValid_(new_node)){
				neighbors.push_back(new_node);
			}
		}
	}

	return neighbors;
};
}