#include <bits/stdc++.h>
#include <vector>
#include <unordered_map>
#include <queue>
#include <math.h>
#include <fstream>

using namespace std;

namespace astar{

struct Point{
	// x coordinate of 2D grid map
	int x;
	// y coordinate of 2D grid map
	int y;

	bool operator == (const Point& other) const{
    return (x == other.x && y == other.y);
	}
};

struct Node{
	Point p;
	//moving cost
	double g;
	//Heuristic cost
	double h;

	Node* parent;

	Node(
		Point input_p,
		Node* input_parent = nullptr)
	: p(input_p),
	  g(0),
	  h(0),
	  parent(input_parent){}

	double getScore(){
		return g + h;
	} 
};

struct CompareScore { 
    bool operator()(Node* const& n1, Node* const& n2) 
    { 
        return n1->getScore() > n2->getScore(); 
    } 
};

struct PointHasher { 
    size_t operator()(const Point& p) const
    { 
        auto hash1 = hash<int>{}(p.x); 
        auto hash2 = hash<int>{}(p.y) << 16;
        return hash1 ^ hash2;
    } 
};  

// This Astar class computes the shortest path in 2D grid with obstacles
// given the start node and goal node.
class Astar{
public:
	// size of the world: length*width
	// flag_directions: 4(4 nodes as neighbors) or 8(8 nodes as negihbors)
	// flag_distance:  1(manhattan distance) or 2(euclidean distance)
	Astar(
		vector<vector<int>> world,
		int flag_directions, 
		int flag_distance);


	stack<Point> findPath(		
		Point start, 
		Point goal);

	void printPath(stack<Point> path);

private: 
	vector<vector<int>> world_;
	int length_;
	int width_;

	int flag_directions_;
	int flag_distance_;

	bool find_goal_;

	priority_queue<Node*, vector<Node*>, CompareScore> visit_queue_;
	unordered_map<Point, Node*, PointHasher> visit_queue_map_; // map for storing nodes in visit queue
	unordered_map<Point, Node*, PointHasher> visited_nodes_; // map for storing visited nodes

	double getDistance_(Point p1, Point p2);

	bool isValid_(Node* n);

	vector<Node*> getNeighbors_(Point p);
};
}
