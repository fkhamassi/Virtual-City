#include "Batiment.h"

using namespace std; // pour garder la cohérence dans tous les fichiers

// Constructeur : initialise chaque attribut avec les valeurs fournies
Batiment::Batiment(int _id, const string& _nom, const string& _type,
                   double _consEau, double _consElec, double _effetSat)
    : id(_id), nom(_nom), type(_type),
      consommationEau(_consEau), consommationElectricite(_consElec), effetSatisfaction(_effetSat)
{
    // Rien d'autre à faire ici, initialisation via la liste d'initialisation
}

// Destructeur virtuel vide (utile si on hérite de cette classe)
Batiment::~Batiment() {
}

// Affiche les informations du bâtiment de façon lisible
void Batiment::afficherDetails() const {
    cout << "Batiment ID: " << id << " | Nom: " << nom << " | Type: " << type << "\n";
    cout << "  Consommation Eau: " << consommationEau << " | Consommation Electricite: " << consommationElectricite << "\n";
    cout << "  Effet sur satisfaction: " << effetSatisfaction << "\n";
}

// Renvoie la consommation d'eau et d'électricité de ce bâtiment
pair<double,double> Batiment::calculerImpactRessources() const {
    return make_pair(consommationEau, consommationElectricite);
}
