#include <iostream>
#include <allegro.h>
#include "utilalleg.h"
#include "boutton.h"
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include "graph.h"

void removeLine(std::string path, int nbLigne)
{
    int j=0;
    std::string ligne;
    std::vector<std::string> file;
    std::ifstream fichier1(path, std::ios::in);
        if(fichier1)
        {
            while(getline(fichier1, ligne))
            {
                j++;
                if(j != nbLigne)
                {
                    file.push_back(ligne);
                }
            }
            fichier1.close();
            std::ofstream fichier2(path, std::ios::out | std::ios::trunc);
            if(fichier2)
            {
                for (auto i = file.begin(); i != file.end(); ++i)
                {
                    fichier2 << *i << std::endl;
                }
                fichier2.close();
            }
            else
                std::cerr << "Erreur à l'ouverture !" << std::endl;
        }
        else
                std::cerr << "Erreur à l'ouverture !" << std::endl;
}

void addLine(std::string path)
{
    std::string valeur;
    std::cin >> valeur;
    std::ifstream file1(valeur + ".txt", std::ios::in);
    std::ifstream file2(valeur + "_weights_0.txt", std::ios::in);
    if(file1 && file2)
    {
    int j=0;
    std::string ligne;
    std::vector<std::string> file;
    std::ifstream fichier1(path, std::ios::in);
        if(fichier1)
        {
            while(getline(fichier1, ligne))
            {
                    file.push_back(ligne);
            }
            fichier1.close();
            std::ofstream fichier2(path, std::ios::out | std::ios::trunc);
            if(fichier2)
        {

                    std::ofstream fichier2(path, std::ios::out | std::ios::trunc);
                    for (auto i = file.begin(); i != file.end(); ++i)
                    {
                        fichier2 << *i << std::endl;
                    }
                    fichier2 << valeur << std::endl;
        }
                    else
                        std::cerr << "Erreur à l'ouverture !" << std::endl;
                        fichier2.close();
                        std::cout << "Graphe ajoute!" << std::endl;
        }
        else
                std::cerr << "Erreur à l'ouverture !" << std::endl;
    }else   allegro_message("Nom de Graphe non existant");
    file1.close();
    file2.close();
}



void initMenu()                     /// Permet d'initialiser les différentes bitmaps du menu
{
    BITMAP* backgroundmenu = load_bitmap("menu.bmp",NULL);    // le menu
    draw_sprite(screen,backgroundmenu,0,0);                     // on affiche le menu
}

void leaveMenu()                    /// Permet de quitter à tout moment
{
    allegro_exit();
    exit(EXIT_SUCCESS);
}

void menu(status* optionMenu)          /// Permet d'accéder aux différents choix du menu
{
    if (mouse_b==1)  /// Si on appuye sur un bouton de la souris
    {
        if (mouse_x>=285 && mouse_x<=500 && mouse_y >=165 && mouse_y <= 195)    // ici on appuye sur play
            *optionMenu = chargerVille;
        if(mouse_x>=285 && mouse_x<=415 && mouse_y >=245 && mouse_y <= 270)     // on appuye sur quitter
            *optionMenu = leaveLoop;
    }
}

std::string chooseVille(std::vector<boutton> page)
{
    int k=1;
    std::string result;
    while(k==1)
    {
        if (mouse_b == 1)
        {
            for (auto i = page.begin(); i != page.end(); ++i)
            {
                if (mouse_x>=i->getX() && mouse_x<=(i->getX()+(i->getSizeLigne()*24)) && mouse_y >=i->getY() && mouse_y <=i->getY()+30)
                {
                    result = i->getLigne();
                    k=0;
                }
            }
        }
    }
    return result;
}

void afficherBase(BITMAP* Villes,FONT* font1,int* k, int* x, int* y){
                    draw_sprite(screen,Villes,0,0);
                    textprintf_ex(screen,font1,350,510,makecol(255,255,255),-1,"Voir Plus");
                    textprintf_ex(screen,font1,15,150,makecol(0,0,0),-1,"Ajouter");
                    textprintf_ex(screen,font1,15,230,makecol(0,0,0),-1,"Supprimer");
                    textprintf_ex(screen,font1,15,300,makecol(0,0,0),-1,"Retour");
                    *k=0;
                    *x = 350;
                    *y = 150;
}

