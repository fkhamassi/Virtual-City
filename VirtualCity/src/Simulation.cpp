#include "Simulation.h"
#include "Usine.h"
#include "Parc.h"
#include "Maison.h"
#include "Service.h"

using namespace std;

// Constructeur : initialise le cycle et lie la ville
Simulation::Simulation(Ville* _ville)
    : cycleActuel(0), ville(_ville)
{
    // Initialisation du générateur de nombres aléatoires
    srand(static_cast<unsigned int>(time(nullptr)));
}

// Démarrage d'un cycle: on applique consommation et production
void Simulation::demarrerCycle() {
    if (ville == nullptr) {
        cout << "Aucune ville liee a la simulation.\n";
        return;
    }
    cycleActuel++;
    cout << "\n--- Debut du cycle " << cycleActuel << " ---\n";

    // Calcul consommation totale
    auto conso = ville->calculerConsommationTotale();
    double consoEau = conso.first;
    double consoElec = conso.second;

    cout << "Consommation totale eau: " << consoEau << " | electricite: " << consoElec << "\n";

    // Application simple : on soustrait les consommations aux ressources si possible
    ville->ressourcesEau -= consoEau;
    ville->ressourcesElectricite -= consoElec;

    // --- Maintenance et couts d'entretien ---
    // On deduit un cout d'entretien pour chaque batiment en fonction de son type
    double coutEntretienTotal = 0.0; // initialise le cout total a zero
    for (const auto& b : ville->batiments) { // pour chaque batiment (auto& = unique_ptr<Batiment>)
        // valeurs simples par type
        if (b->type == "Maison") coutEntretienTotal += 2.0; // entretien maison: 2 par cycle
        else if (b->type == "Usine") coutEntretienTotal += 5.0; // usine: 5 par cycle
        else if (b->type == "Parc") coutEntretienTotal += 1.0; // parc: 1 par cycle
        else if (b->type == "Service") {
            // si c'est un service, recuperer coutEntretien specifique
            Service* s = dynamic_cast<Service*>(b.get()); // .get() donne le pointeur brut
            if (s) coutEntretienTotal += s->coutEntretien; // ajoute le cout du service
        }
    }
    if (coutEntretienTotal > 0) { // si il y a des couts
        cout << "Cout d'entretien total ce cycle: " << coutEntretienTotal << "\n";
        ville->budget -= coutEntretienTotal; // deduit du budget de la ville
        if (ville->budget < 0) { // si le budget devient negatif
            cout << "Budget negatif! Certaines actions seront limitees.\n";
            ville->budget = 0; // remet a zero (pas de dette)
        }
    }

    if (ville->ressourcesEau < 0) {
        cout << "Attention: penurie d'eau!\n";
        ville->satisfaction -= 10.0; // baisse de satisfaction en cas de pénurie
        if (ville->satisfaction < 0) ville->satisfaction = 0;
        ville->ressourcesEau = 0;
    }
    if (ville->ressourcesElectricite < 0) {
        cout << "Attention: penurie d'electricite!\n";
        ville->satisfaction -= 15.0;
        if (ville->satisfaction < 0) ville->satisfaction = 0;
        ville->ressourcesElectricite = 0;
    }

    // Les usines produisent des ressources et augmentent la pollution (effet sur satisfaction)
    double productionTotale = 0.0;  // initialise production a zero
    double pollutionTotale = 0.0;   // initialise pollution a zero
    for (const auto& b : ville->batiments) { // pour chaque batiment
        Usine* u = dynamic_cast<Usine*>(b.get()); // test si c'est une Usine (.get() donne pointeur brut)
        if (u != nullptr) { // si c'est bien une usine
            productionTotale += u->produireRessources(); // ajoute la production
            pollutionTotale += u->calculerPollution();   // ajoute la pollution
        }
    }

    // On utilise la production pour augmenter l'électricité (exemple simplifié)
    if (productionTotale > 0) {
        ville->ressourcesElectricite += productionTotale;
        cout << "Les usines ont produit " << productionTotale << " d'electricite.\n";
    }

    // La pollution réduit la satisfaction
    if (pollutionTotale > 0) {
        cout << "Pollution totale: " << pollutionTotale << " (impact sur satisfaction)\n";
        ville->satisfaction -= pollutionTotale * 0.1; // effet simple
        if (ville->satisfaction < 0) ville->satisfaction = 0;
    }

    // Les parcs augmentent la satisfaction
    double effetParcs = 0.0; // initialise effet a zero
    for (const auto& b : ville->batiments) { // pour chaque batiment
        Parc* p = dynamic_cast<Parc*>(b.get()); // test si c'est un Parc
        if (p != nullptr) { // si c'est bien un parc
            effetParcs += p->ameliorerBienEtre(); // ajoute l'effet du parc
        }
    }
    if (effetParcs > 0) { // si il y a des parcs
        ville->satisfaction += effetParcs * 0.05; // ajoute un effet reduit (0.05 = facteur d'echelle)
        if (ville->satisfaction > 100.0) ville->satisfaction = 100.0; // limite a 100
    }

    // --- DECISIONS AUTOMATIQUES SIMPLES ---
    // Si l'eau est basse, on tente de construire une petite station d'eau (Usine faible pollution)
    const double SEUIL_EAU = 200.0;         // seuil en dessous duquel on construit
    const double COUT_STATION_EAU = 200.0;  // cout de construction
    if (ville->ressourcesEau < SEUIL_EAU) { // si l'eau est basse
        if (ville->budget >= COUT_STATION_EAU) { // si on a assez d'argent
            cout << "Decision auto: construction d'une petite station d'eau (cout " << COUT_STATION_EAU << ")\n";
            // make_unique cree un unique_ptr automatiquement (plus simple que new)
            auto stationEau = make_unique<Usine>(1000 + cycleActuel, "Station Eau", 100.0, 2.0);
            if (ville->construireBatiment(move(stationEau), COUT_STATION_EAU)) { // move transfere la propriete
                // on donne immediatement de l'eau
                ville->ressourcesEau += 100.0;
            }
            // pas besoin de delete, unique_ptr gere automatiquement
        } else {
            cout << "Decision auto: fonds insuffisants pour construire station d'eau.\n";
        }
    }

    // Si l'electricite est basse, tenter une centrale
    const double SEUIL_ELEC = 200.0;      // seuil pour declencher construction
    const double COUT_CENTRALE = 300.0;   // cout de la centrale
    if (ville->ressourcesElectricite < SEUIL_ELEC) { // si electricite basse
        if (ville->budget >= COUT_CENTRALE) { // si budget suffisant
            cout << "Decision auto: construction d'une centrale electrique (cout " << COUT_CENTRALE << ")\n";
            auto centrale = make_unique<Usine>(2000 + cycleActuel, "Centrale", 200.0, 15.0);
            if (ville->construireBatiment(move(centrale), COUT_CENTRALE)) {
                ville->ressourcesElectricite += 200.0; // donne electricite immediate
            }
        } else {
            cout << "Decision auto: fonds insuffisants pour construire centrale.\n";
        }
    }

    // Si la satisfaction est basse, tenter d'embaucher un service de nettoyage
    const double SEUIL_SAT = 50.0;      // seuil de satisfaction critique
    const double COUT_SERVICE = 150.0;  // cout d'embauche du service
    if (ville->satisfaction < SEUIL_SAT) { // si satisfaction trop basse
        if (ville->budget >= COUT_SERVICE) { // si budget suffisant
            cout << "Decision auto: creation d'un service de nettoyage (cout " << COUT_SERVICE << ")\n";
            auto serv = make_unique<Service>(3000 + cycleActuel, "Service Nettoyage", 10.0, 5.0);
            double effetService = serv->fournirService(); // recupere effet avant de transferer
            if (ville->construireBatiment(move(serv), COUT_SERVICE)) {
                // action immediate: augmente satisfaction
                ville->satisfaction += effetService;
                if (ville->satisfaction > 100.0) ville->satisfaction = 100.0; // limite a 100
            }
        } else {
            cout << "Decision auto: fonds insuffisants pour engager service.\n";
        }
    }

    // Mise a jour approximative de la population (somme des habitants dans maisons)
    int pop = 0; // initialise population a zero
    for (const auto& b : ville->batiments) { // pour chaque batiment
        Maison* m = dynamic_cast<Maison*>(b.get()); // test si c'est une Maison
        if (m != nullptr) { // si c'est bien une maison
            pop += m->habitantsActuels; // ajoute le nombre d'habitants de cette maison
        }
    }
    ville->population = pop; // met a jour la population totale de la ville

    cout << "--- Actions du cycle terminees.\n";
}

