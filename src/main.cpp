#include "library.hpp"

int main(){

    std::cout << "Möchten Sie eine Bibliothek öffnen oder eine neue Bibliothek erstellen? Geben Sie ein Öffnen oder Neu: ";
    std::string OeffnenOderNeu;
    std::cin >> OeffnenOderNeu;

    while(!(OeffnenOderNeu == "Öffnen" || OeffnenOderNeu == "Neu")){
        std::cerr << "Fehler: Geben Sie Öffnen oder Neu ein: ";
        std::cin >> OeffnenOderNeu;
    }

    if(OeffnenOderNeu == "Öffnen"){
        std::cout << "Geben Sie den Dateipfad der JSON-Datei ein, welche Sie öffnen möchten: ";     //Bildschirmausgabe
        std::string dateipfad;
        std::cin >> dateipfad;                                          //Einlesen des Dateipfades

        if(!(std::__fs::filesystem::exists(dateipfad))){                  //Überprüfen ob der eingebene Dateipfad existiert
            std::cout << "Der Dateipfad " << dateipfad << " existiert nicht. Möchten Sie eine andere JSON-Datei öffnen? Antwort: Ja oder Nein: ";
            std::string OeffnenJSON;
            std::cin >> OeffnenJSON;

        while(!(OeffnenJSON == "Ja" || OeffnenJSON == "Nein")){       //Schleife damit Ja oder Nein engegeben wird
            std::cerr << "Fehler: Es wurde nicht Ja oder Nein geantwortet. Antworten Sie mit Ja oder Nein: ";
            std::cin >> OeffnenJSON;
            }

            if(OeffnenJSON == "Ja"){
                std::cout << "Geben Sie den Dateipfad der JSON-Datei ein, welche Sie öffnen möchten: ";     //Bildschirmausgabe
                std::string dateipfad2;
                std::cin >> dateipfad2;
                dateipfad = dateipfad2;
            }
            else{
                return 0;
            }
        }

        MusikBibliothek bibliothek(dateipfad);

        std::cout << "Was möchten Sie nun tun? Ausgabe, Titel hinzufügen, Suchen, Daten ändern, ...? Für Beenden 'X' eingeben: ";
        std::string auswahl;
        std::cin.ignore();
        std::getline(std::cin, auswahl);

        while (!(auswahl== "X")){

            if(auswahl == "Ausgabe"){
                bibliothek.Ausgabe();
                }

            else if(auswahl == "Titel hinzufügen"){
                std::vector<Lied> neueLieder = bibliothek.Einlesen();
                bibliothek.LiedHinzufügen(dateipfad, neueLieder);
            }

            else if(auswahl == "Suchen"){
                std::cout << "Möchten Sie nach einem Titel, einem Künstler, einem Album, einem Erscheinungsjahr, einem Genre oder einer Länge suchen? ";
                std::string suchkriterium;
                std::cin.ignore();
                std::cin >> suchkriterium;

                while((suchkriterium != "Titel")&&(suchkriterium != "Künstler")&&(suchkriterium != "Album")&&(suchkriterium != "Erscheinungsjahr")&&(suchkriterium != "Genre")&&(suchkriterium != "Länge")){
                    std::cerr << "Fehlerhafte Eingabe! Geben Sie nochmal ein nach was Sie suchen möchten: ";
                    std::cin >> suchkriterium;
                }

                std::cout << "Geben Sie ein nach was Sie suchen: ";
                std::string suche;
                std::cin >> suche;

                std::vector<Lied> gefundenelieder = bibliothek.suchen(suchkriterium, suche);

                if(!(gefundenelieder.empty())){
                    std::cout << "Diese Titel wurden gefunden: \n\n";
                    bibliothek.AusgabeTitel(gefundenelieder);
                }

            }

            else if(auswahl == "Daten ändern"){
                std::cout << "Geben Sie den Titel ein von dem Sie die Daten ändern möchten: ";
                std::string Titel;
                std::getline (std::cin, Titel);

                std::cout << "Welche Daten möchten Sie ändern? ";
                std::string Metadaten;
                std::getline (std::cin, Metadaten);

                std::cout << "In was soll es geändert werden? ";
                std::string neuerWert;
                std::getline (std::cin, neuerWert);

                std::vector<Lied> gefundenelieder = bibliothek.suchen("Titel", Titel);
                bibliothek.Datenaendern(gefundenelieder, Metadaten, neuerWert, dateipfad);
            }

            std::cout << "Möchten Sie noch etwas tun? Ausgabe, Titel hinzufügen, Suchen, Daten ändern, ...? Für Beenden 'X' eingeben. ";
            std::getline (std::cin, auswahl);
        }
    }


    else if(OeffnenOderNeu == "Neu"){
            std::cout << "Geben Sie den Namen der Bibliothek ein. (mit Endung .json): ";
            std::string neueJSON;
            std::cin >> neueJSON;

            MusikBibliothek::erstelleJSON(neueJSON);
            MusikBibliothek bibliothek(neueJSON);

            std::cout << "Möchten Sie nun Lieder zu ihrer Bibliothek hinzufügen? Ja oder Nein: ";
            std::string hinzufuegen;
            std::cin >> hinzufuegen;

            while(!(hinzufuegen == "Ja" || hinzufuegen == "Nein")){
                std::cerr << "Fehler:  Es wurde nicht mit Ja oder Nein geantwortet. Antworten Sie mit Ja oder Nein: ";
                std::cin >> hinzufuegen;
            }

            if (hinzufuegen == "Ja"){
                std::vector<Lied> neueLieder = bibliothek.Einlesen();
                bibliothek.LiedHinzufügen(neueJSON, neueLieder);
            }
            else {
                return 0;
            }
        }

    return 0;
};
