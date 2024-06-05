#include "library.hpp"

MusikBibliothek::MusikBibliothek(const std::string& dateiname){
    std::ifstream bibliothek(dateiname);                 //Einlesen der JSON-Datei

    if(bibliothek.is_open()){
        json dateien;
        bibliothek >> dateien;          //Einlesen der Daten aus der Musikbibliothek in 'dateien'

        for(const auto& lied : dateien["lieder"]){      //For-Schleife für das Durchlaufen jedes Elements im Array dateien
            Lied neuesLied{                             //Erstellung eines neuen Array mit Struktur Lied und Befüllung mit den Daten aus dateien
                lied["Album"],
                lied["Erscheinungsjahr"],
                lied["Genre"],
                lied["Künstler"],
                lied["Länge"],
                lied["Titel"]
            };
            Lieder.push_back(neuesLied);                //Hinzufügen des erstellten 'neuesLied' zu dem Vektor Lieder
        }
        bibliothek.close();
    }
    else {
        std::cerr << "Fehler: Datei " << dateiname << " konnte nicht geöffnet werden." << std::endl;     //Fehlermeldung, dass Datei nicht geöffnet werden konnte.
    }
}

void MusikBibliothek::Ausgabe() {
    if (Lieder.empty()) {
        std::cout << "Die Bibliothek enthält keine Lieder." << std::endl;       //Meldung wenn die Datei leer ist
        return;
    }
    else {
        std::cout << "Bibliothek wird ausgegeben." << std::endl;
    for (const auto& lied : Lieder) {                                           //For-Schleife für Ausgabe der Lieder aus Vektor Lieder
        std::cout << "Titel: " << lied.Titel << "\n"
                  << "Künstler: " << lied.Kuenstler << "\n"
                  << "Album: " << lied.Album << "\n"
                  << "Erscheinungsjahr: " << lied.Erscheinungsjahr << "\n"
                  << "Genre: " << lied.Genre << "\n"
                  << "Länge: " << lied.Laenge << "\n\n";
        }
    }
}

bool MusikBibliothek::erstelleJSON(const std::string& dateiname){           //Funktion für Erstellung einer neuen JSON-Datei
    json data = {{"lieder", json::array()}};

    std::ofstream datei(dateiname);

    if(datei.is_open()){
        datei<<data.dump(4);
        datei.close();
        std::cout << "Es wurde die leere JSON-Datei " << dateiname << " erstellt." << std::endl;
        return true;
    }
    else{
        std::cerr << "Fehler: Es konnte keine JSON-Datei erstellt werden." << std::endl;
        return false;
    }
}

bool MusikBibliothek::LiedHinzufügen(const Lied& neuesLied){
    Lieder.push_back(neuesLied);
    return true;
}

bool MusikBibliothek::speichern(const std::string& dateiname){
    json dateien;

    for(const auto& lied : Lieder){
        json einzelneslied = {
            {"Titel", lied.Titel},
            {"Künstler", lied.Kuenstler},
            {"Album", lied.Album},
            {"Erscheinungsjahr", lied.Erscheinungsjahr},
            {"Genre", lied.Genre},
            {"Länge", lied.Laenge}
        };

        dateien["lieder"].push_back(einzelneslied);
    }

    std::ofstream datei(dateiname);

    if(datei.is_open()){
    datei << std::setw(4) << dateien;
    datei.close();
    return true;
    }
    else{
        return false;
    }
}
