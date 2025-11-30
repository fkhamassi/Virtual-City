#pragma once

#include <vector>
#include <string>
#include <cstdlib> // pour rand()
#include <ctime>   // pour time()

#include "Ville.h"

using namespace std;

// Classe Simulation : orchestre les cycles et les événements
class Simulation {
public:
    int cycleActuel;      // numéro du cycle en cours
    Ville* ville;         // pointeur vers la ville simulée (géré par l'extérieur)
    vector<string> evenements; // historique simple des événements

    // Constructeur qui prend une ville existante (pour garder simplicité)
    Simulation(Ville* _ville = nullptr);

    // Démarre un cycle : applique consommation/production et met à jour la ville
    void demarrerCycle();

    // Termine un cycle : calcule les indicateurs et affiche le résumé
    void terminerCycle();

    // Déclenche un événement aléatoire qui affecte la ville
    void declencherEvenement();
};
