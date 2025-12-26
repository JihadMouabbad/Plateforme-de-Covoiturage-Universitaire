#ifndef USERMANAGER_H
#define USERMANAGER_H
#include <vector>
#include <fstream>
#include <sstream>
#include "Utilisateur.h"

class UserManager {
    string filename = "users.csv";
public:
    // Inscription
    void inscrire(string nom, string email, string pass) {
        ofstream file(filename, ios::app);
        file << nom << "," << email << "," << pass << endl;
        file.close();
    }

    // Login (Kayrj3 smiya ila nja7, sin "VIDE")
    string seConnecter(string email, string pass) {
        ifstream file(filename);
        string line, n, e, p;
        while(getline(file, line)) {
            stringstream ss(line);
            getline(ss, n, ','); getline(ss, e, ','); getline(ss, p, ',');
            if(e == email && p == pass) return n; // Nja7
        }
        return ""; // Fchel
    }
};
#endif