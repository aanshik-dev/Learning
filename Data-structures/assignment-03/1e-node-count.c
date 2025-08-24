// Write a function in C that prints every second node in a linked list
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} node, *nptr;

void nodeCount(nptr head, int *count) {
  if (head == NULL) {
    return;
  }
  *count += 1;
  nodeCount(head->next, count);
}

int main() {
  nptr head, second, third, fourth, fifth, sixth;
  head = (nptr)malloc(sizeof(node));
  second = (nptr)malloc(sizeof(node));
  third = (nptr)malloc(sizeof(node));
  fourth = (nptr)malloc(sizeof(node));
  fifth = (nptr)malloc(sizeof(node));
  sixth = (nptr)malloc(sizeof(node));

  head->data = 1;
  second->data = 2;
  third->data = 3;
  fourth->data = 4;
  fifth->data = 5;
  sixth->data = 6;

  head->next = second;
  second->next = third;
  third->next = fourth;
  fourth->next = fifth;
  fifth->next = sixth;
  sixth->next = NULL;

  int count = 0;
  nodeCount(head, &count);
  printf("\nNumber of nodes in the linked list: %d\n\n", count);

  return 0;
}