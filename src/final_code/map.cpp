#include "map.hpp"
#include "general.hpp"

#include <glad/glad.h>
#include <Box2D/Box2D.h>
#include "core/constants.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stb_image/stb_image.h>

Map::Map() : m_tileSize(800/21)
{
    m_gridWidth = WINDOW_WIDTH / m_tileSize;
    m_gridHeight = WINDOW_HEIGHT / m_tileSize;
    m_grid.resize(m_gridWidth * m_gridHeight);

    for (int i = 0; i < m_grid.size(); i++) {
        if (i % 2 == 0) {
            m_grid[i] = MapTile::constructible;
        } else {
            m_grid[i] = MapTile::locked;
        }
    }
}

Map::~Map()
{
}

glm::vec2 Map::windowToGrid(float x, float y) {
    unsigned int tileX = x / WINDOW_WIDTH * m_gridWidth;
    unsigned int tileY = y / WINDOW_HEIGHT * m_gridHeight;
    return glm::vec2(tileX, tileY);
}

glm::vec2 Map::gridToWindow(unsigned int x, unsigned int y) {
    float posX = WINDOW_WIDTH / m_gridWidth * x + m_tileSize / 2;
    float posY = WINDOW_HEIGHT / m_gridHeight * y + m_tileSize / 2;
    return glm::vec2(posX, posY);
}

MapTile Map::getTile(unsigned int x, unsigned int y) {
    return m_grid.at(y * m_gridHeight + x);
}

void Map::afficheMap(GLuint texture_id){

    glBindTexture(GL_TEXTURE_2D, texture_id);
        glPushMatrix();
        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex2f(0, WINDOW_HEIGHT);   // bas gauche
            glTexCoord2f(1, 1); glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);    // bas droite
            glTexCoord2f(1, 0); glVertex2f(WINDOW_WIDTH, 0);     // haut droite
            glTexCoord2f(0, 0); glVertex2f(0, 0);    // haut gauche
        glEnd();
        glPopMatrix();

        // Unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);
}

void Map::draw() {
    for (int x = m_tileSize; x < WINDOW_WIDTH; x++) {
        m_dd.DrawSegment(b2Vec2(x, 0), b2Vec2(x, WINDOW_HEIGHT), b2Color(255, 255, 255, 1));
        x += m_tileSize;
    }

    for (int y = m_tileSize; y < WINDOW_HEIGHT; y++) {
        m_dd.DrawSegment(b2Vec2(0, y), b2Vec2(WINDOW_WIDTH, y), b2Color(255, 255, 255, 1));
        y += m_tileSize;
    }
}

