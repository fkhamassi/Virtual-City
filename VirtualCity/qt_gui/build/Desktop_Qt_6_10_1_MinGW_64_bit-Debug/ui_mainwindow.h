/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelTitre;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBoxInfos;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelNomVille;
    QLabel *labelCycle;
    QLabel *labelBudget;
    QLabel *labelPopulation;
    QLabel *labelSatisfaction;
    QLabel *labelNbBatiments;
    QGroupBox *groupBoxRessources;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelEau;
    QLabel *labelElectricite;
    QLabel *labelConsommationEau;
    QLabel *labelConsommationElec;
    QGroupBox *groupBoxActions;
    QGridLayout *gridLayout;
    QPushButton *btnAfficherEtat;
    QPushButton *btnLancerCycle;
    QPushButton *btnEvenement;
    QPushButton *btnAjouterMaison;
    QPushButton *btnAjouterUsine;
    QPushButton *btnAjouterParc;
    QPushButton *btnSupprimerBatiment;
    QPushButton *btnSauvegarder;
    QPushButton *btnCharger;
    QPushButton *btnGenererRapport;
    QGroupBox *groupBoxBatiments;
    QVBoxLayout *verticalLayout_4;
    QListWidget *listWidgetBatiments;
    QGroupBox *groupBoxLog;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *textEditLog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        labelTitre = new QLabel(centralwidget);
        labelTitre->setObjectName("labelTitre");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        labelTitre->setFont(font);
        labelTitre->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitre);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        groupBoxInfos = new QGroupBox(centralwidget);
        groupBoxInfos->setObjectName("groupBoxInfos");
        verticalLayout_2 = new QVBoxLayout(groupBoxInfos);
        verticalLayout_2->setObjectName("verticalLayout_2");
        labelNomVille = new QLabel(groupBoxInfos);
        labelNomVille->setObjectName("labelNomVille");
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        labelNomVille->setFont(font1);

        verticalLayout_2->addWidget(labelNomVille);

        labelCycle = new QLabel(groupBoxInfos);
        labelCycle->setObjectName("labelCycle");

        verticalLayout_2->addWidget(labelCycle);

        labelBudget = new QLabel(groupBoxInfos);
        labelBudget->setObjectName("labelBudget");

        verticalLayout_2->addWidget(labelBudget);

        labelPopulation = new QLabel(groupBoxInfos);
        labelPopulation->setObjectName("labelPopulation");

        verticalLayout_2->addWidget(labelPopulation);

        labelSatisfaction = new QLabel(groupBoxInfos);
        labelSatisfaction->setObjectName("labelSatisfaction");

        verticalLayout_2->addWidget(labelSatisfaction);

        labelNbBatiments = new QLabel(groupBoxInfos);
        labelNbBatiments->setObjectName("labelNbBatiments");

        verticalLayout_2->addWidget(labelNbBatiments);


        horizontalLayout->addWidget(groupBoxInfos);

        groupBoxRessources = new QGroupBox(centralwidget);
        groupBoxRessources->setObjectName("groupBoxRessources");
        verticalLayout_3 = new QVBoxLayout(groupBoxRessources);
        verticalLayout_3->setObjectName("verticalLayout_3");
        labelEau = new QLabel(groupBoxRessources);
        labelEau->setObjectName("labelEau");

        verticalLayout_3->addWidget(labelEau);

        labelElectricite = new QLabel(groupBoxRessources);
        labelElectricite->setObjectName("labelElectricite");

        verticalLayout_3->addWidget(labelElectricite);

        labelConsommationEau = new QLabel(groupBoxRessources);
        labelConsommationEau->setObjectName("labelConsommationEau");

        verticalLayout_3->addWidget(labelConsommationEau);

        labelConsommationElec = new QLabel(groupBoxRessources);
        labelConsommationElec->setObjectName("labelConsommationElec");

        verticalLayout_3->addWidget(labelConsommationElec);


        horizontalLayout->addWidget(groupBoxRessources);


        verticalLayout->addLayout(horizontalLayout);

        groupBoxActions = new QGroupBox(centralwidget);
        groupBoxActions->setObjectName("groupBoxActions");
        gridLayout = new QGridLayout(groupBoxActions);
        gridLayout->setObjectName("gridLayout");
        btnAfficherEtat = new QPushButton(groupBoxActions);
        btnAfficherEtat->setObjectName("btnAfficherEtat");

        gridLayout->addWidget(btnAfficherEtat, 0, 0, 1, 1);

        btnLancerCycle = new QPushButton(groupBoxActions);
        btnLancerCycle->setObjectName("btnLancerCycle");

        gridLayout->addWidget(btnLancerCycle, 0, 1, 1, 1);

        btnEvenement = new QPushButton(groupBoxActions);
        btnEvenement->setObjectName("btnEvenement");

        gridLayout->addWidget(btnEvenement, 0, 2, 1, 1);

        btnAjouterMaison = new QPushButton(groupBoxActions);
        btnAjouterMaison->setObjectName("btnAjouterMaison");

        gridLayout->addWidget(btnAjouterMaison, 1, 0, 1, 1);

        btnAjouterUsine = new QPushButton(groupBoxActions);
        btnAjouterUsine->setObjectName("btnAjouterUsine");

        gridLayout->addWidget(btnAjouterUsine, 1, 1, 1, 1);

        btnAjouterParc = new QPushButton(groupBoxActions);
        btnAjouterParc->setObjectName("btnAjouterParc");

        gridLayout->addWidget(btnAjouterParc, 1, 2, 1, 1);

        btnSupprimerBatiment = new QPushButton(groupBoxActions);
        btnSupprimerBatiment->setObjectName("btnSupprimerBatiment");

        gridLayout->addWidget(btnSupprimerBatiment, 2, 0, 1, 1);

        btnSauvegarder = new QPushButton(groupBoxActions);
        btnSauvegarder->setObjectName("btnSauvegarder");

        gridLayout->addWidget(btnSauvegarder, 2, 1, 1, 1);

        btnCharger = new QPushButton(groupBoxActions);
        btnCharger->setObjectName("btnCharger");

        gridLayout->addWidget(btnCharger, 2, 2, 1, 1);

        btnGenererRapport = new QPushButton(groupBoxActions);
        btnGenererRapport->setObjectName("btnGenererRapport");

        gridLayout->addWidget(btnGenererRapport, 3, 0, 1, 3);


        verticalLayout->addWidget(groupBoxActions);

        groupBoxBatiments = new QGroupBox(centralwidget);
        groupBoxBatiments->setObjectName("groupBoxBatiments");
        verticalLayout_4 = new QVBoxLayout(groupBoxBatiments);
        verticalLayout_4->setObjectName("verticalLayout_4");
        listWidgetBatiments = new QListWidget(groupBoxBatiments);
        listWidgetBatiments->setObjectName("listWidgetBatiments");

        verticalLayout_4->addWidget(listWidgetBatiments);


        verticalLayout->addWidget(groupBoxBatiments);

        groupBoxLog = new QGroupBox(centralwidget);
        groupBoxLog->setObjectName("groupBoxLog");
        verticalLayout_5 = new QVBoxLayout(groupBoxLog);
        verticalLayout_5->setObjectName("verticalLayout_5");
        textEditLog = new QTextEdit(groupBoxLog);
        textEditLog->setObjectName("textEditLog");
        textEditLog->setReadOnly(true);

        verticalLayout_5->addWidget(textEditLog);


        verticalLayout->addWidget(groupBoxLog);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "VirtualCity - Interface Graphique", nullptr));
        labelTitre->setText(QCoreApplication::translate("MainWindow", "VirtualCity - Gestion de Ville", nullptr));
        groupBoxInfos->setTitle(QCoreApplication::translate("MainWindow", "Informations Ville", nullptr));
        labelNomVille->setText(QCoreApplication::translate("MainWindow", "MaVille", nullptr));
        labelCycle->setText(QCoreApplication::translate("MainWindow", "Cycle: 0", nullptr));
        labelBudget->setText(QCoreApplication::translate("MainWindow", "Budget: 0 \342\202\254", nullptr));
        labelPopulation->setText(QCoreApplication::translate("MainWindow", "Population: 0", nullptr));
        labelSatisfaction->setText(QCoreApplication::translate("MainWindow", "Satisfaction: 0%", nullptr));
        labelNbBatiments->setText(QCoreApplication::translate("MainWindow", "B\303\242timents: 0", nullptr));
        groupBoxRessources->setTitle(QCoreApplication::translate("MainWindow", "Ressources", nullptr));
        labelEau->setText(QCoreApplication::translate("MainWindow", "Eau: 0", nullptr));
        labelElectricite->setText(QCoreApplication::translate("MainWindow", "\303\211lectricit\303\251: 0", nullptr));
        labelConsommationEau->setText(QCoreApplication::translate("MainWindow", "Consommation Eau: 0/cycle", nullptr));
        labelConsommationElec->setText(QCoreApplication::translate("MainWindow", "Consommation \303\211lec: 0/cycle", nullptr));
        groupBoxActions->setTitle(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        btnAfficherEtat->setText(QCoreApplication::translate("MainWindow", "Afficher \303\211tat", nullptr));
        btnLancerCycle->setText(QCoreApplication::translate("MainWindow", "Lancer Cycle", nullptr));
        btnEvenement->setText(QCoreApplication::translate("MainWindow", "\303\211v\303\251nement Al\303\251atoire", nullptr));
        btnAjouterMaison->setText(QCoreApplication::translate("MainWindow", "Ajouter Maison", nullptr));
        btnAjouterUsine->setText(QCoreApplication::translate("MainWindow", "Ajouter Usine", nullptr));
        btnAjouterParc->setText(QCoreApplication::translate("MainWindow", "Ajouter Parc", nullptr));
        btnSupprimerBatiment->setText(QCoreApplication::translate("MainWindow", "Supprimer B\303\242timent", nullptr));
        btnSauvegarder->setText(QCoreApplication::translate("MainWindow", "Sauvegarder", nullptr));
        btnCharger->setText(QCoreApplication::translate("MainWindow", "Charger", nullptr));
        btnGenererRapport->setText(QCoreApplication::translate("MainWindow", "G\303\251n\303\251rer Rapport", nullptr));
        groupBoxBatiments->setTitle(QCoreApplication::translate("MainWindow", "Liste des B\303\242timents", nullptr));
        groupBoxLog->setTitle(QCoreApplication::translate("MainWindow", "Journal d'\303\211v\303\251nements", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