// Termine le cycle : on affiche un résumé et on réévalue la satisfaction moyenne
void Simulation::terminerCycle() {
    if (ville == nullptr) return;
    // recalcul simple de la satisfaction
    ville->satisfaction = ville->calculerSatisfaction();

    cout << "--- Fin du cycle " << cycleActuel << " ---\n";
    ville->afficherEtat();
}

// Déclenche un événement aléatoire parmi quelques cas amusants
void Simulation::declencherEvenement() {
    if (ville == nullptr) return;
    int r = rand() % 5; // 0..4
    switch (r) {
        case 0: // nuée de pigeons géants
            cout << "Evenement: Nuée de pigeons géants! Satisfaction -15%.\n";
            ville->satisfaction *= 0.85; // diminution de 15%
            evenements.push_back("Pigeons geants: -15% satisfaction");
            break;
        case 1: // panne de courant augmente consommation de 50%
            cout << "Evenement: Panne de courant! Consommation d'energie +50% pour ce cycle.\n";
            // On augmente temporairement la consommation de chaque batiment
            for (auto& b : ville->batiments) { // pour chaque batiment
                b->consommationElectricite *= 1.5; // augmente de 50%
            }
            evenements.push_back("Panne de courant: +50% conso elec");
            break;
        case 2: // jardiniers en greve
            cout << "Evenement: Jardiniers en greve! Les parcs perdent la moitie de leur effet et satisfaction -20%.\n";
            for (auto& b : ville->batiments) { // pour chaque batiment (auto& pour modifier)
                Parc* p = dynamic_cast<Parc*>(b.get()); // test si c'est un Parc
                if (p != nullptr) {
                    p->effetBienEtre *= 0.5; // reduit effet de moitie
                }
            }
            ville->satisfaction *= 0.8; // -20%
            evenements.push_back("Greve jardiniers: parcs moins efficaces");
            break;
        case 3: // panne de transports publics
            cout << "Evenement: Panne transports publics! Satisfaction chute.\n";
            ville->satisfaction -= 25.0;
            if (ville->satisfaction < 0) ville->satisfaction = 0;
            evenements.push_back("Panne transports: -25 satisfaction");
            break;
        case 4: // tempete de neige
            cout << "Evenement: Tempete de neige! Usines interrompues et habitants grognons.\n";
            // On reduit la production des usines temporairement
            for (auto& b : ville->batiments) { // pour chaque batiment
                Usine* u = dynamic_cast<Usine*>(b.get()); // test si c'est une Usine
                if (u != nullptr) {
                    u->productionRessources *= 0.5; // production divisee par 2
                }
            }
            ville->satisfaction -= 10.0; // reduit satisfaction
            evenements.push_back("Tempete neige: usines ralenties");
            break;
        default:
            break;
    }
}
