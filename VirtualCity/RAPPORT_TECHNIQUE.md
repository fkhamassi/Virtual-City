# Rapport Technique - VirtualCity
## Simulation de Ville Virtuelle en C++

---

## 1. Introduction

**VirtualCity** est une application console en C++ qui simule la gestion d'une ville virtuelle. Le projet permet de créer et gérer différents types de bâtiments, de surveiller les ressources (eau, électricité), de maintenir la satisfaction des habitants, et de réagir à des événements aléatoires.

### Objectifs du projet
- Créer une simulation de ville avec différents bâtiments (maisons, usines, parcs, services)
- Gérer les ressources de manière optimale (eau, électricité, budget, pollution)
- Assurer le bien-être des habitants en maintenant leur satisfaction
- Survivre à des événements imprévus qui bouleversent la ville
- Appliquer les principes de la programmation orientée objet (POO)

---

## 2. Architecture du Projet

### 2.1 Structure des fichiers

Le projet est organisé en modules logiques avec séparation des headers (.h) et implémentations (.cpp) :

```
VirtualCity/
├── src/
│   ├── Batiment.h / Batiment.cpp      # Classe de base
│   ├── Maison.h / Maison.cpp          # Classe dérivée : habitations
│   ├── Usine.h / Usine.cpp            # Classe dérivée : production/pollution
│   ├── Parc.h / Parc.cpp              # Classe dérivée : bien-être
│   ├── Service.h / Service.cpp        # Classe dérivée : services urbains
│   ├── Ville.h / Ville.cpp            # Gestion de la ville
│   ├── Simulation.h / Simulation.cpp  # Logique de simulation
│   └── main.cpp                       # Interface utilisateur (menu console)
├── README.md                          # Instructions d'utilisation
└── RAPPORT_TECHNIQUE.md               # Ce document

```

### 2.2 Diagramme de classes simplifié

```
        Batiment (classe de base)
             |
    +--------+--------+--------+
    |        |        |        |
  Maison   Usine    Parc    Service
  
  Ville (composition)
    - contient: vector<unique_ptr<Batiment>>
    - gère: ressources, budget, satisfaction
    
  Simulation
    - utilise: Ville*
    - orchestre: cycles, événements
```

---

## 3. Principes de Programmation Orientée Objet Utilisés

### 3.1 Héritage

**Classe de base : `Batiment`**
- Contient les attributs communs : `id`, `nom`, `type`, `consommationEau`, `consommationElectricite`, `effetSatisfaction`
- Méthodes virtuelles : `afficherDetails()`, `calculerImpactRessources()`
- Permet le polymorphisme pour traiter tous les bâtiments de manière uniforme

**Classes dérivées :**
1. **`Maison`** : gère la capacité d'habitants
   - Attributs spécifiques : `capaciteHabitants`, `habitantsActuels`
   - Méthodes : `ajouterHabitants()`, `retirerHabitants()`

2. **`Usine`** : production de ressources et pollution
   - Attributs spécifiques : `productionRessources`, `pollution`
   - Méthodes : `produireRessources()`, `calculerPollution()`

3. **`Parc`** : améliore le bien-être
   - Attributs spécifiques : `surface`, `effetBienEtre`
   - Méthodes : `ameliorerBienEtre()`

4. **`Service`** : services urbains (nettoyage, déneigement, etc.)
   - Attributs spécifiques : `coutEntretien`
   - Méthodes : `fournirService()`

### 3.2 Composition

La classe `Ville` contient une collection de bâtiments :
```cpp
vector<unique_ptr<Batiment>> batiments;
```

Cette approche permet :
- De gérer tous les types de bâtiments dans une seule structure
- D'appliquer le polymorphisme (dynamic_cast pour identifier les types)
- De libérer automatiquement la mémoire grâce à `unique_ptr`

### 3.3 Encapsulation

Chaque classe expose des méthodes publiques claires :
- `Ville` : `ajouterBatiment()`, `supprimerBatiment()`, `construireBatiment()`, `sauvegarder()`, `charger()`
- `Simulation` : `demarrerCycle()`, `terminerCycle()`, `declencherEvenement()`

Les détails d'implémentation sont cachés dans les fichiers `.cpp`.

---

## 4. Choix Techniques Importants

### 4.1 Gestion de la mémoire : `unique_ptr`

**Choix initial :** Utilisation de pointeurs bruts (`new`/`delete`)
**Amélioration appliquée :** Conversion vers `std::unique_ptr`

**Justification :**
- **Sécurité** : `unique_ptr` libère automatiquement la mémoire, évitant les fuites mémoire
- **Simplicité** : pas besoin de `delete` manuel dans le destructeur
- **Clarté de propriété** : un seul propriétaire du pointeur (transfert via `std::move`)
- **Moderne et pédagogique** : enseigne les bonnes pratiques C++11/14/17

