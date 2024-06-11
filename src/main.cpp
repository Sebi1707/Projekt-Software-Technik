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

        std::cout << "Was möchten Sie nun tun?\n[1] Ausgabe\n[2] Titel hinzufügen\n[3] Suchen\n[4] Daten ändern\n[5] Titel entfernen\n[6] eine Playlist erstellen\n[7] Titel zu einer Playlist hinzufügen\n[8] Ausgabe Titel der Playlist\n[9] Titel aus einer Playlist entfernen\n[10] Playlist entfernen\n[0] Beenden\n";
        int auswahl;
        std::cin >> auswahl;

        //While-Schleife für Aktionen des Benutzers
        while (!(auswahl== 0)){

            //Ausgabe der Titel
            if(auswahl == 1){
                MusikBibliothek bibliothek2(dateipfad);
                bibliothek2.Ausgabe();
                }

            //Hinzufügen neuer Titel
            else if(auswahl == 2){
                std::vector<Lied> neueLieder = bibliothek.Einlesen();
                bibliothek.LiedHinzufügen(dateipfad, neueLieder);
            }

            //Titel suchen
            else if(auswahl == 3){
                std::cout << "Möchten Sie nach einem Titel, einem Künstler, einem Album, einem Erscheinungsjahr, einem Genre oder einer Länge suchen? ";
                std::string suchkriterium;
                std::cin.ignore();
                std::getline(std::cin, suchkriterium);

                //Überprüfung das richtiges Suchkriterium eingegeben wurde
                while((suchkriterium != "Titel")&&(suchkriterium != "Künstler")&&(suchkriterium != "Album")&&(suchkriterium != "Erscheinungsjahr")&&(suchkriterium != "Genre")&&(suchkriterium != "Länge")){
                    std::cerr << "Fehlerhafte Eingabe! Geben Sie nochmal ein nach was Sie suchen möchten: ";
                    std::cin >> suchkriterium;
                }

                std::cout << "Geben Sie ein nach was Sie suchen: ";
                std::string suche;
                std::getline(std::cin, suche);

                //Ausführung Such-Funktion
                std::vector<Lied> gefundenelieder = bibliothek.suchen(suchkriterium, suche);

                if(!(gefundenelieder.empty())){
                    std::cout << "Diese Titel wurden gefunden: \n\n";
                    bibliothek.AusgabeTitel(gefundenelieder);
                }

            }

            //Änderung von Daten
            else if(auswahl == 4){
                std::cout << "Geben Sie den Titel ein von dem Sie die Daten ändern möchten: ";
                std::string Titel;
                std::cin.ignore();
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
            else if(auswahl == 5){
                std::cin.ignore();
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

            //Playlist erstellen
            else if(auswahl == 6){
                std::cout << "Geben Sie den Namen der Playlist ein: ";
                std::string name;
                std::cin.ignore();
                std::getline(std::cin, name);

                MusikBibliothek::erstellePlaylist(name, dateipfad);

                std::cout << "Möchten Sie Titel aus der Bibliothek zur Playlist hinzufügen? ";
                std::string wahl;
                std::cin >> wahl;

                while(!(wahl == "Nein")){
                    if(wahl == "Ja"){
                    std::cout << "Geben Sie den Titel des Liedes ein: ";
                    std::string Titel;
                    std::cin.ignore();
                    std::getline(std::cin, Titel);

                    bibliothek.TitelzurPlaylist(name, dateipfad, Titel);

                    std::cout << "Möchten Sie weitere Titel zur Playlist hinzufügen? ";
                    std::cin >> wahl;
                    }
                    else{
                        std::cout << "Falsche Eingabe. Geben Sie Ja oder Nein ein: ";
                        std::cin >> wahl;
                        }
                }
            }

            //Titel zu einer Playlist hinzufügen
            else if(auswahl == 7){
                std::cout << "Zu welcher Playlist möchten Sie Titel hinzufügen? ";
                std::cin.ignore();
                std::string playlist;
                std::getline(std::cin, playlist);

                while(true){
                    std::cout << "Geben Sie den Titel des Liedes ein: ";
                    std::string Titel;
                    std::getline(std::cin, Titel);

                    bibliothek.TitelzurPlaylist(playlist, dateipfad, Titel);

                    std::cout << "Möchten Sie ein weiteres Lied hinzufügen? ";
                    std::string wahl;
                    std::cin >> wahl;
                    if(wahl == "Ja"){
                        continue;
                    }
                    else if(wahl == "Nein"){
                        break;
                    }
                    else{
                        std::cerr << "Fehlerhafte Eingabe. Geben Sie Ja oder Nein ein. ";
                        std::cin >> wahl;
                    }
                    std::cin.ignore();
                }
            }

            //Ausgabe der Titel in einer Playlist
            else if(auswahl == 8){
                std::cout << "Welche Playlist möchten Sie ausgeben? ";
                std::string playlist;
                std::cin.ignore();
                std::getline(std::cin, playlist);

                bibliothek.AusgabePlaylist(playlist, dateipfad);
            }

            //Titel aus einer Playlist entfernen
            else if(auswahl == 9){
                std::cout << "Geben Sie den Namen der Playlist ein: ";
                std::string playlist;
                std::cin.ignore();
                std::getline(std::cin, playlist);

                while(true){
                std::cout << "Geben Sie den Titel ein den Sie entfernen möchten: ";
                std::string titel;
                std::getline(std::cin, titel);

                bibliothek.TitelPlaylistentfernen(playlist, dateipfad, titel);

                std::cout << "Möchten Sie weitere Titel entfernen? ";
                std::string wahl;
                std::cin >> wahl;

                while(wahl != "Nein" && wahl !="Ja"){
                    std::cerr << "Fehlerhafte Eingabe geben Sie Ja oder Nein ein: ";
                    std::cin >> wahl;
                    }

                if(wahl == "Ja"){
                    std::cin.ignore();
                    continue;
                    }
                else{
                    std::cin.ignore();
                    break;
                    }
                }
            }

            //Playlist entfernen
            else if(auswahl == 10){
                std::cout << "Welche Playlist möchten Sie entfernen: ";
                std::string playlist;
                std::cin.ignore();
                std::getline(std::cin, playlist);

                bibliothek.Playlistentfernen(playlist, dateipfad);
            }

            else {
                std::cerr << "Fehlerhafte Eingabe. Geben Sie 1-10 ein oder 0 für Beenden. ";
                std::cin >> auswahl;
                continue;
            }

            //Ausgabe und Einlesen für weitere Aktionen
            std::cout << "Möchten Sie noch etwas tun? \n[1] Ausgabe\n[2] Titel hinzufügen\n[3] Suchen\n[4] Daten ändern\n[5] Titel entfernen\n[6] eine Playlist erstellen\n[7] Titel zu einer Playlist hinzufügen\n[8] Ausgabe Titel der Playlist\n[9] Titel aus einer Playlist entfernen\n[10] Playlist entfernen\n[0] Beenden\n";
            std::cin >> auswahl;
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

            std::string dateipfad = neueJSON;

            std::cout << "Was möchten Sie nun tun?\n[1] Ausgabe\n[2] Titel hinzufügen\n[3] Suchen\n[4] Daten ändern\n[5] Titel entfernen\n[6] eine Playlist erstellen\n[7] Titel zu einer Playlist hinzufügen\n[8] Ausgabe Titel der Playlist\n[9] Titel aus einer Playlist entfernen\n[10] Playlist entfernen\n[0] Beenden\n";
            int auswahl;
            std::cin >> auswahl;

            //While-Schleife für Aktionen des Benutzers
            while (!(auswahl== 0)){

                //Ausgabe der Titel
                if(auswahl == 1){
                    MusikBibliothek bibliothek2(dateipfad);
                    bibliothek2.Ausgabe();
                    }

                //Hinzufügen neuer Titel
                else if(auswahl == 2){
                    std::vector<Lied> neueLieder = bibliothek.Einlesen();
                    bibliothek.LiedHinzufügen(dateipfad, neueLieder);
                    }

                //Titel suchen
                else if(auswahl == 3){
                    std::cout << "Möchten Sie nach einem Titel, einem Künstler, einem Album, einem Erscheinungsjahr, einem Genre oder einer Länge suchen? ";
                    std::string suchkriterium;
                    std::cin.ignore();
                    std::getline(std::cin, suchkriterium);

                    //Überprüfung das richtiges Suchkriterium eingegeben wurde
                    while((suchkriterium != "Titel")&&(suchkriterium != "Künstler")&&(suchkriterium != "Album")&&(suchkriterium != "Erscheinungsjahr")&&(suchkriterium != "Genre")&&(suchkriterium != "Länge")){
                        std::cerr << "Fehlerhafte Eingabe! Geben Sie nochmal ein nach was Sie suchen möchten: ";
                        std::cin >> suchkriterium;
                    }

                    std::cout << "Geben Sie ein nach was Sie suchen: ";
                    std::string suche;
                    std::getline(std::cin, suche);

                    //Ausführung Such-Funktion
                    std::vector<Lied> gefundenelieder = bibliothek.suchen(suchkriterium, suche);

                    if(!(gefundenelieder.empty())){
                        std::cout << "Diese Titel wurden gefunden: \n\n";
                        bibliothek.AusgabeTitel(gefundenelieder);
                    }

                }

                //Änderung von Daten
                else if(auswahl == 4){
                    std::cout << "Geben Sie den Titel ein von dem Sie die Daten ändern möchten: ";
                    std::string Titel;
                    std::cin.ignore();
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
                else if(auswahl == 5){
                    std::cin.ignore();

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

                //Playlist erstellen
                else if(auswahl == 6){
                    std::cout << "Geben Sie den Namen der Playlist ein: ";
                    std::string name;
                    std::cin.ignore();
                    std::getline(std::cin, name);

                    MusikBibliothek::erstellePlaylist(name, dateipfad);

                    std::cout << "Möchten Sie Titel aus der Bibliothek zur Playlist hinzufügen? ";
                    std::string wahl;
                    std::cin >> wahl;

                    while(!(wahl == "Nein")){
                        if(wahl == "Ja"){
                        std::cout << "Geben Sie den Titel des Liedes ein: ";
                        std::string Titel;
                        std::cin.ignore();
                        std::getline(std::cin, Titel);

                        bibliothek.TitelzurPlaylist(name, dateipfad, Titel);

                        std::cout << "Möchten Sie weitere Titel zur Playlist hinzufügen? ";
                        std::cin >> wahl;
                        }
                        else{
                            std::cout << "Falsche Eingabe. Geben Sie Ja oder Nein ein: ";
                            std::cin >> wahl;
                        }
                    }
                }

                //Titel zu einer Playlist hinzufügen
                else if(auswahl == 7){
                    std::cout << "Zu welcher Playlist möchten Sie Titel hinzufügen? ";
                    std::cin.ignore();
                    std::string playlist;
                    std::getline(std::cin, playlist);

                    while(true){
                        std::cout << "Geben Sie den Titel des Liedes ein: ";
                        std::string Titel;
                        std::getline(std::cin, Titel);

                        bibliothek.TitelzurPlaylist(playlist, dateipfad, Titel);

                        std::cout << "Möchten Sie ein weiteres Lied hinzufügen? ";
                        std::string wahl;
                        std::cin >> wahl;
                        if(wahl == "Ja"){
                            continue;
                        }
                        else if(wahl == "Nein"){
                            break;
                        }
                        else{
                            std::cerr << "Fehlerhafte Eingabe. Geben Sie Ja oder Nein ein. ";
                            std::cin >> wahl;
                        }
                        std::cin.ignore();
                    }
                }

                //Ausgabe der Titel in einer Playlist
                else if(auswahl == 8){
                    std::cout << "Welche Playlist möchten Sie ausgeben? ";
                    std::string playlist;
                    std::cin.ignore();
                    std::getline(std::cin, playlist);

                    bibliothek.AusgabePlaylist(playlist, dateipfad);
                }

                //Titel aus einer Playlist entfernen
                else if(auswahl == 9){
                    std::cout << "Geben Sie den Namen der Playlist ein: ";
                    std::string playlist;
                    std::cin.ignore();
                    std::getline(std::cin, playlist);

                    while(true){
                        std::cout << "Geben Sie den Titel ein den Sie entfernen möchten: ";
                        std::string titel;
                        std::getline(std::cin, titel);

                        bibliothek.TitelPlaylistentfernen(playlist, dateipfad, titel);

                        std::cout << "Möchten Sie weitere Titel entfernen? ";
                        std::string wahl;
                        std::cin >> wahl;

                        while(wahl != "Nein" && wahl !="Ja"){
                            std::cerr << "Fehlerhafte Eingabe geben Sie Ja oder Nein ein: ";
                            std::cin >> wahl;
                        }

                        if(wahl == "Ja"){
                            std::cin.ignore();
                            continue;
                        }
                        else{
                            std::cin.ignore();
                            break;
                        }
                    }
                }

                //Playlist entfernen
                else if(auswahl == 10){
                    std::cout << "Welche Playlist möchten Sie entfernen: ";
                    std::string playlist;
                    std::cin.ignore();
                    std::getline(std::cin, playlist);

                    bibliothek.Playlistentfernen(playlist, dateipfad);
                }

                else {
                    std::cerr << "Fehlerhafte Eingabe. Geben Sie 1-10 ein oder 0 für Beenden. ";
                    std::cin >> auswahl;
                    continue;
                }

                //Ausgabe und Einlesen für weitere Aktionen
                std::cout << "Möchten Sie noch etwas tun? \n[1] Ausgabe\n[2] Titel hinzufügen\n[3] Suchen\n[4] Daten ändern\n[5] Titel entfernen\n[6] eine Playlist erstellen\n[7] Titel zu einer Playlist hinzufügen\n[8] Ausgabe Titel der Playlist\n[9] Titel aus einer Playlist entfernen\n[10] Playlist entfernen\n[0] Beenden\n";
                std::cin >> auswahl;
            }
        }
        else {
            return 0;
        }
    }
    return 0;
};