void initFichier(std::ifstream& fichier, std::string* ligne){

fichier.clear();
fichier.seekg(0,std::ios::beg);
getline(fichier, *ligne);
}


std::string menuCharger()
{
    int supprimer = 0;
    BITMAP* Villes = load_bitmap("chargerVille.bmp",NULL);
    FONT * font1 = load_font("font2.pcx",NULL,NULL);
    std::ifstream fichier("Villes.txt", std::ios::in);
    std::string ligne, choix;
    if(fichier)
    {
        std::vector<boutton> page;
        boutton but{};
        int k,x,y, condition =0, nbligne = 0, j=0;
        afficherBase(Villes,font1,&k,&x,&y);
        if(getline(fichier, ligne))
        {
            while(condition == 0)
            {
                do
                {
                    k++;
                    but.modifyboutton(x,y+10,ligne);
                    page.push_back(but);
                    textprintf_ex(screen,font1,x,y,makecol(100,100,100),-1,"%s",ligne.c_str());
                    y = y + 70;
                }
                while(getline(fichier, ligne) && k!=5);
                rest(500);
                if(k!=5)
                {
                    initFichier(fichier,&ligne);
                }
                but.modifyboutton(350,510,"Voir Plus");
                page.push_back(but);
                but.modifyboutton(15,160,"Ajouter");
                page.push_back(but);
                but.modifyboutton(15,230,"Supprimer");
                page.push_back(but);
                but.modifyboutton(15,300,"Retour");
                page.push_back(but);
                choix = chooseVille(page);
                if (choix != "Voir Plus" && choix != "Supprimer" && choix != "Ajouter" && choix != "Retour")
                {
                    if(supprimer == 1)
                    {
                        std::ifstream aparcourir("Villes.txt", std::ios::in);
                        while(getline(aparcourir, ligne))
                        {
                            j++;
                            if(ligne == choix)
                            {
                                std::cout<< "Suppression de : " << choix << std::endl;
                                nbligne = j;
                            }
                        }
                        j=0;
                        aparcourir.close();
                        removeLine("Villes.txt", nbligne);
                        supprimer = 0;
                    initFichier(fichier,&ligne);
                    afficherBase(Villes,font1,&k,&x,&y);
                    }
                    else
                    {
                        std::cout << "Vous avez selectionne : "<< choix << std::endl;
                        condition = 1;
                    }
                }
                else if (choix == "Supprimer")
                {
                    if(supprimer == 0)
                    {
                        std::cout<< "Mode Supprimer Active" << std::endl;
                    supprimer =1;
                    initFichier(fichier,&ligne);
                    afficherBase(Villes,font1,&k,&x,&y);
                    }else
                    {
                        std::cout<< "Mode Supprimer Desactive" << std::endl;
                        supprimer = 0;
                    }
                }else if(choix == "Ajouter")
                {
                    std::cout << "Veuillez selectionner le graphe a ajouter : "<< std::endl;
                    addLine("Villes.txt");
                    initFichier(fichier,&ligne);
                    afficherBase(Villes,font1,&k,&x,&y);
                }
                else if(choix == "Retour")  condition = 1;
                else
                {
                    page.clear();
                    afficherBase(Villes,font1,&k,&x,&y);
                }
            }
        }
        fichier.close();
    }
    else
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
    return choix;
}

void AfficherDistCost(graphe g,FONT* font1,bool prim1, bool prim2)
{
    clear_to_color(screen,makecol(255,255,255));
    g.display();
    int c1 = makecol(0,0,0), c2 = makecol(0,0,0);
    if(prim1 == true) c1 = makecol(255,0,0);
    if(prim2 == true) c2 = makecol(0,0,255);
    if(prim1 == true && prim2 == true)
    {
        c1 = makecol(0,255,0);
        c2=c1;
    }
    textprintf_ex(screen,font1,520,50,c1,-1,"Cout 1");
    textprintf_ex(screen,font1,520,100,c2,-1,"Cout 2");
    textprintf_ex(screen,font1,520,150,makecol(0,0,0),-1,"Pareto");
    textprintf_ex(screen,font1,520,200,makecol(0,0,0),-1,"Retour");
}

