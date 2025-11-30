#include "Ville.h"
#include <fstream>
#include "Usine.h"
#include "Parc.h"
#include "Maison.h"
#include "Service.h"

using namespace std;

Ville::Ville(const string& _nom)
    : nom(_nom), budget(1000.0), population(0), satisfaction(100.0), ressourcesEau(1000.0), ressourcesElectricite(1000.0)
{
}

// Destructeur : unique_ptr libere automatiquement la memoire, plus besoin de delete manuel
Ville::~Ville() {
    // batiments.clear() suffit, les unique_ptr se detruisent automatiquement
    batiments.clear();
}

// Ajoute un batiment a la ville (on prend possession via unique_ptr)
void Ville::ajouterBatiment(unique_ptr<Batiment> b) {
    if (b == nullptr) return; // securite : si pointeur vide, on ne fait rien
    batiments.push_back(move(b)); // move transfere la propriete du pointeur au vecteur
}

// Supprime un batiment par ID (unique_ptr libere automatiquement la memoire)
void Ville::supprimerBatiment(int id) {
    for (auto it = batiments.begin(); it != batiments.end(); ++it) {
        if ((*it)->id == id) { // on accede au batiment via ->
            batiments.erase(it);   // enleve du vecteur, unique_ptr libere la memoire
            cout << "Batiment ID " << id << " supprime.\n";
            return;
        }
    }
    // si on arrive ici, on n'a pas trouve le batiment
    cout << "Aucun batiment avec l'ID " << id << " trouve.\n";
}

// Tente de construire un batiment si le budget le permet
bool Ville::construireBatiment(unique_ptr<Batiment> b, double coutConstruction) {
    if (b == nullptr) return false; // si pointeur vide, echec
    if (coutConstruction > budget) {
        // pas assez d'argent : on affiche un message et on retourne false
        cout << "Fonds insuffisants pour construire " << b->nom << ". Cout: " << coutConstruction << ", budget: " << budget << "\n";
        return false;
    }
    budget -= coutConstruction; // on deduit le cout du budget
    cout << "Batiment " << b->nom << " construit (cout " << coutConstruction << "). Budget restant: " << budget << "\n";
    batiments.push_back(move(b)); // on transfere la propriete au vecteur
    return true;
}

// Sauvegarde simple: on ecrit l'etat essentiel dans un fichier texte
bool Ville::sauvegarder(const string& chemin) const {
    ofstream ofs(chemin); // ouvre le fichier en ecriture
    if (!ofs.is_open()) return false; // si echec ouverture, retourne false
    // ecrire les donnees principales ligne par ligne
    ofs << "Ville:" << nom << "\n";
    ofs << "Budget:" << budget << "\n";
    ofs << "Population:" << population << "\n";
    ofs << "Satisfaction:" << satisfaction << "\n";
    ofs << "Eau:" << ressourcesEau << "\n";
    ofs << "Electricite:" << ressourcesElectricite << "\n";
    ofs << "Batiments:" << batiments.size() << "\n";
    for (const auto& b : batiments) { // pour chaque batiment
        // Format tres simple: type|id|nom|consEau|consElec|effet
        ofs << b->type << "|" << b->id << "|" << b->nom << "|" << b->consommationEau << "|" << b->consommationElectricite << "|" << b->effetSatisfaction;
        // champs specifiques selon le type
        const Usine* u = dynamic_cast<const Usine*>(b.get()); // .get() retourne le pointeur brut
        if (u) ofs << "|U|" << u->productionRessources << "|" << u->pollution;
        const Parc* p = dynamic_cast<const Parc*>(b.get());
        if (p) ofs << "|P|" << p->surface << "|" << p->effetBienEtre;
        const Maison* m = dynamic_cast<const Maison*>(b.get());
        if (m) ofs << "|M|" << m->capaciteHabitants << "|" << m->habitantsActuels;
        const Service* s = dynamic_cast<const Service*>(b.get());
        if (s) ofs << "|S|" << s->coutEntretien;
        ofs << "\n";
    }
    ofs.close(); // ferme le fichier
    cout << "Ville sauvegardee dans " << chemin << "\n";
    return true;
}

