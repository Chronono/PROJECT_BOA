#include <iostream>
#include <allegro.h>
#include "utilalleg.h"
#include "boutton.h"
#include <string>
#include <fstream>
#include <vector>

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
                    std::string valeur;
                    std::cin >> valeur;
                    std::ofstream fichier2("Villes.txt", std::ios::out | std::ios::trunc);
                    for (auto i = file.begin(); i != file.end(); ++i)
                    {
                        fichier2 << *i << std::endl;
                    }
                    fichier2 << valeur << std::endl;
        }
                    else
                        std::cerr << "Erreur à l'ouverture !" << std::endl;
                        fichier2.close();
        }
        else
                std::cerr << "Erreur à l'ouverture !" << std::endl;
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

void menu()          /// Permet d'accéder aux différents choix du menu
{
    if (mouse_b==1)  /// Si on appuye sur un bouton de la souris
    {
        if (mouse_x>=285 && mouse_x<=500 && mouse_y >=165 && mouse_y <= 195)    // ici on appuye sur play
            optionMenu = chargerVille;
        if(mouse_x>=285 && mouse_x<=435 && mouse_y >=245 && mouse_y <= 270)     // on appuye sur quitter
            optionMenu = parcours;
        if(mouse_x>=285 && mouse_x<=415 && mouse_y >=325 && mouse_y <= 350)    // on appuye sur option
            optionMenu = leaveLoop;
        printf("%d", optionMenu);
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
    std::cout << result << std::endl;
    return result;
}

void afficherBase(BITMAP* Villes,FONT* font1,int* k, int* x, int* y){
                    draw_sprite(screen,Villes,0,0);
                    textprintf_ex(screen,font1,350,510,makecol(255,255,255),-1,"Voir Plus");
                    textprintf_ex(screen,font1,15,150,makecol(0,0,0),-1,"Ajouter");
                    textprintf_ex(screen,font1,15,230,makecol(0,0,0),-1,"Supprimer");
                    *k=0;
                    *x = 350;
                    *y = 150;
}

void initFichier(std::ifstream& fichier, std::string* ligne){

fichier.clear();
fichier.seekg(0,std::ios::beg);
getline(fichier, *ligne);
}


void menuCharger()
{
    int supprimer = 0;
    BITMAP* Villes = load_bitmap("chargerVille.bmp",NULL);
    FONT * font1 = load_font("font2.pcx",NULL,NULL);
    std::ifstream fichier("Villes.txt", std::ios::in);
    if(fichier)
    {
        std::string ligne, choix;
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
                    std::cout<<ligne<<std::endl;
                    textprintf_ex(screen,font1,x,y,makecol(100,100,100),-1,"%s",ligne.c_str());
                    y = y + 70;
                }
                while(getline(fichier, ligne) && k!=5);
                rest(500);
                if(k!=5)
                {
                    initFichier(fichier,&ligne);
                    supprimer=0;
                }
                but.modifyboutton(350,510,"Voir Plus");
                page.push_back(but);
                but.modifyboutton(15,160,"Ajouter");
                page.push_back(but);
                but.modifyboutton(15,230,"Supprimer");
                page.push_back(but);
                choix = chooseVille(page);
                if (choix != "Voir Plus" && choix != "Supprimer" && choix != "Ajouter")
                {
                    if(supprimer == 1)
                    {
                        std::ifstream aparcourir("Villes.txt", std::ios::in);
                        while(getline(aparcourir, ligne))
                        {
                            j++;
                            if(ligne == choix)
                            {
                                std::cout<< "Tu as suppr: " << choix << std::endl;
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
                    else    condition = 1;
                }
                else if (choix == "Supprimer")
                {
                    supprimer =1;
                    initFichier(fichier,&ligne);
                    afficherBase(Villes,font1,&k,&x,&y);
                }else if(choix == "Ajouter")
                {
                    addLine("Villes.txt");
                    initFichier(fichier,&ligne);
                    afficherBase(Villes,font1,&k,&x,&y);
                }
                else
                {
                    page.clear();
                    afficherBase(Villes,font1,&k,&x,&y);
                }
            }
        }
        rest(5000);
        fichier.close();
    }
    else
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;

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
    initMenu();
    buffer = create_bitmap(SCREEN_W,SCREEN_H);
    clear_to_color(buffer,makecol(255,255,255));
    while (!key[KEY_ESC])
    {
        switch (optionMenu)
        {
        case menuLoop :
            menu();
            break;

        case chargerVille :
            menuCharger();
            std::cout<< "GG"<< std::endl;
            rest(10000);
            break;

        case leaveLoop :
            leaveMenu();
            break;
        }
        rest(64);
    }
}
int main()
{
    initialisation();
    return 0;
}
END_OF_MAIN();

