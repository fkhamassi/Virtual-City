#include "Usine.h"

using namespace std;

// Constructeur : initialise la production et la pollution, ainsi que les consommations liées
Usine::Usine(int _id, const string& _nom, double _production, double _pollution)
    : Batiment(_id, _nom, "Usine", /*consommationEau*/ 20.0, /*consommationElectricite*/ 30.0, /*effetSatisfaction*/ -5.0),
      productionRessources(_production), pollution(_pollution)
{
}

// Retourne la quantité de ressources produites par cycle
double Usine::produireRessources() const {
    return productionRessources;
}

// Retourne la pollution générée par la production
double Usine::calculerPollution() const {
    return pollution;
}

void Usine::afficherDetails() const {
    cout << "--- Usine ---\n";
    Batiment::afficherDetails();
    cout << "  Production ressources: " << productionRessources << " | Pollution: " << pollution << "\n";
}
