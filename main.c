#include <stdio.h>
#include <stdlib.h>
#include "ELTUSER.h"
#include "graphe.h"
#include <stdio.h>
#include <limits.h>
#define N 5
#define INF 99999

int main() {
    graphePondere g = creerGraphe(100);
    int choix;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Ajouter un utilisateur\n");
        printf("2. Ajouter une relation\n");
        printf("3. Supprimer une relation\n");
        printf("4. Afficher le graphe\n");
        printf("5. detruire le graphe\n");
        printf("6. Charger un graphe depuis un fichier\n");
        printf("7. Sauvegarder le graphe dans un fichier\n");
        printf("8. DFS - Amis directs et indirects\n");
        printf("9. BFS - Amis jusqu'a une distance N\n");
        printf("10.DIJKSTRA:trouver les connexions les plus solides \n");
        printf("11.afficher les communautés \n");
        printf("12. supprimer un utilisateur\n");
        printf("13. calculer centralité \n");

        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            int id, age;
            char nom[50];
            printf("ID: "); scanf("%d", &id);
            printf("Nom: "); scanf("%s", nom);
            printf("Age: "); scanf("%d", &age);
            ajouterutilisateur(g, creeruser(id, nom, age));
        } else if (choix == 2) {
            int src, dest, poids;
            printf("Utilisateur source: "); scanf("%d", &src);
            printf("Utilisateur destination: "); scanf("%d", &dest);
            printf("Poids de la relation: "); scanf("%d", &poids);
            ajouterRelation(g, src, dest, poids);
        } else if (choix == 3) {
            int src, dest;
            printf("Utilisateur source: "); scanf("%d", &src);
            printf("Utilisateur destination: "); scanf("%d", &dest);
            supprimerRelation(g, src, dest);
        } else if (choix == 4) {
            afficherGraphe(g);
        } else if(choix==5){
        detruiregraphe(g);
        }
        else if (choix == 6) {
            char fichier[100];
            printf("Nom du fichier: "); scanf("%s", fichier);
            g = chargerGraphe(fichier);
        } else if (choix == 7) {
            char fichier[100];
            printf("Nom du fichier: "); scanf("%s", fichier);
            sauvegarderGraphe(g, fichier);
        }
        else if(choix==8){int id;
            printf("ID utilisateur pour DFS : ");
            scanf("%d", &id);
            int* visite = malloc(g->V * sizeof(int));
            for (int i = 0; i < g->V; i++) visite[i] = 0;
            dfs(g, id, visite);
            free(visite);
        }else if(choix==9){ int id;printf("ID utilisateur pour BFS a distance : ");
            scanf("%d", &id);
             bfs(g, id);}
        else if(choix==10){int id1;int id2;
        printf(" donner ID utilisateur 1 : ");
        scanf("%d", &id1);
        printf(" donner ID utilisateur 2 : ");
        scanf("%d", &id2);
        dijkstra(g, id1, id2);
        }else if(choix==11){trouvercom(g);}
        else if(choix==12){int id1; printf(" donner ID utilisateur : ");
        scanf("%d", &id1);
        supprimerUtilisateur(g, id1);}
        else if(choix==13){
    centraliteProximiteTous(g);}
    } while (choix != 0);

    detruiregraphe(g);
    return 0;
}
