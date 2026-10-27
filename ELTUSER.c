#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ELTUSER.h"
ELEMENT creeruser(int id,const char*nom,int age){
  ELEMENT u=malloc(sizeof(UtilisateurStruct));
  u->id=id;
  strcpy(u->nom,nom);
  u->age=age;
  return u;
 }
void afficheruser(ELEMENT u){
 if(u)
    printf("%s ( %d ans )[ID: %d]\n ",u->nom,u->age,u->id);
 }
void detruireuser(ELEMENT u){
 free(u);}
