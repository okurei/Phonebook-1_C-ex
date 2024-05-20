#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int L = 50;

typedef struct node
{
    char *name;
    char *number;
    struct node *sx;
    struct node *dx;
}
node;

node* search(node *ptr);
void printContact(node *ptr);
void printContacts(node *ptr);
node* new(node *ptr);
void getContact(char *q, char *a);
void deleteContact(node *ptr);
node* target(node *tmp, node *ptr);
int getInstruction();



int main(){
    node *head = NULL;

    while(1){
        int op = getInstruction();
        switch(op){
            case 1:
                printContact(head);
                break;
            case 2:
                head = new(head);                
                break;
            case 3:
                deleteContact(head);
                break;
            case 4:
                printContacts(head);
                break;
            case 5:
                printf("Closing.");
                //deleteAllContact(head);
                return 0;
                break;
            default:
                printf("Invalid selection. ");
        }
    }
}

node* search(node *ptr){
    char src[L];
    getContact("Search for: ", src);
    while (ptr->sx != NULL){
        if (strcmp(src, ptr->name) == 0 || strcmp(src, ptr->number) == 0){
            return ptr;
            break;
        }
        else{
            ptr = ptr->sx;
        }
    }
    ptr = NULL;
    return ptr;
}

void printContact(node *ptr){
    node *tmp = NULL;
    tmp = search(ptr);
    if (tmp != NULL){
        printf("Contact info:\nName: %s\nPhone number: %s\n", tmp->name, tmp->number);
        printf("\n");
    }
    else{
        printf("Contact not found\n");
    }
}

void printContacts(node *ptr){
    node *tmp = NULL;
    tmp = ptr;
    while (tmp != NULL){
        printf("Contact info:\nName: %s\nPhone number: %s\n", tmp->name, tmp->number);
        printf("\n");
        tmp = tmp->sx;
    }
}

node* new(node *ptr){
    node *tmp = malloc(sizeof(node));
    char a1[L];
    getContact("Cognome e Nome: ", a1);
    char a2[L];
    getContact("Numero: ", a2);

    tmp->name = malloc(L + 1);
    tmp->number = malloc(L + 1);

    strcpy(tmp->name, a1);
    strcpy(tmp->number, a2);
    tmp->sx = NULL;
    tmp->dx = NULL;
    if (ptr == NULL){
        ptr = tmp;
        return ptr;
    }
    node *trg = target(tmp, ptr);
    if (trg->dx == NULL)
    {
        if(strcmp(tmp->name, trg->name) > 0){
            if (trg->sx == NULL){
                tmp->dx = trg;
                trg->sx = tmp;
                return ptr;
            }
            else{
                tmp->dx = trg;
                tmp->sx = trg->sx;
                tmp->sx->dx = tmp;
                trg->sx = tmp;
                return ptr;
            }
        }
        else {
            tmp->sx = trg;
            trg->dx = tmp;
            ptr = tmp;
            return ptr;
        }
    }
    else {
        if (strcmp(tmp->name, trg->name) > 0){
            trg->sx = tmp;
            tmp->dx = trg;
            return ptr;
        }
        else {
            tmp->dx = trg->dx;
            tmp->sx = trg;
            trg->dx->sx = tmp;
            trg->dx = tmp;
            return ptr;
        }
    }
}

void getContact(char *q, char *a){
    printf("%s", q);
    fgets(a, L, stdin);
    a [strcspn(a, "\n")] = '\0';
    for (int i = 0; a[i] != '\0'; i++){
        a[i] = toupper((unsigned char)a[i]);
    }
}

void deleteContact(node *ptr){
    node *trg = NULL;
    trg = search(ptr);
    if(trg->sx == NULL && trg->dx == NULL){
        free(trg);
    }
    else if(trg->dx == NULL){
        trg->sx->dx = NULL;
        free(trg);
    }
    else if(trg->sx == NULL){
        trg->dx->sx = NULL;
        free(trg);
    }
    else{
        trg->sx->dx = trg->dx;
        trg->dx->sx = trg->sx;
        free(trg);
    }
    printf("Contact deleted\n");
}

node* target(node *tmp, node *ptr){
    if (strcmp(tmp->name, ptr->name) < 0 || ptr->sx == NULL){
        return ptr;
        }
    else{
        ptr = ptr->sx;
        ptr = target(tmp, ptr);
    }
}

int getInstruction(){
    int op;
    printf("Please, select one of the following option:\n1 to print a contact\n2 to add a new contact\n3 to delete a contact,\n4 to print all the contact\n5 to close the phone book\n");
    scanf("%i", &op);
    getchar();
    return op;
}