#pragma once

#include <glad/glad.h>
#include <GL/glu.h>
#include <vector>
#include <string>

struct pixel{
    int r, g, b;
};

struct type_Tower{
    int cad, pui, port, cout;
    float r,g,b;
};

class Tower {
public:
    Tower(float m_cadence, float m_puissance, float m_portee);
    ~Tower();

    /* Getters */
    float getCadence() const { return m_cadence; }
    float getPuissance() const { return m_puissance; }
    float getPortee() const { return m_portee; }

    /* Setters */
    void setCadence(float cad) { m_cadence = cad; }
    void setPuissance(float puis) { m_puissance = puis; }
    void setPortee(float port) { m_portee = port; }
    int isConstructible(std::vector<pixel> pixels, float x,float y, std::vector<int> coord_towers);

private:
    float m_cadence;
    float m_puissance;
    float m_portee;
};

std::vector<pixel> readPPM();
void afficheTower(GLuint texture, int x, int y);
void afficheCercle(int x, int y, int rayon, float r, float g, float b);
void Tir(float x_monstre, float y_monstre, float x_tour, float y_tour);





