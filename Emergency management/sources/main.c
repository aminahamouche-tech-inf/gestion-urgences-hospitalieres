#include "patients.h"
#include "queue.h"
#include "consultation_results.h"
#include "file_io.h"
#include <stdio.h>
#include <string.h>

void display_menu(queue q, obs_list *list, int total_discharged, int total_referred,
                  int refere_cardio, int refere_radio, int refere_chirurgie, int refere_autres)
{
  char choice_display;
  printf("***display***\n");
  printf(" \n");
  printf("       [1]:display queue\n");
  printf("       [2]:display patients under observation\n");
  printf("       [3]:display historique\n");
  printf("       [4]:display statistiques\n");
  printf(" \n");
  printf("would you enter the caracter of the operation that you want to do:");
  scanf(" %c", &choice_display);
  switch (choice_display)
  {
  case '1':
    display_queue(q);
    break;
  case '2':
    display_observation(*list);
    break;
  case '3':
    display_historique("data/historique.txt");
    break;
  case '4':
    remplir_stats(q, *list, total_discharged, total_referred,
                  refere_cardio, refere_radio, refere_chirurgie, refere_autres, "data/stats.txt");
    display_stat("data/stats.txt");
    break;
  default:
    printf("choix invalide\n");
    break;
  }
}
void consultation_menu(patient p, obs_list *list, queue q, int ticket, int *total_discharged, int *total_referred,
                       int *refere_cardio, int *refere_radio, int *refere_chirurgie, int *refere_autres)
{
  char choice_sous_menu;
  // dans le cas ou le medecin n'a pas saisie le ticket du patient
  if (ticket == 0)
  {
    printf("no patient on consultation.\n");
    return;
  }
  printf("***Record the consultation results***\n");
  printf(" \n");
  printf("       [a]:discharge with prescreption \n");
  printf("       [b]:place under observation\n");
  printf("       [c]:Release a patient from observation\n");
  printf("       [d]:refer to another departement\n");
  printf(" \n");
  printf("would you enter the caracter of the operation that you want to do:\n");
  scanf(" %c", &choice_sous_menu);

  switch (choice_sous_menu)
  {
  case 'a':
  {
    // la j'ai pas utilise le ticket car le p je le recupere avec get head lors de l'appel du patient
    char prescription[50];
    printf("enter the prescription:");
    scanf(" %[^\n]", prescription);
    p.statut = discharged;
    discharged_patient_historique(p, prescription, "data/historique.txt");
    printf("patient %s %s has been discharged", p.first_name, p.surname);
    (*total_discharged)++;
    break;
  }
  case 'b':
    // je fais des {} pour ce case pour pouvoir declarer dedans
    {
      int bed_number;
      char treatment[100];

      do
      {
        printf("numero du lit:");
        scanf("%d", &bed_number);
        if (is_bed_occupied(bed_number, *list))
        {
          printf("this bed number is already occupied ,please pick anotherone\n");
        }

      } while (is_bed_occupied(bed_number, *list));

      printf("treatment:");
      scanf(" %[^\n]", treatment);
      admit_patient(list, p, bed_number, treatment);
      sauvegarde_list(*list, "data/observation.dat");
      printf("patient %s %s is under observation", p.first_name, p.surname);
      break;
    }
  case 'c':
  {
    discharge_patient(list, ticket);
    sauvegarde_list(*list, "data/observation.dat");
    printf("patient %s %s has been released from observation", p.first_name, p.surname);
    break;
  }
  case 'd':
  {
    int choix_dept;
    t_departement new_departement;

    printf("Choisir le departement :\n");
    printf("  1: Cardiologie\n  2: Radiologie\n  3: Chirurgie\n  4: Autres\n");
    scanf("%d", &choix_dept);

    switch (choix_dept)
    {
    case 1:
      new_departement = Cardiologie;
      break;
    case 2:
      new_departement = Radiologie;
      break;
    case 3:
      new_departement = Chirurgie;
      break;
    default:
      new_departement = autres;
      break;
    }

    refer_patient(list, p, ticket, new_departement);
    sauvegarde_list(*list, "data/observation.dat");
    printf("patient %s %s has been refered to %s departement",
           p.surname, p.first_name, departement_to_string(new_departement));
    (*total_referred)++;

    switch (new_departement)
    {
    case Cardiologie:
      (*refere_cardio)++;
      break;
    case Radiologie:
      (*refere_radio)++;
      break;
    case Chirurgie:
      (*refere_chirurgie)++;
      break;
    default:
      (*refere_autres)++;
      break;
    }

    break;
  }
  default:
    printf("invalide choice ,would you retry please\n");
    break;
  }
}
int main()

