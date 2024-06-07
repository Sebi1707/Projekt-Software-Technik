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
        std::cin >> dateipfad;                                              //Einlesen des Dateipfades

        if(!(std::__fs::filesystem::exists(dateipfad))){                    //Überprüfen ob der eingebene Dateipfad existiert
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

        MusikBibliothek bibliothek(dateipfad);                              //Initialisieren der Musikbibliothek

        std::cout << "Was möchten Sie nun tun? Ausgabe, Titel hinzufügen, Suchen, Daten ändern, Titel entfernen...? Für Beenden 'X' eingeben: ";
        std::string auswahl;
        std::cin.ignore();
        std::getline(std::cin, auswahl);

        //While-Schleife für Aktionen des Benutzers
        while (!(auswahl== "X")){

            //Ausgabe der Titel
            if(auswahl == "Ausgabe"){
                MusikBibliothek bibliothek2(dateipfad);
                bibliothek2.Ausgabe();
                }

            //Hinzufügen neuer Titel
            else if(auswahl == "Titel hinzufügen"){
                std::vector<Lied> neueLieder = bibliothek.Einlesen();
                bibliothek.LiedHinzufügen(dateipfad, neueLieder);
            }

            //Titel suchen
            else if(auswahl == "Suchen"){
                std::cout << "Möchten Sie nach einem Titel, einem Künstler, einem Album, einem Erscheinungsjahr, einem Genre oder einer Länge suchen? ";
                std::string suchkriterium;
                std::cin.ignore();
                std::cin >> suchkriterium;

                //Überprüfung das richtiges Suchkriterium eingegeben wurde
                while((suchkriterium != "Titel")&&(suchkriterium != "Künstler")&&(suchkriterium != "Album")&&(suchkriterium != "Erscheinungsjahr")&&(suchkriterium != "Genre")&&(suchkriterium != "Länge")){
                    std::cerr << "Fehlerhafte Eingabe! Geben Sie nochmal ein nach was Sie suchen möchten: ";
                    std::cin >> suchkriterium;
                }

                std::cout << "Geben Sie ein nach was Sie suchen: ";
                std::string suche;
                std::cin >> suche;

                //Ausführung Such-Funktion
                std::vector<Lied> gefundenelieder = bibliothek.suchen(suchkriterium, suche);

                if(!(gefundenelieder.empty())){
                    std::cout << "Diese Titel wurden gefunden: \n\n";
                    bibliothek.AusgabeTitel(gefundenelieder);
                }

            }

            //Änderung von Daten
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

                //Ausführung Such-Funktion und Daten Änderung
                std::vector<Lied> gefundenelieder = bibliothek.suchen("Titel", Titel);
                bibliothek.Datenaendern(gefundenelieder, Metadaten, neuerWert, dateipfad);
            }

            //Titel entfernen
            else if(auswahl == "Titel entfernen"){
                //While-Schleife für mehrmaliges Entfernen von Titeln
                while(true){
                std::cout << "Welchen Titel möchten Sie entfernen? ";
                std::string Titel;
                std::getline(std::cin, Titel);

                //While-Schleife falls Titel nicht gefunden wurde
                while(true){
                    if(bibliothek.entfernen(Titel, dateipfad)){
                        break;
                    }
                    else{
                        std::cout << "Geben Sie einen vorhandenen Titel ein: ";
                        std::getline(std::cin, Titel);
                        }
                }

                std::cout << "Möchten Sie noch weitere Titel entfernen? Ja oder Nein: ";
                std::string wahl;
                std::cin >> wahl;

                while(wahl != "Ja" && wahl != "Nein"){
                    std::cerr << "Fehlerhafte Eingabe. Geben Sie Ja oder Nein ein: ";
                    std::cin >> wahl;
                    }
                if(wahl == "Nein"){
                    std::cin.ignore();
                    break;
                    }
                }
            }
            //Ausgabe und Einlesen für weitere Aktionen
            std::cout << "Möchten Sie noch etwas tun? Ausgabe, Titel hinzufügen, Suchen, Daten ändern, Titel entfernen, ...? Für Beenden 'X' eingeben. ";
            std::getline (std::cin, auswahl);
        }
    }


    else if(OeffnenOderNeu == "Neu"){
        std::cout << "Geben Sie den Namen der Bibliothek ein. (mit Endung .json): ";
        std::string neueJSON;
        std::cin >> neueJSON;

        //Erstellen und Initialisieren der neuen Musikbibliothek
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
