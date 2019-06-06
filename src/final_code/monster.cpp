#include "monster.hpp"
#include "map_reader.hpp"
#include "general.hpp"

#include <glad/glad.h>
#include <stdio.h>
#include <GL/glu.h>
#include "core/constants.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <math.h>
#include <stb_image/stb_image.h>



Monster::Monster(float pv, mapNode actualNode, mapNode nextNode) : m_pv(pv), m_actualNode(actualNode), m_nextNode(nextNode){
    printf("Monstre créé\n");
    m_pv_total=m_pv;
}

Monster::~Monster() {
    printf("Monstre détruit\n");
}

int Monster::suivre_chemin(mapNode sortie, std::vector<mapNode> nodes, GLuint* texture){
    if(m_nextNode.id!=sortie.id){
        if(((m_j==0) & (m_a==3.8*m_nextNode.x))|((m_i==0)&(m_b==3.8*m_nextNode.y-3.8*25)))
        {
            m_actualNode=m_nextNode;
            m_nextNode=nodes[m_actualNode.adj];
            if(m_actualNode.x<m_nextNode.x){
                m_i=1;
                m_j=0;
            }
            if(m_actualNode.y<m_nextNode.y){
                m_i=0;
                m_j=1;
            }  
            if(m_actualNode.x>m_nextNode.x){
                m_i=-1;
                m_j=0;
            }
            if(m_actualNode.y>m_nextNode.y){
                m_i=0;
                m_j=-1;
            }       
        }

        this->avance(nodes, texture);
        m_a=m_a+m_i;
        m_b=m_b+m_j;
        return 0;
    }
    else{
        this->avance(nodes, texture);
        m_a=m_a+1;
        if(this->getCoord().x==sortie.x*3.8){
            return 1;
        }
    }
}

void Monster::avance(std::vector<mapNode> nodes, GLuint* texture){

    glPushMatrix();
        glTranslatef(m_a,m_b,0);
        glBindTexture(GL_TEXTURE_2D, *texture);
        glPushMatrix();
        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex2f(3.8*nodes[1].x-57-WINDOW_WIDTH/40, 3.8*nodes[1].y+WINDOW_HEIGHT/40); // bas gauche 
            glTexCoord2f(1, 1); glVertex2f(3.8*nodes[1].x-57+WINDOW_WIDTH/40, 3.8*nodes[1].y+WINDOW_HEIGHT/40); // bas droite 
            glTexCoord2f(1, 0); glVertex2f(3.8*nodes[1].x-57+WINDOW_WIDTH/40, 3.8*nodes[1].y-WINDOW_HEIGHT/40); // haut droite  
            glTexCoord2f(0, 0); glVertex2f(3.8*nodes[1].x-57-WINDOW_WIDTH/40, 3.8*nodes[1].y-WINDOW_HEIGHT/40); // haut gauche 
        glEnd();
        glPopMatrix();

     glPopMatrix();
     // Unbind texture
     glBindTexture(GL_TEXTURE_2D, 0);

}

coord Monster::getCoord(){
    coord myMonster;
    myMonster.x=(3.8*15-57-WINDOW_WIDTH/40)+m_a;
    myMonster.y=(3.8*25-WINDOW_HEIGHT/40)+m_b;
    return myMonster;
}


int Monster::degats(int degat){
    int mort=0;
    m_pv-=degat;
    if(m_pv<=0){
        printf("Le monstre est mort !\n");
        mort=1;
    }
    return mort;
}

void Monster::drawPVMonster(){

    float pourcentagePV = m_pv*100/m_pv_total;

    glPushMatrix();
        coord myMonster=this->getCoord();

        if(pourcentagePV <= 10)
            glColor3ub(255,0,0);
        else if(pourcentagePV <= 30)
            glColor3ub(255,96,0);
        else if(pourcentagePV <= 50)
            glColor3ub(255,150,0);
        else if(pourcentagePV <= 70)
            glColor3ub(255,240,0);
        else
            glColor3ub(27,101,10);

        glBegin(GL_QUADS);
            glVertex2f(myMonster.x+10, myMonster.y+5);
            glVertex2f(myMonster.x+30, myMonster.y+5);
            glVertex2f(myMonster.x+30, myMonster.y+8);
            glVertex2f(myMonster.x+10, myMonster.y+8);
         
        glEnd();
        
        glColor3ub(255,255,255);

    glPopMatrix();
}

/*
void Monster::PathFinding(){
	
}*/
