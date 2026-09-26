#ifndef OBSERVATION_H
#define OBSERVATION_H
#include "patients.h"
#include "queue.h"
#include <stdbool.h>
// CONSTANTS

#define MAX_SURNAME    50    
#define MAX_FIRSTNAME  50    
#define MAX_TREATMENT  100   
#define MAX_DATE       20   

 typedef enum t_departement t_departement;
 enum t_departement
 {
    Cardiologie,
    Radiologie,
    Chirurgie,
    autres
 };
 typedef struct t_PatientObs PatientObs;
 struct t_PatientObs
 {
    patient p;
    char treatement[MAX_TREATMENT];
    int bed_number;
    t_departement departement;
 };

 //structure pour gerer la liste par le controleur
 // linked list of patients under observation

typedef struct t_node_obs     t_node_obs;
typedef t_node_obs*           obs_list;    

struct t_node_obs 
{
      PatientObs obs;
      obs_list   next;     
};
 // declarations of all functions 

void initialization_observation_list(obs_list *list);
void admit_patient(obs_list *list,patient p, int bed_number, char treatment[100]);
void discharge_patient(obs_list *list, int p_ticket);
void display_observation(obs_list list);
void refer_patient(obs_list *list, patient p_consultation, int p_ticket, t_departement new_departement);
char* departement_to_string(t_departement d);
void free_observation_list(obs_list *list);
bool is_bed_occupied(int bed_number,obs_list list);

#endif