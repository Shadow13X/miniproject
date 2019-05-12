
/////////// Ajout Emprunte /////////////

void e_add(Emprunte empr)
{
    FILE *femp1,*femp = NULL;
    femp = fopen("empruntes", "ab");
    femp1 = fopen("logs", "ab");
    if (!femp&&!femp1)
    {
        printf("ERREUR ,LE FICHIER N'EXISTE PAS !");
    }
    else
    {
        printf("Entrez le code de l'adherent :\n");
        scanf("%d", &(empr.id_ad));
        printf("Entrez le code film :\n");
        scanf("%d", &(empr.id_film));
        printf("Entrez la date d'emprunte :\n");
        scanf("%d/%d/%d", &(empr.d_empr.j),&(empr.d_empr.m),&(empr.d_empr.a));
        printf("Entrez la date de retour:\n");
        scanf("%d/%d/%d", &(empr.d_rtr.j),&(empr.d_rtr.m),&(empr.d_rtr.a));
        fwrite(&empr,sizeof(empr),1,femp);
        fwrite(&empr,sizeof(empr),1,femp1);
        fclose(femp);
        fclose(femp1);
    }
}
/////////// Retour Emprunte ////////////

void e_back(int idad,int id_movie)
{
    int i = 0;
    Emprunte e_tmp;
    Film film;
    FILE *f = fopen("empruntes", "rb");//ouvir le fichier fname
    FILE *_f = fopen("film", "rb");
    printf("test");
    if (!f)
    {
        printf("Unable to open file empruntes");
    }
    else
    {
        FILE *p = fopen("tmp.bin", "wb");                 //creer un autre fichier pour
        while (fread(&e_tmp, sizeof(Emprunte), 1, f) != NULL) //searching in all the element of the file
        {
            if ((e_tmp.id_ad==idad)&&(e_tmp.id_film==id_movie))
            {
                printf("A film with requested name found and deleted.\n\n");
                i = 1;
                if (!_f)
                {
                    printf("Unable to open file empruntes");
                }
                else
                {
                    FILE *k = fopen("tmp1.bin", "wb");                 //creer un autre fichier pour
                    while (fread(&film, sizeof(Film), 1, _f) != NULL) //searching in all the element of the file
                    {
                        if (film.code_film==id_movie)
                        {
                            printf("A copy is added.\n\n");
                            (film.nbr_copie)++;
                            i = 1;
                            fwrite(&film, sizeof(Film), 1, k);
                        }
                        else
                        {
                            fwrite(&film, sizeof(Film), 1, k);
                        }
                    }
                    if (!i)
                    {
                        printf("No copies were found \n");
                    }
                    fclose(_f);
                    fclose(k);
                    remove("film");
                    rename("tmp1.bin","film");
                }
            }
            else
            {
                fwrite(&e_tmp, sizeof(Emprunte), 1, p);
            }
        }
        if (!i)
        {
            printf("No recore of this borrow found \n");
        }
        fclose(f);
        fclose(p);
        remove("empruntes");
        rename("tmp.bin","empruntes");
    }

}
/////////// Ajout film /////////////////

void m_add(Film movie)
{ //fonction pour ajouter un film

    //movie est un pointeur sur les films existant
    FILE *f = NULL;                 //pointeur de type file pour pointer sur fichier
    f = fopen("film", "ab");       //ouvrir le fichier film.txt pour "appending informations"
    if (!f)                         //si f == null
        printf("ERREUR ,LE FICHIER N'EXISTE PAS !");
    else
    {
        printf("Entrez le code film :\n");
        scanf("%d", &(movie.code_film));
        printf("Entrez le titres film :\n");
        scanf(" %s", &(movie.titre));
        printf("Entrez le nombre de copies disponibles :\n");
        scanf("%d", &(movie.nbr_copie));
        printf("Entrez le type du film :\n");
        fflush(stdin);
        movie.type=getchar();
        printf("L'audience adapte pour le film :\n");
        fflush(stdin);
        movie.adapted=getchar();
        fwrite(&movie,sizeof(Film),1,f);
        fclose(f);//fermer le fichier apres l'ajout des informations                                                                                                                                                                                                            //incrementer le nombre des films
    }
}
/////////// modifier un film ///////////

void m_modif(Film *movie)
{ //fonction pour modifier un film
    int n;
    FILE *f = NULL;          //pointeur de type file pour pointer sur fichier
    f = fopen("film", "ab");//ouvrir le fichier film.txt pour le modifier
    _f=fopen("film", "rb");
    if (!f)                  //si f == null
        printf("ERREUR ,LE FICHIER N'EXISTE PAS !");
    else
    {
        printf("Entrer le code film que vous voulez modifier : ");
        scanf("%d", &n);
        int i=0;
        while (fread(&movie, sizeof(Film), 1, _f) != NULL)
        {
            if (movie.code_film == n)
            {
                printf("Entrez le code film :\n");
                scanf("%d", &movie.code_film);
                printf("Entrez le titres film :\n");
                scanf(" %s", movie.titre);
                printf("Entrez le nombre de copies disponibles :\n");
                scanf("%d", &movie.nbr_copie);
                printf("Entrez le type du film :\n");
                fflush(stdin);
                movie.type = getchar();
                printf("L'audience adapte pour le film :\n");
                fflush(stdin);
                movie.adapted = getchar();
                fwrite(&movie,sizeof(Film),1,f); //ajouter les infos du film a la fin du prog
                fclose(f);
                i=1;
            }
            else
            {
                fwrite(&movie, sizeof(Film), 1, f);
            }
        }
        if (!i)
        {
            printf("No film found with the requested name: %s\n\n", titre);
        }
    }
}
/////////// supprimer un film //////////

void m_del(char *titre) //fname :  file name,titre : titre du film
{                                        //fonction pour supprimer un film
    Film movie;
    int i = 0;
    FILE *f = fopen("film", "rb"); //ouvir le fichier fname
    if (!f)
    {
        printf("Unable to open file %s", fname);
    }
    else
    {
        FILE *p = fopen("tmp.bin", "wb");                 //creer un autre fichier pour
        while (fread(&movie, sizeof(Film), 1, f) != NULL) //searching in all the element of the file
        {
            if (strcmp(titre, movie.titre) == 0)
            {
                printf("A film with requested name found and deleted.\n\n");
                i = 1;
            }
            else
            {
                fwrite(&movie, sizeof(Film), 1, p);
            }
        }
        if (!i)
        {
            printf("No film found with the requested name: %s\n\n", titre);
        }
        fclose(f);
        fclose(p);
        remove("film");
        rename("tmp.bin", "film");
    }
}
/////////// affichage liste film ///////

void m_show(Film *movie)
{
    char c;
    FILE *f = fopen("film", "rb");
    if (!f) //si f == null
        printf("ERREUR ,LE FICHIER N'EXISTE PAS !");
    else
    {
        while ((c = fgetc(f) != EOF))
        {
            printf("%c", c);
        }
    }
    fclose(f);
}
