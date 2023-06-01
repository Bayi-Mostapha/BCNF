#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure pour les depandances fonctionelles
typedef struct FD
{
    char side;
    char *c;
    struct FD *next;
} element;

//structure pour les relations et la fermeture
typedef struct att
{
    char *c;
    struct att *next;

} attribut;
typedef struct KEYS
{
    attribut **keys;
    int n;
} KEYS;
//*************************************************************
element* delete_problem(element *head);
element* delete_value_function(element *head,char *tab );
element** delete_transitivity(element **head, int ndf);
element* delete_value_function(element *head,char *tab );
element* add_debut_function(element *head,char *tab,int a);
attribut* add_end(attribut *head,char *tab);
attribut* copy_relation(attribut *head1,attribut *head2);
void find_keys( attribut *R,element **head,int number);
attribut* delete_last (attribut *head);
attribut* delete_first (attribut *head);
attribut* destroy(attribut *head);
int key(attribut *P,attribut *K);
void closure_1(element **head,attribut *P,int number);
void closure(element *head,attribut *P);
attribut* add_attribut_to_closure(attribut *head,char *t);
attribut* choose_attributs_of_closure(attribut *head,attribut *L);
void affiche_FD(element *head);
element* add_to_list_function(element *head,char *tab,int a);
element* add_new_FD(attribut *L,element *head);
element** add_functional_depandencies(attribut *L,element **head, int *nFD);
int recherche_in_function(element *P,char *t);
void affiche_relation(attribut *head,char type);
attribut* add_to_list_relation(attribut *head,char *tab);
attribut* add_relation(attribut *head);
int recherche(attribut *P,char *t);
//**************************************************
//rechercher un attribut dans une realtion
int recherche(attribut *P,char *t)
{
    attribut *tmp;
    tmp=P;
    while(tmp!=NULL)
    {
        if(strcmp(tmp->c,t)==0)  return 1;
        tmp=tmp->next;
    }
    return 0;
}
//*************************************************************
//fonction pour ajouter des attributs dans la relation
attribut* add_relation(attribut *head)
{

    char tab[100],tab2[100];
    int i=0,j;
    printf("\n\t\t\tENTRER LA RELATION SOUS FORME (sid,sname,...) : ");
    scanf("%s",tab);
    while(tab[i]!='\0')
    {
        j=0;
        while(tab[i]!=',' && tab[i]!='\0')
        {
            tab2[j]=tab[i];
            i++;
            j++;
        }
        tab2[j]='\0';
        if(recherche(head,tab2)==0)
            head=add_to_list_relation(head,tab2);
        strcpy(tab2,"");
        if(tab[i]=='\0')
            break;
        i++;
    }
    return head;
}
///**********************************************************
//fonction pour stocker les attributs dans une liste
attribut* add_to_list_relation(attribut *head,char *tab)
{
    attribut *newone,*tmp;
    newone=(attribut*)malloc(sizeof( attribut));
    newone->c=(char*)malloc(sizeof(char)*strlen(tab));
    fflush(stdin);
    strcpy(newone->c,tab);
    fflush(stdin);
    if(head==NULL)
    {
        newone->next=NULL;//si la liste est vide
        head=newone;
        return head;
    }
    tmp=head;
    while(tmp->next!=NULL)
    {
        tmp=tmp->next;
    }
    tmp->next=newone;
    newone->next=NULL;
    return head;
}
//////////////////////////////////////////////////////////////////////
//fonction pour afficher les relation
void affiche_relation(attribut *head,char type)
{
    //type c'est seulement pour afficher soit R( ou C(
    attribut *tmp;
    printf("\n\n");
    if(head==NULL)
    {
        printf("\n\t\t\tVOTRE RELATION EST VIDE!!\n");
        return ;
    }
    if(type=='r')
        printf("\t\t\tR(");
    else if(type=='c')
        printf("\t\t\tC(");
    else
        printf("(");
    tmp=head;
    while(tmp->next!=NULL)
    {
        printf("%s,",tmp->c);
        tmp=tmp->next;
    }
    printf("%s)\n\n\n",tmp->c);
}
//******************************************************************
//recherche un attribut dans une DF
int recherche_in_function(element *P,char *t)
{
    element *tmp;
    tmp=P;
    while(tmp!=NULL)
    {
        if(strcmp(tmp->c,t)==0)
            return 1;
        tmp=tmp->next;
    }
    return 0;
}
//////////////////////////////////////////////////////
int recherche_in_function_left(element *P,char *t)
{
    element *tmp;
    tmp=P;
    while(tmp->side!= 'R')
    {
        if(strcmp(tmp->c,t)==0)
            return 1;
        tmp=tmp->next;
    }
    return 0;
}
//////////////////////////////////////////////////////////////////////
//******************************************************************
element** add_functional_depandencies(attribut *L,element **head, int *nFD)
{
    int nbr ;
    printf("\n\t\t\tENTRER LE NOMBRE DE DEPENDANCES FONCTIONNELLES: ");
    scanf("%d",&nbr);
    head=(element**)malloc(sizeof(element*)*nbr);
    for (int i=0; i<nbr; i++)
        head[i]=(element*)malloc(sizeof(element));

    for (int i=0; i<nbr; i++)
    {
        head[i]=NULL;
        head[i]=add_new_FD(L,head[i]);
    }
    for(int i=0; i<nbr; i++)
        affiche_FD(head[i]);
    *nFD=nbr;
    return head;
}
element* add_new_FD(attribut *L,element *head)
{
    char tmp[100];
    char att[100];
    printf("\n\t\t\tENTRER DEPENDANCE FONCTIONNELLE (a,..->b,..): ");
    fflush(stdin);
    scanf("%s",tmp);
    int i,k,j=0;
    for(i=0; i<strlen(tmp); i++)
    {
        if(tmp[i]=='-')
        {
            att[j]='\0';
            j=0;
            head=add_to_list_function(head,att,1);
            break;
        }
        if(tmp[i]==',')
        {
            att[j]='\0';
            j=0;
            head=add_to_list_function(head,att,1);
            continue;
        }
        att[j]=tmp[i];
        j++;
    }
    i+=2;
    for(k=i; k<strlen(tmp); k++)
    {
        if(tmp[k]==',')
        {
            att[j]='\0';
            j=0;
            head=add_to_list_function(head,att,2);
            continue;
        }
        att[j]=tmp[k];
        j++;
    }
    att[j]='\0';
    head=add_to_list_function(head,att,2);
    return head;
}

