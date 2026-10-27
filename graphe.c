#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe.h"
#include "ELTUSER.h"
#define MAX 100
#include <stdio.h>
#include <limits.h>
#define N 5
#define INF 99999

graphePondere creerGraphe(int V){
 graphePondere g= malloc(sizeof(*g));
 g->V=V;
 g->utilisateurs=malloc(V*sizeof(ELEMENT));
 g->adjList=malloc(V*sizeof(Node));
 for(int i=0;i<V;i++){
    g->utilisateurs[i]=NULL;
     g->adjList[i]=NULL;
 }
 return g;
 }
 void detruiregraphe(graphePondere g){
    for (int i = 0; i < g->V; i++) {
        Node c = g->adjList[i];
        while (c) {
            Node t = c;
            c = c->next;
            free(t);
        }
        if (g->utilisateurs[i]) {
            detruireuser(g->utilisateurs[i]);
        }
    }
    free(g->utilisateurs);
    free(g->adjList);
    free(g);
}
int supprimerUtilisateur(graphePondere g, int id) {

    if (!g || id < 0 || id >= g->V || !g->utilisateurs[id]) {
        return -1;
    }
    for (int i = 0; i < g->V; i++) {
        if (i != id && g->utilisateurs[i]) {
            Node* curr = &g->adjList[i];
            while (*curr) {
                if ((*curr)->user->id == id) {
                    Node temp = *curr;
                    *curr = (*curr)->next;
                    free(temp);
                    break;
                } else {
                    curr = &(*curr)->next;}}}
}

    Node current = g->adjList[id];
    while (current) {
        Node temp = current;
        current = current->next;
        free(temp);}
    g->adjList[id] = NULL;
    detruireuser(g->utilisateurs[id]);
    g->utilisateurs[id] = NULL;
    return 0;
}


int ajouterutilisateur(graphePondere g,ELEMENT user){
  if(user->id>=g->V){
    return -1;}
    if (g->utilisateurs[user->id] != NULL) {
        return -2; }
    g->utilisateurs[user->id]=user;
    FILE* f = fopen("user.txt", "a");
    if (f != NULL) {
        fprintf(f, "U %d %s %d\n", user->id, user->nom, user->age);

        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture \n");
    }printf("ajout avec succes \n");

    return 0;
  }
