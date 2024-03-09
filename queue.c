#include "queue.h"
#include <stdio.h>


int queue_size (queue_t *queue) 
{    
    // Tratando o caso particular de fila vazia:
    if (!queue) return 0;

    // Fila não vazia:
    int counter = 1;

    for (queue_t *aux = queue; aux->next != queue; aux = aux->next, counter++);
    return counter;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*) ) 
{
    // Tratando hipótese de fila vazia:
    if (!queue) return ;

    // Fila não vazia:
    print_elem(queue);
    for (queue_t *aux = queue->next; aux != queue; print_elem(aux), aux = aux->next);
}

int queue_append (queue_t **queue, queue_t *elem)
{
    // Tratando eventuais erros:
    if (!queue || !elem) { 
        fprintf(stderr, "<< Erro identificado >>  Fila ou elemento inexistente.\n");
        return -1;
    } 

    if (elem->prev || elem->next) {
        fprintf(stderr, "<< Erro identificado >>  Elemento pertencente a outra fila ou já está presente na fila passada.\n");
        return -2;
    }

    // Situação de inserção em fila vazia.
    if (!*queue) {
        *queue = elem;
        elem->next = elem;
        elem->prev = elem;
    } else {
        // Inserção no final em fila não vazia.
        elem->prev = (*queue)->prev;
        elem->next = *queue;
        (*queue)->prev->next = elem;
        (*queue)->prev = elem;
    }
       
    return 0; // Operação bem-sucedida.
}

int queue_remove(queue_t** queue, queue_t* elem) {
    if (!queue || !elem) {
        fprintf(stderr, "< Erro identificado >  Fila ou elemento inexistente.\n");
        return -1;
    }

    queue_t *aux = (*queue);

    if (!(*queue)) {
        fprintf(stderr, "< Erro identificado >  Tentativa de remoção de fila vazias.\n");
        return -2;
    }

    // Buscando na fila:
    while (aux != elem) {
        aux = aux->next;

        if (aux == (*queue)) {
            fprintf(stderr, "< Erro identificado >  Elemento não está na fila passada.\n");
            return -3;
        }
    }

    // Caso de fila com um elemento: ela é esvaziada.
    if (elem->next == elem && elem->prev == elem) {
        elem->next = NULL;
        elem->prev = NULL;
        (*queue) = NULL;
        
        return 1;
    }

    // Caso particular de fila com pelo menos dois elementos.
    if ((*queue) == elem)     // O elemento buscado é o primeiro da fila, se isso for verdade.
        (*queue) = elem->next;

    elem->next->prev = elem->prev;
    elem->prev->next = elem->next;
    elem->next = NULL;
    elem->prev = NULL;

    return 1; // Operação bem-sucedida.
}