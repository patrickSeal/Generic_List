#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/list_gen.h"

//------------------------ [PRIVATE METHODS] ---------------------------------------------------

int addTypeToList(Gen_List *l, char *type);
List_Element *new_List_Element(void *data, char *type, List_Element *next);

//--------------------------------------------------------------------------------------------

Gen_List *new_Gen_List(){
    Gen_List *lp = (Gen_List *) malloc(sizeof(Gen_List));
    if(lp == NULL){
        perror("malloc");
        return NULL;
    }
    lp->element_types = NULL;
    lp->head = NULL;
    lp->size = 0;
    lp->amount_of_types = 0;
    return lp;
}

int getSize(Gen_List *list){
    if(list != NULL){
        return list->size;
    }else return -1;
}

int addElement(Gen_List *list, void *ep, char *type){
    if(list->head == NULL){ // list is empty
        if(addTypeToList(list, type) == 0) return 0;
        List_Element *e = new_List_Element(ep, type, NULL);
        if(e == NULL) return 0;
        list->head = e;
        list->size += 1;
        return 1;
    }

    List_Element *iter = list->head;
    while(iter->next != NULL){
        iter = iter->next;
    }
    if(addTypeToList(list, type) == 0) return 0;
    List_Element *e = new_List_Element(ep, type, NULL);
    if(e == NULL) return 0;
    
    iter->next = e;
    list->size += 1;
    return 1;
}

int insertElement(Gen_List *list, void *ep, char *type, int index){
    if(index <= 0 || index >= list->size){ // element will be added at the end of the list
        if(addElement(list, ep, type) == 0) return 0;
        else return 1;
    }else{
        List_Element *iter = list->head;
        while(index != 0){
            iter = iter->next;
            index -= 1;
        }
        if(addTypeToList(list, type) == 0) return -1; 
        List_Element *e = new_List_Element(ep, type, iter->next);
        if(e == NULL) return -1;

        iter->next = e;
        list->size += 1;
        return 1;
    }
}

int removeElement(Gen_List *list, int index){
    if(list->head == NULL){
        printf("Can't remove any elements. -> List is empty.\n");
        return -1;
    }
    if(index >= list->size){
        printf("No element at index %d in Gen_List %p!\n", index, list);
        return -2;
    }
    if(index == 0){ // remove head
        List_Element *toRemove = list->head;
        list->head = list->head->next;
        free(toRemove);
        list->size -= 1;
        return 0;
    }
    // case index is negativ -> remove the last element in the list
    List_Element *toRemoveNext = list->head;
    int countIndex = 1;
    while(toRemoveNext->next->next != NULL){
        if(countIndex == index){ // next Element has to be removed
            List_Element *toBeRemoved = toRemoveNext->next;
            toRemoveNext->next = toBeRemoved->next;
            free(toBeRemoved);
            list->size -= 1;
            return 0;
        }else{
            toRemoveNext = toRemoveNext->next;
            countIndex++;
        }
    }
    // reached End of List -> last Element will be removed
    free(toRemoveNext->next);
    toRemoveNext->next = NULL;
    list->size -= 1;
    return 0;
}

void *getElement(Gen_List *list, int index){
    if(index < 0 || index >= list->size){
        printf("No Element at Index %d.\n", index);
        return NULL;
    }
    List_Element *iter = list->head;
    int countToZero = index;
    while(countToZero > 0){
        iter = iter->next;
        countToZero -= 1;
    }
    return iter->data;
}

char *getType(Gen_List *list, int index){
    if(index < 0 || index >= list->size){
        printf("No Element at Index %d.\n", index);
        return NULL;
    }
    List_Element *iter = list->head;
    int countToZero = index;
    while(countToZero > 0){
        iter = iter->next;
        countToZero -= 1;
    }
    return iter->type;
}

int printList(Gen_List *list){
    List_Element *iter = list->head;
    int index = 0;
    while(iter != NULL){
        printf("[idx]: %d   [type]: %s      [pointer]: %p       [next]: %p\n", index, iter->type, iter, iter->next);
        iter = iter->next;
        index += 1;
    }
    return 0;
}

//-------------------[PRIVATE]-------------------------------------------------------------------------------------

int addTypeToList(Gen_List *l, char *type){
    if(l->amount_of_types == 0){
        l->element_types = (char **) malloc(sizeof(char *));
        if(l->element_types == NULL){
            perror("malloc");
            return 0;
        }
        *(l->element_types) = type;
        l->amount_of_types += 1;
        return 1;
    }else{
        for(int i = 0; i < l->amount_of_types; i++){
            if(!strcmp(*((l->element_types)+i), type)){ // type is already in the list
                return 1;
            }
        }
        l->element_types = (char **) realloc(l->element_types, ((l->amount_of_types) + 1) * sizeof(char *));
        if(l->element_types == NULL){
            perror("realloc");
            return 0;
        }
        *((l->element_types)+l->amount_of_types) = type;
        l->amount_of_types += 1;
        return 1;
    }
}

List_Element *new_List_Element(void *data, char *type, List_Element *next){
    List_Element *e = (List_Element *) malloc(sizeof(List_Element));
    if(e == NULL){
        perror("malloc");
        return NULL;
    }
    e->data = data;
    e->type = type;
    e->next = next;
    return e;
}

// ---------------------------- Only for testing purposes -----------------------------------------------------------
int main(void){
    
    int i1, i2, i3, i4;
    i1 = 5;
    i2 = 7;
    i3 = 23;
    i4 = 212345;

    Gen_List *l = new_Gen_List();
    addElement(l, &i1, "int");
    addElement(l, &i2, "int");
    addElement(l, &i3, "int");
    insertElement(l, &i4, "int", -1);
    printList(l);
    removeElement(l, 10);
    removeElement(l, 2);
    removeElement(l, 0);
    removeElement(l, -2130);
    printList(l);
    return 0;
}