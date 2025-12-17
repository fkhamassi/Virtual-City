#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QMenu>
#include <QAction>
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
    
        // Interactions liste (aucune modification du .ui requise)
        connect(ui->listWidgetBatiments, &QListWidget::itemDoubleClicked,
            this, &MainWindow::onBatimentDoubleClique);
        ui->listWidgetBatiments->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(ui->listWidgetBatiments, &QListWidget::customContextMenuRequested,
            this, &MainWindow::afficherMenuContexteBatiment);
        connect(ui->listWidgetBatiments, &QListWidget::currentRowChanged,
            this, [this](int){ mettreAJourDetailsSelection(); });
    
        // Menubar runtime (pas de changement .ui) pour ajouter un Service
        auto menuBat = menuBar()->addMenu("Bâtiments");
        QAction* actionAjouterService = menuBat->addAction("Ajouter Service...");
        connect(actionAjouterService, &QAction::triggered, this, &MainWindow::ajouterService);
    
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

    // Afficher un récapitulatif détaillé de chaque bâtiment
    QString info;
    info += QString("Ville: %1\nBudget: %2  |  Eau: %3  |  Élec: %4\nPopulation: %5  |  Satisfaction: %6\n\n")
                .arg(QString::fromStdString(ville->nom))
                .arg(ville->budget, 0, 'f', 2)
                .arg(ville->ressourcesEau, 0, 'f', 1)
                .arg(ville->ressourcesElectricite, 0, 'f', 1)
                .arg(ville->population)
                .arg(ville->satisfaction, 0, 'f', 1);

    info += QString("Bâtiments (%1):\n").arg(ville->batiments.size());
    for (const auto& b : ville->batiments) {
        info += detailsBatiment(b.get());
        info += "\n";
    }
    QMessageBox::information(this, "État de la ville", info);
    ajouterLog("État de la ville affiché.");
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
    
    // Message court sur la sélection
    mettreAJourDetailsSelection();
}

void MainWindow::ajouterLog(const QString& message)
{
    ui->textEditLog->append(QString("[%1] %2").arg(simulation->cycleActuel).arg(message));
}

void MainWindow::rafraichirListeBatiments()
{
    ui->listWidgetBatiments->clear();
    
    for (const auto& bat : ville->batiments) {
        QString base = QString("ID:%1 | %2 - %3")
                           .arg(bat->id)
                           .arg(QString::fromStdString(bat->type))
                           .arg(QString::fromStdString(bat->nom));

        if (auto m = dynamic_cast<const Maison*>(bat.get())) {
            base += QString(" | cap %1, hab %2")
                        .arg(m->capaciteHabitants)
                        .arg(m->habitantsActuels);
        } else if (auto u = dynamic_cast<const Usine*>(bat.get())) {
            base += QString(" | prod %1, poll %2")
                        .arg(u->productionRessources, 0, 'f', 1)
                        .arg(u->pollution, 0, 'f', 1);
        } else if (auto p = dynamic_cast<const Parc*>(bat.get())) {
            base += QString(" | surf %1, effet %2")
                        .arg(p->surface, 0, 'f', 1)
                        .arg(p->effetBienEtre, 0, 'f', 1);
        } else if (auto s = dynamic_cast<const Service*>(bat.get())) {
            base += QString(" | coût ent. %1")
                        .arg(s->coutEntretien, 0, 'f', 1);
        }
        ui->listWidgetBatiments->addItem(base);
    }
}

