#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "C:\Users\jebbar\Desktop\MiniProjet\structure.h"
#include "C:\Users\jebbar\Desktop\MiniProjet\fonctions.h"

int main()
{
    Film movie;
    Emprunte empr;
    int idad,i;
    for(i=0;i<3;i++)
    {
        m_add(movie);
    }
    for(i=0;i<3;i++)
    {
        e_add(empr);
    }
    e_lfe();
    printf("Entrez l'id de l'adherent pour lequel vous voulez voir les films emprunté:");
    scanf("%d",&idad);
    e_lfa(idad);
    return 0;
}
