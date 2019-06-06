#include "general.hpp"

#include <glad/glad.h>
#include <stdio.h>
#include <string>
#include "core/constants.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stb_image/stb_image.h>

int m_imgWidth;
int m_imgHeight;
int m_imgChannels;

unsigned char* loadImage(const char image_path[]){
    /* Chargement de l'image */
    unsigned char *image = stbi_load(image_path, &m_imgWidth, &m_imgHeight, &m_imgChannels, STBI_rgb_alpha);
    if (nullptr == image)
    {
        printf("Echec du chargement de l'image %s\n", image_path);
        //debug_break();
    }
    return image;
}

GLuint initTexture(unsigned char *image){  
    // Autorisation de l'affichage des textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    /* Initialisation de la texture */
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_imgWidth, m_imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return texture_id;

}

void afficheTexte(int x, int y, char *s, void *font)
{
    int len,i; // len donne la longueur de la chaîne de caractères

    glRasterPos2f(x,y); // Positionne le premier caractère de la chaîne
    len = (int) strlen(s); // Calcule la longueur de la chaîne
    for (i = 0; i < len; i++) glutBitmapCharacter(font,s[i]); // Affiche chaque caractère de la chaîne
}

void afficheBoutons(GLuint texture, int x, int y){

    glBindTexture(GL_TEXTURE_2D, texture);
        glPushMatrix();
            glBegin(GL_QUADS);
                glTexCoord2f(0, 1); glVertex2f(x-WINDOW_WIDTH/40, y-WINDOW_HEIGHT/40);   // bas gauche
                glTexCoord2f(1, 1); glVertex2f(x+WINDOW_WIDTH/40, y-WINDOW_HEIGHT/40);    // bas droite
                glTexCoord2f(1, 0); glVertex2f(x+WINDOW_WIDTH/40, y+WINDOW_HEIGHT/40);     // haut droite
                glTexCoord2f(0, 0); glVertex2f(x-WINDOW_WIDTH/40, y+WINDOW_HEIGHT/40);    // haut gauche
            glEnd();

        glPopMatrix();

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

}