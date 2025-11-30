VirtualCity - Simulation de Ville Virtuelle

But: fournir un exemple simple et tr\u00e8s comment\u00e9 en C++ (console) pour apprendre la structure OOP.

Am\u00e9liorations version finale:
- Gestion m\u00e9moire s\u00e9curis\u00e9e avec `unique_ptr` (plus besoin de `new`/`delete` manuel)
- Budget r\u00e9aliste avec co\u00fbts de construction et entretien par cycle
- D\u00e9cisions automatiques simples (construction auto station eau/centrale/service si seuils atteints)
- Sauvegarde/chargement de ville (options menu 8/10)
- G\u00e9n\u00e9ration de rapport texte (option 9)
- Commentaires d\u00e9taill\u00e9s pour d\u00e9butants dans tous les fichiers

Compilation (Windows avec g++) :

Ouvrez un terminal PowerShell et ex\u00e9cutez :

```powershell
# Aller dans le dossier contenant les sources
cd D:/CoPilot/VirtualCity/src
# Compiler tous les .cpp
g++ -std=c++17 *.cpp -o VirtualCity.exe
# Lancer le programme
./VirtualCity.exe
```

Notes :
- Le code est volontairement simple et tr\u00e8s comment\u00e9 pour un d\u00e9butant.
- Tous les fichiers placent `using namespace std;` en haut, comme demand\u00e9.
- Le projet est en console pour rester accessible ; ajouter une interface Qt est possible mais d\u00e9passe la port\u00e9e d'un exemple p\u00e9dagogique.

Sauvegarde / Rapport:
- Vous pouvez sauvegarder l'\u00e9tat de la ville via le menu (option 8) et generer un rapport texte (option 9).
- Charger une ville sauvegard\u00e9e (option 10).

Compilation et test rapide (PowerShell) :

```powershell
cd D:/CoPilot/VirtualCity/src
g++ -std=c++17 *.cpp -o D:/CoPilot/VirtualCity/VirtualCity.exe
cd ..
./VirtualCity.exe
```

Fichiers principaux :
- `src/Batiment.h` / `src/Batiment.cpp` : classe de base
- `src/Maison.h` / `src/Maison.cpp` : d\u00e9riv\u00e9e Maison
- `src/Usine.h` / `src/Usine.cpp` : d\u00e9riv\u00e9e Usine
- `src/Parc.h` / `src/Parc.cpp` : d\u00e9riv\u00e9e Parc
- `src/Service.h` / `src/Service.cpp` : d\u00e9riv\u00e9e Service
- `src/Ville.h` / `src/Ville.cpp` : classe Ville avec gestion des b\u00e2timents
- `src/Simulation.h` / `src/Simulation.cpp` : logique de simulation (cycles, \u00e9v\u00e9nements)
- `src/main.cpp` : interface console simple

Am\u00e9liorations possibles :
- Ajouter GUI (Qt) pour une exp\u00e9rience visuelle.
- Enrichir la logique \u00e9conomique (revenus, taxes, optimisations avanc\u00e9es).

