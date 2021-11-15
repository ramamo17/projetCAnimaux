#include"fonctions.h"
#include<stdio.h>
#include<stdlib.h>
void usage(char *prog) {
    fprintf(stderr, "Usage: %s r n input.phine output.phine [c]\n\n\tr: 0 (without randomness) or 1 (with randomness)\n\tn: number of iterations\n\tc: [option] nombre of generated images after the n iterations\n", prog);
}

void tore(int *x,int *y, int hauteur, int largeur){
    if (*x<0)
        *x+=hauteur;
    if(*y<0)
        *y+=largeur;
    *x=*x%hauteur;
    *y=*y%largeur;
}

void mutation(Animal *animal){
    int i= (rand()%8);
    int z= ((rand()%3)-1);
    animal->gene[i]+=z;
    if (animal->gene[i]<0){
        animal->gene[i]=0;
    }


}

void repro(Animal *animal, Liste *liste){
    //printf("%d",animal->energie);
    animal->energie=((animal->energie)/2);
    ajoutdebut(liste,animal);
}


void mortanimal(Animal *animal, Liste *liste){
    if (animal->energie<1){
        if(animal->prec==NULL){
            liste->debut=animal->suiv;
            liste->debut->prec=NULL;
        }
        else {
            if(animal->suiv==NULL){
                animal->prec->suiv=NULL;
            }
            else{
            animal->prec->suiv=animal->suiv;
            animal->suiv->prec=animal->prec;
            }
        }

    free(animal);
    liste->taille-=1;
    }
}

void orienter(Animal *animal){
    int c=0;
    for (int i=0; i<8; i++){
        c+=animal->gene[i];
    }
    int x=rand()%(c+1);
    int i=0;
    int b=animal->gene[i];
    i+=1;
    while (b<x){
        b+=animal->gene[i];
        i+=1;
    }
    animal->direction=(animal->direction+(i-1))%8;
}
void deplacer(Animal *animal){
    if (animal->direction==0){
        (animal->y)--;
    }
    if (animal->direction==1){
        (animal->x)++;
        (animal->y)--;
    }
    if (animal->direction==2){
        (animal->x)++;
    }
    if (animal->direction==3){
        (animal->x)++;
        (animal->y)++;
    }
    if (animal->direction==4){
        (animal->y)++;
    }
    if (animal->direction==5){
        (animal->x)--;
        (animal->y)++;
    }
    if (animal->direction==6){
        (animal->x)--;
    }
    if (animal->direction==7){
        (animal->x)--;
        (animal->y)--;
    }
    animal->energie-=1;
}
void manger(Animal *animal, int largeur, int monde[][largeur], Liste *liste,int gain, int seuil){
    if (monde[animal->x][animal->y]>0){
        monde[animal->x][animal->y]-=1;
        animal->energie+=gain;
        if (animal->energie>seuil-1)
            repro(animal, liste);
    }
}

void ajoutdebut(Liste *l, Animal *animal){
        Animal *nouv = malloc(sizeof(Animal));
        nouv->x= animal->x;
        nouv->y= animal->y;
        nouv->distance=0;

        nouv->energie=animal->energie;
        nouv->direction=animal->direction;
        nouv->famille=animal->famille;
        for (int i=0;i<8;i++){
            nouv->gene[i]=animal->gene[i];

        }
        mutation(nouv);
        nouv->suiv=l->debut;
        nouv->prec=NULL;
        if (l->debut)
            l->debut->prec=nouv;
        l->debut=nouv;
        l->taille+=1;
}

void ajoutfin(Liste *l, int x, int y, int direction, int energie, int gene[8], int famille){
	Animal* nouv = malloc(sizeof(Animal));
	nouv->x = x;
    nouv->y= y;
    nouv->distance=0;
    nouv->energie=energie;
    nouv->direction=direction;
    nouv->famille=famille;
    for (int i=0;i<8;i++){
        nouv->gene[i]=gene[i];
    }
    nouv->suiv=NULL;
    nouv->prec=l->fin;
    if (l->fin)
        l->fin->suiv=nouv;
    l->fin=nouv;
    l->taille+=1;
}
void affiche(Liste* l){
	Animal* nouv=l->debut;
	while(nouv!=NULL){
		printf("%d et %d\n",nouv->distance, nouv->famille);
		nouv=nouv->suiv;
	}
}

void cuisiner(int hauteur, int largeur, int hoasis, int loasis,int xoasis,int yoasis, int monde[][largeur]){
    int a=(rand()%hauteur);
    int b=(rand()%largeur);
    monde[a][b]+=1;

    if (hoasis!=0 && loasis!=0){
    a=(xoasis+(rand()%hoasis));
    b=(yoasis+(rand()%loasis));
    monde[a][b]+=1;
    }



}
void verifgene(Animal *animal){
    if (animal->gene[0]<0 || animal->gene[1]<0 || animal->gene[2]<0 || animal->gene[3]<0 || animal->gene[4]<0 || animal->gene[5]<0 || animal->gene[6]<0 || animal->gene[7]<0){
        printf("le fichier ne respecte pas le format .phine (gene)");
        exit(1);
        }

    if(animal->gene[7]>1000){
        printf("le fichier ne respecte pas le format .phine");
        exit(1);
    }

}
void verifanim(Animal *animal){
    if (animal->x<0 || animal->y<0 || animal->direction<0 || animal->energie<0 || animal->famille<0){
        printf("%d %d %d %d %d",animal->x,animal->y,animal->direction,animal->energie,animal->famille);
        printf("le fichier ne respecte pas le format .phine (anim)");
        exit(1);
    }
}


