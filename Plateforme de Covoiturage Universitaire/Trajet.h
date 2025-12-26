#ifndef TRAJET_H
#define TRAJET_H

#include <string>
#include <iostream>
#include <iomanip> 

using namespace std;

class Trajet {
public:
    int id;
    string depart, arrivee, date, heure, conducteur; // <-- Zedt heure hna
    int places;
    double prix;

    // Constructeur mbeddel (Zedna hr)
    Trajet(int id, string d, string a, string dt, string hr, int p, double pr, string c) 
        : id(id), depart(d), arrivee(a), date(dt), heure(hr), places(p), prix(pr), conducteur(c) {}

    // Convertir objet -> CSV (Zedna l'heure f l'wst)
    string toExcelFormat() const {
        // ID,DEPART,ARRIVEE,DATE,HEURE,PLACES,PRIX,CONDUCTEUR
        return to_string(id) + "," + depart + "," + arrivee + "," + date + "," + heure + "," + to_string(places) + "," + to_string(prix) + "," + conducteur;
    }

    void afficher() const {
        cout << "| ID:" << id << " | " << depart << " -> " << arrivee 
             << " | Le " << date << " a " << heure  // <-- Affichage Zwin
             << " | " << places << " pl"
             << " | " << prix << " DH"
             << " | Par: " << conducteur << endl;
    }
};
#endif