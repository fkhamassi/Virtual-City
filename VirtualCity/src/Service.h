#ifndef SERVICE_H
#define SERVICE_H

#include "Batiment.h"

using namespace std;

// Classe Service : représente un service de la ville (nettoyage, déneigement, ...)
class Service : public Batiment {
public:
    double coutEntretien; // cout d'entretien par cycle

    Service(int _id = 0, const string& _nom = "Service", double _effet = 5.0, double _coutEntretien = 5.0);

    // Action du service : retourne l'effet sur la satisfaction
    double fournirService() const;

    void afficherDetails() const override;
};

#endif
