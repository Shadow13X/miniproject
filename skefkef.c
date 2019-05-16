#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fonction.h"
// tableau des adherents : subs.
// tableau des empruntes : borrow.
// tableau des films : movie.
int main()
{
    load_from_file("adherent");
    load_from_file("film");
    load_from_file("emprunte");
    int choice,x,y;
	do
	{
		main_menu();
		printf("Entrer votre choix : ");
		scanf(" %d",&choice);
		fflush(stdin);
		switch(choice)
		{
			case 1: do{
						a_menu();
						printf("Entrer votre choix : ");
						scanf("%d",&y);
						fflush(stdin);
						switch(y)
						{
							case 1: a_add();
							    	break;
							case 2: a_show_one();
									break;
							case 3: a_del();
									break;
							case 4: printf("Entrer le numero de l'adherent que vous souhaitez rechercher :");
									scanf("%d",&x);
							        if(a_search(x)==0)
							        {
							        	printf("Cette personne est bien notre adherent\n");
							        }
									break;
							case 5: a_modify();
									break;
							case 6: a_sort();
									break;
							case 0:break;
							case 9: save_file();
                                    return 0;
                            default:printf("ceci n'est pas un choix.");
						}
					 }
 					while(y!=0);
				break;
			case 2: do{
						m_menu();
						printf("Entrer votre choix : ");
						scanf(" %d",&y);
						fflush(stdin);
						switch(y)
						{
							case 1: m_add();
							   		break;
							case 2: m_modif();
									break;
							case 3: m_del();
									break;
							case 4: printf("Entrer le code du film que vous souhaitez rechercher :");
									scanf("%d",&x);
							        if(m_search(x)==0)
							        {
							        	printf("On a ce film.\n");
							        };
									break;
							case 5: m_show(movie);
									break;
                            case 0: break;
							case 9: save_file();
                                    return 0;
						}
					 }
 					while(y!=0);
				break;
			case 3: do{
						e_menu();
						printf("Entrer votre choix : ");
						scanf(" %d",&y);
						fflush(stdin);
						switch(y)
						{
						    case 1: e_borrow();
							   		break;
							case 2: e_return();
									break;
							case 3: e_show_m();
									break;
							case 4: e_show_a();
									break;
							case 5: e_show_a_m();
									break;
                            case 0: break;
                            case 9: save_file();
                                    return 0;
						}
					 }
 					while(y!=0);
                    break;
            case 9: save_file();
                    return 0;
	 		default: printf("Merci pour votre temps .\n");
		}
 	}
 	while(choice!=0);
    save_file();
    return 0;
}
