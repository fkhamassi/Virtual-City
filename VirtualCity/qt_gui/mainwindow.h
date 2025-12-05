#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <memory>
#include "Ville.h"
#include "Simulation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots pour les boutons
    void afficherEtatVille();
    void lancerCycle();
    void declencherEvenement();
    void ajouterMaison();
    void ajouterUsine();
    void ajouterParc();
    void supprimerBatiment();
    void sauvegarderVille();
    void genererRapport();
    void chargerVille();

private:
    Ui::MainWindow *ui;
    
    // Objets de simulation
    std::unique_ptr<Ville> ville;
    std::unique_ptr<Simulation> simulation;
    
    int prochainId; // Pour générer des IDs uniques
    
    // Méthodes utilitaires
    void mettreAJourAffichage();
    void ajouterLog(const QString& message);
    void rafraichirListeBatiments();
};

#endif // MAINWINDOW_H