**Exemple d'utilisation :**
```cpp
// Création d'un bâtiment
auto maison = make_unique<Maison>(1, "Maison Centre", 6);

// Transfert de propriété à la ville
ville.ajouterBatiment(move(maison));

// Pas besoin de delete, unique_ptr s'en charge automatiquement
```

### 4.2 Budget et décisions automatiques

**Problème initial :** Le budget existait mais n'était pas utilisé

**Solution implémentée :**
1. **Coûts de construction** : méthode `construireBatiment(batiment, cout)` déduit le coût du budget
2. **Coûts d'entretien** : chaque cycle applique des coûts d'entretien par type de bâtiment
3. **Décisions automatiques** : 
   - Si eau < 200 → construction automatique d'une station d'eau
   - Si électricité < 200 → construction d'une centrale électrique
   - Si satisfaction < 50 → embauche d'un service de nettoyage

**Justification :**
- Simule une gestion réaliste des finances urbaines
- Évite la faillite complète de la ville (décisions automatiques de secours)
- Enseigne les concepts de seuils et de réactivité dans une simulation

### 4.3 Sauvegarde et chargement

**Format choisi :** Fichier texte simple (format ligne par ligne avec séparateur `|`)

**Exemple de sauvegarde :**
```
Ville:VirtualCity
Budget:984
Population:0
Satisfaction:100
Eau:941
Electricite:1029
Batiments:3
Maison|1|Maison Centre|7.5|4.5|2|M|6|0
Usine|2|Usine Electrique|20|30|-5|U|50|10
Parc|3|Parc Central|2|1|12|P|200|12
```

**Justification :**
- **Lisible par un humain** : facile à déboguer et vérifier
- **Simple à parser** : utilisation de `getline()` et `substr()`
- **Extensible** : ajout de nouveaux champs facilement
- **Pédagogique** : montre la manipulation de fichiers en C++

**Méthode `charger()` :**
- Lit les données ligne par ligne
- Reconstruit les bâtiments selon leur type (U, M, P, S)
- Utilise `make_unique` pour créer les objets
- Gère les erreurs d'ouverture de fichier

### 4.4 Événements aléatoires

**Liste des événements implémentés :**
1. **Nuée de pigeons géants** : -15% satisfaction
2. **Panne de courant** : +50% consommation électricité
3. **Grève des jardiniers** : effet des parcs réduit de 50%, -20% satisfaction
4. **Panne des transports publics** : -25 satisfaction
5. **Tempête de neige** : production usines réduite de 50%, -10 satisfaction

**Mécanisme :**
```cpp
int r = rand() % 5;  // Génère nombre aléatoire 0-4
switch (r) {
    case 0: // pigeons...
    case 1: // panne...
    // etc.
}
```

**Justification :**
- Rend la simulation dynamique et imprévisible
- Force le joueur à gérer des crises
- Simule la réalité des événements urbains
- Enseigne la gestion d'état et les modifications temporaires

---

## 5. Logique de Simulation (Cycle)

### 5.1 Étapes d'un cycle

Chaque cycle (`demarrerCycle()`) suit ces étapes :

1. **Calcul de consommation totale** (eau + électricité)
2. **Déduction des ressources** avec gestion des pénuries
3. **Application des coûts d'entretien** par type de bâtiment
4. **Production des usines** (ressources + pollution)
5. **Effet des parcs** sur satisfaction
6. **Décisions automatiques** (construction si seuils critiques)
7. **Mise à jour de la population** (somme habitants des maisons)
8. **Recalcul de la satisfaction globale**

### 5.2 Formules utilisées

**Satisfaction :**
```cpp
// Effet moyen des bâtiments
double effetMoyen = sommeEffets / batiments.size();
double nouvelleSatisfaction = satisfaction + effetMoyen;
// Bornes : [0, 100]
```

**Impact pollution :**
```cpp
ville->satisfaction -= pollutionTotale * 0.1;
```

**Effet parcs :**
```cpp
ville->satisfaction += effetParcs * 0.05;
```

**Justification des coefficients :**
- `0.1` pour pollution : impact modéré mais visible
- `0.05` pour parcs : effet progressif sur plusieurs cycles
- Valeurs ajustées pour équilibrer la simulation

---

## 6. Choix de Conception pour Débutants

### 6.1 `using namespace std;`

**Appliqué dans tous les fichiers** comme demandé dans le cahier des charges.

**Justification :**
- Simplifie la lecture pour débutants (pas de `std::` partout)
- Réduit la verbosité du code
- Facilite la compréhension des concepts de base

**Note :** Dans un projet professionnel, on éviterait cela dans les headers.

### 6.2 Commentaires ultra-détaillés

**Approche adoptée :**
- Commentaire pour chaque bloc logique
- Explication des paramètres et retours de fonction
- Clarification des concepts (unique_ptr, move, dynamic_cast, etc.)