{
  int choice;
  char surname[20];
  char first_name[20];
  int age;
  int total_discharged = 0;
  int total_referred = 0;
  int refere_cardio = 0;
  int refere_radio = 0;
  int refere_chirurgie = 0;
  int refere_autres = 0;
  patient p;
  queue q;
  // initialisation
  create_queue(&q);
  obs_list list;
  initialization_observation_list(&list);
  charger_queue(&q, "data/queue.dat");
  load_id("data/id.txt");
  if (q.rear != NULL)
    ticket_function(q.rear->value.ticket);
  charger_observation(&list, "data/observation.dat", q);

  do
  {

    printf("*** Hospital Emergency Management System***");
    printf("\n");
    printf("       [1]:Register a patient's arrival\n");
    printf("       [2]:call the next patient\n");
    printf("       [3]:Record the consultation results\n");
    printf("       [4]:display\n");
    printf("       [5]:exit\n");
    printf(" \n");

    printf("would you enter the number of the opration that you want to do:");
    scanf("%d", &choice);
    switch (choice)
    {
      // Register a patient's arrival
    case 1:
    {
      char answer;
      answer = 'Y';
      while (answer == 'Y' || answer == 'y')
      {
        do
        {
          printf("would you enter the surname of the patient please:\n");
          scanf(" %[^\n]", surname);
          if (!correct_name(surname))
          {
            printf("the surname should contain only letters\n");
          }
        } while (!correct_name(surname));
        do
        {
          printf("would you enter the firstname of the patient please:\n");
          scanf(" %[^\n]", first_name);
          if (!correct_name(first_name))
          {
            printf("the first name should contain only letters\n");
          }
        } while (!correct_name(first_name));
        printf("would you enter the age of the patient please:\n");
        scanf("%d", &age);
        p = create_patient(surname, first_name, age);
        enqueue(&q, p);
        save_id("data/id.txt");
        // on la sauvgarde apres la mise a jour dans le fichier
        sauvegarde_queue(&q, "data/queue.dat");
        printf("would you register another patient ?? (Y/N)");
        scanf(" %c", &answer);
      }

      break;
    }
      // appeler prochain patient
    case 2:
      // on recupere le 1er de la queue
      if (q.front == NULL)
      {
        printf("no patient is waiting\n");
        break;
      }
      // dois_je verifier si la queue est vide malgres i did it in get head???
      p = get_head(&q);
      p.statut = in_consultation;
      // ce que on affiche sur l'ecran dans la salle d'attente
      printf("[ %d] %s %s \n", p.ticket, p.surname, p.first_name);
      // nrml de faire dequeue le medecin va travailler avec le p qu'on vient de recuperer
      dequeue(&q);
      sauvgarde_queue(&q, "data/queue.dat");
      break;
    case 3:
      // sous_menu!!
      {
        int ticket = 0;
        printf("ticket:");
        scanf("%d", &ticket);
        consultation_menu(p, &list, q, ticket, &total_discharged, &total_referred,
                          &refere_cardio, &refere_radio, &refere_chirurgie, &refere_autres);
      }
      break;
    case 4:
      display_menu(q, &list, total_discharged, total_referred,
                   refere_cardio, refere_radio, refere_chirurgie, refere_autres);
      break;
    }

  } while (choice != 5);
  free_observation_list(&list);
}
