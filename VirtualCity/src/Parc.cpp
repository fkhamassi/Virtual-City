#include "Parc.h"

using namespace std;

Parc::Parc(int _id, const string& _nom, double _surface, double _effet)
    : Batiment(_id, _nom, "Parc", /*consommationEau*/ 2.0, /*consommationElectricite*/ 1.0, /*effetSatisfaction*/ _effet),
      surface(_surface), effetBienEtre(_effet)
{
}

// Renvoie l'effet de bien-être du parc
double Parc::ameliorerBienEtre() const {
    return effetBienEtre;
}

void Parc::afficherDetails() const {
    cout << "--- Parc ---\n";
    Batiment::afficherDetails();
    cout << "  Surface: " << surface << " | Effet bien-etre: " << effetBienEtre << "\n";
}
