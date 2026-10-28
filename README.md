# Gestion des Urgences Hospitalières

Programme en langage C développé pour simuler la gestion du flux des patients au sein d'un service d'urgence : enregistrement à l'arrivée, suivi de la prise en charge, sortie ou référencement vers un autre département. 
Il s'agit d'un programme console (non hébergé) réalisé dans un cadre pédagogique.
> Projet académique réalisé dans le cadre du module **DSA-2 (Algorithmiques et structure de données 2)** — 1ère année ingènieur en Informatique, Université A. Mira, Béjaïa (2025/2026).

## Fonctionnalités

- **Enregistrement des patients**: à leur arrivée, avec attribution automatique d'un identifiant et d'un ticket
- **Gestion de la file d'attente**: selon le principe FIFO (First In, First Out)
- **Suivi des patients sous observation** : admission, mise à jour, sortie, référencement vers un autre département (Cardiologie, Radiologie, Chirurgie, Autres)
- **Historique des opérations**: (admissions, consultations, sorties, référencements)
- **Statistiques du service**: (patients en attente, sous observation, sortis, référés par département)
- **Persistance des données**: entre les sessions via des fichiers binaires et texte

## Architecture du projet

Le projet suit une architecture **modulaire**, chaque fonctionnalité étant isolée dans un module `.h` (déclarations) / `.c` (implémentation), répartis dans trois dossiers :

- **headers/** : `patients.h`, `queue.h`, `consultation_results.h`, `file_io.h`
- **sources/** : `patient.c`, `queue.c`, `consultation_results.c`, `file_io.c`, `main.c` (coordinateur : menus et boucle principale)
- **data/** : fichiers générés à l'exécution pour la persistance (`queue.dat`, `observation.dat`, `historique.txt`, `stats.txt`, `id.txt`)

Un rapport détaillé (`Rapport_Projet_Gestion_Urgences_Hospitalieres.pdf`) décrit les choix de conception et les difficultés rencontrées.

## Compilation et exécution

Depuis le dossier `Emergency management/` :

```bash
gcc sources/*.c -Iheaders -o urgences
./urgences
```

Le programme charge automatiquement les données des sessions précédentes depuis le dossier `data/` au démarrage.

## Auteurs

Projet réalisé en équipe dans le cadre du module DSA-2 :
- **HAMOUCHE Amina** (G4)
- ISSAADI Yasmine (G4)
- HADDADI Meriem (G3)

Encadrants : M. BAKLI, M. OUZEGGANE, Mme. BENSLIMANE

### Contribution personnelle (HAMOUCHE Amina)

- Conception et implémentation du module **patients** (`patients.h` / `patient.c`) : structure patient, création, affichage, validation des noms
- Conception et implémentation du module **queue** (`queue.h` / `queue.c`) : file d'attente FIFO (enqueue, dequeue, get_head, affichage)
- Contribution au débogage général des autres modules du projet
- Rédaction du rapport .
