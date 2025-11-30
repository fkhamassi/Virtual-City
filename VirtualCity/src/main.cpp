#include <iostream>
#include <limits>
#include <memory> // pour make_unique (gestion automatique memoire)

#include "Ville.h"
#include "Maison.h"
#include "Usine.h"
#include "Parc.h"
#include "Simulation.h"

using namespace std;

// Fonction utilitaire pour attendre une entrée de l'utilisateur
void pause() {
    cout << "Appuyez sur Entree pour continuer...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    // Création de la ville (pas besoin de pointeur ici, objet direct)
    Ville maVille("VirtualCity");

    // Création d'une simulation liée à la ville (passage par adresse)
    Simulation sim(&maVille);

    // Ajout d'exemples de bâtiments pour démarrer (make_unique cree des unique_ptr)
    maVille.ajouterBatiment(make_unique<Maison>(1, "Maison Centre", 6));
    maVille.ajouterBatiment(make_unique<Usine>(2, "Usine Electrique", 50.0, 10.0));
    maVille.ajouterBatiment(make_unique<Parc>(3, "Parc Central", 200.0, 12.0));

    bool quitter = false;
    while (!quitter) {
        cout << "\n=== Menu VirtualCity ===\n";
        cout << "1. Afficher etat de la ville\n";
        cout << "2. Lancer un cycle de simulation\n";
        cout << "3. Declencher un evenement aleatoire\n";
        cout << "8. Sauvegarder la ville\n";
        cout << "9. Generer rapport de la ville\n";
        cout << "4. Ajouter une maison\n";
        cout << "5. Ajouter une usine\n";
        cout << "6. Ajouter un parc\n";
        cout << "7. Supprimer un batiment par ID\n";
        cout << "0. Quitter\n";
        cout << "Choix: ";
        int choix;
        if (!(cin >> choix)) {
            // gestion simple en cas d'entrée non numérique
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrée invalide. Reessayez.\n";
            continue;
        }

        switch (choix) {
            case 1:
                maVille.afficherEtat();
                pause();
                break;
            case 2:
                sim.demarrerCycle();
                sim.terminerCycle();
                pause();
                break;
            case 3:
                sim.declencherEvenement();
                pause();
                break;
            case 8: { // sauvegarder
                cin.ignore(); // ignore newline restant
                string chemin;
                cout << "Chemin fichier sauvegarde (ex: ville.txt): ";
                getline(cin, chemin); // lit le chemin complet
                if (maVille.sauvegarder(chemin)) cout << "Sauvegarde terminee.\n";
                else cout << "Erreur sauvegarde.\n";
                pause();
                break;
            }
            case 9: { // generer rapport
                cin.ignore();
                string chemin;
                cout << "Chemin fichier rapport (ex: rapport.txt): ";
                getline(cin, chemin);
                if (maVille.genererRapport(chemin)) cout << "Rapport genere.\n";
                else cout << "Erreur rapport.\n";
                pause();
                break;
            }
            case 10: { // charger ville
                cin.ignore();
                string chemin;
                cout << "Chemin fichier a charger (ex: ville.txt): ";
                getline(cin, chemin);
                if (maVille.charger(chemin)) cout << "Ville chargee avec succes.\n";
                else cout << "Erreur chargement.\n";
                pause();
                break;
            }
            case 4: { // ajouter maison
                int id; string nom; int capacite;
                cout << "Entrez ID: "; cin >> id; cin.ignore(); // lit ID et ignore newline
                cout << "Nom maison: "; getline(cin, nom); // lit nom complet
                cout << "Capacite: "; cin >> capacite; // lit capacite
                maVille.ajouterBatiment(make_unique<Maison>(id, nom, capacite)); // cree et ajoute
                cout << "Maison ajoutee.\n";
                pause();
                break;
            }
            case 5: { // ajouter usine
                int id; string nom; double prod, poll;
                cout << "Entrez ID: "; cin >> id; cin.ignore();
                cout << "Nom usine: "; getline(cin, nom);
                cout << "Production: "; cin >> prod;
                cout << "Pollution: "; cin >> poll;
                maVille.ajouterBatiment(make_unique<Usine>(id, nom, prod, poll)); // cree et ajoute
                cout << "Usine ajoutee.\n";
                pause();
                break;
            }
            case 6: { // ajouter parc
                int id; string nom; double surface;
                cout << "Entrez ID: "; cin >> id; cin.ignore();
                cout << "Nom parc: "; getline(cin, nom);
                cout << "Surface: "; cin >> surface;
                maVille.ajouterBatiment(make_unique<Parc>(id, nom, surface, 10.0)); // cree et ajoute
                cout << "Parc ajoute.\n";
                pause();
                break;
            }
            case 7: { // supprimer batiment
                int id; cout << "Entrez ID du batiment a supprimer: "; cin >> id;
                maVille.supprimerBatiment(id); // appelle methode de suppression
                pause();
                break;
            }
            case 0: // quitter
                quitter = true;
                break;
            default: // choix invalide
                cout << "Choix non reconnu.\n";
                break;
        }
    }

    // Pas besoin de delete, maVille est un objet local qui se detruit automatiquement
    cout << "Au revoir !\n";
    return 0; // fin du programme
}
