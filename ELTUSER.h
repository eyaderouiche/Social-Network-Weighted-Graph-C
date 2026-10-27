#ifndef ELTUSER_H_INCLUDED
#define ELTUSER_H_INCLUDED
typedef struct {
 int id;
 char nom[50];
 int age;
 } UtilisateurStruct, *ELEMENT;

ELEMENT creeruser(int id,const char*nom,int age);
void afficheruser(ELEMENT u);
void detruireuser(ELEMENT u);



#endif // ELTUSER_H_INCLUDED
