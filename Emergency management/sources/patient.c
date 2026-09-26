#include "patients.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// static:cause it's a patient.c detail
static int id = 0;
static int ticket = 0;

// function definitions
patient create_patient(char surname[20], char first_name[20], int age)
{
   patient p;

   id++;
   ticket++;
   strcpy(p.surname, surname);
   strcpy(p.first_name, first_name);
   p.age = age;
   p.id = id;
   p.ticket = ticket;
   p.statut = on_hold;
   return p;
}

void ticket_function(int val1)
{
   ticket = val1;
}
void display_patient(patient p)
{
   printf("informations about the  patient number:%d\n", p.ticket);
   printf("ID:%d\n", p.id);
   printf("surname:%s\n", p.surname);
   printf("first_name:%s\n", p.first_name);
   printf("age:%d\n", p.age);
   switch (p.statut)
   {
   case on_hold:
      printf("statut:on hold\n");
      break;
   case in_consultation:
      printf("statut:in consultation\n");
      break;
   case under_observation:
      printf("statut:under observation\n");
      break;
   case referred:
      printf("statut:referred\n");
      break;
   case discharged:
      printf("statut:discharged\n");
      break;
   }
}
   bool correct_name(char s[20])
   {
      int i;
      i=0;
      while(s[i]!='\0')
      {
         if(!isalpha(s[i]) && s[i]!=' ')
         {
            return false;
         }
        i++;
      }
      return true;
   }

  void save_id(char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f)
    {
        fprintf(f, "%d", id);
        fclose(f);
    }
}

void load_id(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f)
    {
        fscanf(f, "%d", &id);
        fclose(f);
    }
}
