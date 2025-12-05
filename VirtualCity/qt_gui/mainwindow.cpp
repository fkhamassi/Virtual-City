#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <sstream>

// Inclusion des classes de bâtiments
#include "Maison.h"
#include "Usine.h"
#include "Parc.h"
#include "Service.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , prochainId(1)
{
    ui->setupUi(this);
    
    // Initialisation de la ville et de la simulation
    ville = std::make_unique<Ville>("MaVille");
    ville->budget = 10000.0;
    ville->ressourcesEau = 1000.0;
    ville->ressourcesElectricite = 1000.0;
    
    simulation = std::make_unique<Simulation>(ville.get());
    
    // Connexion des boutons aux slots
    connect(ui->btnAfficherEtat, &QPushButton::clicked, this, &MainWindow::afficherEtatVille);
    connect(ui->btnLancerCycle, &QPushButton::clicked, this, &MainWindow::lancerCycle);
    connect(ui->btnEvenement, &QPushButton::clicked, this, &MainWindow::declencherEvenement);
    connect(ui->btnAjouterMaison, &QPushButton::clicked, this, &MainWindow::ajouterMaison);
    connect(ui->btnAjouterUsine, &QPushButton::clicked, this, &MainWindow::ajouterUsine);
    connect(ui->btnAjouterParc, &QPushButton::clicked, this, &MainWindow::ajouterParc);
    connect(ui->btnSupprimerBatiment, &QPushButton::clicked, this, &MainWindow::supprimerBatiment);
    connect(ui->btnSauvegarder, &QPushButton::clicked, this, &MainWindow::sauvegarderVille);
    connect(ui->btnGenererRapport, &QPushButton::clicked, this, &MainWindow::genererRapport);
    connect(ui->btnCharger, &QPushButton::clicked, this, &MainWindow::chargerVille);
    
    // Affichage initial
    mettreAJourAffichage();
    ajouterLog("Bienvenue dans VirtualCity!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::afficherEtatVille()
{
    mettreAJourAffichage();
    ajouterLog("État de la ville mis à jour.");
}

void MainWindow::lancerCycle()
{
    simulation->demarrerCycle();
    simulation->terminerCycle();
    
    mettreAJourAffichage();
    rafraichirListeBatiments();
    
    ajouterLog(QString("Cycle %1 terminé.").arg(simulation->cycleActuel));
}

void MainWindow::declencherEvenement()
{
    simulation->declencherEvenement();
    mettreAJourAffichage();
    
    if (!simulation->evenements.empty()) {
        ajouterLog(QString::fromStdString(simulation->evenements.back()));
    }
}

void MainWindow::ajouterMaison()
{
    bool ok;
    QString nom = QInputDialog::getText(this, "Nouvelle Maison",
                                       "Nom de la maison:", QLineEdit::Normal,
                                       QString("Maison_%1").arg(prochainId), &ok);
    if (ok && !nom.isEmpty()) {
        int capacite = QInputDialog::getInt(this, "Capacité",
                                           "Capacité d'habitants:", 4, 1, 20, 1, &ok);
        if (ok) {
            double cout = 500.0;
            if (ville->budget >= cout) {
                auto maison = std::make_unique<Maison>(prochainId++, nom.toStdString(), capacite);
                ville->construireBatiment(std::move(maison), cout);
                
                mettreAJourAffichage();
                rafraichirListeBatiments();
                ajouterLog(QString("Maison '%1' ajoutée.").arg(nom));
            } else {
                QMessageBox::warning(this, "Budget insuffisant", 
                                   QString("Coût: %1€, Budget: %2€").arg(cout).arg(ville->budget));
            }
        }
    }
}

void MainWindow::ajouterUsine()
{
    bool ok;
    QString nom = QInputDialog::getText(this, "Nouvelle Usine",
                                       "Nom de l'usine:", QLineEdit::Normal,
                                       QString("Usine_%1").arg(prochainId), &ok);
    if (ok && !nom.isEmpty()) {
        double cout = 1000.0;
        if (ville->budget >= cout) {
            auto usine = std::make_unique<Usine>(prochainId++, nom.toStdString(), 15.0, 8.0);
            ville->construireBatiment(std::move(usine), cout);
            
            mettreAJourAffichage();
            rafraichirListeBatiments();
            ajouterLog(QString("Usine '%1' ajoutée.").arg(nom));
        } else {
            QMessageBox::warning(this, "Budget insuffisant", 
                               QString("Coût: %1€, Budget: %2€").arg(cout).arg(ville->budget));
        }
    }
}

void MainWindow::ajouterParc()
{
    bool ok;
    QString nom = QInputDialog::getText(this, "Nouveau Parc",
                                       "Nom du parc:", QLineEdit::Normal,
                                       QString("Parc_%1").arg(prochainId), &ok);
    if (ok && !nom.isEmpty()) {
        double cout = 300.0;
        if (ville->budget >= cout) {
            auto parc = std::make_unique<Parc>(prochainId++, nom.toStdString(), 150.0, 15.0);
            ville->construireBatiment(std::move(parc), cout);
            
            mettreAJourAffichage();
            rafraichirListeBatiments();
            ajouterLog(QString("Parc '%1' ajouté.").arg(nom));
        } else {
            QMessageBox::warning(this, "Budget insuffisant", 
                               QString("Coût: %1€, Budget: %2€").arg(cout).arg(ville->budget));
        }
    }
}

void MainWindow::supprimerBatiment()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Supprimer Bâtiment",
                                 "ID du bâtiment à supprimer:", 1, 1, 1000, 1, &ok);
    if (ok) {
        ville->supprimerBatiment(id);
        mettreAJourAffichage();
        rafraichirListeBatiments();
        ajouterLog(QString("Bâtiment ID %1 supprimé.").arg(id));
    }
}

