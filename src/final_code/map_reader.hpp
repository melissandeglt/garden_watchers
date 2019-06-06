#ifndef MAP_READER_H
#define MAP_READER_H

struct mapNode{
	int id;
	int type;
	int x, y;
	int adj;
};


std::vector<mapNode> loadITD();

#endif // MAP_READER_H