void AfficherGraphique(){
    clear_to_color(screen,makecol(255,255,255));
    line(screen, 150, 50, 150, 550, makecol(0,0,0));
    line(screen, 150, 550, 650, 550, makecol(0,0,0));
    textprintf_ex(screen,font,60,40,makecol(0,0,0),-1,"Cout 1");
    textprintf_ex(screen,font,650,570,makecol(0,0,0),-1,"Cout 2");
    triangle(screen,150, 25,140, 50,160, 50,makecol(0,0,0));
    triangle(screen,650,560,650,540,675,550,makecol(0,0,0));
}


void PaPa(bool okcool, int couleur, std::string brd, std::string ct){
graphe g(brd, ct);
std::vector<std::string> frontpareto = g.getFrontiereSolPareto(okcool);
std::pair<float,float> PdsPareto;
for(std::string  i : frontpareto)
{
    PdsPareto = g.getPoidsSolPareto(i);
    line(screen, 8*PdsPareto.first + 148, 550 - 8*PdsPareto.second,8*PdsPareto.first + 152,550 - 8*PdsPareto.second, couleur);
    line(screen, 8*PdsPareto.first + 150, 548 - 8*PdsPareto.second,8*PdsPareto.first + 150,552 - 8*PdsPareto.second, couleur);
}
}


void AfficherGraphe(std::string choix)
{
                std::string weight = choix + "_weights_0.txt";
                bool fin = false, prim1 = false, prim2 = false, par = false;
                boutton temp;
                std::string selection;
                std::vector<boutton> bouttons, paret;
                choix = choix + ".txt";
                graphe g(choix,weight);
                FONT * font1 = load_font("fontsommet.pcx",NULL,NULL);
                AfficherDistCost(g,font1, prim1, prim2);
                temp.modifyboutton(520,50,"Cout 1");
                bouttons.push_back(temp);
                temp.modifyboutton(520,100,"Cout 2");
                bouttons.push_back(temp);
                temp.modifyboutton(520,150,"Pareto");
                bouttons.push_back(temp);
                temp.modifyboutton(520,200,"Retour");
                bouttons.push_back(temp);
                while(fin == false && par == false)
                {
                    selection = chooseVille(bouttons);
                    rest(100);
                    if(selection == "Cout 1")
                    {
                        if(prim1 == false) prim1 = true;
                        else prim1 = false;
                    }
                    if(selection == "Cout 2")
                    {
                        if(prim2 == false) prim2 = true;
                        else prim2 = false;
                    }
                    if(selection == "Retour") fin = true;
                    if(selection == "Pareto") par = true;
                if(prim1 == false && prim2 == false)
                {
                    AfficherDistCost(g,font1,prim1,prim2);
                }
                if(prim1 == true && prim2 == false)
                {
                    AfficherDistCost(g,font1,prim1,prim2);
                    g.AfficherDistance();
                }
                if(prim1 == false && prim2 == true)
                {
                    AfficherDistCost(g,font1,prim1,prim2);
                    g.AfficherCost();
                }
                if(prim1 == true && prim2 == true)
                {
                    AfficherDistCost(g,font1,prim1,prim2);
                    g.AfficherDistance();
                    g.AfficherCost();
                    g.AfficherBoth();
                }
                while (par == true)
                {
                        AfficherGraphique();
                        PaPa(false, makecol(255,0,0), choix, weight);
                        PaPa(true, makecol(0,255,0), choix , weight);
                        temp.modifyboutton(600,30,"Retour");
                        paret.push_back(temp);
                        textprintf_ex(screen,font1,600,30,makecol(0,0,0),-1,"Retour");
                        selection = chooseVille(paret);
                        if(selection == "Retour")
                        {
                            AfficherDistCost(g,font1,prim1,prim2);
                            par = false;
                        }

                }
            }
}


void initialisation()
{
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    install_mouse();
    install_timer();
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,WIDTH,HEIGHT,0,0)!=0)
    {
        allegro_message("Probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
    status optionMenu = menuLoop;
    std::string choix, weight;
    while (!key[KEY_ESC])
    {
        switch (optionMenu)
        {
        case menuLoop :
            initMenu();
            menu(&optionMenu);
            break;

        case chargerVille :
            choix = menuCharger();
            if(choix != "Retour")   AfficherGraphe(choix);
            else optionMenu = menuLoop;
            break;

        case leaveLoop:
            return ;
            break;
        }
        rest(64);
    }
}
