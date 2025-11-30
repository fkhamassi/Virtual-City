#include "Service.h"
#include <iostream>

using namespace std;

Service::Service(int _id, const string& _nom, double _effet, double _coutEntretien)
    : Batiment(_id, _nom, "Service", /*consommationEau*/ 1.0, /*consommationElectricite*/ 2.0, /*effetSatisfaction*/ _effet),
      coutEntretien(_coutEntretien)
{
}

double Service::fournirService() const {
    return effetSatisfaction; // valeur simple
}

void Service::afficherDetails() const {
    cout << "--- Service ---\n";
    Batiment::afficherDetails();
    cout << "  Cout entretien: " << coutEntretien << " | Effet service: " << effetSatisfaction << "\n";
}
