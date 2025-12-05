#ifndef BATIMENT_H
#define BATIMENT_H

#include <string>
#include <iostream>

using namespace std; // demandé par l'utilisateur : rend le code plus lisible pour un débutant

// Classe de base représentant un bâtiment générique
class Batiment {
public:
    // Attributs principaux (public pour simplifier la lecture pour débutants)
    int id;                  // identifiant unique du bâtiment
    string nom;              // nom du bâtiment
    string type;             // type du bâtiment ("Maison", "Usine", "Parc", ...)
    double consommationEau;  // consommation d'eau par cycle
    double consommationElectricite; // consommation d'électricité par cycle
    double effetSatisfaction; // effet sur la satisfaction des habitants (positif ou négatif)

    // Constructeur simple qui initialise les attributs
    Batiment(int _id = 0, const string& _nom = "", const string& _type = "",
             double _consEau = 0.0, double _consElec = 0.0, double _effetSat = 0.0);

    // Destructeur virtuel pour permettre l'héritage propre
    virtual ~Batiment();

    // Méthode pour afficher les détails du bâtiment
    virtual void afficherDetails() const;

    // Méthode qui calcule l'impact sur les ressources (eau, électricité)
    // Retourne une paire (eau, electricite)
    virtual pair<double,double> calculerImpactRessources() const;
};

#endif
