#include "library.hpp"

int main(){

    std::cout << "Geben Sie den Dateipfad der JSON-Datei ein, welche Sie öffnen möchten: ";     //Bildschirmausgabe
    std::string dateipfad;
    std::cin >> dateipfad;                  //Einlesen des Dateipfades

    if(!std::__fs::filesystem::exists(dateipfad)){        //Überprüfen ob der eingebene Dateipfad existiert
        std::cout << "Der Dateipfad " << dateipfad << " existiert nicht. Möchten Sie eine neue JSON-Datei erstellen? Antwort: Ja oder Nein: ";
        std::string neueJSON;
        std::cin >> neueJSON;

        while(!(neueJSON == "Ja" || neueJSON == "Nein")){       //Schleife damit Ja oder Nein engegeben wird
            std::cerr << "Fehler: Es wurde nicht Ja oder Nein geantwortet. Antworten Sie mit Ja oder Nein: ";
            std::cin >> neueJSON;
        }

        if(neueJSON == "Ja"){                                   //Entscheidung ob JSON-Datei erstellt wird
            MusikBibliothek::erstelleJSON(dateipfad);           //Erstellen einer neuen JSON-Datei
        }
        else if(neueJSON == "Nein"){
            std::cout << "Es wird keine JSON-Datei erstellt." << std::endl;
            return 0;
        }
    }

    std::cout << "Möchten Sie " << dateipfad << " ausgeben? Ja oder Nein: ";
    std::string Ausgabe;
    std::cin >> Ausgabe;

    while (!(Ausgabe == "Ja" || Ausgabe == "Nein")){            //Schleife damit Ja oder Nein engegeben wird
        std::cerr << "Fehler:  Es wurde nicht mit Ja oder Nein geantwortet. Antworten Sie mit Ja oder Nein: " <<std::endl;
        std::cin >> Ausgabe;
    }

    if(Ausgabe == "Ja"){
        std::cout << "Wird ausgegeben" << std::endl;
        MusikBibliothek bibliothek(dateipfad);          //Übergabe an die Musikbibliothek-Funktion
        bibliothek.Ausgabe();                           //Ausgabe der Daten aus der JSON-Datei
    }
    else if(Ausgabe == "Nein") {
        return 0;
    }

    return 0;
};
