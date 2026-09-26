#include "file_io.h"
#include <stdio.h>
#include <stdlib.h>
#include "patients.h"
#include "queue.h"
#include "consultation_results.h"
// une procedure qui permet de sauvgarder chaque nouveau patients qui est dans la queue et le mettre dans un fichier

void sauvegarde_queue(queue *q, char *filename)
{
    FILE *f;
    node *cur;
    f = fopen(filename, "wb");
    if (!f)
    {
        printf("erreur ouverture fichier\n");
        return;
    }
    else
    {
        if (q->front == NULL)
        {
            printf("aucun patient en_attente");
        }
        else
        {

            cur = q->front;
            while (cur != NULL) // parcourir tous les nodes
            {
                if (cur->value.statut == on_hold)
                {
                    fwrite(&cur->value, sizeof(patient), 1, f);
                }

                cur = cur->next;
            }

            /*fclose(f);on a pas le droit de le mettre ici dans le cas ou f==NULL
            fclose(NULL) PEUT causer un crash*/
           
        }
     fclose(f);
    }
}

// une procedure qui permet de remplir the queue  apartir le fichier ......
void charger_queue(queue *q, char *filename)
{
    // declaration des variables locales
    FILE *f;
    // buffer
    patient x;
    f = fopen(filename, "rb");
    if (!f)
    {
        printf("erreur ouverture fichier\n");
    }
    else
    {
        // faire une boucle pour lire chaque ligne du fichier transformer en patient et l'ajouter dans la queue
        while (fread(&x, sizeof(patient), 1, f) == 1)
        {
            // ajouter dans la queue
            enqueue(q, x);
        }
        // why fclose dans le bloc else car dans lautre cas f==NULL fclose(null) error
        fclose(f);
    }
}
/*sauvgarder les patients EN OBSERVATION evec leurs informations dans un fichier*/
/*on sait que les observations sans sous forme d'une list (obs_list)*/
void sauvegarde_list(obs_list list, char *filename) /*dans cette fonction j'ai besoin comme
 parametre d'entree les observations que meryem a fait plus le fochier ou jv faire mes
 sauvgardations*/
{
    // declaration
    FILE *f;
    obs_list temp;             // un pointeur temporaire pour parcourir la liste
    f = fopen(filename, "wb"); // we are working with binary files
    if (!f)
    {
        printf("erreur ouverture fichier \n");
        return;
    }
    temp = list;
    // faire une boucle pour parcourir temp jusqu'a la fin de la boucle
    while (temp != NULL)
    {
        fwrite(&temp->obs, sizeof(PatientObs), 1, f);
        temp = temp->next;
    }
    fclose(f);
}
void charger_observation(obs_list *list, char *filename, queue q)
{
    // declaration
    FILE *f;
    PatientObs pobs;
    f = fopen(filename, "rb");
    if (!f)
    {
        printf("fichier introuvable!!\n");
        // patient temporaire juste pour stocker ce qu'on lit du fichier dans la liste
        /* now on veut creer une boucle qui permet de lire un seule patient apartir du f et
        et de l'ajouter a la liste*/
    }
    else
    {

        while (fread(&pobs, sizeof(PatientObs), 1, f) == 1) /*lire un patient depuis f et le mettre dans p*/
        {
            // now on veut ajouter le patient p dans la liste d'observation
            admit_patient(list, pobs.p, pobs.bed_number, pobs.treatement);
        }
        fclose(f);
    }
}

void display_historique(char *file_name)
{
    FILE *f;
    char ligne[200];
    f = fopen(file_name, "r");
    if (!f)
    {
        printf("erreur fichier introuvabe ou vide");
    }
    else
    {
        printf("les patients dans l'historique\n");
        while (fgets(ligne, sizeof(ligne), f) != NULL)
        {
            printf("%s", ligne);
        }
        fclose(f);
    }
}
/*bon now cette procedure vas remplir le fichier stats.txt c-a-d le stut de chaque patient */
 void remplir_stats(queue q, obs_list list, int total_discharged, int total_referred,
                    int refere_cardio, int refere_radio, int refere_chirurgie, int refere_autres,
                    char *file_name)
{
    FILE *f = fopen(file_name, "w");
    if (!f)
    {
        printf("erreur d'ouverture fichier\n");
        return;
    }

    // compter patients en attente dans la queue
    int nb_attente = 0;
    node *cur_q = q.front;
    while (cur_q != NULL)
    {
        nb_attente++;
        cur_q = cur_q->next;
    }

    // compter patients sous observation + départements
    int nb_observation = 0;
    int nb_cardio = 0;
    int nb_radio = 0;
    int nb_chirurgie = 0;
    int nb_autres = 0;
    obs_list cur_obs = list;
    while (cur_obs != NULL)
    {
        nb_observation++;
        switch (cur_obs->obs.departement)
        {
        case Cardiologie:
            nb_cardio++;
            break;
        case Radiologie:
            nb_radio++;
            break;
        case Chirurgie:
            nb_chirurgie++;
            break;
        case autres:
            nb_autres++;
            break;
        }
        cur_obs = cur_obs->next;
    }

    int total = nb_attente + nb_observation + total_discharged + total_referred;

    fprintf(f, "=== Statistiques ===\n");
    fprintf(f, "Total patients      : %d\n", total);
    fprintf(f, "En attente          : %d\n", nb_attente);
    fprintf(f, "Sous observation    : %d\n", nb_observation);
    fprintf(f, "Sortis              : %d\n", total_discharged);
    fprintf(f, "Referes             : %d\n", total_referred);
    fprintf(f, "References : Cardio=%d  Radio=%d  Chir=%d  Autres=%d\n",
        nb_cardio + refere_cardio, nb_radio + refere_radio,
        nb_chirurgie + refere_chirurgie, nb_autres + refere_autres);
    fclose(f);
}
void display_stat(char *file_name)
{
    FILE *f;
    char ligne[200];
    f = fopen(file_name, "r");
    if (!f)
    {
        printf("erreur fichier introuvabe ou vide");
    }

    else
    {
        while (fgets(ligne, sizeof(ligne), f) != NULL)
        {
            printf("%s", ligne);
        }

        fclose(f);
    }
}
void discharged_patient_historique(patient p, char prescription[50], char *file_name)
{
    FILE *f = fopen(file_name, "a");
    if (f)
    {
        fprintf(f, "Ticket N:%d:%s %s -prescription:%s\n",
                p.ticket, p.first_name, p.surname, prescription);
        fclose(f);
    }
}
