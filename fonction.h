#include "structure.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

/////////// G var ///////////////////////////////////////////
int size,size_m,size_a,size_e;
Film *movie;
Adherent *subs;
Emprunte *borrow;
/////////// extern input //////////////////////////////////////
void saisie(char *s)
{
    int size=1;
    char c;
    s=(char *)malloc(1);
    if (s==NULL)
    {
    printf( " pas assez de mémoire 1!!! \n" );
    system("exit");
    }
    while(c!='\n')
    {
        c=getchar();
        if(((c<='z')&&(c>='a'))||((c<='Z')&&(c>='A'))||(c==' ')||(c==';')||(c==',')||((c<='9')&&(c>='0')))
        {
            *(s+size-1)=c;
            size++;
            //printf("test");
            s=realloc(s,size);
            if (s==NULL)
            {
            printf( " pas assez de mémoire 2 !!! \n" );
            system("exit");
            }
        }
    }
    s=realloc(s,size--);
    if (s==NULL)
    {
        printf( " pas assez de mémoire 2 !!! \n" );
        system("exit");
    }
    //return size;
}
/////////// load file in a structure array ////////////////////
void load_from_file(char *fname)
{
    size =0;
	int i = 0;
	FILE *fp;
	fp= fopen(fname, "rt");
	size = get_count(fname);
    if(!strcmp(fname,"adherent"))
    {
    	size_a=size;
    	subs = malloc(size);
        for(; i < size; i++)
        {
            fscanf(fp, "%d %s %s %s %s %c\n", subs[i].code_adh,subs[i].nom,subs[i].prenom,subs[i].adresse,subs[i].phone,subs[i].categorie);
        }
    }else if(!strcmp(fname,"film"))
    {
        size_m=size;
        movie = malloc(size);
        for(; i < size; i++)
        {
            fscanf(fp, "%d %s %d %c %c\n", movie[i].code_film,movie[i].titre,movie[i].nbr_copie,movie[i].type,movie[i].adapted);
        }
    }else if(!strcmp(fname,"emprunte"))
    {
        size_e=size;
        borrow = malloc(size);
        for(; i < size ; i++)
        {
            fscanf(fp, "%d %d %d/%d/%d %d/%d/%d\n", borrow[i].id_ad,borrow[i].id_film,borrow[i].d_empr.j,borrow[i].d_empr.m,borrow[i].d_empr.a,borrow[i].d_rtr.j,borrow[i].d_rtr.m,borrow[i].d_rtr.a);
        }
    }
    fclose(fp);
}
/////////// count the number of lines in a file ///////////////
int get_count(char* str)
{

    char c;
    int count = 0;
    FILE *fp = fopen(str, "rt");

    if (fp == NULL)
 		return -1;

    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            count++;

    fclose(fp);
    return count;
}
/////////// Save file /////////////////////////////////////////
void save_file()
{
	int i,j,k=i=j=0;

	FILE *fp_a;
	FILE *fp_f=fopen("film","wt");
	FILE *fp_e=fopen("emprunte","wt");
    printf("test");
    fp_a=fopen("adherent","w");
    if(fp_a==NULL)
        perror("Error: ");
    if (!fp_a)
    {
        for(i=0; i < size_a; i++)
        {
            fprintf(fp_a, "%d %s %s %s %s %c\n", subs[i].code_adh,subs[i].nom,subs[i].prenom,subs[i].adresse,subs[i].phone,subs[i].categorie);
        }
    }else{printf("bullshit");}
//    for(j=0; j < size_m; j++)
//    {
//        fprintf(fp_f, "%d %s %d %c %c\n", movie[j].code_film,movie[j].titre,movie[j].nbr_copie,movie[j].type,movie[j].adapted);
//    }
//    for(k=0; k < size_e; k++)
//    {
//        fprintf(fp_e, "%d %d %d/%d/%d %d/%d/%d\n", borrow[k].id_ad,borrow[k].id_film,borrow[k].d_empr.j,borrow[k].d_empr.m,borrow[k].d_empr.a,borrow[k].d_rtr.j,borrow[k].d_rtr.m,borrow[k].d_rtr.a);
//    }
    close(fp_e);
    close(fp_f);
    close(fp_a);
}
/////////// add user //////////////////////////////////////////
void a_add()
{
	subs=realloc(subs,size_a+1);
    printf("Entrer votre numero :");            // la saisie des informations de l'adherent
    scanf("%d",&subs[size_a].code_adh);
    printf("Entrer votre nom :");
    scanf("%s",subs[size_a].nom);
    printf("Entrer votre prenom :");
    scanf("%s",subs[size_a].prenom);
    printf("Entrer votre adresse:");
    fflush(stdin);
    saisie(subs[size_a].adresse);
    printf("Entrer votre numero de telephone :");
    gets(subs[size_a].phone);
    printf("Entrer votre categorie adulte (A),enfant(E) et adolescent (T)  :");
    fflush(stdin);
    subs[size_a].categorie=getchar();
	size_a++; // la var correspondent à la taille du tab s'inscremente chaque fois qu'on ajoute un adherent .
}
/////////// delete user ///////////////////////////////////////
void a_del()
{
	int i,j;
	char x;
	printf("Entrer N° de l'adherent que vous souhaitez supprimer :"); /* La demande de la saisie du numero de l'adherent à supprimer .*/
	scanf("%s",&x);
	for (i=0;i<size_a;i++) // la balayge du tab des numero afin de retrouver le numero corresponent
	{
		if (subs[i].code_adh==x) // la cas où le numero de l'adherent existe
		{
            for (j=i;j<size_a;j++) // le nouveau tab commencera de l'indice de l'adherent à supprimer
            {
                subs[j]=subs[j+1]; // la suupression de l'adherent en ecrasant son data (stockage de l'adherent qui le suit dans son espace memoire )
            }
        }
        else // la cas contraire
		{
			printf("Cette personne n'est pas notre adherent.\n");
		}

    }
    size_a--;
    subs=realloc(subs,size_a); // la diminution de la taille du tab des structures adherent apres suppression d'un element de ce dernie
}
/////////// show one subscriber ///////////////////////////////
void a_show_one()
{
	int i;
	char x;
	printf("Entrer le numero de l'adherent que vous souhaitez afficher :");
	scanf("%s",&x);
    int flag=1;
	for (i=0;i<size_a;i++) // balayage à la recherche d'un identification du numero
	{
		if (subs[i].code_adh==x) // Dans le cas où on identifie le numero de l'adherent
		{
			printf(" votre N° : %s \n",subs[i].code_adh); // Affichage des informations de l'adherent
			printf(" votre nom: %s \n",subs[i].nom);
			printf(" votre prenom : %s \n",subs[i].prenom);
			printf(" votre adresse : %s \n",subs[i].adresse);
			printf(" votre numero de telephone : %s \n",subs[i].phone);
			printf(" votre categorie : %c \n",subs[i].categorie);
			break;
			flag=0;
		}
	}
	if(flag)
    {
        printf("Cette personne n'est pas notre adherent\n");
    }
}
/////////// search a subscriber ///////////////////////////////
int a_search(int x)
{
	int i;
	//printf("Entrer le numero de l'adherent que vous souhaitez rechercher :");
	//scanf("%d",&x);
	int flag=1; // la lecture du numero de l'adherent à rechercher
	for (i=0;i<size_a;i++) // balayage à la recherche d'un identification du numero
	{
		if (subs[i].code_adh==x) // Dans le cas où on identifie le numero de l'adherent
		{
			//printf("Cette personne est bien notre adherent\n");
			return 0;
			break;
		}
	}
	if(flag)
    {
        printf("Cette personne n'est pas notre adherent\n");
        return 1;
    }
}
/////////// search a subscriber ///////////////////////////////
int m_search(int x)
{
	int i;
	//printf("Entrer le numero de l'adherent que vous souhaitez rechercher :");
	//scanf("%d",&x);
	int flag=1; // la lecture du numero de l'adherent à rechercher
	for (i=0;i<size_m;i++) // balayage à la recherche d'un identification du numero
	{
		if (movie[i].code_film==x) // Dans le cas où on identifie le numero de l'adherent
		{
			//printf("Cette personne est bien notre adherent\n");
			return 0;
			break;
		}
	}
	if(flag)
    {
        printf("Ce film n'existe pas.\n");
        return 1;
    }
}
/////////// search a borrow record ////////////////////////////
int e_search(int x,int y)
{
	int i;
	//printf("Entrer le numero de l'adherent que vous souhaitez rechercher :");
	//scanf("%d",&x);
	int flag=1; // la lecture du numero de l'adherent à rechercher
	for (i=0;i<size_m;i++) // balayage à la recherche d'un identification du numero
	{
		if (borrow[i].id_ad==x) // Dans le cas où on identifie le numero de l'adherent
		{
			if (borrow[i].id_film==y) // Dans le cas où on identifie le numero de l'adherent
            {
                printf("record deleted perfectly!\n");
                return 0;
                break;
            }
		}
	}
	if(flag)
    {
        printf("no record found.\n");
        return 1;
    }
}
/////////// alphabetic sort ///////////////////////////////////
void a_sort()
{
    int i,j;
    Adherent tmp;
    for (i = 0; i < size_a -1 ; i++)
    {
        for (j = i + 1; j < size_a; j++)
        {
            if (strcmp(subs[i].nom,subs[j].nom) > 0)
            {
                memcpy(&tmp,&subs[i], sizeof(Adherent));
                memcpy(&subs[i],&subs[j], sizeof(Adherent));
                memcpy(&subs[j], &tmp, sizeof(Adherent));
            }
        }
    }
    for (i=0;i<size_a;i++)
    {

        printf(" votre N° : %s \n",subs[i].code_adh); // Affichage des informations de l'adherent
        printf(" votre nom: %s \n",subs[i].nom);
        printf(" votre prenom : %s \n",subs[i].prenom);
        printf(" votre adresse : %s \n",subs[i].adresse);
        printf(" votre numero de telephone : %s \n",subs[i].phone);
        printf(" votre categorie : %c \n",subs[i].categorie);
    }

}
/////////// modify user ///////////////////////////////////////
void a_modify()
{
    int i;
	char x ;
	printf("Entrer le numero de l'adherent que vous souhaitez modifier:");
	scanf("%s",&x);
	for (i=0;i<size;i++) // la balayge du tab des numero afin de retrouver le numero corresponent
	{
		if (subs[i].code_adh==x) // la cas où le numero de l'adherent existe
		{
			printf("Entrer votre numero :");            // la saisie des informations de l'adherent
			scanf("%d",subs[i].code_adh);
            printf("Entrer votre nom :");
			scanf("%s",subs[i].nom);
            printf("Entrer votre prenom :");
            scanf("%s",subs[i].prenom);
            printf("Entrer votre adresse:");
            fflush(stdin);
            saisie(subs[size_a].adresse);
            printf("Entrer votre numero de telephone :06");
			scanf("%d",subs[i].phone);
            printf("Entrer votre categorie adulte (A),enfant(E) et adolescent (T)  :");
            fflush(stdin);
            subs[size_a].categorie=getchar();
		}
		else
		{
			printf("Cette personne n'est pas notre adherent.");

		}
    }
}
/////////// add movie /////////////////////////////////////////
void m_add() //fonction pour ajouter un film
{
    movie = realloc(movie, (size_m + 1));
    printf("Entrez le code film :\n");
    scanf("%d", &(movie[size_m].code_film));
    printf("Entrez le titres film :\n");
    scanf(" %s", movie[size_m].titre);
    printf("Entrez le nombre de copies disponibles :\n");
    scanf("%d", &(movie[size_m].nbr_copie));
    printf("Entrez le type du film :\n");
    scanf(" %c", &(movie[size_m].type));
    printf("L'audience adapte pour le film :\n");
    scanf(" %c", &(movie[size_m].adapted));
    size_m++; //incrementer le nombre des films
}
/////////// modify movie //////////////////////////////////////
void m_modif()
{
    int n;
    printf("Entrer le code film que vous voulez modifier : ");
    scanf("%d", &n);
    int j,i = 0;
    for (j = 0; j <= size_m; j++)
    {
        if (movie[j].code_film == n)
        {
            printf("Entrez le code film :\n");
            scanf("%d", &movie[j].code_film);
            printf("Entrez le titres film :\n");
            scanf(" %s", movie[j].titre);
            printf("Entrez le nombre de copies disponibles :\n");
            scanf("%d", &movie[j].nbr_copie);
            printf("Entrez le type du film :\n");
            fflush(stdin);
            movie[j].type = getchar();
            printf("L'audience adapte pour le film :\n");
            fflush(stdin);
            movie[j].adapted = getchar();
            i = 1;
        }
    }
    if (!i)
    {
        printf("No film found with the requested code ! \n\n");
    }
}
/////////// delete movie //////////////////////////////////////
void m_del()
{
    int n;
    printf("Entrer le code film que vous voulez supprimer : ");
    scanf("%d", &n);
    int k,j,i = 0;
    for (j = 0; j <= size_m; j++)
    {
        if (movie[j].code_film == n)
        {
            for (k=j;k<size_m;k++)
            {
                movie[j].code_film=movie[k+1].code_film;
                strcpy(movie[k].titre,movie[k+1].titre);
                movie[k].nbr_copie = movie[k+1].nbr_copie;
                movie[k].type = movie[k+1].type;
                movie[k].adapted = movie[k+1].adapted;
                i = 1;
            }
            size_m--;
        }

        break;
    }
    if (!i)
    {
        printf("No film found with the requested code ! \n\n");
    }
    movie=realloc(movie,size_m);
}
/////////// alphabetic sort ///////////////////////////////////
void m_show(Film *movie)
{
    char *x;
    int j,i;
    x = (char *)malloc(20 * sizeof(char));
    for (i = 1; i < size_m; i++)
    {
        strcpy(x, movie[i].titre);
        j = i - 1;
        while (j >= 0 && strcmp(x, movie[j].titre) < 0)
        {
            strcpy(movie[j + 1].titre, movie[j].titre);
            j = j - 1;
        }
        strcpy(movie[j + 1].titre, x);
    }
}
////////// check if movie is available ////////////////////////
int is_available(int x)
{
    int i;
	//printf("Entrer le numero de l'adherent que vous souhaitez rechercher :");
	//scanf("%d",&x);
	int flag=1; // la lecture du numero de l'adherent à rechercher
	for (i=0;i<size_m;i++) // balayage à la recherche d'un identification du numero
	{
		if (movie[i].code_film==x) // Dans le cas où on identifie le numero de l'adherent
		{
			//printf("Cette personne est bien notre adherent\n");
			if(movie[i].nbr_copie>0)
            {
                movie[i].nbr_copie--;
                return 0;
                break;
            }
		}
	}
	if(flag)
    {
        printf("Il n'y a pas des copies libres.\n");
        return 1;
    }
}
////////// check if movie is adapted to subscriber ////////////
int is_adapted(int x,char t)
{
    int i;
	//printf("Entrer le numero de l'adherent que vous souhaitez rechercher :");
	//scanf("%d",&x);
	int flag=1; // la lecture du numero de l'adherent à rechercher
	for (i=0;i<size_m;i++) // balayage à la recherche d'un identification du numero
	{
		if (movie[i].code_film==x) // Dans le cas où on identifie le numero de l'adherent
		{
			//printf("Cette personne est bien notre adherent\n");
			if((toupper(movie[i].adapted)==toupper(t))||(toupper(movie[i].adapted)=='A'))
            {
                return 0;
            }
		}
	}
	if(flag)
    {
        printf("ce film n'est pas adapte à votre categorie.\n");
        return 1;
    }
}
////////// returns the category of subscriber /////////////////
char a_type(int x)
{
    int i;
	//printf("Entrer le numero de l'adherent que vous souhaitez rechercher :");
	//scanf("%d",&x);
	int flag=1; // la lecture du numero de l'adherent à rechercher
	for (i=0;i<size_a;i++) // balayage à la recherche d'un identification du numero
	{
		if (subs[i].code_adh==x) // Dans le cas où on identifie le numero de l'adherent
		{
			return subs[i].categorie;
		}
	}
}
////////// check if subscriber borrows are limit //////////////
int e_limit(int x)
{
    char t;
    t=a_type(x);
    int k=0;
    int i,j;
    for (i=0;i<size_e;i++)
    {
        if(borrow[i].id_ad==x)
        {
            k++;
        }
    }
    if(toupper(t)=='W')
    {
        if(k>0)
        {
            printf("T'es deja en cas limite.\n");
            return 0;
        }else{return 1;}
    }else if(toupper(t)=='T')
    {
        if(k>1)
        {
            printf("T'es deja en cas limite.\n");
            return 0;
        }else{return 1;}
    }else if(toupper(t)=='A')
    {
        if(k>2)
        {
            printf("T'es deja en cas limite.\n");
            return 0;
        }else{return 1;}
    }
}
/////////// borrow movie //////////////////////////////////////
int e_borrow()
{
    int i,x,y;
    char c;
    char type;
    int flag=1;
    while(flag)
    {
        printf("Entrez le code de l'adherent :\n");
        scanf("%d", &x);
        flag=a_search(x);
        if (flag)
        {
            printf("Voulez vous essayer un autre code(y/n):");
            fflush(stdin);
            c=getchar();
            if (c=='y')
            {
                continue;
            }else{ return 0;}
        }
        type=a_type(x);
        flag=e_limit(x);
        if (flag)
        {
            return 0;
        }
    }
    flag=1;
    while(flag)
    {
        printf("Entrez le code film :\n");
        scanf("%d", &y);
        flag=m_search(y);
        if (flag)
        {
            printf("Voulez vous essayer un autre code(y/n):");
            fflush(stdin);
            c=getchar();
            if (c=='y')
            {
                continue;
            }else{ return 0;}
        }
        flag=is_adapted(y,type);
        if (flag)
        {
            printf("Voulez vous essayer un autre film mieux adapte(y/n):");
            fflush(stdin);
            c=getchar();
            if (c=='y')
            {
                continue;
            }else{ return 0;}
        }
        flag=is_available(y);
        if (flag)
        {
            printf("Voulez vous essayer un autre film qui est disponible(y/n):");
            fflush(stdin);
            c=getchar();
            if (c=='y')
            {
                continue;
            }else{ return 0;}
        }
    }
    borrow = realloc(borrow, (size_e + 1));
    borrow[size_e].id_ad=x;
    borrow[size_e].id_film=y;
    printf("Entrez la date d'emprunte :\n");
    scanf("%d/%d/%d", &(borrow[size_e].d_empr.j),&(borrow[size_e].d_empr.m),&(borrow[size_e].d_empr.a));
    printf("Entrez la date de retour:\n");
    scanf("%d/%d/%d", &(borrow[size_e].d_rtr.j),&(borrow[size_e].d_rtr.m),&(borrow[size_e].d_rtr.a));
    size_e++;
    for (i=0;i<size_m;i++)
    {
        if (movie[i].code_film==y)
        {
            movie[i].nbr_copie--;
        }
    }
}
/////////// return movie //////////////////////////////////////
void e_return()
{
	int i,j,l,flag=1;
	char x,y;
	while (flag)
    {
        printf("Entrer N° de l'adherent:"); /* La demande de la saisie du numero de l'adherent à supprimer .*/
        scanf("%s",&x);
        printf("Entrer N° du film:"); /* La demande de la saisie du numero de l'adherent à supprimer .*/
        scanf("%s",&y);
        flag=e_search(x,y);
    }
	for (i=0;i<size_e;i++) // la balayge du tab des numero afin de retrouver le numero corresponent
	{
		if ((borrow[i].id_ad==x)&&(borrow[i].id_film==y)) // la cas où le numero de l'adherent existe
		{
            for (j=i;j<size_a;j++) // le nouveau tab commencera de l'indice de l'adherent à supprimer
            {
                borrow[j]=borrow[j+1]; // la suupression de l'adherent en ecrasant son data (stockage de l'adherent qui le suit dans son espace memoire )
            }
        }
        else // la cas contraire
		{
			printf("Cette personne n'est pas notre adherent.\n");
		}

    }
    for (l=0;l<size_m;l++)
    {
        if(movie[l].code_film==y)
        {
            movie[l].nbr_copie++;
        }
    }
    size_e--;
    borrow=realloc(borrow,size_e); // la diminution de la taille du tab des structures adherent apres suppression d'un element de ce dernie
}
/////////// showing the list of borrowed movies ///////////////
void e_show_m()
{
    int *tmp;
    int l,i,j,flag,k=flag=0;
    tmp=malloc(1);
    for(i=0;i<size_e;i++)
    {
        for(j=0;j<size_m;j++)
        {
            if (movie[j].code_film==borrow[i].id_film)
            {
                for(l=0;l<=k;l++)
                {
                    if(*(tmp+l)==borrow[i].id_film)
                    {
                        flag=1;
                        break;
                    }
                }
                if(!flag)
                {
                    tmp=realloc(tmp,k+1);
                    *(tmp+k)=borrow[i].id_film;
                    k++;
                }
            }
        }
    }
    printf("Les films empruntes:\n");
    k--;
    for(i=0;i<k;i++)
    {
        for(j=0;j<size_m;j++)
        {
            if (movie[j].code_film==tmp[i])
            {
                printf("%s\n",movie[j].titre);
            }
        }
    }
    free(tmp);
}
/////////// showing the list of borrowers /////////////////////
void e_show_a()
{
    int *tmp;
    int l,i,j,flag,k=flag=0;
    tmp=malloc(1);
    for(i=0;i<size_e;i++)
    {
        for(j=0;j<size_a;j++)
        {
            if (subs[j].code_adh==borrow[i].id_ad)
            {
                for(l=0;l<=k;l++)
                {
                    if(*(tmp+l)==borrow[i].id_ad)
                    {
                        flag=1;
                        break;
                    }
                }
                if(!flag)
                {
                    tmp=realloc(tmp,k+1);
                    *(tmp+k)=borrow[i].id_ad;
                    k++;
                }
            }
        }
    }
    k--;
    printf("Les emprunteurs de films:\n");
    for(i=0;i<k;i++)
    {
        for(j=0;j<size_a;j++)
        {
            if (subs[j].code_adh==tmp[i])
            {
                printf("%s %s\n",subs[j].nom,subs[j].prenom);
            }
        }
    }
    free(tmp);
}
/////////// showing movies borrowed by a subscriber ///////////
void e_show_a_m()
{
    int i,j,x;
    printf("Entrez le numero de l'adherent dont vous voulez afficher les films empruntes.\n");
    scanf("%d",&x);
    for(i=0;i<size_a;i++)
    {
        if(subs[i].code_adh==x)
        {
            printf("les films empruntes par %s %s :\n",subs[i].nom,subs[i].prenom);
            break;
        }
    }
    for(i=0;i<size_e;i++)
    {
        if(borrow[i].id_ad==x)
        {
            for(j=0;j<size_m;j++)
            {
                if(borrow[i].id_film==movie[j].code_film)
                {
                    printf("- %s\n",movie[j].titre);
                }
            }
        }
    }
}
/////////// subscribers menu //////////////////////////////////
void a_menu()
{
	printf("\t\t\t MENU ADHERENT  \n");
	printf(" \n 1- Ajouter un adherent .");
    printf(" \n 2- Afficher un adherent .");
    printf(" \n 3- Supprimer un adherent .");
    printf(" \n 4- Rechercher un adherent .");
    printf(" \n 5- Modifier un adherent .");
    printf(" \n 6- Afficher tous les adherents .");
    printf(" \n \t Tapez 0 pour revenir au menu principal  .\n");
    printf(" \n \t Tapez 9 pour sotir .\n");
}
/////////// movies menu ///////////////////////////////////////
void m_menu()
{
    printf("\t\t\t MENU FILM  \n");
	printf(" \n 1- Ajouter un film.");
	printf(" \n 2- Modifier un film .");
	printf(" \n 3- Supprimer un film.");
	printf(" \n 4- Rechercher un film .");
	printf(" \n 5- Afficher tous les films .");
	printf(" \n \t Tapez 0 pour revenir au menu principal  .\n");
	printf(" \n \t Tapez 9 pour sotir .\n");
}
/////////// borrows menu //////////////////////////////////////
void e_menu()
{
	printf("\t\t\t MENU PRETS \n");
	printf(" \n 1- Emprunter un film.");
	printf(" \n 2- Rendre un film .");
	printf(" \n 3- Afficher la liste des films empruntes.");
	printf(" \n 4- Afficher la liste des emprunteurs de films .");
	printf(" \n 5- Afficher la liste des films empruntes par un adherent .");
	printf(" \n \t Tapez 0 pour revenir au menu principal .\n");
	printf(" \n \t Tapez 9 pour sotir .\n");
}
/////////// main menu /////////////////////////////////////////
void main_menu()
{
	printf("\t\t\t MENU PRINCIPAL  \n");
	printf(" \n 1- Aller au menu adherent.");
	printf(" \n 2- Aller au menu film .");
	printf(" \n 3- Aller au menu prêts.");
	printf(" \n \t Tapez 9 pour sotir .\n");
}
///////////////////////////////////////////////////////////////
