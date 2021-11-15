#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"fonctions.h"
#include<time.h>





int main(int argc, char *argv[]){
   int n = 0;
   int c = 0;
   char* input;
   char* output;
   int r;

   if(argc<5 || argc>6) {
      usage(argv[0]);
      return 0;
   }

   if(sscanf(argv[1], "%d", &r)!=1 || (r != 1 && r!=0)) {
      fprintf(stderr, "incorrect value for r (%s)\n", argv[1]);
      usage(argv[0]);
      return 0;
   }

   if(sscanf(argv[2], "%d", &n)!=1) {
      fprintf(stderr, "incorrect value for n (%s)\n", argv[2]);
      usage(argv[0]);
      return 0;
   }

   input=argv[3];
   output=argv[4];

   if(argc>5 && sscanf(argv[5], "%d", &c)!=1) {
      fprintf(stderr, "incorrect value for c (%s)\n", argv[3]);
      usage(argv[0]);
      return 0;
   }

   printf("args: %d %d %s %s %d\n", r, n, input, output, c);

   if(r) {
      srand(time(NULL));
   }

//gestion arguments execution

    int hauteur=0;
    int largeur=0;
    int xoasis=0;
    int yoasis=0;
    int hoasis=0;
    int loasis=0;
    int gain=0;
    int seuil=0;
//Variables pour stocker les paramètres
    int compteur_ligne=0;
    int longueur=0;
    int compt=0;
    int compt_famille=2;
    int compteur_presence=0;
    int compteur_tour=0;
    int aa=0;
    int ab=0;
    int ac=0;
    int ad=0;
    int tae[8]={0};
    int ae;
    char *af;
    

//variables pour faciliter la lecture fichier



Animal *animal1 = malloc(sizeof(Animal));
	if(animal1==NULL) return 0;
	animal1->suiv = NULL;
	animal1->x=0;
        animal1->y=0;
	animal1->prec = NULL;
	animal1->famille=1;
	animal1->distance=0;

Liste *liste = malloc(sizeof(Liste));
    if(liste==NULL) return 0;
    liste->debut=animal1;
    liste->fin=animal1;
    liste->taille=1;

//on crée notre liste doublement chaînée d'animaux et le potentiel premier animal

    FILE *fichier = NULL;
    char chaine[500]="";


    fichier = fopen(input, "r");


    if (fichier == NULL)
        exit(1);


    while(fgets(chaine,500,fichier)!=NULL){
        compteur_ligne+=1;
    }
    fclose(fichier);

    compteur_ligne-=7; //indiquera donc le nombre d'animaux de la 1ère génération
    if (compteur_ligne<1){
        printf("le fichier ne respecte pas le format .phine (ligne)");
        return 0;
    }

    fichier=fopen(input, "r");




    af=fgets(chaine, 500, fichier);
    ae=fscanf(fichier, "%s %d %d",chaine, &hauteur, &largeur);
    af=fgets(chaine, 500, fichier);
    ae=fscanf(fichier, "%s %d %d %d %d",chaine, &xoasis, &yoasis, &hoasis, &loasis);
    af=fgets(chaine, 500, fichier);
    ae=fscanf(fichier, "%s %s %d",chaine,chaine, &gain);
    af=fgets(chaine, 500, fichier);
    ae=fscanf(fichier, "%s %s %d",chaine, chaine, &seuil);
    af=fgets(chaine, 500, fichier);
    af=fgets(chaine, 500, fichier);
    af=fgets(chaine, 500, fichier);
    ae=fscanf(fichier, "%s", chaine);
    //variables temporaires stockant les paramètres du premier animal
    longueur=strlen(chaine);
    compt=1;
    while (longueur >1){
        animal1->x+=compt*(chaine[longueur-1]-48);
        longueur-=1;
        compt*=10;
    }

    ae=fscanf(fichier, "%s", chaine);
    longueur=strlen(chaine);
    compt=1;
    while (longueur >1){
        animal1->y+=compt*(chaine[longueur-2]-48);
        longueur-=1;
        compt*=10;
    }
    //comme les coordonnées sont précédées ou suivies d'une paranthèse, on prend la chaîne entière sur laquelle on fait des opérations pour ne garder que les nombres

    ae=fscanf(fichier, "%d %d %s", &animal1->direction, &animal1->energie,chaine);
    ae=fscanf(fichier, "%d %d %d %d %d %d %d %d",&animal1->gene[0], &animal1->gene[1], &animal1->gene[2], &animal1->gene[3], &animal1->gene[4], &animal1->gene[5], &animal1->gene[6], &animal1->gene[7]);
    compteur_ligne-=1;

   verifgene(animal1);
   verifanim(animal1);
   verifautre(hauteur, largeur, xoasis, yoasis, hoasis, loasis, gain, seuil);
   // on fait les vérifs des paramètres du fichier


    // FONCTION POUR AJOUTER LES AUTRES ANIMAUX, même principe que le premier animal
    while(compteur_ligne>0) {
        af=fgets(chaine, 500, fichier);
        compteur_ligne-=1;
        ae=fscanf(fichier, "%s", chaine);
        if(!strcmp(chaine,"&")){
            printf("trouve!\n");
            break;
        }
        // sert pour lire le fichier sortie qu'on voudrait exécuter en entrée
        longueur=strlen(chaine);
        compt=1;
        while (longueur >1){
        aa+=compt*(chaine[longueur-1]-48);
        longueur-=1;
        compt*=10;
        }


        ae=fscanf(fichier, "%s", chaine);
        if (af==NULL)
            return 0;
        longueur=strlen(chaine);
        compt=1;
        while (longueur >1){
        ab+=compt*(chaine[longueur-2]-48);
        longueur-=1;
        compt*=10;
        }

        ae=fscanf(fichier, "%d %d %s", &ac, &ad,chaine);
        ae=fscanf(fichier, "%d %d %d %d %d %d %d %d",&tae[0], &tae[1], &tae[2], &tae[3], &tae[4], &tae[5], &tae[6], &tae[7]);
        if(ae==0)
           return 0;
        ajoutfin(liste,aa,ab,ac,ad,tae,compt_famille);
        aa=0;
        ab=0;
        compt_famille+=1;
        verifgene(liste->fin);
        verifanim(liste->fin);
    }
	



    fclose(fichier);


    int monde[hauteur][largeur];
    for (int i=0; i<hauteur; i++)
    {
        for (int j=0; j<largeur; j++)
        {
            monde[i][j]=0;
        }
    }
    // on crée notre monde

    Animal* nouv=liste->debut;
    while(nouv!=NULL){
        tore(&(nouv->x),&(nouv->y),hauteur,largeur);

        nouv=nouv->suiv;

	}

    tore(&xoasis,&yoasis,hauteur,largeur);
    // on change les coordonnées de l'oasis et des animaux si elles sortent du monde
while(compteur_tour<n){
	if (liste->debut==NULL||liste->taille==0){
        	printf("tous les animaux sont morts");
        	return 0;
        }
    compteur_tour+=1;
    if (compteur_tour%1000000000==0){
        printf("%dG tours\n",compteur_tour/1000000000);
    }
    else if(compteur_tour%1000000==0){
        printf("%dM tours\n",compteur_tour/1000000);
    }
    else if(compteur_tour%100000==0){
        printf("%d tours\n",compteur_tour);
    }
    
    cuisiner( hauteur, largeur, hoasis, loasis, xoasis, yoasis, monde);
    

    nouv=liste->debut;
	while(nouv!=NULL){

        orienter(nouv);
	deplacer(nouv);
	tore(&(nouv->x),&(nouv->y),hauteur,largeur);
        manger(nouv,largeur,monde,liste,gain,seuil);
        

        mortanimal(nouv,liste);
        if (liste->debut==NULL||liste->taille==0){
        	printf("tous les animaux sont morts");
        	return 0;
        }
        
	nouv=nouv->suiv;
	}
	nouv=liste->debut;
	
}
// on traite les n tours demandés
    nouv=liste->debut;
    while(nouv!=NULL){
        nouv->distance=distance(nouv, xoasis, yoasis, hoasis, loasis, hauteur, largeur);
        nouv=nouv->suiv;
    }
    tri_bulles(liste,liste->taille);
// on trie en fonction de la distance


    fichier=fopen(output,"w");
    if (fichier !=NULL){

    fprintf(fichier,"#monde de test avec petite Beauce\nMonde %d %d #hauteur largeur\nBeauce %d %d %d %d #position du coin superieur gauche de la Beauce puis sa hauteur largeur\nEnergie Nourriture %d #gain d'energie si de la nourriture est mangee\nSeuil Reproduction %d #seuil d'energie a partir duquel un animal se duplique\n\n#animaux, un par ligne\n", hauteur, largeur, xoasis, yoasis, hoasis, loasis, gain, seuil);
    nouv=liste->debut;
    while(nouv!=NULL){

        fprintf(fichier,"(%d %d) %d %d | %d %d %d %d %d %d %d %d | (%d)#position (x,y) initiale de l'animal, direction initiale ..\n", nouv->x, nouv->y, nouv->direction, nouv->energie, nouv->gene[0], nouv->gene[1], nouv->gene[2], nouv->gene[3], nouv->gene[4], nouv->gene[5], nouv->gene[6], nouv->gene[7],nouv->famille);
        nouv=nouv->suiv;
    }
    fprintf(fichier,"\n");
    fprintf(fichier,"\n");
    fputs("& par famille\n",fichier);


    for (int f=1; f<compt_famille+1; f++){
        compteur_presence=0;
        nouv=liste->debut;
        while(nouv!=NULL){
            if(nouv->famille==f){
                compteur_presence=1;
                fprintf(fichier,"(%d %d) %d %d | %d %d %d %d %d %d %d %d | (%d)#position (x,y) initiale de l'animal, direction initiale ..\n", nouv->x, nouv->y, nouv->direction, nouv->energie, nouv->gene[0], nouv->gene[1], nouv->gene[2], nouv->gene[3], nouv->gene[4], nouv->gene[5], nouv->gene[6], nouv->gene[7],nouv->famille);
            }
            nouv=nouv->suiv;
        }
        if(compteur_presence)
                fprintf(fichier,"\n");
    }


    fclose(fichier);
    }
    //ecriture du fichier sortie
    affiche(liste);
    //indique la distance et la famille


    return 0;


}
