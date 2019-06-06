#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GL/glu.h>
#include <stb_image/stb_image.h>

unsigned char* loadImage(const char image_path[]);
GLuint initTexture(unsigned char *image);
void afficheTexte(int x, int y, char *s, void *font);
void afficheBoutons(GLuint texture, int x, int y);