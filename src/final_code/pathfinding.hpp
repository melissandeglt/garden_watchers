/*#ifndef PATHFINDING_H
#define PATHFINDING_H

typedef struct Point{
	int x;
	int y;
	int cost;
	float heuri;
	float total_cost= cost+heuri;
}point;

float heuristic(int x1, int y1, int x2, int y2);
point findNeighbours(point my_point);
int isPath(point my_point);

class aStar {
public:
	

private:
};

#endif // PATHFINDING_H*/