#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "core/debug-draw.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <glad/glad.h>
#include <GL/glu.h>
#include "map_reader.hpp"

struct coord
{
    float x,y;
};

class Monster {
public:
    Monster(float m_pv, mapNode m_actualNode, mapNode m_nextNode);
    ~Monster();

    //void Monster::PathFinding();
    void avance(std::vector<mapNode> nodes, GLuint* texture);
    int suivre_chemin(mapNode sortie, std::vector<mapNode> nodes, GLuint* texture);
    coord getCoord();
    int degats(int degat);
    void drawPVMonster();

private:
    float m_pv, m_pv_total;
    mapNode m_actualNode;
    mapNode m_nextNode;
    int m_a=0, m_b=1, m_i=1, m_j=0;
};
