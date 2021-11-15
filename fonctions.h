#include<stdio.h>
#include<stdlib.h>
struct Animal{
        int x;
        int y;
        int direction;
        int energie;
        int gene[8];
        struct Animal *suiv;
        struct Animal *prec;
        int famille;
        int distance;
    };
    typedef struct Animal Animal;

struct Liste{
        Animal *debut;
        Animal *fin;
        int taille;
    };
    typedef struct Liste Liste;

void usage(char *prog);
void repro(Animal *animal, Liste *liste);//
void tore(int *x,int *y, int hauteur, int largeur); //
void mortanimal(Animal *animal, Liste *liste);//
void orienter(Animal *animal); //
void deplacer(Animal *animal); //
void mutation(Animal *animal); //
void ajoutdebut(Liste *l, Animal *animal);//
void ajoutfin(Liste *l, int x, int y, int direction, int energie, int gene[8], int famille);//
void affiche(Liste* l); //
void manger(Animal *animal, int largeur, int monde[][largeur], Liste *liste, int gain, int seuil);//
void cuisiner(int hauteur, int largeur, int oasis_hauteur, int oasis_largeur,int x_oasis,int y_oasis, int monde[][largeur]);//
void verifgene(Animal *animal);//
void verifanim(Animal *animal);//
void verifautre(int hauteur, int largeur, int xoasis, int yoasis, int hoasis, int loasis, int gain, int seuil);//
int distance(Animal *animal, int xoasis, int yoasis, int hoasis, int loasis, int hauteur, int largeur);
//void tri_insertion(Liste *liste);
void tri_bulles(Liste *liste,int taille);

