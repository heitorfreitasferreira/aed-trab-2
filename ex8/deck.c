#include <stdlib.h>
#include "deck.h"

struct deque
{
  no *beg;
  no *end;
};
typedef struct
{
  float info;
  struct no *prox;
} no;
Deque cria_deque()
{
  Deque queue;
  queue = (Deque)malloc(sizeof(struct deque));
  if (queue)
  {
    queue->end = NULL;
    queue->beg = NULL;
  }
  return queue;
}
int Deque_vazia(Deque queue) { return (!(queue->beg)); }

int push(Deque queue, float elem)
{
  no *q;
  q = (struct no *)malloc(sizeof(no));
  if (!q)
    return 0;
  q->info = elem;
  q->prox = NULL;
  if (Deque_vazia(queue))
    queue->beg = q;
  else
    queue->end->prox = q;
  queue->end = q;
  return 1;
}
int unshift(Deque queue, float elem)
{
  //FALTA
}
int shift(Deque queue, float *elem)
{
  if (Deque_vazia(queue))
    return 0;
  no *aux = queue->beg;
  *elem = aux->info;
  if (queue->beg == queue->end)
    queue->end = NULL;
  queue->beg = aux->prox;
  free(aux);
  return 1;
}
int pop(Deque queue, float *elem)
{
  //FALTA
}
int esvazia_Deque(Deque queue)
{
  no *aux = queue->beg;
  no *aux2;
  while (aux != NULL && aux->prox != NULL)
  {
    aux2 = aux->prox;
    free(aux);
    aux = aux2;
  }
  queue->beg = NULL;
  queue->end = NULL;
  return 1;
}