int supprimerRelation(graphePondere g, int src, int dest) {
    if (!g->utilisateurs[src] || !g->utilisateurs[dest]){
            return -1;}
    Node* c = &g->adjList[src];
    while (*c) {
        if ((*c)->user->id == dest) {
            Node t = *c;
            *c = (*c)->next;
            free(t);
            break;
        }
        c = &(*c)->next;
    }
    c = &g->adjList[dest];
    while (*c) {
        if ((*c)->user->id == src) {
            Node t = *c;
            *c = (*c)->next;
            free(t);
            break;
        }
         c = &(*c)->next;
    }
    return 0;
}
int ajouterRelation(graphePondere g, int src, int dest, int poids) {
    if (!g->utilisateurs[src] || !g->utilisateurs[dest]) {
        return -1;
    }
    Node nouveau1 = malloc(sizeof(structNode));
    if (!nouveau1) {return -2;}

    nouveau1->user = g->utilisateurs[dest];
    nouveau1->weight = poids;
    nouveau1->next = g->adjList[src];
    g->adjList[src] = nouveau1;

    Node nouveau2 = malloc(sizeof(structNode));
    if (!nouveau2) return -2;

    nouveau2->user = g->utilisateurs[src];
    nouveau2->weight = poids;
    nouveau2->next = g->adjList[dest];
    g->adjList[dest] = nouveau2;

    return 0;
}
void afficherGraphe(graphePondere g){
    for (int i = 0; i < g->V; i++) {
        if (g->utilisateurs[i]) {
            printf("%s (%d) : ", g->utilisateurs[i]->nom, g->utilisateurs[i]->id);
            Node temp = g->adjList[i];
            while (temp) {
                printf("----%d----> %s (%d) ", temp->weight, temp->user->nom, temp->user->id);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}
graphePondere chargerGraphe(const char* user) {
    FILE* f = fopen(user, "r");
    if (!f) {
       printf("Erreur d'ouverture du fichier");
        return NULL;
    }
    graphePondere g = creerGraphe(100);
    char ligne[256];
    while (fgets(ligne, sizeof(ligne), f)) {
        if (ligne[0] == 'U') {
            int id, age;
            char nom[50];
            sscanf(ligne, "U %d %s %d", &id, nom, &age);
            ajouterutilisateur(g,creeruser(id, nom, age));
        } else if (ligne[0] == 'R') {
            int src, dest, poids;
            sscanf(ligne, "R %d %d %d", &src, &dest, &poids);
            ajouterRelation(g, src, dest, poids);
        }
    }
    fclose(f);
    return g;
}


void sauvegarderGraphe(graphePondere g, const char* user) {
    FILE* f = fopen(user, "w");
    if (!f) {
      printf("Erreur de sauvegarde");
        return;
    }

    for (int i = 0; i < g->V; i++) {
        if (g->utilisateurs[i]) {
            fprintf(f, "U %d %s %d\n", g->utilisateurs[i]->id,
                                       g->utilisateurs[i]->nom,
                                       g->utilisateurs[i]->age);
        }
    }

    for (int i = 0; i < g->V; i++) {
        Node temp = g->adjList[i];
        while (temp) {
            if (i < temp->user->id)
                fprintf(f, "R %d %d %d\n", i, temp->user->id, temp->weight);
            temp = temp->next;}}
    fclose(f);
}
void dfs(graphePondere g, int idUser, int* visite ) {
    visite[idUser] = 1;

    printf("%s ", g->utilisateurs[idUser]->nom);

    Node voisin = g->adjList[idUser];
    while (voisin != NULL) {
        int v = voisin->user->id;
        if (!visite[v]) {
            dfs(g, v, visite);
        }
        voisin = voisin->next;
    }
}
void bfs(graphePondere g, int idUser) {
    if (idUser < 0 || idUser >= g->V || g->utilisateurs[idUser] == NULL)
        return;

    int* visite = (int*)calloc(g->V, sizeof(int));
    int* file = (int*)malloc(g->V * sizeof(int));
    int debut = 0, fin = 0;
    int* niveau = (int*)calloc(g->V, sizeof(int));

    visite[idUser] = 1;
    niveau[idUser] = 0;
    file[fin++] = idUser;


    printf("Utilisateurs accessibles depuis %s (BFS) :\n", g->utilisateurs[idUser]->nom);


    while (debut < fin) {

        int courant = file[debut++];
        Node voisin = g->adjList[courant];
        while (voisin != NULL) {
            int idVoisin = voisin->user->id;
            if (!visite[idVoisin]) {
                visite[idVoisin] = 1;
                niveau[idVoisin] = niveau[courant] + 1;
                file[fin++] = idVoisin;
            }
            voisin = voisin->next;
        }
    }


    free(visite);
    free(file);
    free(niveau);
}
void dijkstra(graphePondere g, int depart, int arrivee) {
    int dist[MAX];
    int visite[MAX] = {0};
    int precedent[MAX];

    for (int i = 0; i < g->V; i++) {
        dist[i] = INF;
        precedent[i] = -1;
    }

    dist[depart] = 0;

    for (int i = 0; i < g->V - 1; i++) {
        int min = INF;
        int u = -1;


        for (int j = 0; j < g->V; j++) {
            if (!visite[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1) break;

        visite[u] = 1;

        Node voisin = g->adjList[u];
        while (voisin != NULL) {
            int v = voisin->user->id;
            int poids = voisin->weight;

            if (!visite[v] && dist[u] + poids < dist[v]) {
                dist[v] = dist[u] + poids;
                precedent[v] = u;
            }

            voisin = voisin->next;
        }
    }

    if (dist[arrivee] == INF) {
        printf("Pas de chemin entre %s et %s.\n",
               g->utilisateurs[depart]->nom,
               g->utilisateurs[arrivee]->nom);
        return;
    }


    int chemin[MAX];
    int k = 0;
    for (int i = arrivee; i != -1; i = precedent[i]) {
        chemin[k++] = i;
    }

    printf("Chemin trouvé : ");
    for (int i = k - 1; i >= 0; i--) {
        printf("%s", g->utilisateurs[chemin[i]]->nom);
        if (i > 0) printf(" -> ");
    }
    printf("\n Poids total : %d\n", dist[arrivee]);
}
void trouvercom(graphePondere g) {
    if (g == NULL) return;

    int* dejaVisite = (int*)calloc(g->V, sizeof(int));
    int* fileAttente = (int*)malloc(g->V * sizeof(int));
    int indiceDebut, indiceFin;
    int numeroCommunaute = 1;

    for (int utilisateur = 0; utilisateur < g->V; utilisateur++) {
        if (g->utilisateurs[utilisateur] != NULL && dejaVisite[utilisateur] == 0) {
            indiceDebut = 0;
            indiceFin = 0;

            printf("Communauté %d: [", numeroCommunaute);
            numeroCommunaute++;

            fileAttente[indiceFin++] = utilisateur;
            dejaVisite[utilisateur] = 1;

            int estPremierNom = 1;

            while (indiceDebut < indiceFin) {
                int utilisateurActuel = fileAttente[indiceDebut++];

                if (!estPremierNom) {
                    printf(", ");
                }
                printf("%s", g->utilisateurs[utilisateurActuel]->nom);
                estPremierNom = 0;

                Node voisin = g->adjList[utilisateurActuel];
                while (voisin != NULL) {
                    int idVoisin = voisin->user->id;

                    if (dejaVisite[idVoisin] == 0) {
                        fileAttente[indiceFin++] = idVoisin;
                        dejaVisite[idVoisin] = 1;
                    }

                    voisin = voisin->next;
                }
            }

            printf("]\n");
        }
    }

    free(dejaVisite);
    free(fileAttente);
}

void dijkstraCentralite(graphePondere g, int source, int* dist) {
    int visite[MAX] = {0};
    for (int i = 0; i < g->V; i++) {
        dist[i] = INF;
    }
    dist[source] = 0;

    for (int count = 0; count < g->V - 1; count++) {
        int min = INF;
        int u = -1;
        for (int i = 0; i < g->V; i++) {
            if (!visite[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1) return;
        visite[u] = 1;

        Node voisin = g->adjList[u];
        while (voisin != NULL) {
            int v = voisin->user->id;
            int poids = voisin->weight;
            if (!visite[v] && dist[u] + poids < dist[v]) {
                dist[v] = dist[u] + poids;
            }
            voisin = voisin->next;
        }
    }
}

void centraliteProximiteTous(graphePondere g) {
    double centralites[MAX];
    double max = 0.0;
    int meilleurs[MAX];
    int nbMeilleurs = 0;

    for (int v = 0; v < g->V; v++) {
        if (g->utilisateurs[v] == NULL) continue;

        int dist[MAX];
        dijkstraCentralite(g, v, dist);

        int somme = 0;
        for (int u = 0; u < g->V; u++) {
            if (u != v && g->utilisateurs[u] != NULL && dist[u] < INF) {
                somme += dist[u];
            }
        }

        if (somme != 0)
            centralites[v] = 1.0 / (somme + 1);
        else
            centralites[v] = 0.0;

        if (centralites[v] > max) {
            max = centralites[v];
            nbMeilleurs = 0;
            meilleurs[nbMeilleurs++] = v;
        } else if (centralites[v] == max) {
            meilleurs[nbMeilleurs++] = v;
        }
    }

    for (int i = 0; i < g->V; i++) {
        if (g->utilisateurs[i]) {
            printf("Noeud %s (%d) : %.4f\n", g->utilisateurs[i]->nom, i, centralites[i]);
        }
    }

    printf("Noeud(s) le(s) plus central(aux) : ");
    for (int i = 0; i < nbMeilleurs; i++) {
        printf("%s (%d) ", g->utilisateurs[meilleurs[i]]->nom, meilleurs[i]);
    }
    printf("\n");
}