// Charge l'etat de la ville depuis un fichier (version simplifiee pour debutants)
bool Ville::charger(const string& chemin) {
    ifstream ifs(chemin); // ouvre le fichier en lecture
    if (!ifs.is_open()) { // si echec ouverture
        cout << "Erreur: impossible d'ouvrir " << chemin << "\n";
        return false;
    }
    // nettoyer les batiments existants avant de charger
    batiments.clear(); // unique_ptr libere automatiquement la memoire

    string ligne; // variable pour lire chaque ligne
    // lire les donnees principales
    if (getline(ifs, ligne)) nom = ligne.substr(ligne.find(':') + 1); // extrait apres ':'
    if (getline(ifs, ligne)) budget = stod(ligne.substr(ligne.find(':') + 1)); // convertit en double
    if (getline(ifs, ligne)) population = stoi(ligne.substr(ligne.find(':') + 1)); // convertit en int
    if (getline(ifs, ligne)) satisfaction = stod(ligne.substr(ligne.find(':') + 1));
    if (getline(ifs, ligne)) ressourcesEau = stod(ligne.substr(ligne.find(':') + 1));
    if (getline(ifs, ligne)) ressourcesElectricite = stod(ligne.substr(ligne.find(':') + 1));
    
    int nbBatiments = 0; // nombre de batiments a charger
    if (getline(ifs, ligne)) nbBatiments = stoi(ligne.substr(ligne.find(':') + 1));

    // lire chaque batiment (format: type|id|nom|consEau|consElec|effet|...)
    for (int i = 0; i < nbBatiments; ++i) {
        if (!getline(ifs, ligne)) break; // lit la ligne du batiment
        // decoupage simple par le separateur '|'
        vector<string> parts; // vecteur pour stocker les morceaux
        size_t pos = 0;
        while ((pos = ligne.find('|')) != string::npos) { // cherche '|'
            parts.push_back(ligne.substr(0, pos)); // extrait le morceau
            ligne.erase(0, pos + 1); // enleve le morceau traite
        }
        parts.push_back(ligne); // dernier morceau

        if (parts.size() < 6) continue; // si format invalide, saute cette ligne

        // extrait les champs de base
        string type = parts[0];
        int id = stoi(parts[1]);
        string nomBat = parts[2];
        double consEau = stod(parts[3]);
        double consElec = stod(parts[4]);
        double effet = stod(parts[5]);

        // cree le batiment selon son type
        unique_ptr<Batiment> bat = nullptr; // pointeur vide au depart
        if (parts.size() > 6 && parts[6] == "U") { // Usine
            double prod = stod(parts[7]);
            double poll = stod(parts[8]);
            bat = make_unique<Usine>(id, nomBat, prod, poll); // cree une Usine
        } else if (parts.size() > 6 && parts[6] == "P") { // Parc
            double surf = stod(parts[7]);
            double effetB = stod(parts[8]);
            bat = make_unique<Parc>(id, nomBat, surf, effetB); // cree un Parc
        } else if (parts.size() > 6 && parts[6] == "M") { // Maison
            int cap = stoi(parts[7]);
            bat = make_unique<Maison>(id, nomBat, cap); // cree une Maison
            if (parts.size() > 8) {
                Maison* m = dynamic_cast<Maison*>(bat.get());
                if (m) m->habitantsActuels = stoi(parts[8]); // restaure habitants
            }
        } else if (parts.size() > 6 && parts[6] == "S") { // Service
            double coutEnt = stod(parts[7]);
            bat = make_unique<Service>(id, nomBat, effet, coutEnt); // cree un Service
        } else {
            // type de base Batiment
            bat = make_unique<Batiment>(id, nomBat, type, consEau, consElec, effet);
        }

        if (bat) batiments.push_back(move(bat)); // ajoute le batiment a la ville
    }

    ifs.close(); // ferme le fichier
    cout << "Ville chargee depuis " << chemin << " (" << batiments.size() << " batiments).\n";
    return true;
}

// Genere un rapport texte simple, legible pour integrer dans une presentation
bool Ville::genererRapport(const string& chemin) const {
    ofstream ofs(chemin); // ouvre le fichier en ecriture
    if (!ofs.is_open()) return false; // si echec, retourne false
    // ecrit le rapport ligne par ligne
    ofs << "Rapport de la ville: " << nom << "\n\n";
    ofs << "Budget: " << budget << "\n";
    ofs << "Population: " << population << "\n";
    ofs << "Satisfaction: " << satisfaction << "\n";
    ofs << "Ressources - Eau: " << ressourcesEau << ", Electricite: " << ressourcesElectricite << "\n\n";
    ofs << "Batiments (resume):\n";
    for (const auto& b : batiments) { // pour chaque batiment
        ofs << "- [" << b->type << "] " << b->nom << " (ID:" << b->id << ")\n";
    }
    ofs << "\nEvenements: (historique non disponible dans cette version)\n";
    ofs.close(); // ferme le fichier
    cout << "Rapport genere dans " << chemin << "\n";
    return true;
}

// Calcule la consommation totale d'eau et d'électricité en sommant sur tous les bâtiments
pair<double,double> Ville::calculerConsommationTotale() const {
    double totalEau = 0.0;  // initialise compteur eau a zero
    double totalElec = 0.0; // initialise compteur electricite a zero
    for (const auto& b : batiments) { // pour chaque batiment (auto& = unique_ptr<Batiment>)
        auto impact = b->calculerImpactRessources(); // appelle la methode du batiment
        totalEau += impact.first;   // ajoute consommation eau
        totalElec += impact.second; // ajoute consommation electricite
    }
    return make_pair(totalEau, totalElec); // retourne le total sous forme de paire
}

// Calcule la satisfaction globale comme une moyenne pondérée simple des effets des bâtiments
double Ville::calculerSatisfaction() const {
    if (batiments.empty()) return satisfaction; // si pas de batiments, garde satisfaction actuelle
    double sommeEffets = 0.0; // initialise somme a zero
    for (const auto& b : batiments) { // pour chaque batiment
        sommeEffets += b->effetSatisfaction; // ajoute l'effet du batiment
    }
    // satisfaction de base plus effet moyen des batiments
    double effetMoyen = sommeEffets / batiments.size(); // calcule la moyenne
    double nouvelleSatisfaction = satisfaction + effetMoyen; // ajoute a la satisfaction actuelle
    // bornes entre 0 et 100
    if (nouvelleSatisfaction < 0.0) nouvelleSatisfaction = 0.0;   // minimum 0
    if (nouvelleSatisfaction > 100.0) nouvelleSatisfaction = 100.0; // maximum 100
    return nouvelleSatisfaction;
}

// Affiche l'état synthétique de la ville
void Ville::afficherEtat() const {
    cout << "===== Etat de la ville : " << nom << " =====\n";
    cout << "Budget: " << budget << " | Eau: " << ressourcesEau << " | Electricite: " << ressourcesElectricite << "\n";
    cout << "Population (approx): " << population << " | Satisfaction actuelle: " << satisfaction << "\n";
    cout << "Nombre de batiments: " << batiments.size() << "\n";
    cout << "Liste des batiments :\n";
    for (const auto& b : batiments) { // pour chaque batiment
        b->afficherDetails(); // appelle la methode d'affichage du batiment
    }
}