// ===== Helpers d'affichage et sélection =====
QString MainWindow::detailsBatiment(const Batiment* b) const
{
    if (!b) return "";
    QString d;
    d += QString("- [ID:%1] %2 - %3\n")
             .arg(b->id)
             .arg(QString::fromStdString(b->type))
             .arg(QString::fromStdString(b->nom));
    d += QString("    Conso: eau %1, élec %2 | Effet sat: %3\n")
             .arg(b->consommationEau, 0, 'f', 1)
             .arg(b->consommationElectricite, 0, 'f', 1)
             .arg(b->effetSatisfaction, 0, 'f', 1);

    if (auto m = dynamic_cast<const Maison*>(b)) {
        d += QString("    Maison: capacité %1, habitants %2\n")
                 .arg(m->capaciteHabitants)
                 .arg(m->habitantsActuels);
    } else if (auto u = dynamic_cast<const Usine*>(b)) {
        d += QString("    Usine: production %1, pollution %2\n")
                 .arg(u->productionRessources, 0, 'f', 1)
                 .arg(u->pollution, 0, 'f', 1);
    } else if (auto p = dynamic_cast<const Parc*>(b)) {
        d += QString("    Parc: surface %1, effet bien-être %2\n")
                 .arg(p->surface, 0, 'f', 1)
                 .arg(p->effetBienEtre, 0, 'f', 1);
    } else if (auto s = dynamic_cast<const Service*>(b)) {
        d += QString("    Service: coût entretien %1\n")
                 .arg(s->coutEntretien, 0, 'f', 1);
    }
    return d;
}

QString MainWindow::resumeCourtBatiment(const Batiment* b) const
{
    if (!b) return "";
    QString r = QString("%1 - %2 (ID:%3)")
                    .arg(QString::fromStdString(b->type))
                    .arg(QString::fromStdString(b->nom))
                    .arg(b->id);
    if (auto m = dynamic_cast<const Maison*>(b)) {
        r += QString(" | hab: %1/%2")
                 .arg(m->habitantsActuels)
                 .arg(m->capaciteHabitants);
    } else if (auto u = dynamic_cast<const Usine*>(b)) {
        r += QString(" | prod: %1, poll: %2")
                 .arg(u->productionRessources, 0, 'f', 1)
                 .arg(u->pollution, 0, 'f', 1);
    } else if (auto p = dynamic_cast<const Parc*>(b)) {
        r += QString(" | surf: %1, effet: %2")
                 .arg(p->surface, 0, 'f', 1)
                 .arg(p->effetBienEtre, 0, 'f', 1);
    } else if (auto s = dynamic_cast<const Service*>(b)) {
        r += QString(" | coût ent.: %1")
                 .arg(s->coutEntretien, 0, 'f', 1);
    }
    return r;
}

int MainWindow::indexSelectionBatiment() const
{
    auto item = ui->listWidgetBatiments->currentItem();
    if (!item) return -1;
    return ui->listWidgetBatiments->row(item);
}

Maison* MainWindow::maisonSelectionnee() const
{
    int idx = indexSelectionBatiment();
    if (idx < 0 || idx >= static_cast<int>(ville->batiments.size())) return nullptr;
    return dynamic_cast<Maison*>(ville->batiments[idx].get());
}

Service* MainWindow::serviceSelectionne() const
{
    int idx = indexSelectionBatiment();
    if (idx < 0 || idx >= static_cast<int>(ville->batiments.size())) return nullptr;
    return dynamic_cast<Service*>(ville->batiments[idx].get());
}

void MainWindow::mettreAJourDetailsSelection()
{
    int idx = indexSelectionBatiment();
    if (idx >= 0 && idx < static_cast<int>(ville->batiments.size())) {
        Batiment* b = ville->batiments[idx].get();
        statusBar()->showMessage(resumeCourtBatiment(b));
    } else {
        statusBar()->clearMessage();
    }
}

// ===== Interactions =====
void MainWindow::onBatimentDoubleClique(QListWidgetItem* item)
{
    if (!item) return;
    int idx = ui->listWidgetBatiments->row(item);
    if (idx < 0 || idx >= static_cast<int>(ville->batiments.size())) return;

    Batiment* b = ville->batiments[idx].get();
    QMessageBox::information(this, "Détails du bâtiment", detailsBatiment(b));

    if (auto m = dynamic_cast<Maison*>(b)) {
        // Proposer d'ajouter/retirer des habitants
        QStringList options = {"Ajouter", "Retirer", "Annuler"};
        bool ok = false;
        QString choix = QInputDialog::getItem(this, "Habitants",
                                              "Action:", options, 2, false, &ok);
        if (ok && (choix == "Ajouter" || choix == "Retirer")) {
            int nb = QInputDialog::getInt(this, "Nombre",
                                          "Nombre d'habitants:", 1, 1, 1000, 1, &ok);
            if (ok) {
                if (choix == "Ajouter") m->ajouterHabitants(nb);
                else m->retirerHabitants(nb);
                mettreAJourAffichage();
                rafraichirListeBatiments();
                ajouterLog(QString("Maison mise à jour: %1 habitants.").arg(m->habitantsActuels));
            }
        }
    }
}

