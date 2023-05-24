#include "header.h"

TCoada* InitQ ()
{ 
  TCoada* c;
  c = (TCoada*)malloc(sizeof(TCoada));
  if ( ! c ) return NULL;                  

  c->inc = c->sf = NULL;
  return c;
}

void DistrQ(TCoada **c)
{
  TLista p, aux;
  p = (*c)->inc;
  while(p)
  {
    aux = p;
    p = p->urm;
    free(aux);
  }
  free(*c);
  *c = NULL;
}

void IntrQ(TCoada *c, int linie, int coloana) { 
    TLista aux;
    aux = (TLista)malloc(sizeof(TCelula));

    if(!aux)
    return;
    
    aux->linie = linie;
    aux->coloana = coloana;

    aux->urm = NULL;
    if (c->sf != NULL) {
        aux->urm = c->inc;
        c->inc = aux;
    }
    else
    c->inc = aux;
    c->sf = aux;
}

void ExtrQ(TCoada *c, int *linie, int *coloana) { 
  if( !c)
  return;
  TLista aux = c->inc;
  *linie = c->inc->linie;
  *coloana = c->inc->coloana;
  c->inc = c->inc->urm;
  if(!c->inc) {
    c->sf = NULL;
  }
  free(aux);                    
}