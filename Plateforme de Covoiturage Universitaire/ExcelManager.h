#ifndef EXCELMANAGER_H
#define EXCELMANAGER_H

#include <vector>
#include <fstream>
#include <sstream>
#include "Trajet.h"

class ExcelManager {
private:
    string filename = "database.csv";

public:
    void save(const vector<Trajet>& trajets) {
        ofstream file(filename);
        // Header Jdid (Fih HEURE)
        file << "ID,DEPART,ARRIVEE,DATE,HEURE,PLACES,PRIX,CONDUCTEUR" << endl; 
        for (const auto& t : trajets) file << t.toExcelFormat() << endl;
        file.close();
    }

    vector<Trajet> load() {
        vector<Trajet> liste;
        ifstream file(filename);
        if (!file.is_open()) return liste;

        string line;
        getline(file, line); // Na9ez Header

        while (getline(file, line)) {
            stringstream ss(line);
            string segment;
            vector<string> row;
            while (getline(ss, segment, ',')) row.push_back(segment);

            // Daba wellaw 8 d les colonnes (hit zedna Heure)
            if (row.size() >= 8) {
                // row[4] hiya HEURE
                Trajet t(stoi(row[0]), row[1], row[2], row[3], row[4], stoi(row[5]), stod(row[6]), row[7]);
                liste.push_back(t);
            }
        }
        file.close();
        return liste;
    }
};
#endif