void MainWindow::afficherMenuContexteBatiment(const QPoint& pos)
{
    QPoint globalPos = ui->listWidgetBatiments->viewport()->mapToGlobal(pos);
    auto item = ui->listWidgetBatiments->itemAt(pos);
    QMenu menu;
    QAction* actDetails = menu.addAction("Afficher détails");
    QAction* actAjouter = nullptr;
    QAction* actRetirer = nullptr;
    QAction* actAjouterService = menu.addAction("Ajouter Service...");
    QAction* actActiverService = menu.addAction("Activer Service (effet)");

    int idx = -1;
    if (item) {
        idx = ui->listWidgetBatiments->row(item);
        if (idx >= 0 && idx < static_cast<int>(ville->batiments.size())) {
            if (dynamic_cast<Maison*>(ville->batiments[idx].get())) {
                actAjouter = menu.addAction("Ajouter habitants...");
                actRetirer = menu.addAction("Retirer habitants...");
            }
        }
    }

    QAction* chosen = menu.exec(globalPos);
    if (!chosen) return;
    if (chosen == actDetails && item) {
        onBatimentDoubleClique(item);
    } else if (chosen == actAjouter) {
        ajouterHabitantsMaison();
    } else if (chosen == actRetirer) {
        retirerHabitantsMaison();
    } else if (chosen == actAjouterService) {
        ajouterService();
    } else if (chosen == actActiverService) {
        activerServiceSelectionne();
    }
}

void MainWindow::ajouterHabitantsMaison()
{
    if (Maison* m = maisonSelectionnee()) {
        bool ok = false;
        int nb = QInputDialog::getInt(this, "Ajouter habitants",
                                      "Nombre d'habitants à ajouter:", 1, 1, 1000, 1, &ok);
        if (ok) {
            m->ajouterHabitants(nb);
            mettreAJourAffichage();
            rafraichirListeBatiments();
            ajouterLog(QString("Ajout de %1 habitants (total: %2)").arg(nb).arg(m->habitantsActuels));
        }
    }
}

void MainWindow::retirerHabitantsMaison()
{
    if (Maison* m = maisonSelectionnee()) {
        bool ok = false;
        int nb = QInputDialog::getInt(this, "Retirer habitants",
                                      "Nombre d'habitants à retirer:", 1, 1, 1000, 1, &ok);
        if (ok) {
            m->retirerHabitants(nb);
            mettreAJourAffichage();
            rafraichirListeBatiments();
            ajouterLog(QString("Retrait de %1 habitants (total: %2)").arg(nb).arg(m->habitantsActuels));
        }
    }
}

void MainWindow::ajouterService()
{
    bool ok;
    QString nom = QInputDialog::getText(this, "Nouveau Service",
                                       "Nom du service:", QLineEdit::Normal,
                                       QString("Service_%1").arg(prochainId), &ok);
    if (ok && !nom.isEmpty()) {
        double cout = 400.0;
        if (ville->budget >= cout) {
            auto serv = std::make_unique<Service>(prochainId++, nom.toStdString(), 8.0, 5.0);
            ville->construireBatiment(std::move(serv), cout);
            mettreAJourAffichage();
            rafraichirListeBatiments();
            ajouterLog(QString("Service '%1' ajouté.").arg(nom));
        } else {
            QMessageBox::warning(this, "Budget insuffisant",
                                 QString("Coût: %1€, Budget: %2€").arg(cout).arg(ville->budget));
        }
    }
}

void MainWindow::activerServiceSelectionne()
{
    if (Service* s = serviceSelectionne()) {
        double effet = s->fournirService();
        ville->satisfaction += effet;
        if (ville->satisfaction > 100.0) ville->satisfaction = 100.0;
        mettreAJourAffichage();
        ajouterLog(QString("Service activé: +%1 sat").arg(effet, 0, 'f', 1));
    }
}
