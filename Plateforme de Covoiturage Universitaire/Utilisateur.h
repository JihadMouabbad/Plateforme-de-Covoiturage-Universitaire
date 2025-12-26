#ifndef UTILISATEUR_H
#define UTILISATEUR_H
#include <string>
using namespace std;

class Utilisateur {
public:
    string nom, email, password;
    
    Utilisateur(string n, string e, string p) : nom(n), email(e), password(p) {}
    
    string toCSV() const { return nom + "," + email + "," + password; }
};
#endif