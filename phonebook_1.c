#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

    bool i = true;
    while(i){
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
                i = false;
                break;
            default:
                printf("Invalid selection. ");
        }
    }
}

/**
 * Search and return a node
 * @return
*/
node* search(node *ptr){
    char src[L];
    node *tmp = NULL;
    tmp = ptr;
    getContact("Search for: ", src);
    while (tmp != NULL){
        if (strcmp(src, tmp->name) == 0 || strcmp(src, tmp->number) == 0){
            return tmp;
        }
        else if (tmp->sx != NULL){
            tmp = tmp->sx;
        }
        else {
            return NULL;
        }
    }

}

/**
 * Call search and print the node
 * @return
*/
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

/**
 * Print all node
 * @return
*/
void printContacts(node *ptr){
    node *tmp = NULL;
    tmp = ptr;
    while (tmp != NULL){
        printf("Contact info:\nName: %s\nPhone number: %s\n", tmp->name, tmp->number);
        printf("\n");
        tmp = tmp->sx;
    }
}

/**
 * Allocate a new node
 * @return
*/
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
    /**
     * Add the node to the sorted list
    */
    node *trg = target(tmp, ptr);
    if (trg == NULL){
        return ptr;
    }
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

/**
 * Get a contact from user input, print the prompt char *q
 * @return
*/
void getContact(char *q, char *a){
    printf("%s", q);
    fgets(a, L, stdin);
    a [strcspn(a, "\n")] = '\0';
    for (int i = 0; a[i] != '\0'; i++){
        a[i] = toupper((unsigned char)a[i]);
    }
}

/**
 * Call search and delete the contact if found
 * Some problem with the delete function
 * todo remove the empty node from the list
 * @return
*/
void deleteContact(node *ptr){
    node *trg = NULL;
    trg = search(ptr);
    if (trg != NULL){
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
    else{
        printf("Contact not found\n");
    }
}
/**
 * Compare node by name and return the bigger node or the tail
 * @return
*/
node* target(node *tmp, node *ptr){
    if (strcmp(tmp->name, ptr->name) < 0 || ptr->sx == NULL){
        return ptr;
    }
    else if (strcmp(tmp->name, ptr->name) == 0){
        printf("Contact already exist\n");
        free(tmp);
        return NULL;
    }
    else{
        ptr = ptr->sx;
        ptr = target(tmp, ptr);
    }
}

/**
 * take the iteger from the user input and return it. 
*/
int getInstruction(){
    int op;
    printf("Please, select one of the following option:\n1 to print a contact\n2 to add a new contact\n3 to delete a contact,\n4 to print all the contact\n5 to close the phone book\n");
    scanf("%i", &op);
    getchar();
    return op;
}
