#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <memory> // pour unique_ptr (gestion automatique de la memoire)

#include "Batiment.h"

using namespace std;

// Classe Ville : contient les bâtiments, les ressources et les indicateurs globaux
class Ville {
public:
    string nom;           // nom de la ville
    double budget;        // budget disponible
    int population;       // population totale (calculée)
    double satisfaction;  // satisfaction moyenne des habitants (0..100)

    double ressourcesEau; // eau disponible
    double ressourcesElectricite; // electricite disponible

    // Stockage des bâtiments : utilisation de unique_ptr pour gestion automatique de la memoire
    // unique_ptr libere automatiquement la memoire quand il est detruit (plus sur que new/delete)
    vector<unique_ptr<Batiment>> batiments;

    // Constructeur simple
    Ville(const string& _nom = "MaVille");

    // Destructeur : doit libérer la mémoire des bâtiments alloués
    ~Ville();

    // Gestion des bâtiments
    void ajouterBatiment(unique_ptr<Batiment> b); // prend possession du batiment
    void supprimerBatiment(int id); // supprime par identifiant
    // Tente de construire un batiment en deduisant le cout du budget
    // Retourne true si construction reussie
    bool construireBatiment(unique_ptr<Batiment> b, double coutConstruction);

    // Sauvegarde l'état simple de la ville dans un fichier texte
    bool sauvegarder(const string& chemin) const;

    // Charge l'etat de la ville depuis un fichier (fonction simplifiee)
    bool charger(const string& chemin);

    // Genere un rapport texte simple (pour presentation / rendu)
    bool genererRapport(const string& chemin) const;

    // Calculs globaux
    pair<double,double> calculerConsommationTotale() const; // (eau, electricite)
    double calculerSatisfaction() const; // calcule la satisfaction globale

    // Affiche l'état de la ville
    void afficherEtat() const;
};