**Exemple :**
```cpp
// pour chaque batiment (auto& = unique_ptr<Batiment>)
for (const auto& b : ville->batiments) {
    // test si c'est une Usine (.get() donne pointeur brut)
    Usine* u = dynamic_cast<Usine*>(b.get());
    if (u != nullptr) { // si c'est bien une usine
        productionTotale += u->produireRessources(); // ajoute la production
    }
}
```

### 6.3 Pas de templates ni de concepts avancés

**Évité :**
- Templates complexes
- Métaprogrammation
- Lambda expressions avancées
- Concepts C++20

**Utilisé :**
- Héritage simple et clair
- `vector` (conteneur standard de base)
- `unique_ptr` (expliqué simplement)
- `dynamic_cast` (pour tester les types)

---

## 7. Tests et Validation

### 7.1 Compilation

**Compilateur utilisé :** g++ avec C++17

**Commande :**
```powershell
g++ -std=c++17 *.cpp -O2 -o VirtualCity.exe
```

**Résultat :** Compilation sans erreurs ni warnings.

### 7.2 Tests fonctionnels effectués

| Test | Description | Résultat |
|------|-------------|----------|
| Affichage état initial | Afficher ville avec 3 bâtiments | ✅ Pass |
| Lancer 2 cycles | Vérifier consommation, budget, satisfaction | ✅ Pass |
| Événement aléatoire | Déclencher événement et vérifier impacts | ✅ Pass |
| Sauvegarder ville | Créer fichier ville.txt | ✅ Pass |
| Charger ville | Recharger depuis fichier | ✅ Pass |
| Générer rapport | Créer rapport.txt | ✅ Pass |
| Décision auto (eau basse) | Forcer eau < 200 → station construite | ✅ Pass |
| Décision auto (satisfaction) | Forcer sat < 50 → service créé | ✅ Pass |
| Ajout bâtiment manuel | Ajouter maison, usine, parc via menu | ✅ Pass |
| Suppression bâtiment | Supprimer par ID | ✅ Pass |

### 7.3 Gestion des erreurs

**Cas gérés :**
- Budget insuffisant pour construction → message d'erreur, construction annulée
- Fichier sauvegarde introuvable → message d'erreur, retour `false`
- Entrée utilisateur invalide (non numérique) → `cin.clear()`, redemander
- Bâtiment ID inexistant → message "Aucun batiment trouvé"
- Pénurie ressources → message d'alerte, satisfaction réduite

---

## 8. Points Forts du Projet

1. **Architecture claire et modulaire** : séparation en classes logiques
2. **Respect des principes POO** : héritage, polymorphisme, encapsulation
3. **Gestion mémoire moderne** : `unique_ptr` pour éviter fuites
4. **Fonctionnalités complètes** : sauvegarde/chargement, décisions auto, événements
5. **Code pédagogique** : commentaires détaillés, pas de concepts avancés
6. **Testé et fonctionnel** : compilation réussie, tests manuels validés

---

## 9. Limitations et Améliorations Possibles

### 9.1 Limitations actuelles

- **Pas d'interface graphique** : version console uniquement
- **Décisions automatiques simples** : pas d'algorithme d'optimisation avancé
- **Événements non paramétrables** : probabilités fixes
- **Pas de multi-threading** : simulation séquentielle
- **Format sauvegarde basique** : pas de JSON/XML

### 9.2 Améliorations futures

1. **Interface graphique Qt** :
   - Fenêtre principale avec carte de la ville
   - Boutons pour chaque action
   - Graphiques de statistiques (budget, satisfaction au fil du temps)

2. **Système économique avancé** :
   - Revenus (taxes des habitants)
   - Prêts bancaires
   - Investissements à long terme

3. **IA de gestion** :
   - Algorithme génétique pour optimiser placements de bâtiments
   - Prédiction des besoins futurs
   - Stratégies adaptatives

4. **Multijoueur** :
   - Comparaison de villes entre joueurs
   - Mode compétitif (meilleure satisfaction)

5. **Sauvegarde avancée** :
   - Format JSON ou XML structuré
   - Historique complet des événements
   - Statistiques détaillées

---

## 10. Conclusion

Le projet **VirtualCity** remplit les objectifs du cahier des charges :
- ✅ Classes bien organisées avec headers séparés
- ✅ Principes POO respectés (héritage, composition, polymorphisme)
- ✅ Gestion des ressources (eau, électricité, budget, pollution)
- ✅ Système de satisfaction des habitants
- ✅ Événements aléatoires implémentés
- ✅ Code très commenté et accessible aux débutants
- ✅ Sauvegarde/chargement fonctionnel
- ✅ Décisions automatiques pour gérer la ville

Le code est **compilable, testé et fonctionnel**. Il offre une base solide pour apprendre la POO en C++ tout en simulant une gestion de ville réaliste et dynamique.

---

**Auteur :** Projet VirtualCity  
**Date :** 30 novembre 2025  
**Langage :** C++17  
**Compilateur testé :** g++ (MinGW/GCC)
