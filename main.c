#include <stdio.h>
#include<string.h>
typedef struct Date{
    unsigned jour ;
    unsigned mois ;
    unsigned anne ;
}Date;
typedef struct Etudiant{
    long Code ;
    char Nom[20] ;
    char Prenom[20] ;
    Date Date_Naissance ;
    float Tnotes[10] ;
    float Moy ;
}Etud;
void SAISIE_DATE(struct Date *date) {
    printf("Donner L'anne :\n");
    scanf("%u", &(date->anne));
    printf("Donner Le mois :\n");
    scanf("%u", &(date->mois));
    printf("Donner le jour :\n");
    scanf("%u", &(date->jour));
}
int TEST (struct Etudiant etud , int T[] , int n ){
    for (int i = 0 ; i < n ; i++){
        if (T[i] == etud.Code)
            return 1 ;
    }
    return 0 ;
}
int BISSEXTILE(struct Date a){
    if (((a.anne%4 == 0)&&(a.anne % 100 != 0))||(a.anne%400 == 0))
        //les condition pour savoir une anne bissextile
        return 1 ;
    else
        return 0;
}


unsigned JOUR_MAX(struct Date date){
    unsigned jour_Max ;
    switch (date.mois) {
        case 1 :case 3 :case 5 :case 7 :case 8 :case 10 :case 12 :
            jour_Max = 31 ;
            break;
        case 4 : case 6 : case 11 : case 9 :
            jour_Max = 30 ;
            break;
        default:
            // tester si l'anné est bissextile ou non
            if (BISSEXTILE(date))
                jour_Max = 29 ;
            else
                jour_Max = 28 ;
            break;


    }
    return jour_Max ;
}
int VALID_DATE(struct Date date){
    int erreur = 0 ;
    if (date.anne < 1900 ){
        printf("L'anne est invalide!\n");
        //test pour la validité de l'anné ,
        erreur++;
    }
    if (date.mois > 12 || date.mois < 1){
        printf("Le mois est invalide!\n");
        //condition d'erreur si le mois est non valide ,
        erreur++;
    }
    if(date.jour > JOUR_MAX(date)){
        printf("Jour invalide!\n");
        //si le jour est non verifié --> Message d'erreur ,
        erreur++;
    }

    return (erreur<=0);



}
int exist(int A , const int T[] , int pos ){
    for (int i = 0 ; i < pos  ; i++){
        if (T[i] == A){
            printf("Ce code deja existe chez l'etudiant numero %d :\n",i+1);
            return 1 ;
        }
    }
    return 0;
}
float CALCUL_MOY(float TC[] , Etud etudiant, int NN){
    float M = 0;
    float S_Coefficient = 0 ;
    for (int i = 0 ; i < NN ; i++){
        M += TC[i] * etudiant.Tnotes[i] ;
        S_Coefficient += TC[i] ;
    }
    return M / S_Coefficient ;
}
void Coordonne(struct Etudiant *etudiant , int i , Etud T[] ,int NN , float TC[]){
    do{
        scanf("%ld",&(etudiant->Code));
    }while(exist(etudiant->Code,T,i));
    printf("Le nom de l'etudiant %d :\n",i+1);
    scanf("%s",&(etudiant->Nom));
    printf("Le prenom :\n");
    scanf("%s",&(etudiant->Prenom));
    printf("La date de naissance :\n");
    do{
        SAISIE_DATE(&etudiant->Date_Naissance);
    }while(!VALID_DATE(etudiant->Date_Naissance));
    printf("Donner les NOTES : \n");
    for (int i = 0 ; i < NN ; i++ ){
        printf("\nMatiere Coff %.1f : ",TC[i]);
        do{
            scanf("%f",&(etudiant->Tnotes[i]));
        }while(etudiant->Tnotes[i] < 0 || etudiant->Tnotes[i] > 20);
    }
    etudiant->Moy = CALCUL_MOY(TC,*etudiant,NN);


}

void Remplir(struct Etudiant *etudiant,Etud T[] , int n ,int NN , float TC[]){
    for (int i = 0 ; i < n ; i++){
        printf("Donner le code de l'etudiant numero %d :\n",i+1);
        Coordonne(&T[i] , i  , T , NN , TC);
    }
}

void SAISIR_COIFF(int TC[] , int NN){
    for(int i = 0 ; i < NN ; i++){
        printf("Donner le Coifficient n %d :\n",i+1);
        do{
            scanf("%f",&TC[i]);
        }while(TC[i] <= 0);
    }
}
float MOYENNE_CLASS(Etud T[] , int ne ){
    int moy = 0 ;
    for (int i = 0 ; i < ne ; i++){
        moy += T[i].Moy ;
    }
    return moy / ne ;
}
/*void Affiche(Etud TE[] , int ne ){
    for (int i = 0 ; i < ne ; i++){
        printf("%s %s a %.2f moyenne :\n",TE[i].Nom,TE[i].Prenom,TE[i].Moy);

    }
}*/
void swapStrings(Etud *str1, Etud *str2) {
    Etud temp; // Assurez-vous que la taille de temp est suffisante
    temp = *str1 ;
    *str1 = *str2 ;
    *str2 = temp ;
}

void Trie(Etud *arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j]->Nom, arr[j + 1]->Nom) > 0) {
                swapStrings(arr[j], arr[j + 1]);
            }
        }
    }
}
int RANG(Etud etudiant , Etud TE[] , int ne){
    int compteur = 1 ;
    for (int i = 0 ; i < ne ; i++){
        if (TE[i].Moy > etudiant.Moy)
            compteur++;
    }
    return compteur ;
}
void AFFICHE_DATE(struct Date date ){
    printf("Date de naissance : %u/%u/%u \n",date.anne,date.mois,date.jour);
}
void Affiche(Etud TE[] , int ne ){
    for (int i = 0 ; i < ne ; i++){
        printf("%s %s :\n",TE[i].Nom,TE[i].Prenom);
        AFFICHE_DATE(TE[i].Date_Naissance);
        printf("Moyenne = %.2f et Rang = %d:\n",TE[i].Moy, RANG(TE[i],TE,ne));
        printf("\n---------------------------------------------\n");
    }
}
int main() {
    Etud etud ;
    Etud TE[20];
    int ne ;
    float TC[10];
    int NN ;
    float Moyenne_Class ;
    printf("\n----------------------------------\n");
    printf("Donner le nombre des etudiants :\n");
    scanf("%d",&ne);
    printf("\n----------------------------------\n");
    printf("Donner le nombre des notes :\n");
    scanf("%d",&NN);
    printf("\n----------------------------------\n");
    SAISIR_COIFF(TC,NN);
    printf("\n----------------------------------\n");
    Remplir(&etud,TE,ne , NN ,TC);
    Moyenne_Class = MOYENNE_CLASS(TE,ne);
    printf("\n----------------------------------\n");
    printf("Le moyenne du class est %.2f ", Moyenne_Class);
    printf("\n----------------------------------\n");
    //Trie(TE,ne);
    printf("\n----------------------------------\n");
    Affiche(TE , ne );
    printf("\n----------------------------------\n");
    return 0;
}
