# Rapport Technique - VirtualCity
## Simulation de Ville Virtuelle en C++

---

## 1. Introduction

**VirtualCity** est une simulation de gestion de ville en C++ avec interface console et Qt. Le joueur gère des bâtiments, des ressources (eau, électricité, budget), et doit maintenir la satisfaction des habitants face à des événements imprévus.

### Objectifs
- Gérer différents types de bâtiments (maisons, usines, parcs, services)
- Optimiser les ressources et le budget
- Maintenir la satisfaction des habitants
- Réagir aux événements aléatoires

---

## 2. Architecture

### Structure des fichiers
```
VirtualCity/
├── src/
│   ├── Batiment.h/.cpp     # Classe de base
│   ├── Maison.h/.cpp       # Habitations
│   ├── Usine.h/.cpp        # Production + pollution
│   ├── Parc.h/.cpp         # Bien-être
│   ├── Service.h/.cpp      # Services urbains
│   ├── Ville.h/.cpp        # Conteneur principal
│   ├── Simulation.h/.cpp   # Moteur de simulation
│   └── main.cpp            # Menu console
└── qt_gui/                 # Interface Qt
```

### Hiérarchie des classes
```
Batiment (base)
  ├── Maison      (capacité habitants)
  ├── Usine       (production + pollution)
  ├── Parc        (améliore satisfaction)
  └── Service     (nettoyage, déneigement)

Ville              (composition)
  └── vector<unique_ptr<Batiment>>

Simulation         (orchestration)
  └── gère cycles et événements
```

---

## 3. Principes POO Utilisés

### Héritage
**Batiment (base)** : `id`, `nom`, `type`, `consommationEau`, `consommationElectricite`, `effetSatisfaction`

**Classes dérivées** :
- **Maison** : `capaciteHabitants`, `habitantsActuels`
- **Usine** : `productionRessources`, `pollution`
- **Parc** : `surface`, `effetBienEtre`
- **Service** : `coutEntretien`

### Polymorphisme
Méthodes virtuelles : `afficherDetails()`, `calculerImpactRessources()`

### Composition
```cpp
class Ville {
    vector<unique_ptr<Batiment>> batiments;  // Tous types confondus
};
```

---

## 4. Choix Techniques

### Gestion mémoire : `unique_ptr`
- Libération automatique (pas de `delete`)
- Évite les fuites mémoire
- Transfert de propriété avec `std::move()`

```cpp
auto maison = make_unique<Maison>(1, "Centre", 6);
ville.ajouterBatiment(move(maison));  // Transfert
```

### Budget et décisions automatiques
- **Construction** : coût déduit du budget
- **Entretien** : coût par cycle selon le type
- **Décisions auto** :
  - Eau < 200 → Station d'eau
  - Électricité < 200 → Centrale
  - Satisfaction < 50 → Service nettoyage

### Sauvegarde/Chargement
Format texte simple :
```
Ville:MaVille
Budget:984
Population:12
Satisfaction:75.5
Eau:850
Electricite:720
Batiments:3
Maison|1|Centre|7.5|4.5|2|M|6|4
Usine|2|Electrique|20|30|-5|U|50|10
Parc|3|Central|2|1|12|P|200|12
```

### Événements aléatoires
1. **Pigeons géants** : -15% satisfaction
2. **Panne électrique** : +50% consommation
3. **Grève jardiniers** : parcs -50% effet, -20% satisfaction
4. **Panne transports** : -25 satisfaction
5. **Tempête neige** : usines -50% production, -10 satisfaction

---

## 5. Logique de Simulation

### Cycle de simulation
1. Calcul consommation (eau + électricité)
2. Déduction ressources + pénalités si pénurie
3. Coûts d'entretien
4. Production usines + pollution
5. Effet parcs sur satisfaction
6. Décisions automatiques
7. Mise à jour population
8. Recalcul satisfaction globale

### Formules clés
```cpp
// Satisfaction
satisfaction += effetMoyenBatiments;
satisfaction -= pollutionTotale * 0.1;
satisfaction += effetParcs * 0.05;
// Bornes [0, 100]
```

---

## 6. Tests et Validation

### Compilation
```powershell
g++ -std=c++17 *.cpp -o VirtualCity.exe
```
✅ Compilation sans erreurs

### Tests fonctionnels
| Test | Résultat |
|------|----------|
| Cycles de simulation | ✅ |
| Événements aléatoires | ✅ |
| Sauvegarde/Chargement | ✅ |
| Génération rapport | ✅ |
| Décisions automatiques | ✅ |
| Ajout/Suppression bâtiments | ✅ |

### Gestion d'erreurs
- Budget insuffisant → construction annulée
- Fichier introuvable → message d'erreur
- Pénurie ressources → alerte + baisse satisfaction

---

## 7. Points Forts

✅ Architecture POO claire et modulaire  
✅ Gestion mémoire moderne (`unique_ptr`)  
✅ Double interface (console + Qt)  
✅ Sauvegarde/Chargement fonctionnel  
✅ Événements aléatoires créatifs  
✅ Code commenté et lisible  
✅ Décisions automatiques intelligentes  

---

## 8. Améliorations Possibles

- 🗺️ Carte visuelle 2D de la ville
- 📊 Graphiques d'évolution (ressources, satisfaction)
- 💰 Système économique (taxes, revenus)
- 🏛️ Nouveaux bâtiments (hôpital, école, police)
- 🌐 Mode multijoueur
- 🤖 IA d'optimisation

---

## 9. Conclusion

Le projet **VirtualCity** respecte toutes les exigences :
- ✅ Classes organisées avec headers séparés
- ✅ Principes POO (héritage, composition, polymorphisme)
- ✅ Gestion ressources complète
- ✅ Satisfaction des habitants
- ✅ Événements aléatoires implémentés

Le code est **compilable, testé et fonctionnel**, offrant une simulation de ville réaliste et dynamique.

---

**Langage** : C++17  
**Compilateur** : g++ (MinGW/GCC)  
**Interface** : Console + Qt 6.x

