#ifndef MAISON_H
#define MAISON_H

#include "Batiment.h"

using namespace std;

// Classe Maison dérivée de Batiment : peut accueillir des habitants
class Maison : public Batiment {
public:
    int capaciteHabitants;   // capacité maximale d'habitants
    int habitantsActuels;    // nombre d'habitants actuellement

    // Constructeur avec valeurs par défaut
    Maison(int _id = 0, const string& _nom = "Maison", int _capacite = 4);

    // Méthodes spécifiques
    void ajouterHabitants(int nb);  // ajoute des habitants (si capacité disponible)
    void retirerHabitants(int nb);  // retire des habitants (si possible)

    // Réimplémentation pour afficher plus de détails
    void afficherDetails() const override;
};

#endif
