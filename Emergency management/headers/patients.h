#ifndef PATIENTS_H
#define PATIENTS_H
  // necessary includes
#include <stdio.h>
#include <string.h>
#include<stdbool.h>
// custom types

typedef enum t_statut t_statut;
enum t_statut
{
    on_hold,
    in_consultation,
    under_observation,
    referred,
    discharged
};

typedef struct t_patient patient;
struct t_patient
{
    int id;
    char surname[20];
    char first_name[20];
    int age;
    int ticket;
    t_statut statut;
};

// function's prototypes

// the receptionist uses this function to record the arriving patient
patient create_patient(char surname[20], char first_name[20], int age);

// the docter uses this function to change  patient's statut 
t_statut update_statut(char statut[20]);

/*the docter uses it to see the patient_information*/
void display_patient(patient p);

/*we use it to avoid that id and ticket restart from zero each time we execute the program 
it allows the program to get the last ticket and id given*/
void ticket_function(int val1);

//to avoid writing digits and symboles in the surname or first name case
bool correct_name(char s[20]);

void save_id(char *filename);

void load_id(char *filename);
/*pour verifier l'age le truc c'est que on a scanf(%d) donc si j'ecris abc directement ca bloque
  donc on doit convertir en string faire le traitement puis reconvertir en int c'est long on verra */
#endif