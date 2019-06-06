#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "core/debug-draw.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <glad/glad.h>
#include <GL/glu.h>

enum class MapTile { constructible = 0, path = 1, locked = 2 };

class Map {
public:
    Map();
    ~Map();

    glm::vec2 windowToGrid(float x, float y);
    glm::vec2 gridToWindow(unsigned int x, unsigned int y);
    MapTile getTile(unsigned int x, unsigned int y);

    void draw();
    void afficheMap(GLuint texture_id);


private:
    std::vector<MapTile> m_grid;
    unsigned int m_tileSize;
    unsigned int m_gridWidth;
    unsigned int m_gridHeight;
    DebugDraw m_dd;
};
