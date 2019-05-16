#include <stdio.h>
#include<stdlib.h>
typedef struct
{
    int j,m,a;
} Date;

//////////// Film /////////////

typedef struct
{
    int code_film;  //code film;
    char titre[50]; // titre de film
    int nbr_copie;  // nombre de copie disponibles
    char type;      //type de film
    char adapted;   //Adapte
} Film;

/////////// Empruntes /////////

typedef struct
{
    int id_ad,id_film;
    Date d_empr,d_rtr;
}Emprunte;

/////////// Adherent //////////

typedef struct
{
    int code_adh;
    char nom[20];
    char prenom[20];
    char phone[20];
    char *adresse;
    char categorie;
}Adherent;
