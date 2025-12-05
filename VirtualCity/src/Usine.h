#ifndef USINE_H
#define USINE_H

#include "Batiment.h"

using namespace std;

// Classe Usine dérivée de Batiment : produit des ressources et génère de la pollution
class Usine : public Batiment {
public:
    double productionRessources; // quantité produite par cycle
    double pollution;            // pollution générée par cycle

    Usine(int _id = 0, const string& _nom = "Usine", double _production = 10.0, double _pollution = 5.0);

    // Méthodes spécifiques
    double produireRessources() const; // renvoie la production
    double calculerPollution() const;  // renvoie la pollution

    void afficherDetails() const override;
};

#endif
