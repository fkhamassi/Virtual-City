#include "Maison.h"

using namespace std;

// Constructeur : initialise une maison avec une consommation par habitant simple
Maison::Maison(int _id, const string& _nom, int _capacite)
    : Batiment(_id, _nom, "Maison", /*consommationEau*/ 5.0 * _capacite / 4.0,
               /*consommationElectricite*/ 3.0 * _capacite / 4.0, /*effetSatisfaction*/ 2.0),
      capaciteHabitants(_capacite), habitantsActuels(0)
{
    // On fixe des valeurs simples pour consommation relative à la capacité.
}

// Ajoute des habitants en vérifiant la capacité
void Maison::ajouterHabitants(int nb) {
    if (nb <= 0) return; // rien à faire pour nb <= 0
    int possible = capaciteHabitants - habitantsActuels; // place restante
    if (nb <= possible) {
        habitantsActuels += nb;
    } else {
        // si on dépasse la capacité, on remplit la maison au maximum
        habitantsActuels = capaciteHabitants;
    }
}

// Retire des habitants en évitant d'aller en dessous de zéro
void Maison::retirerHabitants(int nb) {
    if (nb <= 0) return; // rien à faire
    if (nb >= habitantsActuels) {
        habitantsActuels = 0; // on retire tous les habitants
    } else {
        habitantsActuels -= nb;
    }
}

// Affiche les détails de la maison, puis appelle la méthode de la classe de base
void Maison::afficherDetails() const {
    cout << "--- Maison ---\n";
    Batiment::afficherDetails(); // affiche id, nom, type, consumptions
    cout << "  Capacite habitants: " << capaciteHabitants << " | Habitants actuels: " << habitantsActuels << "\n";
}
