// necessary includes
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "patients.h"
#include <string.h>
// function definitions

static bool is_empty(queue q);
/*la 1ere qs qui vous viendra en tete pourquoi j'ai fais
 la signature de full et empty dans le .c pas le .h . alors dans le concept de l'ADT
 la specification (le .h dans ce cas) doit detrminer quoi faire c_a_d enfiler,afficher..
 et pas comment faire on doit laisser le choix a l'implementeur de definir ses fonctions
 de la maniere dont il veut,si dans sa definition(implementation) il a besoin de is_empty il
 la declara lui meme */
static bool is_empty(queue q)
{
    return (q.front == NULL);
}

void create_queue(queue *q)
{
    q->front = NULL;
    q->rear = NULL;
}

void display_queue(queue q)
{
    node *tmp;
    if (is_empty(q))
    {
        printf("aucun patient en attente\n");
    }
    else
    {
        tmp = q.front;
        while (tmp != NULL)
        {
            display_patient(tmp->value);
            tmp = tmp->next;
        }
    }
}

void enqueue(queue *q, patient p)
{
    node *tmp;
    // preparer le node
    tmp = malloc(sizeof(node));
    tmp->value = p;
    tmp->next = NULL;
    if (is_empty(*q))
    {
        q->front = tmp;
    }
    else
    {
        q->rear->next = tmp;
    }
    // in both cases the node tmp is the last one
    q->rear = tmp;
}
/*patient dequeue(queue *q) si on fait ca dequeue va changer l'etat de
   l'adt et retourner quelque chose bad pratique
so on devisera le travaille sur head et dequeue to get a clean code :) */

void dequeue(queue *q)
{
    node *tmp;

    if (is_empty(*q))
    {
        printf("your queue is empty");
    }
    else
    {
        // garder l/adresse du node pour le liberer
        tmp = q->front;
        // supprimer le node de la file
        q->front = q->front->next;
        free(tmp);
        tmp = NULL;
        // DANS LE CAS OU queue contenait un seul element elle deviendra vide
    }
    if (q->front == NULL)
    {
        q->rear = NULL;
    }
}
patient get_head(queue *q)
{
    patient vide;
    vide.id = -1;
    vide.ticket = -1;
    vide.age = 0;
    strcpy(vide.surname, "");
    strcpy(vide.first_name, "");
    vide.statut = on_hold;

    if (is_empty(*q))
    {
        printf("your queue is empty");
        return vide;
    }
    return q->front->value;
}


