#include "map.hpp"
#include "map_reader.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iterator>

using namespace std;

std::vector<mapNode> loadITD()
{
	ifstream file("./data/map.itd", ios::in | ios::binary);  // on ouvre le fichier en lecture
	string a, ligne;
	std::vector<string> texteITD;
	std::vector<mapNode> nodes;

	if(file.is_open())  // si l'ouverture a réussi
	{       
		fprintf(stderr, "Fichier ITD ouvert\n" );
		while(getline(file, ligne))
		{
			texteITD.push_back(std::move(ligne));
		}

		mapNode myNode;
		for (int i=9; i<texteITD.size(); i++){
			sscanf (texteITD[i].c_str(),"%d %d %d %d",&myNode.id, &myNode.type, &myNode.x, &myNode.y);
			nodes.push_back(myNode);  		
		}
		 for (int i=10; i<texteITD.size(); i++){
			sscanf (texteITD[i].c_str(),"%*d %*d %*d %*d %d",&nodes[i-9].adj);	
		}


			file.close();  // on ferme le fichier
	}
	else  
			fprintf(stderr, "Erreur pour ouvrir le fichier ITD !\n" );

	return nodes;

}