void MainWindow::sauvegarderVille()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder la ville",
                                                    "", "Fichiers texte (*.txt)");
    if (!fileName.isEmpty()) {
        if (ville->sauvegarder(fileName.toStdString())) {
            ajouterLog("Ville sauvegardée avec succès.");
            QMessageBox::information(this, "Sauvegarde", "Ville sauvegardée avec succès!");
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de la sauvegarde.");
        }
    }
}

void MainWindow::genererRapport()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Générer rapport",
                                                    "rapport.txt", "Fichiers texte (*.txt)");
    if (!fileName.isEmpty()) {
        if (ville->genererRapport(fileName.toStdString())) {
            ajouterLog("Rapport généré avec succès.");
            QMessageBox::information(this, "Rapport", "Rapport généré avec succès!");
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de la génération du rapport.");
        }
    }
}

void MainWindow::chargerVille()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Charger une ville",
                                                    "", "Fichiers texte (*.txt)");
    if (!fileName.isEmpty()) {
        if (ville->charger(fileName.toStdString())) {
            mettreAJourAffichage();
            rafraichirListeBatiments();
            ajouterLog("Ville chargée avec succès.");
            QMessageBox::information(this, "Chargement", "Ville chargée avec succès!");
        } else {
            QMessageBox::warning(this, "Erreur", "Échec du chargement.");
        }
    }
}

void MainWindow::mettreAJourAffichage()
{
    // Mise à jour des informations de base
    ui->labelNomVille->setText(QString::fromStdString(ville->nom));
    ui->labelBudget->setText(QString("Budget: %1 €").arg(ville->budget, 0, 'f', 2));
    ui->labelPopulation->setText(QString("Population: %1").arg(ville->population));
    ui->labelSatisfaction->setText(QString("Satisfaction: %1%").arg(ville->satisfaction, 0, 'f', 1));
    
    // Ressources
    ui->labelEau->setText(QString("Eau: %1").arg(ville->ressourcesEau, 0, 'f', 1));
    ui->labelElectricite->setText(QString("Électricité: %1").arg(ville->ressourcesElectricite, 0, 'f', 1));
    
    // Consommation totale
    auto [consEau, consElec] = ville->calculerConsommationTotale();
    ui->labelConsommationEau->setText(QString("Consommation Eau: %1/cycle").arg(consEau, 0, 'f', 1));
    ui->labelConsommationElec->setText(QString("Consommation Élec: %1/cycle").arg(consElec, 0, 'f', 1));
    
    // Cycle actuel
    ui->labelCycle->setText(QString("Cycle: %1").arg(simulation->cycleActuel));
    
    // Nombre de bâtiments
    ui->labelNbBatiments->setText(QString("Bâtiments: %1").arg(ville->batiments.size()));
}

void MainWindow::ajouterLog(const QString& message)
{
    ui->textEditLog->append(QString("[%1] %2").arg(simulation->cycleActuel).arg(message));
}

void MainWindow::rafraichirListeBatiments()
{
    ui->listWidgetBatiments->clear();
    
    for (const auto& bat : ville->batiments) {
        QString info = QString("ID:%1 | %2 - %3")
                          .arg(bat->id)
                          .arg(QString::fromStdString(bat->type))
                          .arg(QString::fromStdString(bat->nom));
        ui->listWidgetBatiments->addItem(info);
    }
}
