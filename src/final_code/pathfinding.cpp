
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>


/*#include "pathfinding.hpp"

// calcul de la distance théorique jusqu'au point d'arrivée
float heuristic(int x1, int y1, int x2, int y2){
	return sqrt(pow((x1-x2),2)+pow((y1-y2),2));
}

// Les 4 voisins d'un point
point neighbours[4];
point findNeighbours(point my_point, point arrivee) {
    neighbours[0].x = my_point.x-1; 
    neighbours[0].y = my_point.y;
    //neighbours[0].cost = ?;
    neighbours[0].heuri = heuristic(neighbours[0].x,neighbours[0].y,arrivee.x,arrivee.y);
    neighbours[1].x = my_point.x; 
    neighbours[1].y = my_point.y-1;
    //neighbours[1].cost = ?;
    neighbours[1].heuri = heuristic(neighbours[1].x,neighbours[1].y,arrivee.x,arrivee.y);
    neighbours[2].x = my_point.x+1; 
    neighbours[2].y = my_point.y;
    //neighbours[2].cost = ?;
    neighbours[2].heuri = heuristic(neighbours[2].x,neighbours[2].y,arrivee.x,arrivee.y);
    neighbours[3].x = my_point.x; 
    neighbours[3].y = my_point.y+1;
    //neighbours[3].cost = ?;
    neighbours[3].heuri = heuristic(neighbours[3].x,neighbours[3].y,arrivee.x,arrivee.y);
    retrun neighbours;
}

// Retourne 1 si le point est un chemin et 0 sinon
/*
int isPath(point my_point){
	if (le point est un chemin){retrun 1;}
	else {return 0;}
}*/


