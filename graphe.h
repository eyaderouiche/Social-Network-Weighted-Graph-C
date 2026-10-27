#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "ELTUSER.h"
 typedef struct structNode {
 ELEMENT user;
 int weight;
 struct structNode* next;
 } structNode, *Node;
 typedef struct {
 int V;
 ELEMENT* utilisateurs;
 Node* adjList;
 } *graphePondere;
 graphePondere creergraphe(int V);
 void detruiregraphe(graphePondere g);
 int ajouterutilisateur(graphePondere,ELEMENT user);
 int ajouterRelation(graphePondere g, int src, int dest, int poids);
 int supprimerUtilisateur(graphePondere g, int id);
 int supprimerRelation(graphePondere g, int src, int dest);
 void afficherGraphe(graphePondere g);
 graphePondere chargerGraphe(const char* filename);
 void sauvegarderGraphe(graphePondere g, const char* filename);
 void dfs(graphePondere g, int idUser, int* visite );
 void bfs(graphePondere g, int idUser);
 void dijkstra(graphePondere g, int depart, int arrivee);
 void trouvercom(graphePondere g);


#endif // GRAPH_H_INCLUDED