element* add_to_list_function(element *head,char *tab,int a)
{
    element *newone,*tmp;
    newone=(element*)malloc(sizeof(element));
    newone->c=(char*)malloc(sizeof(char)*strlen(tab));
    strcpy(newone->c,tab);
    if(a==1)
        newone->side='L';
    else
        newone->side='R';
    fflush(stdin);
    //si la liste est vide
    if(head==NULL)
    {
        newone->next=NULL;
        head=newone;
        return head;
    }
    //ajouter l'element au dernier
    tmp=head;
    while(tmp->next!=NULL)
    {
        tmp=tmp->next;
    }
    tmp->next=newone;
    newone->next=NULL;
    return head;
}
//**************************************************************
void affiche_FD(element *head)//fonction pour afficher les dependances fonctionelle
{
    element *tmp;
    int d=1;
    printf("\n\n");
    tmp=head;
    if(head==NULL)
    {
        printf("\n\t\t\tVOTRE LISTE DE DEPENDANCES FONCIONNELLES EST VIDE");
        return ;
    }
    printf("\t\t\t--------------------\n\t\t\t");
    while(tmp!=NULL)
    {
        if(tmp->side=='R'&&d==1)
        {
            printf("--> ");
            printf("%s ",tmp->c);
            d++;
        }
        else printf("%s ",tmp->c);

        tmp=tmp->next;
    }
}
//*******************************************************
attribut* choose_attributs_of_closure(attribut *head,attribut *L)//fonction pour ajouter des attributs dans closure(avant calculer)
{
    int i=0,j;
    char tab[100],tab2[100];
    printf("\n\t\t\tENTRER LES ATTRIBUTS (sid,sname..) : ");
    scanf("%s",tab);
    while(tab[i]!='\0')
    {
        j=0;
        while(tab[i]!=',' && tab[i]!='\0')
        {
            tab2[j]=tab[i];
            i++;
            j++;
        }
        tab2[j]='\0';
        if(recherche(head,tab2) ==1 && recherche(L,tab2)==0)
            L=add_to_list_relation(L,tab2);
        strcpy(tab2,"");
        if(tab[i]=='\0')
            break;
        i++;
    }
    return L;
}
//************************************************************************************************************
//************************************************************************************************************
void closure(element *head,attribut *P)
{
    //head est une liste chainee des depandances fonctionnels
    //P est la fermeture
    element *tmp;
    attribut *ptmp;
    int d=0,f=0;
    tmp=head;
    while(tmp->side!='R')//calculer la partie gauche d'une DF (combien d'attribut)
    {
        f++;
        tmp=tmp->next;
    }
    ptmp=P;
    while(ptmp!=NULL)
    {

        tmp=head;
        while(tmp->side!='R')
        {
            if(strcmp(tmp->c,ptmp->c)==0)
            {
                d++;
            }
            tmp=tmp->next;
        }
        ptmp=ptmp->next;
    }
    if(f==d)   //tester si le nombre d'element trouver egale a le nombre des attributs de la partie gauche
    {
        tmp=head;
        while(tmp->side!='R')
        {
            tmp=tmp->next;
        }
        while(tmp!=NULL)
        {
            if(recherche(P,tmp->c)==0)
            {
                P=add_to_list_relation(P,tmp->c);
            }
            tmp=tmp->next;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////
void closure_1(element **head,attribut *P,int number)
{
    for(int j=0; j<number; j++)
        for(int i=0; i<number; i++)
            closure(head[i],P);
}
//*********************************************************
//************************************************************************************************************
attribut* add_end(attribut *head,char *tab)
{
    attribut *newone,*tmp;
    newone=(attribut*)malloc(sizeof( attribut));
    newone->c=(char*)malloc(sizeof(char)*strlen(tab));
    fflush(stdin);
    strcpy(newone->c,tab);
    fflush(stdin);
    if(head==NULL)
    {
        newone->next=NULL;//si la liste est vide
        head=newone;
        return head;
    }
    tmp=head;
    while(tmp->next!=NULL)
    {
        tmp=tmp->next;
    }
    tmp->next=newone;
    newone->next=NULL;
    return head;
}
//////////////////////////////////////////////////////////
attribut* copy_relation(attribut *head1,attribut *head2)
{
    attribut *tmp;
    tmp=head1;
    while(tmp!=NULL)
    {
        head2=add_end(head2,tmp->c);
        tmp=tmp->next;
    }
    return head2;
}
/////////////////////////////////////////////////////////////////////////////////
//************************************************************************************************************
attribut* delete_last (attribut *head)
{
    attribut *tmp;
    tmp=head;
    while(tmp->next->next!=NULL)tmp=tmp->next;
    tmp->next=NULL;

    return head;
}
//*******************************************************************************
attribut* delete_first (attribut *head)
{
    attribut *tmp;
    tmp=head;
    head=head->next;
    free(tmp);
    return head;
}
//********************************************************************************

element* delete_value_function(element *head,char *tab )
{
    element *tmp,*ptmp;
    tmp=head;
    if(head==NULL)
        return head;
    if(strcmp(head->c, tab) == 0)
    {
        head=head->next;
        free(tmp);
        return head;
    }
    tmp=head;
    ptmp=tmp->next;
    while(ptmp!=NULL)
    {
        if(strcmp(ptmp->c, tab) == 0)
        {
            tmp->next=ptmp->next;
            free(ptmp);
            return head;
        }
        tmp=ptmp;
        ptmp=ptmp->next;
    }
    return head;
}
//**********************************************************
element* add_debut_function(element *head,char *tab,int a)
{
    element *newone;
    newone=(element*)malloc(sizeof(element));
    newone->c=(char*)malloc(sizeof(char)*strlen(tab));
    strcpy(newone->c,tab);
    if(a==1)
        newone->side='L';
    else
        newone->side='R';
    fflush(stdin);
    //si la liste est vide
    if(head==NULL)
    {
        newone->next=NULL;
        head=newone;
        return head;
    }
    newone->next=head;
    head=newone;
    return head;
}
//////////////////////////////////////////////////////////////////////////////
attribut* delete_value(attribut *head,char *tab )
{
    attribut *tmp,*ptmp;
    tmp=head;
    if(head==NULL)
        return head;
    if(strcmp(head->c, tab) == 0)
    {
        head=head->next;
        free(tmp);
        return head;
    }
    tmp=head;
    ptmp=tmp->next;
    while(ptmp!=NULL)
    {
        if(strcmp(ptmp->c, tab) == 0)
        {
            tmp->next=ptmp->next;
            free(ptmp);
            return head;
        }
        tmp=ptmp;
        ptmp=ptmp->next;
    }
    return head;
}
//***********************************************************
int number_of_atts(attribut *head)
{
    attribut *tmp=head;
    int n=0;
    while(tmp)
    {
        n++;
        tmp=tmp->next;
    }
    return n;
}
//******************************************************************************
attribut *createCopy(attribut *head)
{
    attribut *head2=NULL;
    attribut *tmp=head;
    while(tmp)
    {
        head2=add_to_list_relation(head2,tmp->c);
        tmp=tmp->next;
    }
    return head2;
}
attribut* chuffle(attribut *head, int beg)
{
    attribut *tmp=head;
    char temp[100];
    int i=0;
    while(i!=beg&&tmp)
    {
        tmp=tmp->next;
        i++;
    }
    while(1)
    {
        if(tmp==NULL||tmp->next==NULL)
            break;
        strcpy(temp,tmp->c);
        strcpy(tmp->c,tmp->next->c);
        strcpy(tmp->next->c,temp);
        tmp=tmp->next->next;
    }
    return head;
}
int compare(attribut *head1,attribut *head2)
{
    attribut *tmp1=head1,*tmp2=head2;
    while(tmp1)
    {
        //printf("test compare\n");
        if(strcmp(tmp1->c,tmp2->c)!=0)
        {
            return 0;
        }
        tmp1=tmp1->next;
        tmp2=tmp2->next;
    }
    return 1;
}
int isvalid(attribut *tmp, int i)
{
    int j=0;
    while(j<i)
    {
        if(tmp==NULL)
            break;
        j++;
        tmp=tmp->next;
    }
    if(j<i)
        return 0;
    return 1;
}
int compareKeys(attribut *key1,attribut *key2)
{
    int n1=number_of_atts(key1);
    int n2=number_of_atts(key2);
    if(n1!=n2)
    {
        return 0;
    }
    attribut *tmp1=key1;
    attribut *tmp2=key2;
    int occ=0;
    while(tmp1)
    {
        tmp2=key2;
        while(tmp2)
        {
            if(strcmp(tmp1->c,tmp2->c)==0)
            {
                occ++;
            }
            tmp2=tmp2->next;
        }
        tmp1=tmp1->next;
    }
    if(n1==occ)
        return 1;
    return 0;
}
KEYS cleanKeys(KEYS keys)
{
    int i,j,k;
    for(i=0; i<keys.n; i++)
    {
        for(j=i+1; j<keys.n-1; j++)
        {
            if(compareKeys(keys.keys[i],keys.keys[j]))
            {
                for(k=j; k<keys.n-1; k++)
                {
                    keys.keys[k]=keys.keys[k+1];
                }
                keys.keys=(attribut**)realloc(keys.keys,sizeof(attribut*)*--keys.n);
                j=i+1;
            }
        }
    }
    return keys;
}
KEYS findKeys(attribut *R,int nfd,element **functions)
{
    int n=number_of_atts(R);
    int j,chunkSize=1,beg=0;
    attribut *key=NULL;
    attribut *C=NULL;
    attribut *tmp1=R;
    attribut *tmp2=R;
    attribut *chufled=createCopy(R);
    int flag=1;

    attribut **keys=(attribut**)malloc(sizeof(attribut*));
    int ind=0;
    //*************************************************************
    while(!compare(R,chufled)||flag)
    {
        flag=0;
        while(chunkSize<=n)
        {
            while(isvalid(tmp1,chunkSize))
            {
                for(j=0; j<chunkSize; j++)
                {
                    key=add_to_list_relation(key,tmp2->c);
                    tmp2=tmp2->next;
                }
                C=createCopy(key);
                closure_1(functions,C,nfd);
                if(number_of_atts(C) == number_of_atts(R))
                {
                    keys[ind]=key;
                    ind++;
                    keys=(attribut**)realloc(keys,sizeof(attribut*)*(ind+1));
                }
                key=NULL;
                C=NULL;
                tmp1=tmp1->next;
                tmp2=tmp1;
            }
            tmp1=chufled;
            tmp2=chufled;
            chunkSize++;
        }
        chufled=chuffle(chufled,beg);
        tmp1=chufled;
        tmp2=chufled;
        beg++;
        chunkSize=1;
        if(beg>n-1)
            beg=0;
    }
    //*************************************************************
    KEYS K;
    K.keys=keys;
    K.n=ind;//(ind+1);
    return K;
}
void affiche_keys(KEYS keys)//fonction pour afficher les dependances fonctionelle
{
    attribut *tmp;
    int i;
    printf("\n");
    for(i=0; i<keys.n; i++)
    {
        tmp=keys.keys[i];
        printf("\n\t\t\t(");
        while(tmp->next!=NULL)
        {
            printf("%s,",tmp->c);
            tmp=tmp->next;
        }
        printf("%s)\n",tmp->c);
    }
}
int keyExists(KEYS keys,attribut *key)
{
    int i;
    for(i=0; i<keys.n; i++)
    {
        if(compareKeys(keys.keys[i],key))
            return 1;
    }
    return 0;
}
KEYS findMinimalKeys(KEYS keys)
{
    KEYS minimalKeys;
    minimalKeys.n=0;
    minimalKeys.keys=(attribut**)malloc(sizeof(attribut*));
    int size=1;
    int flag=0;
    int i,j;
    for(i=0; i<keys.n; i++)
    {
        for(j=0; j<keys.n; j++)
        {
            if(number_of_atts(keys.keys[j])==size && !keyExists(minimalKeys,keys.keys[j]))
            {
                minimalKeys.keys[minimalKeys.n]=keys.keys[j];
                minimalKeys.n++;
                minimalKeys.keys=(attribut**)realloc(minimalKeys.keys,sizeof(attribut*)*(minimalKeys.n+1));
                flag=1;
            }
        }
        if(!flag)
        {
            size++;
        }
    }
    return minimalKeys;
}


//************************************************************************************************************
//************************************************************************************************************
attribut* destroy(attribut *head)
{
    //deallouer la liste et la vider
    //si liste contient un ou aucun element
    if(head==NULL)
    {
        return head;
    }
    attribut *tmp1=head;
    if(tmp1->next==NULL)
    {
        head=NULL;
        free(tmp1);
        return head;
    }
    attribut *tmp2=tmp1->next;
    while(tmp2)
    {
        free(tmp1);
        tmp1=tmp2;
        tmp2=tmp2->next;
    }
    free(tmp1);
    head=NULL;
    return head;
}
//************************************************************************************************************
int key(attribut *P,attribut *K)
{
    attribut *tmp;
    int size1=0,size2=0;
    tmp=P;
    while(tmp!=NULL)
    {
        size1++;
        tmp=tmp->next;
    }
    tmp=K;
    while(tmp!=NULL)
    {
        size2++;
        tmp=tmp->next;
    }
    if(size1==size2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
///////////////////////////////////////////////////////////////////////////////
void boyce_codd(element **head,attribut *R,int nFD)
{
    //head is  the FDs
    element *tmp;
    attribut *keyy=NULL;
    attribut **relations,*stmp,*new_relation=NULL;
    int d=0,f=0,k=0,c=0;
    int i =0,j;
    int nkey;
    //creer tableau pour stocker les nouveaux relations (liste chainee)
    relations=(attribut**)malloc(sizeof(attribut*)*(nFD+1));
    for(int i=0; i<nFD+1; i++)
        relations[i]=(attribut*)malloc(sizeof(attribut));

    //creer une copie de la relation
    new_relation=copy_relation(R,new_relation);
    //change it with a function mostafa !!
    printf("\n\t\t\tENTRER LE NOMBRE DE CLES: ");
    scanf("%d",&nkey);

    j=0;
    while(j!=nkey)
    {
        keyy=choose_attributs_of_closure(R,keyy);
        c=0;
        while(c!=nFD)
        {

            d=0;
            f=0;
            k=0;
            //calculer la partie gauche d'une DF (combien d'attribut)
            tmp=head[c];
            while(tmp->side!='R')
            {
                f++;
                tmp=tmp->next;
            }

            //calculer combien d'attribut commun entre la partie gauche et le cle
            stmp=keyy;
            while(stmp!=NULL)
            {
                tmp=head[c];
                k++;
                while(tmp->side!= 'R')
                {
                    if(strcmp(tmp->c,stmp->c)==0)
                    {
                        d++;
                    }
                    tmp=tmp->next;
                }
                stmp=stmp->next;
            }
            if(f==d && f==k)
            {
                for(i=c ; i<nFD ; i++)
                {
                    head[i] = head[i+1];
                }
                head[nFD]= NULL;
                nFD--;
                c--;
            }
            c++;
        }
        keyy=destroy(keyy);
        j++;
    }

    //if all the functions respect BCNF
    if(head[0] == NULL )
    {
        printf("\n\t\t\tIL N'Y A PAS DES DEPENDANCES FONCTIONNELLES QUI EN VIOLATION DE FNBC!!\n");
        return ;
    }
    //delete transitivity

    head=delete_transitivity(head,nFD);

    c=0 ;
    while(c!=nFD)
    {
        relations[c]=NULL;
        tmp=head[c];
        while(tmp!=NULL)//ajouter les attributs a la relation
        {
            relations[c]=add_to_list_relation(relations[c],tmp->c);
            tmp=tmp->next;
        }
        tmp=head[c];
        while(tmp->side!='R')//parcourir jusqu'a la partie droite de la liste
        {
            tmp=tmp->next;
        }
        while(tmp!=NULL)//supprimer la parite gauche
        {
            new_relation=delete_value(new_relation,tmp->c);
            tmp=tmp->next;
        }
        c++;
    }

    stmp=new_relation;
    relations[c]=NULL;
    while(stmp!=NULL)//ajouter les attributs a la relation
    {
        relations[c]=add_to_list_relation(relations[c],stmp->c);
        stmp=stmp->next;
    }
    c++;

    printf("\n\t\t\tDECOMPOSITION EN FNBC:\n ");
    for( i=0; i<c; i++)
        affiche_relation(relations[i],'r');
}
//******************************************************************************
element** delete_transitivity(element **head, int ndf)
{
    element *tmp,*ptmp,*stmp;
    for(int i=0 ; i<ndf ; i++)
    {
        if(head[i]==NULL) continue;
        for(int j=0 ; j<ndf ; j++)
        {
            if(j == i || head[j]==NULL) continue ;
            tmp=head[i];
            ptmp = head[j];
            //parcourer jusqu'a la partie droit
            while(tmp->side!='R')
            {
                tmp=tmp->next;
            }
            //debut de traitement
            while(tmp!=NULL)
            {
                ptmp = head[j];

                while(ptmp->side != 'R')
                {

                    if(strcmp(ptmp->c,tmp->c)==0)
                    {
                        stmp = head[i];
                        while(stmp->side!='R')
                        {
                            if(recherche_in_function_left(head[j],stmp->c)==0  )
                            {
                                head[j]= add_debut_function(head[j],stmp->c,1);
                            }
                            stmp=stmp->next;
                        }
                        head[j]=delete_value_function(head[j],tmp->c);
                    }
                    ptmp=ptmp->next ;
                }
                tmp=tmp->next;
            }
        }
    }
    printf("\n\t\t\tLES DEPENDANCES FONCTIONNELLES EN VIOLATION DE FNBC:\n");
    for(int j=0 ; j<ndf ; j++)
        affiche_FD(head[j]);
    return head;
}
//***********************************************************************
element** copyfuncs(element **funcs1,int nbr)
{
    element **head;
    element *tmp;
    head=(element**)malloc(sizeof(element*)*nbr);
    for (int i=0; i<nbr; i++)
        head[i]=NULL;
    for (int i=0; i<nbr; i++)
    {
        tmp=funcs1[i];
        while(tmp)
        {
            if(tmp->side=='L')
                head[i]=add_to_list_function(head[i],tmp->c,1);
            else
                head[i]=add_to_list_function(head[i],tmp->c,2);
            tmp=tmp->next;
        }
    }
    return head;
}
//************************************************************************
int main()
{
    int *nFD=(int*)malloc(sizeof(int));
    attribut *head=NULL,*clo=NULL;
    element **functions=NULL;
    int choice;
    int choice2;
    int choice3;
    KEYS keys;

    head=add_relation(head);
    attribut *head2=createCopy(head);
    affiche_relation(head,'r');
    functions=add_functional_depandencies(head,functions,nFD);
    element **f=copyfuncs(functions,*nFD);
    do
    {
        do
        {
            printf("\n\t\t\t1: CALCULER UNE FERMETURE\n\t\t\t2: FNBC\n\t\t\t3: TROUVER LES CLES\n\t\t\t0: QUTTIER\n ");
            scanf("%d",&choice);
            switch(choice)
            {
            case 1:
                clo=NULL;
                clo=choose_attributs_of_closure(head,clo);
                closure_1(f,clo,*nFD);
                affiche_relation(clo,'c');
                break;
            case 2:
                boyce_codd(functions,head,*nFD);
                break;
            case 3:
                keys=findKeys(head2,*nFD,f);
                keys=cleanKeys(keys);
                KEYS MK=findMinimalKeys(keys);
                printf("\n\t\t\tMINIMAL KEYS:\n");
                affiche_keys(MK);
                break;
            case 0:
                break;
            default:
                printf("\n\t\t\tERREUR!!\t");
            }
            functions=copyfuncs(f,*nFD);
        }
        while(choice!=0);
        system("pause");
        system("cls");
        printf("\n\t\t\tEST CE QUE VOUS VOULEZ QUITTER LE PROGRAMME 1: OUI\n ");
        scanf("%d",&choice);
        if(choice==1)
        {
            system("cls");
            printf("\n\n\t\t\tBYE\t:D\n\n");
            exit(0);
        }
        choice=1;
        printf("\n\t\t\tEST CE QUE VOUS VOULEZ ENTRER UNE AUTRE RELATION 1: OUI\n ");
        scanf("%d",&choice2);
        if(choice2==1)
        {
            head=NULL;
            head=add_relation(head);
            head2=createCopy(head);
            affiche_relation(head,'r');
            functions=NULL;
            functions=add_functional_depandencies(head,functions,nFD);
            f=copyfuncs(functions,*nFD);
        }
        else
        {
            printf("\n\t\t\tEST CE QUE VOUS VOULEZ CHANGER LES DEPENDANCES FONCTIONNELLES 1: OUI\n ");
            scanf("%d",&choice3);
            if(choice3==1)
            {
                functions=NULL;
                head=createCopy(head2);
                functions=add_functional_depandencies(head2,functions,nFD);
                f=copyfuncs(functions,*nFD);
            }
            else
            {
                head=createCopy(head2);
                functions=copyfuncs(f,*nFD);
            }
        }
    }
    while(choice!=0);
    return 0;
}
