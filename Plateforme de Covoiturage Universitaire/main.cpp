#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "Trajet.h"
#include "ExcelManager.h"
#include "UserManager.h"

using namespace std;

// Globals
vector<Trajet> mesTrajets;
ExcelManager db;
UserManager um;
string utilisateurConnecte = ""; // Hna kan-khbiw chkon connecte

void vider() { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

// Helpers
int getNextId() {
    int maxId = 0;
    for(const auto& t : mesTrajets) if(t.id > maxId) maxId = t.id;
    return maxId + 1;
}

bool comparerPrix(const Trajet& a, const Trajet& b) { return a.prix < b.prix; }
bool comparerID(const Trajet& a, const Trajet& b) { return a.id < b.id; }

int main() {
    // ---------------- PHASE 1: LOGIN / INSCRIPTION ----------------
    cout << "=== BIENVENUE SUR COVOIT'FAC ===" << endl;
    
    while(utilisateurConnecte == "") {
        cout << "\n1. Se connecter\n2. Creer un compte\n0. Quitter\nChoix: ";
        int c; cin >> c; vider();
        
        if (c == 0) return 0;
        
        if (c == 1) {
            string e, p;
            cout << "Email : "; getline(cin, e);
            cout << "Mot de passe : "; getline(cin, p);
            utilisateurConnecte = um.seConnecter(e, p);
            if(utilisateurConnecte == "") cout << ">> Erreur : Email ou mot de passe incorrect." << endl;
        }
        else if (c == 2) {
            string n, e, p;
            cout << "Nom complet : "; getline(cin, n);
            cout << "Email : "; getline(cin, e);
            cout << "Mot de passe : "; getline(cin, p);
            um.inscrire(n, e, p);
            cout << ">> Compte cree ! Connectez-vous maintenant." << endl;
        }
    }

    // ---------------- PHASE 2: SYSTEME COVOITURAGE ----------------
    mesTrajets = db.load();
    cout << "\n>> Bonjour " << utilisateurConnecte << " ! Connexion reussie." << endl;

    int choix = -1;
    while (choix != 0) {
        cout << "\n==========================================" << endl;
        cout << "        MENU PRINCIPAL (User: " << utilisateurConnecte << ")" << endl;
        cout << "==========================================" << endl;
        cout << "1. Afficher les trajets (Par defaut)" << endl;
        cout << "2. Ajouter un trajet" << endl;
        cout << "3. Modifier un trajet" << endl;
        cout << "4. Supprimer un trajet" << endl;
        cout << "5. Rechercher (Destination)" << endl;
        cout << "6. Trier par Prix (Moins cher)" << endl;
        cout << "7. Statistiques" << endl;
      //  cout << "8. ACTUALISER (Refresh)" << endl;
        cout << "0. Deconnexion & Quitter" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Votre choix : "; 
        cin >> choix; vider();

        // 1. AFFICHER
        if (choix == 1) {
            sort(mesTrajets.begin(), mesTrajets.end(), comparerID); // Remettre ordre ID
            cout << "\n--- LISTE DES TRAJETS ---" << endl;
            if (mesTrajets.empty()) cout << "Aucun trajet." << endl;
            else for (const auto& t : mesTrajets) t.afficher();
        }
        
        // 2. AJOUTER
        else if (choix == 2) {
            string d, a, date, heure; // <-- Zedt variable
            int p; double prix;
            
            cout << "Depart : "; getline(cin, d);
            cout << "Arrivee : "; getline(cin, a);
            cout << "Date (JJ/MM) : "; getline(cin, date);
            cout << "Heure (HH:MM) : "; getline(cin, heure); // <-- Kan-tlbo sa3a
            cout << "Places : "; cin >> p;
            cout << "Prix : "; cin >> prix; vider();

            // Creation avec Heure
            Trajet nouveau(getNextId(), d, a, date, heure, p, prix, utilisateurConnecte);
            mesTrajets.push_back(nouveau);
            db.save(mesTrajets);
            cout << ">> Trajet publie a " << heure << " !" << endl;
        }

        // 3. MODIFIER
        else if (choix == 3) {
            int id; cout << "ID a modifier : "; cin >> id; vider();
            bool tr = false;
            for (auto& t : mesTrajets) {
                if (t.id == id) {
                    // Bonus: Verifier wach dyalo
                    if(t.conducteur != utilisateurConnecte) {
                        cout << ">> Erreur: Ce n'est pas votre trajet !" << endl;
                        tr = true; break;
                    }
                    cout << "Nouveau Prix : "; cin >> t.prix; vider();
                    db.save(mesTrajets);
                    cout << ">> Prix modifie !" << endl;
                    tr = true; break;
                }
            }
            if (!tr) cout << ">> ID introuvable ou acces refuse." << endl;
        }

        // 4. SUPPRIMER
        else if (choix == 4) {
            int id; cout << "ID a supprimer : "; cin >> id; vider();
            for (auto it = mesTrajets.begin(); it != mesTrajets.end(); ++it) {
                if (it->id == id) {
                    if(it->conducteur != utilisateurConnecte) {
                         cout << ">> Erreur: Vous ne pouvez supprimer que vos trajets." << endl;
                    } else {
                        mesTrajets.erase(it);
                        db.save(mesTrajets);
                        cout << ">> Trajet supprime." << endl;
                    }
                    break;
                }
            }
        }

        // 5. RECHERCHER
        else if (choix == 5) {
            string v; cout << "Destination : "; getline(cin, v);
            cout << "\n--- Resultats ---" << endl;
            bool found = false;
            for(const auto& t : mesTrajets) {
                if(t.arrivee == v) { t.afficher(); found = true; }
            }
            if(!found) cout << "Walou." << endl;
        }

        // 6. TRIER
        else if (choix == 6) {
            sort(mesTrajets.begin(), mesTrajets.end(), comparerPrix);
            cout << "\n--- CLASSEMENT PAR PRIX ---" << endl;
            for(const auto& t : mesTrajets) t.afficher();
        }

        // 7. STATS
        else if (choix == 7) {
            if(mesTrajets.empty()) cout << "Pas de donnees." << endl;
            else {
                double total = 0;
                for(const auto& t : mesTrajets) total += t.prix;
                cout << "\n--- STATISTIQUES ---" << endl;
                cout << "Total Trajets: " << mesTrajets.size() << endl;
                cout << "Prix Moyen: " << (total/mesTrajets.size()) << " DH" << endl;
            }
        }

        // 8. REFRESH
       // else if (choix == 8) {
         //   mesTrajets = db.load();
           // cout << ">> Actualisation reussie." << endl;
       // }
    }
    
    return 0;
}