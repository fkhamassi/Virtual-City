#ifndef PARC_H
#define PARC_H

#include "Batiment.h"

using namespace std;

// Classe Parc dérivée de Batiment : améliore le bien-être des habitants
class Parc : public Batiment {
public:
    double surface;       // surface du parc
    double effetBienEtre; // effet positif sur le bien-être / satisfaction

    Parc(int _id = 0, const string& _nom = "Parc", double _surface = 100.0, double _effet = 10.0);

    // Méthode spécifique : améliore le bien-être (retourne la valeur d'amélioration)
    double ameliorerBienEtre() const;

    void afficherDetails() const override;
};

#endif
