#include "consultation_results.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "patients.h"
#include "file_io.h"
static bool is_empty(obs_list list);
static bool is_empty(obs_list list)
{
    return (list == NULL);
}

void initialization_observation_list(obs_list *list)
{
    *list = NULL;
}

void admit_patient(obs_list *list, patient p,int bed_number, char treatment[100])
{
    t_node_obs *cur_list;
    PatientObs pobs;

    pobs.p = p;
    pobs.p.statut = under_observation;
    pobs.bed_number = bed_number;
    pobs.departement = autres;
    strcpy(pobs.treatement, treatment);
    if (is_empty(*list))
    {
        *list = malloc(sizeof(t_node_obs));
        (*list)->obs = pobs;
        (*list)->next = NULL;
    }
    else
    {

        cur_list = *list;
        while (cur_list->next != NULL)
        {
            cur_list = cur_list->next;
        }
        cur_list->next = malloc(sizeof(t_node_obs));
        cur_list = cur_list->next;
        cur_list->obs = pobs;
        cur_list->next = NULL;
    }
}

void display_observation(obs_list list)
{
    obs_list cur;
    if (is_empty(list))
    {
        printf("no patient is under observation");
    }
    else
    {
        cur = list;
        while (cur != NULL) // loop for all the patients
        {
            printf("informations about the  patient number:%d\n", cur->obs.p.ticket);
            printf("ID:%d\n", cur->obs.p.id);
            printf("surname:%s\n", cur->obs.p.surname);
            printf("first_name:%s\n", cur->obs.p.first_name);
            printf("age:%d\n", cur->obs.p.age);
            printf("treatement: %s\n", cur->obs.treatement);
            printf("the number of the patient bed:%d\n", cur->obs.bed_number);
            cur = cur->next; // pass to the next patient
        }
    }
}
void discharge_patient(obs_list *list, int p_ticket)
{
    t_node_obs *cur, *prev;
    if (is_empty(*list))
    {
        printf("La liste d'observation est vide.\n");
        return;
    }

    prev = NULL;
    cur = *list;
    // parcourir
    while (cur != NULL && cur->obs.p.ticket != p_ticket)
    {
        prev = cur;
        cur = cur->next;
    }
    // verifier il est sortit a cause de quoi
    if (cur == NULL)
    {
        printf("Patient avec ticket %d introuvable.\n", p_ticket);
        return;
    }
    cur->obs.p.statut = discharged;
    // supprimer le node
    if (prev == NULL)
        *list = cur->next; // cas du 1er node
    else
        prev->next = cur->next; // cas des nodes au milieux ou a la fin

    // printf("Patient %s %s (ticket %d) sorti de l'observation.\n",
    // cur->obs.p.surname, cur->obs.p.first_name, p_ticket);
    free(cur);
}
char* departement_to_string(t_departement d)
{
    switch (d)
    {
        case Cardiologie: return "Cardiologie";
        case Radiologie:  return "Radiologie";
        case Chirurgie:   return "Chirurgie";
        default:          return "Autres";
    }
}

void refer_patient(obs_list *list, patient p_consultation, int p_ticket, t_departement new_departement)
{
    t_node_obs *cur, *previous;
    FILE *f;

    // verifier si c'est le patient en consultation
    if (p_consultation.ticket == p_ticket)
    {
        f = fopen("data/historique.txt", "a");
        if (f)
        {
            fprintf(f, "Ticket N:%d: %s %s -referred vers: %s\n",
                    p_consultation.ticket, p_consultation.first_name,
                    p_consultation.surname, departement_to_string(new_departement));
            fclose(f);
        }
       }
    
    if (is_empty(*list))
    {
        printf("La liste d'observation est vide.\n");
        return;
    }

    previous = NULL;
    cur = *list;
    while (cur != NULL && cur->obs.p.ticket != p_ticket)
    {
        previous = cur;
        cur = cur->next;
    }

    if (cur == NULL)
    {
        printf("Patient avec ticket %d introuvable.\n", p_ticket);
        return;
    }

    cur->obs.p.statut = referred;
    cur->obs.departement = new_departement;
    // ecrire dans historique avant de supprimer le node
    f = fopen("data/historique.txt", "a");
    if (f)
    {
        fprintf(f, "Ticket N°:%d: %s %s -referred vers: %s\n",
                cur->obs.p.ticket, cur->obs.p.first_name,
                cur->obs.p.surname, departement_to_string(new_departement));
        fclose(f);
    }

    // supprimer le node
    if (previous == NULL)
        *list = cur->next;
    else
        previous->next = cur->next;

    free(cur);
}

void free_observation_list(obs_list *list)
{
    t_node_obs *cur, *temp;

    cur = *list;
    while (cur != NULL)
    {
        temp = cur;
        cur = cur->next;
        free(temp);
    }
    *list = NULL;
    //"Liste d'observation liberee.");
}

bool is_bed_occupied(int bed_number,obs_list list)
{
    t_node_obs* cur;
    //parcourir la list
     cur=list;
     while(cur!=NULL)
     {
        if(cur->obs.bed_number==bed_number)
        {
            return true;
        }
       cur=cur->next;
    }
     return false;
   
}  