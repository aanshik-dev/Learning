// Write a function in C to traverse and print a singly linked list.
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} node, *nptr;

int main() {
  nptr head, second, third;
  head = (nptr)malloc(sizeof(node));
  second = (nptr)malloc(sizeof(node));
  third = (nptr)malloc(sizeof(node));

  head->data = 1;
  head->next = second;

  second->data = 2;
  second->next = third;

  third->data = 3;
  third->next = NULL;

  nptr temp = head;
  while (temp != NULL) {
    printf("%d ", temp->data);
    temp = temp->next;
  }

  return 0;
}