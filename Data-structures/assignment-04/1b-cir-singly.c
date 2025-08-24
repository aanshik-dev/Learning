#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} node, *nptr;

void revtrav(nptr cur, nptr head) {
  if (cur->next == head) {
    printf(" %d ", cur->data);
    return;
  }
  revtrav(cur->next, head);
  printf(" %d ", cur->data);
}
// ---------------------------------------------------
nptr insertNode(nptr head) {
  int loc;
  printf("\nPlease choose location from menu: ");
  scanf(" %d", &loc);
  nptr cur = head;
  nptr temp = (nptr)malloc(sizeof(node));

  int data;
  if (loc == 1 || loc == 3) {
    printf("Enter data: ");
    scanf(" %d", &data);
    temp->data = cur->data;
    cur->data = data;
    temp->next = cur->next;
    cur->next = temp;
    return loc == 1 ? cur : temp;

  } else if (loc == 2) {
    int post;
    printf("Enter Position: ");
    scanf(" %d", &post);
    printf("Enter data: ");
    scanf(" %d", &data);

    for (int i = 1; i < post; i++) {
      cur = cur->next;
      if (cur == head) {
        printf("This location is invalid\n");
        return head;
      }
    }
    temp->data = cur->data;
    cur->data = data;
    temp->next = cur->next;
    cur->next = temp;
  } else {
    printf("Invalid choice\n");
  }
  return head;
}
// ---------------------------------------------------
nptr delNode(nptr head) {
  int type, ref;
  printf("\nPlease choose delete type from the menu: ");
  scanf(" %d", &type);
  nptr cur = head;
  if (type == 1) {
    printf("Enter position: ");
    scanf(" %d", &ref);
    for (int i = 1; i < ref; i++) {
      cur = cur->next;
      if (cur == head) {
        printf("This location is invalid\n");
        return head;
      }
    }
    nptr temp = cur->next;
    cur->data = cur->next->data;
    cur->next = cur->next->next;
    if (temp == head) {
      free(temp);
      return cur;
    }
    free(temp);
    return head;

  } else if (type == 2) {
    printf("Enter value: ");
    scanf(" %d", &ref);
    int flag = 0;

    while (cur->next != head) {
      if (cur->data == ref) {
        flag = 1;
        nptr temp = cur->next;
        cur->data = cur->next->data;
        cur->next = cur->next->next;
        free(temp);
      } else
        cur = cur->next;
      if (cur->next == head && cur->data == ref) {
        flag = 1;
        nptr temp = cur->next;
        cur->data = cur->next->data;
        cur->next = cur->next->next;
        free(temp);
        return cur;
      }
    }
    if (flag == 0)
      printf("Data not found in the list");
  } else {
    printf("Invalid choice\n");
  }
  return head;
}
// ---------------------------------------------------
void travList(nptr head) {
  int dir;
  printf("\nPlease choose direction to traverse: ");
  scanf(" %d", &dir);
  nptr cur = head;

  if (dir == 1) {
    printf("Forward Traversed list: (");
    while (cur->next != head) {
      printf(" %d ", cur->data);
      cur = cur->next;
    }
    printf(" %d )\n", cur->data);
  } else if (dir == 2) {
    printf("Reverse Traversed list: (");
    revtrav(cur, head);
    printf(")\n");

  } else {
    printf("Invalid choice\n");
  }
}
// ---------------------------------------------------
void searchList(nptr head) {
  int data, count = 0;
  nptr cur = head;
  printf("\nPlease enter data to search: ");
  scanf(" %d", &data);
  do {
    count++;
    if (data == cur->data) {
      printf("%d found at %d position\n", data, count);
      return;
    }
    cur = cur->next;
  } while (cur != head);
  printf("Data Not found in List\n");
}
// ---------------------------------------------------
void revList(nptr cur, nptr head, nptr prev) {
  if (cur->next == head) {
    head->next = cur;
    return;
  }
  revList(cur->next, head, prev);
  if (cur == head) {
    prev->next = head;
    return;
  }
  cur->next->next = cur;
}
// ---------------------------------------------------
int main() {
  nptr head = (nptr)malloc(sizeof(node));
  head->next = head;
  head->data = 0;

  do {
    printf("\n    ***** MENU *****\n");
    printf("    1. Insert node\n    2. Delete Node\n    3. Traverse\n    4. Search\n    5. Reverse\n    6. Exit\n");

    int c;
    printf("\nPlease choose an operation from given menu: ");
    scanf(" %d", &c);

    if (c == 1) {
      // Insertion (at beginning, end, or specific position)
      printf("\n    1. Insert at beginning\n    2. Insert at Position\n    3. Insert at end\n");
      head = insertNode(head);

    } else if (c == 2) {
      // Deletion (by position or value)
      printf("\n    1. Delete by Position\n    2. Delete by Value\n");
      head = delNode(head);

    } else if (c == 3) {
      // Traversal (forward and reverse)
      printf("\n    1. Traverse Forward\n    2. Traverse Reverse\n");
      travList(head);

    } else if (c == 4) {
      // Searching for a value
      searchList(head);

    } else if (c == 5) {
      // Reversing the list
      revList(head, head, head->next);

    } else if (c == 6) {
      printf("\nTerminating...\n");
      break;

    } else {
      printf("Invalid choice\n");
    }
    printf("\nCircular list:   (o) %d ", head->data);
    nptr cur = head->next;
    while (cur != head) {
      printf("%d ", cur->data);
      cur = cur->next;
    }
    printf("%d (o)\n", head->data);
  } while (1);

  return 0;
}