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

        std::cout << "Was möchten Sie nun tun? Ausgabe, Titel hinzufügen, ...? Für Beenden 'X' eingeben: ";
        std::string auswahl;
        std::cin.ignore();
        std::getline(std::cin, auswahl);

        while (!(auswahl== "X")){

            if(auswahl == "Ausgabe"){
                bibliothek.Ausgabe();
                }

            else if(auswahl == "Titel hinzufügen"){
                while(true){
                Lied neuesLied;

                std::cout << "Geben Sie den Titel des Liedes ein: " << std::endl;
                std::getline (std::cin, neuesLied.Titel);
                std::cout << "Geben Sie den Künstler ein: " << std::endl;
                std::getline (std::cin, neuesLied.Kuenstler);
                std::cout << "Geben Sie das Album ein: " << std::endl;
                std::getline (std::cin, neuesLied.Album);
                std::cout << "Geben Sie das Erscheinungsjahr ein: " << std::endl;
                std::cin >> neuesLied.Erscheinungsjahr;
                std::cout << "Geben Sie das Genre ein: "<< std::endl;
                std::cin.ignore();
                std::getline (std::cin, neuesLied.Genre);
                std::cout << "Geben Sie die Länge des Liedes ein(MM:SS): " << std::endl;
                std::getline (std::cin, neuesLied.Laenge);

                bibliothek.LiedHinzufügen(neuesLied);

                std::cout << "Möchten Sie ein weiteres Lied hinzufügen? Ja oder Nein: ";
                std::string weiteres;
                std::cin >> weiteres;
                if(!(weiteres == "Ja")){
                    std::cin.ignore();
                    bibliothek.speichern(dateipfad);
                    break;
                    }
                }
            }

            std::cout << "Möchten Sie noch etwas tun? Ausgabe, Titel hinzufügen,...? Für Beenden 'X' eingeben. ";
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
                while(hinzufuegen == "Ja"){
                Lied neuesLied;

                std::cin.ignore();
                std::cout << "Geben Sie den Titel des Liedes ein: " << std::endl;
                std::getline (std::cin, neuesLied.Titel);
                std::cout << "Geben Sie den Künstler ein: " << std::endl;
                std::getline (std::cin, neuesLied.Kuenstler);
                std::cout << "Geben Sie das Album ein: " << std::endl;
                std::getline (std::cin, neuesLied.Album);
                std::cout << "Geben Sie das Erscheinungsjahr ein: " << std::endl;
                std::cin >> neuesLied.Erscheinungsjahr;
                std::cout << "Geben Sie das Genre ein: "<< std::endl;
                std::cin.ignore();
                std::getline (std::cin, neuesLied.Genre);
                std::cout << "Geben Sie die Länge des Liedes ein(MM:SS): " << std::endl;
                std::getline (std::cin, neuesLied.Laenge);


                bibliothek.LiedHinzufügen(neuesLied);

                std::cout << "Möchten Sie ein weiteres Lied hinzufügen? Ja oder Nein: ";
                std::cin >> hinzufuegen;

                if(!(hinzufuegen == "Ja")){
                    bibliothek.speichern(neueJSON);
                    break;
                    }
                }
            }
            else {
                return 0;
            }
        }

    return 0;
};
