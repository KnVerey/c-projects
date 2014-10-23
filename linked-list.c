#include <stdlib.h>
#include <stdio.h>

struct node {
  int data;
  struct node* next;
};

void PushNode(struct node** headRef, int data) {
  struct node* newNode = malloc(sizeof(struct node));

  newNode->data = data;
  newNode->next = *headRef;
  *headRef = newNode;
}

int main()
{
  struct node* head = NULL;
  PushNode(&head, 1);
  PushNode(&head, 2);
  printf("%d\n", head->data);
  return 0;
}
