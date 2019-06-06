#include "tower.hpp"
#include "general.hpp"

#include <glad/glad.h>
#include <stdio.h>
#include <GL/glu.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "core/constants.hpp"
#include <math.h>


using namespace std;
static const int CIRCLE_SUBDIVS = 2<<5;

Tower::Tower(float cad, float puis, float port) : m_cadence(cad), m_puissance(puis), m_portee(port) {
    printf("Tour créée\n");
}

Tower::~Tower() {
    printf("Tour détruite\n");
}

int Tower::isConstructible(std::vector<pixel> pixels,float x,float y, std::vector<int> coord_towers){
    if(pixels[(int(y)-1)*210+int(x)].r==255){
        int libre=1;
        for(int i=0; i<coord_towers.size(); i+=2){
            if((x>(coord_towers[i]-5*3.8)) && (x<(coord_towers[i]+5*3.8)) && (y>(coord_towers[i+1]-5*3.8)) && (y<(coord_towers[i+1]+5*3.8))){
                libre=0;
            }
        }
        if(libre==1){
            printf("pixel :%d\n", (y-1)*210+x);
            printf("x:%f y:%f\n",x,y);
            printf("Constructible\n");
            return 1;
        }else printf("Il y a déjà une tour ici, tu ne peux pas construire\n");
    }
    else {
        printf("Pas constructible\n");
        return 0;
    }

}

std::vector<pixel> readPPM(){
    std::vector<pixel> pixels;
    int width, height;

    FILE* F;
    F = fopen("./images/map.ppm", "r");
    if (!F) {
        printf("On ne peut pas ouvrir le PPM %s", "./images/map.ppm");
    }

    fscanf(F,"%*s %d %d %*d",&width,&height);

    for(int i=0;i<width*height;i++)
    {
        int red,green,blue;
        pixel myPixel;
        fscanf(F,"%d %d %d",&red,&green,&blue);
        myPixel.r=red;
        myPixel.g=green;
        myPixel.b=blue;
        pixels.push_back(myPixel);

    }
    fclose(F);
    return pixels;
}

void afficheTower(GLuint texture, int x, int y){

    glBindTexture(GL_TEXTURE_2D, texture);
        glPushMatrix();
            glBegin(GL_QUADS);
                glTexCoord2f(0, 1); glVertex2f(x-WINDOW_WIDTH/24, y-WINDOW_HEIGHT/24);   // bas gauche
                glTexCoord2f(1, 1); glVertex2f(x+WINDOW_WIDTH/24, y-WINDOW_HEIGHT/24);    // bas droite
                glTexCoord2f(1, 0); glVertex2f(x+WINDOW_WIDTH/24, y+WINDOW_HEIGHT/24);     // haut droite
                glTexCoord2f(0, 0); glVertex2f(x-WINDOW_WIDTH/24, y+WINDOW_HEIGHT/24);    // haut gauche
            glEnd();

        glPopMatrix();

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

}

void afficheCercle(int x, int y, int rayon, float r, float g, float b){

        int vectorY1=y + rayon;
        int vectorX1=x;

        glBegin(GL_LINE_STRIP);
        glColor3ub(r, g, b);
        for(int i=0;i<1000;i++)
        {
            int vectorX=x+(rayon*(float)sin((double)i));
            int vectorY=y+(rayon*(float)cos((double)i));
            glVertex2d(vectorX1,vectorY1);
            vectorY1=vectorY;
            vectorX1=vectorX;
        }
        glColor3ub(255., 255., 255.);
        glEnd();   
}

void Tir(float x_monstre, float y_monstre, float x_tour, float y_tour){
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);
    glVertex2d(x_monstre,y_monstre);
    glVertex2d(x_tour,y_tour);
    glColor3ub(255., 255., 255.);
    glEnd();   
}