void verifautre(int hauteur, int largeur, int xoasis, int yoasis, int hoasis, int loasis, int gain, int seuil){
    if (hauteur<1 || largeur<1 || xoasis<0 || yoasis<0 || hoasis<0 || loasis<0 || gain<0 || seuil<1){
        printf("le fichier ne respecte pas le format .phine (autre)");
        exit(1);
    }
}
int distance(Animal *animal, int xoasis, int yoasis, int hoasis, int loasis, int hauteur, int largeur){
    int xcentre=(xoasis+hoasis/2);


    int ycentre=(yoasis+loasis/2);

    int a=animal->x-xcentre;
    int b=animal->x-largeur-xcentre;

    a=(a>=0?a:-a);
    b=(b>=0?b:-b);
    a=(a<=b?a:b);
    int c=animal->x+largeur-xcentre;

    c=(c>=0?c:-c);
    a=(a<=c?a:c);

    int d=animal->y-ycentre;
    int e=animal->y-hauteur-ycentre;
    d=(d>=0?d:-d);
    e=(e>=0?e:-e);

    d=(d<=e?d:e);

    int f=animal->y+hauteur-ycentre;
    f=(f>=0?f:-f);
    d=(d<=f?d:f);

    a=(a>=d?a:d);
    return (a);

}

/*void tri_insertion(Liste *liste){
     Animal* nouv=liste->debut;
     Animal* tmp=malloc(sizeof(Animal));
     Animal* tmp2=malloc(sizeof(Animal));
     tmp=nouv;
    tmp2=nouv;
    while(tmp2!=NULL){
            printf("%d    %d\n",tmp2->distance, tmp->distance);
          if (tmp2->distance<tmp->distance)
                tmp=tmp2;
          tmp2=tmp2->suiv;
          }
    if(tmp->prec!=NULL)
            tmp->prec->suiv=tmp->suiv;
          if (tmp->suiv!=NULL)
            tmp->suiv->prec=tmp->prec;
          tmp->suiv=nouv->suiv;
          if(tmp->suiv!=NULL)
            tmp->suiv->prec=tmp;
          liste->debut=tmp;

          tmp->prec=nouv;
          nouv=nouv->suiv;


     while(nouv!=NULL){
          tmp=nouv;
          tmp2=nouv;
          while(tmp2!=NULL){
            printf("%d    %d\n",tmp2->distance, tmp->distance);
          if (tmp2->distance<tmp->distance)
                tmp=tmp2;
          tmp2=tmp2->suiv;
          }
          if(tmp->prec!=NULL)
            tmp->prec->suiv=tmp->suiv;
          if (tmp->suiv!=NULL)
            tmp->suiv->prec=tmp->prec;
          tmp->suiv=nouv->suiv;
          if(tmp->suiv!=NULL)
            tmp->suiv->prec=tmp;
          nouv->suiv=tmp;

          tmp->prec=nouv;
          nouv=nouv->suiv;

          }
       }
*/
//tentative inaboutie de gestion des pointeurs pour trier par ordre croissant

void tri_bulles(Liste *liste,int taille){
    if (taille!=1){
    int cond=1;
    int tmp=0;
    Animal *pa=liste->debut;
    while(cond){
        cond=0;
        pa=liste->debut;
        while(pa->suiv!=NULL){
            if(pa->distance>pa->suiv->distance){
                cond=1;
                tmp=pa->distance;
                pa->distance=pa->suiv->distance;
                pa->suiv->distance=tmp;

                tmp=pa->x;
                pa->x=pa->suiv->x;
                pa->suiv->x=tmp;

                tmp=pa->y;
                pa->y=pa->suiv->y;
                pa->suiv->y=tmp;

                tmp=pa->energie;
                pa->energie=pa->suiv->energie;
                pa->suiv->energie=tmp;

                tmp=pa->direction;
                pa->direction=pa->suiv->direction;
                pa->suiv->direction=tmp;

                tmp=pa->famille;
                pa->famille=pa->suiv->famille;
                pa->suiv->famille=tmp;

                tmp=pa->gene[0];
                pa->gene[0]=pa->suiv->gene[0];
                pa->suiv->gene[0]=tmp;

                tmp=pa->gene[1];
                pa->gene[1]=pa->suiv->gene[1];
                pa->suiv->gene[1]=tmp;

                tmp=pa->gene[2];
                pa->gene[2]=pa->suiv->gene[2];
                pa->suiv->gene[2]=tmp;

                tmp=pa->gene[3];
                pa->gene[3]=pa->suiv->gene[3];
                pa->suiv->gene[3]=tmp;

                tmp=pa->gene[4];
                pa->gene[4]=pa->suiv->gene[4];
                pa->suiv->gene[4]=tmp;

                tmp=pa->gene[5];
                pa->gene[5]=pa->suiv->gene[5];
                pa->suiv->gene[5]=tmp;

                tmp=pa->gene[6];
                pa->gene[6]=pa->suiv->gene[6];
                pa->suiv->gene[6]=tmp;

                tmp=pa->gene[7];
                pa->gene[7]=pa->suiv->gene[7];
                pa->suiv->gene[7]=tmp;
            }
        pa=pa->suiv;

        }
    }



    }
}
