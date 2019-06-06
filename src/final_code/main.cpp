#ifdef _WIN32
#include <windows.h>
#endif
#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stb_image/stb_image.h>
#include <math.h>
#include <string>
#include <GL/glut.h>
#include <GL/glu.h>

#include "core/init.hpp"
#include "general.hpp"
#include "map.hpp"
#include "tower.hpp"
#include "monster.hpp"
#include "building.hpp"
#include "map_reader.hpp"


static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(int argc, char **argv) {
    SDL_Window* window = imac::init();
    if (window == nullptr) {
        printf("[INIT] Init not achieved !");
        debug_break();
    }


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    //Menu
    int menu=0;
    Map debut;
    unsigned char *image2;
    image2 = loadImage("./images/menu.jpg");
    GLuint texture_id2;
    texture_id2 = initTexture(image2);

    //Aide
    Map aide;
    unsigned char *image3;
    image3 = loadImage("./images/aide.jpg");
    GLuint texture_id3;
    texture_id3 = initTexture(image3);

     //Perdu
    Map perdu;
    unsigned char *image4;
    image4 = loadImage("./images/perdu.jpg");
    GLuint texture_id4;
    texture_id4 = initTexture(image4);

    //Gagne
    Map gagne;
    unsigned char *image5;
    image5 = loadImage("./images/gagne.jpg");
    GLuint texture_id5;
    texture_id5 = initTexture(image5);

    //Bouton pause
    unsigned char *image6;
    image6 = loadImage("./images/pause.png");
    GLuint texture_id6;
    texture_id6 = initTexture(image6);

    //Bouton play
    unsigned char *image7;
    image7 = loadImage("./images/play.png");
    GLuint texture_id7;
    texture_id7 = initTexture(image7);

    //Play
    Map pause;
    unsigned char *image8;
    image8 = loadImage("./images/image_pause.jpg");
    GLuint texture_id8;
    texture_id8 = initTexture(image8);

    //Argent
    glutInit(&argc, argv); // initialisation de GLUT
     
    // Map 
    Map carte_jardin;
    unsigned char *image;
    image = loadImage("./images/jardin_last.jpg");
    GLuint texture_id;
    texture_id = initTexture(image);

    //Tower
    unsigned char *img_tour;
    std::string type="merle";
    type_Tower tour;
    std::vector<int> coord_towers;
    std::vector<GLuint> texture_tour;
    std::vector<type_Tower> element_tower;
    int m_dist_monst;
    std::vector<pixel> pixelsPPM = readPPM();
    std::vector<int> temps_cadence;
    std::vector<int> aFait1Tir;
    
    //Monster
    std::vector<GLuint*>  texture_monstre;
    GLuint* actual_texture_monstre;
    //Monstre 1
    std::vector<Monster*> monsters;
    int mort=0;
    unsigned char *img_monstre;
    img_monstre = loadImage("./images/fourmis.png");
    GLuint texture_fourmis;
    texture_fourmis = initTexture(img_monstre);
    int pv=60;
    actual_texture_monstre=&texture_fourmis;
    //Monstre 2
    unsigned char *img_monstre2;
    img_monstre2 = loadImage("./images/cafard.png");
    GLuint texture_cafard;
    texture_cafard = initTexture(img_monstre2);
    //Monstre 3
    unsigned char *img_monstre3;
    img_monstre3 = loadImage("./images/perce_oreille.png");
    GLuint texture_perce;
    texture_perce = initTexture(img_monstre3);
    //Monstre 4
    unsigned char *img_monstre4;
    img_monstre4 = loadImage("./images/mante_religieuse.png");
    GLuint texture_mante;
    texture_mante = initTexture(img_monstre4);

    //Graphe des noeuds
    std::vector<mapNode> nodes = loadITD();
    mapNode sortie=nodes[0];
    mapNode actualNode=nodes[1];
    mapNode nextNode=nodes[nodes[1].adj];
    int changeMonster=0;
    int a=0, b=1, i=1, j=0;
    int nbMonsters=0;
    int nbMonstreByLoop=3;

    unsigned int loopCount = 0;
    unsigned int loopCountWaves = 0;

    //Argent
    int money=100;

    /* Boucle principale */
    bool loop = true;
    while (loop) {

        Uint32 startTime = SDL_GetTicks();

       
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        if(menu==0){
            debut.afficheMap(texture_id2);
        }

        if(menu==2){
            aide.afficheMap(texture_id3);
        }

        if(menu==3){
            perdu.afficheMap(texture_id4);
        }

        if(menu==4){
            gagne.afficheMap(texture_id5);
        }

        if(menu==5){
            pause.afficheMap(texture_id8);
            afficheBoutons(texture_id7,200*3.8,10*3.8);
        }

        if(menu==1){
            
            loopCount++;
            loopCountWaves++;

            carte_jardin.afficheMap(texture_id);
            for(int ind=0; ind<texture_tour.size(); ind++){
                afficheCercle(coord_towers[ind*2], coord_towers[(ind*2)+1], element_tower[ind].port, element_tower[ind].r, element_tower[ind].g, element_tower[ind].b);
                afficheTower(texture_tour[ind], coord_towers[ind*2], coord_towers[(ind*2)+1]);
            }

            //Affiche bouton pause
            afficheBoutons(texture_id6,200*3.8,20*3.8);
            

            if(loopCount==60 && nbMonsters<nbMonstreByLoop){
                Monster* myMonster =  new Monster(pv, nodes[1], nodes[nodes[1].adj]);
                monsters.push_back(myMonster);
                texture_monstre.push_back(actual_texture_monstre);
                nbMonsters++;
                loopCount=0;
            }

            char moneyChar[10];
            sprintf(moneyChar,"%d",money);
            afficheTexte(190*3.8, 11*3.8, moneyChar, GLUT_BITMAP_HELVETICA_18);

            
            if(type=="merle"){
                tour.cad=70;
                tour.pui=20;
                tour.port=110;
                tour.r=255.;
                tour.g=200.;
                tour.b=200.;
                tour.cout=50.;
                img_tour = loadImage("./images/merle.png");
                afficheTexte(150*3.8, 11*3.8, "merle", GLUT_BITMAP_HELVETICA_18);
            }
            
            if(type=="poule_eau"){
                tour.cad=30;
                tour.pui=30;
                tour.port=80;   
                tour.r=255.;
                tour.g=200.;
                tour.b=255.; 
                tour.cout=60.;   
                img_tour = loadImage("./images/poule_eau.png");
                afficheTexte(150*3.8, 11*3.8, "poule d'eau", GLUT_BITMAP_HELVETICA_18);
            }

            if(type=="hirondelle"){
                tour.cad=30;
                tour.pui=70;
                tour.port=90;
                tour.r=200.;
                tour.g=200.;
                tour.b=255.;
                tour.cout=70.;
                img_tour = loadImage("./images/hirondelle.png");
                afficheTexte(150*3.8, 11*3.8, "hirondelle", GLUT_BITMAP_HELVETICA_18);
            }
            
            if(type=="aigle"){
                tour.cad=90;
                tour.pui=100;
                tour.port=100;
                tour.r=200.;
                tour.g=255.;
                tour.b=200.;
                tour.cout=80.;
                img_tour = loadImage("./images/aigle.png");
                afficheTexte(150*3.8, 11*3.8, "aigle", GLUT_BITMAP_HELVETICA_18);
            }

           //Monstres avancent  
            if (monsters.size()>0){
                for(int h=0; h<monsters.size(); h++){
                    int estSorti=0;
                    estSorti=((monsters[h])->suivre_chemin(sortie,nodes, texture_monstre[h]));
                    monsters[h]->drawPVMonster();
                    if(estSorti==1){
                        menu=3;
                    }
                    if((mort==1)){
                        delete monsters[h];
                        //delete texture_monstre[h];
                        monsters.erase(monsters.begin()+h);
                        texture_monstre.erase(texture_monstre.begin()+h);
                        mort=0;
                        money+=7;
                    }

                }
            }
            if(changeMonster==7 && monsters.size()==0){
                menu=4;
            }

            //TIR
            for(int ind=0; ind<element_tower.size(); ind++){
                for(int h=0; h<monsters.size(); h++){
                    float x_monstre=monsters[h]->getCoord().x;
                    float y_monstre=monsters[h]->getCoord().y;
                    float x_tour=coord_towers[ind*2];
                    float y_tour=coord_towers[(ind*2)+1];

                    m_dist_monst=pow(x_tour-x_monstre,2)+pow(y_tour-y_monstre,2);
                    if(m_dist_monst<=pow(element_tower[ind].port,2)){
                        if (temps_cadence[ind]==0 && aFait1Tir[ind]==0){
                            printf("TIR!\n");
                            Tir(x_monstre,y_monstre,x_tour,y_tour);
                            mort=monsters[h]->degats(element_tower[ind].pui);
                            aFait1Tir[ind]=1;
                        }
                    }
                }
                if (aFait1Tir[ind]==1){
                    temps_cadence[ind]=temps_cadence[ind]+1;
                    if(temps_cadence[ind]==element_tower[ind].cad){
                        temps_cadence[ind]=0;
                        aFait1Tir[ind]=0;
                    }
                }
            }

        if(loopCountWaves==20*60){
            printf("Nouvelle vague de monstres\n");
            nbMonsters = 0;
            loopCount = 0;
            loopCountWaves=0;
            nbMonstreByLoop+=2;
            if(changeMonster<8){
                if(changeMonster==1){
                    pv=80;
                    actual_texture_monstre=&texture_cafard;
                }
                if(changeMonster==3){
                    pv=100;
                    actual_texture_monstre=&texture_perce;
                }
                if(changeMonster==5){
                    pv=150;
                    actual_texture_monstre=&texture_mante;
                }
                changeMonster++;
            }
        }

    }
        //carte_jardin.draw();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                loop = false;
                break;
            }

            switch (e.type) {
                case SDL_MOUSEBUTTONUP:
                    {   
                        //si on clique sur commencer partie
                        if(menu==0 && 70*3.8<e.button.x && e.button.x <150*3.8 && 100*3.8<e.button.y && e.button.y <110*3.8){
                            menu=1;
                        }

                        if(menu==1){

                            //si on clique sur infos
                            if(129*3.8<e.button.x && e.button.x <135*3.8 && 7*3.8<e.button.y && e.button.y <13*3.8){
                                afficheCercle(132*3.8, 10*3.8, 5*3.8, 255, 0, 0);
                                menu=2;
                            }

                            //si on clique sur pause
                            if(195*3.8<e.button.x && e.button.x <205*3.8 && 15*3.8<e.button.y && e.button.y <25*3.8){
                                afficheCercle(200*3.8, 20*3.8, 5*3.8, 255, 0, 0);
                                menu=5;
                            }

                            if (89*3.8<e.button.y && e.button.y <96*3.8 && 10*3.8<e.button.x && e.button.x <16*3.8) {
                                afficheCercle(13*3.8, 93*3.8, 5*3.8, 255, 200, 200);
                                type="merle";
                            }

                            if (116*3.8<e.button.y && e.button.y <124*3.8 && 10*3.8<e.button.x && e.button.x <16*3.8) {
                                afficheCercle(13*3.8, 120*3.8, 5*3.8, 255, 200, 255);
                                type="poule_eau";
                            }

                            if (141*3.8<e.button.y && e.button.y <149*3.8 && 10*3.8<e.button.x && e.button.x <16*3.8) {
                                afficheCercle(13*3.8, 145*3.8, 5*3.8, 200, 200, 255);
                                type="hirondelle";
                            }

                            if (171*3.8<e.button.y && e.button.y <179*3.8 && 10*3.8<e.button.x && e.button.x <16*3.8) {
                                afficheCercle(13*3.8, 175*3.8, 5*3.8, 200, 255, 200);
                                type="aigle";
                            }


                            Tower oisal(tour.cad,tour.pui,tour.port);
                            int isConstr = oisal.isConstructible(pixelsPPM, e.button.x/3.8, e.button.y/3.8, coord_towers);
                            if(isConstr==1){
                                if(money>=tour.cout){
                                    money-=tour.cout;
                                    coord_towers.push_back(e.button.x);
                                    coord_towers.push_back(e.button.y);
                                    texture_tour.push_back(initTexture(img_tour));
                                    element_tower.push_back(tour);
                                    temps_cadence.push_back(0);
                                    aFait1Tir.push_back(0);
                                }
                                else printf("Tu n'as pas assez d'argent");
                            }
                        }
                        //si on clique sur la croix dans la page infos
                        if(menu==2 && 189*3.8<e.button.x && e.button.x <199*3.8 && 9*3.8<e.button.y && e.button.y <19*3.8){
                            afficheCercle(194*3.8, 14*3.8, 5*3.8, 255, 0, 0);
                            menu=1;
                        }

                        //Quand on est en pause
                        if(menu==5 && 195*3.8<e.button.x && e.button.x <205*3.8 && 5*3.8<e.button.y && e.button.y <15*3.8){
                            //si on clique sur play
                            afficheCercle(200*3.8, 20*3.8, 5*3.8, 255, 0, 0);
                            menu=1;
                        }
                        
                    }
                    break;

                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);

                    /*if (e.key.keysym.sym == 'w') { 
                        nbMonsters = 0;
                        loopCount = 0;
                        nbMonstreByLoop+=2;
                        if(changeMonster<8){
                            if(changeMonster==1){
                                pv=80;
                                actual_texture_monstre=&texture_cafard;
                            }
                            if(changeMonster==3){
                                pv=100;
                                actual_texture_monstre=&texture_perce;
                            }
                            if(changeMonster==5){
                                pv=150;
                                actual_texture_monstre=&texture_mante;
                            }
                            changeMonster++;
                        }

                    }*/
                    break;

                default:
                    break;
            }
        }

        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if (elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
         /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);
    }


    /* Liberation de la memoire allouee sur le GPU pour la texture */
    glDeleteTextures(1, &texture_id);
    glDeleteTextures(1, &texture_id2);
    glDeleteTextures(1, &texture_id3);
    glDeleteTextures(1, &texture_id4);
    glDeleteTextures(1, &texture_id5);
    glDeleteTextures(1, &texture_id6);
    glDeleteTextures(1, &texture_id7);
    glDeleteTextures(1, &texture_id8);
    glDeleteTextures(1, &texture_fourmis);
    glDeleteTextures(1, &texture_cafard);
    glDeleteTextures(1, &texture_perce);
    glDeleteTextures(1, &texture_mante);
    glDeleteTextures(1, actual_texture_monstre);
    
    /* Liberation de la mémoire occupee par img */
    stbi_image_free(image);
    stbi_image_free(image2);
    stbi_image_free(image3);
    stbi_image_free(image4);
    stbi_image_free(image5);
    stbi_image_free(image6);
    stbi_image_free(image7);
    stbi_image_free(image8);
    stbi_image_free(img_tour);
    stbi_image_free(img_monstre);
    stbi_image_free(img_monstre2);
    stbi_image_free(img_monstre3);
    stbi_image_free(img_monstre4);

    /* Cleanup */
    SDL_DestroyWindow(window);
    SDL_Quit();

    for (Monster* monster: monsters) {
        delete monster;
    }

    for (GLuint textureDeTour: texture_tour) {
        delete &textureDeTour;
    }

    for (GLuint* textureDeMonstre: texture_monstre) {
        delete textureDeMonstre;
    }

    return EXIT_SUCCESS;
}