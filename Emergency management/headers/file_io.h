#ifndef FILE_IO_H
#define FILE_IO_H
#include <stdio.h>
#include "queue.h"
#include "patients.h"
#include "consultation_results.h"
//sauvgarder queue dans un fichier
void sauvegarde_queue (queue* q,char *filename);
void charger_queue (queue* q,char *filename);
//sauvgarder les observations des patients dans un fichier
void sauvegarde_list(obs_list list,char *filename );
void charger_observation(obs_list *list,char *filename,queue q);

void discharged_patient_historique(patient p, char prescription[50], char *file_name);
void display_historique(char *file_name);

void remplir_stats(queue q, obs_list list, int total_discharged, int total_referred,
                    int refere_cardio, int refere_radio, int refere_chirurgie, int refere_autres,
                    char *file_name);
void display_stat(char *file_name);

#endif