#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "utillist.h"


TList listUnion  (const TList list1, const TList list2);


int main(void) {

  int v[] = {1, 4, 5, 6, 7, 8};
  int w[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int x[] = {2, 3, 9};

  TList l1 = fromArray(v, 6);
  TList l2 = fromArray(w, 9);
  TList l3 = listUnion(l1, l2);
  assert(checkElems(l3, w, 9));
  freeList(l3);

  l3 = listUnion(l2, l1);
  assert(checkElems(l3, w, 9));
  freeList(l3);

  l3 = listUnion(l2, l2);
  assert(checkElems(l3, w, 9));
  freeList(l3);

  l3 = listUnion(l2, NULL);
  assert(checkElems(l3, w, 9));
  freeList(l3);

  l3 = listUnion(NULL, l2);
  assert(checkElems(l3, w, 9));
  freeList(l3);
  freeList(l1);
  freeList(l2);
  
  l1 = fromArray(v, 6);
  l2 = fromArray(x, 3);
  l3 = listUnion(l1, l2);
  freeList(l1);
  freeList(l2);
  assert(checkElems(l3, w, 9));
  freeList(l3);


  printf ("OK!\n");
  return 0;
}

TList listCpy(const TList list) {
    if (list == NULL) return NULL;
    TList new = malloc(sizeof(*new));
    new->elem = list->elem;
    new->tail = listCpy(list->tail);
    return new;
}

TList listUnion  (const TList list1, const TList list2) {
    if (list1 == NULL) return listCpy(list2);
    else if (list2 == NULL) return listCpy(list1);
    TList newNode = malloc(sizeof(*newNode));
    if (list1->elem < list2->elem) {
        newNode->elem = list1->elem;
        newNode->tail = listUnion(list1->tail, list2);
    } else if (list1->elem > list2->elem){
        newNode->elem = list2->elem;
        newNode->tail = listUnion(list1, list2->tail);
    } else {
        newNode->elem = list2->elem;
        newNode->tail = listUnion(list1->tail, list2->tail);
    }
    return newNode;
}

