#ifndef QUEUE_H
#define QUEUE_H

//NECESSARY INCLUDES
#include<stdio.h>
#include"patients.h"

//custom types
typedef struct t_node node;
typedef struct t_queue queue;

struct t_node
{
    patient value;
    node* next;
};

struct t_queue
{
    node* front;
    node* rear;
};

//function's prototypes
void create_queue(queue* q);
void enqueue(queue* q,patient p);
patient get_head(queue *q);
void dequeue(queue* q);
void display_queue(queue q);

#endif
