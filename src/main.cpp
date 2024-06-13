#include "library.hpp"
#include <filesystem>

std::string getInputLine(const std::string& prompt){
    std::string input;
    std::cout << prompt << std::endl;
    std::getline(std::cin, input);
    return input;
}


void printMenu(){
    std::cout << "Was möchten Sie nun tun?\n[1] Ausgabe\n[2] Titel hinzufügen\n[3] Suchen\n[4] Daten ändern\n[5] Titel entfernen\n[6] eine Playlist erstellen\n[7] Titel zu einer Playlist hinzufügen\n[8] Ausgabe Titel der Playlist\n[9] Titel aus einer Playlist entfernen\n[10] Playlist entfernen\n[0] Beenden\n";
}

int main(){

    std::string OeffnenOderNeu = getInputLine("Möchten Sie eine Bibliothek öffnen oder eine neue Bibliothek erstellen? Geben Sie ein Öffnen oder Neu: ");

    while(!(OeffnenOderNeu == "Öffnen" || OeffnenOderNeu == "Neu")){
        OeffnenOderNeu = getInputLine("Fehler: Geben Sie Öffnen oder Neu ein: ");
    }

    if(OeffnenOderNeu == "Öffnen"){
        std::string dateipfad = getInputLine("Geben Sie den Dateipfad der JSON-Datei ein, welche Sie öffnen möchten: ");

        if(!(std::filesystem::exists(dateipfad))){                    //Überprüfen ob der eingebene Dateipfad existiert
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
        printMenu();
        int auswahl;
        std::cin >> auswahl;

        //While-Schleife für Aktionen des Benutzers
        while (!(auswahl == 0)){

            //Ausgabe der Titel
            if(auswahl == 1){
                MusikBibliothek bibliothek2(dateipfad);
                bibliothek2.Ausgabe();
                }

            //Hinzufügen neuer Titel
            else if(auswahl == 2){
                std::cin.ignore();
                std::vector<Lied> neueLieder = bibliothek.Einlesen();
                bibliothek.LiedHinzufügen(dateipfad, neueLieder);
            }

            //Titel suchen
            else if(auswahl == 3){
                std::cin.ignore();
                std::string suchkriterium = getInputLine("Möchten Sie nach einem Titel, einem Künstler, einem Album, einem Erscheinungsjahr, einem Genre oder einer Länge suchen? ");

                //Überprüfung das richtiges Suchkriterium eingegeben wurde
                while((suchkriterium != "Titel")&&(suchkriterium != "Künstler")&&(suchkriterium != "Album")&&(suchkriterium != "Erscheinungsjahr")&&(suchkriterium != "Genre")&&(suchkriterium != "Länge")){
                    suchkriterium = getInputLine("Fehlerhafte Eingabe! Geben Sie nochmal ein nach was Sie suchen möchten: ");
                }

                std::string suche = getInputLine("Geben Sie ein nach was Sie suchen: ");

                //Ausführung Such-Funktion
                std::vector<Lied> gefundenelieder = bibliothek.suchen(suchkriterium, suche);

                if(!(gefundenelieder.empty())){
                    std::cout << "Diese Titel wurden gefunden: \n\n";
                    bibliothek.AusgabeTitel(gefundenelieder);
                }

            }

            //Änderung von Daten
            else if(auswahl == 4){
                std::cin.ignore();
                std::string Titel = getInputLine("Geben Sie den Titel ein von dem Sie die Daten ändern möchten: ");

                std::string Metadaten = getInputLine("Welche Daten möchten Sie ändern? ");

                std::string neuerWert = getInputLine("In was soll es geändert werden? ");

                //Ausführung Such-Funktion und Daten Änderung
                std::vector<Lied> gefundenelieder = bibliothek.suchen("Titel", Titel);
                bibliothek.Datenaendern(gefundenelieder, Metadaten, neuerWert, dateipfad);
            }

            //Titel entfernen
            else if(auswahl == 5){
                std::cin.ignore();
                std::string Titel = getInputLine("Welchen Titel möchten Sie entfernen? ");

                //While-Schleife für mehrmaliges Entfernen von Titeln
                while(true){

                std::string sicher = getInputLine("Möchten Sie den Titel wirklich löschen? ");

                if (sicher == "Ja"){
                    //While-Schleife falls Titel nicht gefunden wurde
                    while(true){
                    if(bibliothek.entfernen(Titel, dateipfad)){
                        break;
                    }
                    else{
                        Titel = getInputLine("Geben Sie einen vorhandenen Titel ein: ");
                        }
                }
                }
                else if(sicher == "Nein"){
                    break;
                }
                else{
                    sicher = getInputLine("Fehlerhafte Eingabe. Geben Sie Ja oder Nein ein. ");
                }

                std::string wahl = getInputLine("Möchten Sie noch weitere Titel entfernen? Ja oder Nein: ");

                while(wahl != "Ja" && wahl != "Nein"){
                    std::cerr << "Fehlerhafte Eingabe. Geben Sie Ja oder Nein ein: ";
                    std::cin >> wahl;
                    }
                if(wahl == "Nein"){
                    break;
                    }
                else if(wahl == "Ja"){
                    Titel = getInputLine("Welchen Titel möchten Sie entfernen? ");
                }
                }
            }

            //Playlist erstellen
            else if(auswahl == 6){
                std::cin.ignore();
                std::string name = getInputLine("Geben Sie den Namen der Playlist ein: ");

                MusikBibliothek::erstellePlaylist(name, dateipfad);

                std::string wahl = getInputLine("Möchten Sie Titel aus der Bibliothek zur Playlist hinzufügen? ");

                while(!(wahl == "Nein")){
                    if(wahl == "Ja"){
                    std::string Titel = getInputLine("Geben Sie den Titel des Liedes ein: ");

                    bibliothek.TitelzurPlaylist(name, dateipfad, Titel);

                    wahl = getInputLine("Möchten Sie weitere Titel zur Playlist hinzufügen? ");
                    }
                    else{
                        wahl = getInputLine("Falsche Eingabe. Geben Sie Ja oder Nein ein: ");
                        }
                }
            }

            //Titel zu einer Playlist hinzufügen
            else if(auswahl == 7){
                std::cin.ignore();
                std::string playlist = getInputLine("Zu welcher Playlist möchten Sie Titel hinzufügen? ");
                while(!(bibliothek.ExistPlaylist(playlist, dateipfad))){
                        playlist = getInputLine("Geben Sie eine bestehende Playlist ein: ");
                }
                while(true){
                    std::string Titel = getInputLine("Geben Sie den Titel des Liedes ein: ");


                    bibliothek.TitelzurPlaylist(playlist, dateipfad, Titel);

                    std::string wahl = getInputLine("Möchten Sie ein weiteres Lied hinzufügen? ");

                    if(wahl == "Ja"){
                        continue;
                    }
                    else if(wahl == "Nein"){
                        break;
                    }
                    else{
                        wahl = getInputLine("Fehlerhafte Eingabe. Geben Sie Ja oder Nein ein. ");
                    }
                }
            }



            //Ausgabe der Titel in einer Playlist
            else if(auswahl == 8){
                std::cin.ignore();
                std::string playlist = getInputLine("Welche Playlist möchten Sie ausgeben? ");

                while(!(bibliothek.ExistPlaylist(playlist, dateipfad))){
                    playlist = getInputLine("Geben Sie eine existierende Playlist ein: ");
                }

                bibliothek.AusgabePlaylist(playlist, dateipfad);
            }

            //Titel aus einer Playlist entfernen
            else if(auswahl == 9){
                std::cin.ignore();
                std::string playlist = getInputLine("Geben Sie den Namen der Playlist ein: ");

                while(!(bibliothek.ExistPlaylist(playlist, dateipfad))){
                    playlist = getInputLine("Geben Sie eine existierende Playlist ein: ");
                }

                while(true){
                std::string titel = getInputLine("Geben Sie den Titel ein den Sie entfernen möchten: ");
                std::string sicher = getInputLine("Wollen Sie wirklich löschen?");
                while(sicher != "Ja" && sicher != "Nein"){
                    sicher = getInputLine("Fehlerhafte Eingabe. Geben Sie Ja oder Nein ein: ");
                }
                if(sicher == "Ja"){
                    bibliothek.TitelPlaylistentfernen(playlist, dateipfad, titel);
                }
                else{
                    break;
                }

                std::string wahl = getInputLine("Möchten Sie weitere Titel entfernen? ");


                while(wahl != "Nein" && wahl !="Ja"){
                    wahl = getInputLine("Fehlerhafte Eingabe geben Sie Ja oder Nein ein: ");
                    }

                if(wahl == "Ja"){
                    continue;
                    }
                else{
                    break;
                    }
                }
            }

            //Playlist entfernen
            else if(auswahl == 10){
                std::cin.ignore();
                std::string playlist = getInputLine("Welche Playlist möchten Sie entfernen: ");

                while(!(bibliothek.ExistPlaylist(playlist, dateipfad))){
                    playlist = getInputLine("Geben Sie eine existierende Playlist ein: ");
                }

                bibliothek.Playlistentfernen(playlist, dateipfad);
            }

            else {
                std::cerr << "Fehlerhafte Eingabe. Geben Sie 1-10 ein oder 0 für Beenden. ";
                std::cin >> auswahl;
                continue;
            }

            //Ausgabe und Einlesen für weitere Aktionen
            printMenu();
            std::cin >> auswahl;
        }
    }


    else if(OeffnenOderNeu == "Neu"){
        std::string neueJSON = getInputLine("Geben Sie den Namen der Bibliothek ein. (mit Endung .json): ");

        //Erstellen und Initialisieren der neuen Musikbibliothek
        MusikBibliothek::erstelleJSON(neueJSON);
        MusikBibliothek bibliothek(neueJSON);

        std::string hinzufuegen = getInputLine("Möchten Sie nun Lieder zu ihrer Bibliothek hinzufügen? Ja oder Nein: ");


        while(!(hinzufuegen == "Ja" || hinzufuegen == "Nein")){
            hinzufuegen = getInputLine("Fehler:  Es wurde nicht mit Ja oder Nein geantwortet. Antworten Sie mit Ja oder Nein: ");
        }

        if (hinzufuegen == "Ja"){
            std::vector<Lied> neueLieder = bibliothek.Einlesen();
            bibliothek.LiedHinzufügen(neueJSON, neueLieder);

            std::string dateipfad = neueJSON;

            printMenu();
        int auswahl;
        std::cin >> auswahl;

        //While-Schleife für Aktionen des Benutzers
        while (!(auswahl == 0)){

            //Ausgabe der Titel
            if(auswahl == 1){
                MusikBibliothek bibliothek2(dateipfad);
                bibliothek2.Ausgabe();
                }

            //Hinzufügen neuer Titel
            else if(auswahl == 2){
                std::cin.ignore();
                std::vector<Lied> neueLieder = bibliothek.Einlesen();
                bibliothek.LiedHinzufügen(dateipfad, neueLieder);
            }

            //Titel suchen
            else if(auswahl == 3){
                std::cin.ignore();
                std::string suchkriterium = getInputLine("Möchten Sie nach einem Titel, einem Künstler, einem Album, einem Erscheinungsjahr, einem Genre oder einer Länge suchen? ");

                //Überprüfung das richtiges Suchkriterium eingegeben wurde
                while((suchkriterium != "Titel")&&(suchkriterium != "Künstler")&&(suchkriterium != "Album")&&(suchkriterium != "Erscheinungsjahr")&&(suchkriterium != "Genre")&&(suchkriterium != "Länge")){
                    suchkriterium = getInputLine("Fehlerhafte Eingabe! Geben Sie nochmal ein nach was Sie suchen möchten: ");
                }

                std::string suche = getInputLine("Geben Sie ein nach was Sie suchen: ");

                //Ausführung Such-Funktion
                std::vector<Lied> gefundenelieder = bibliothek.suchen(suchkriterium, suche);

                if(!(gefundenelieder.empty())){
                    std::cout << "Diese Titel wurden gefunden: \n\n";
                    bibliothek.AusgabeTitel(gefundenelieder);
                }

            }

            //Änderung von Daten
            else if(auswahl == 4){
                std::cin.ignore();
                std::string Titel = getInputLine("Geben Sie den Titel ein von dem Sie die Daten ändern möchten: ");

                std::string Metadaten = getInputLine("Welche Daten möchten Sie ändern? ");

                std::string neuerWert = getInputLine("In was soll es geändert werden? ");

                //Ausführung Such-Funktion und Daten Änderung
                std::vector<Lied> gefundenelieder = bibliothek.suchen("Titel", Titel);
                bibliothek.Datenaendern(gefundenelieder, Metadaten, neuerWert, dateipfad);
            }

            //Titel entfernen
            else if(auswahl == 5){
                std::cin.ignore();
                std::string Titel = getInputLine("Welchen Titel möchten Sie entfernen? ");

                //While-Schleife für mehrmaliges Entfernen von Titeln
                while(true){

                std::string sicher = getInputLine("Möchten Sie den Titel wirklich löschen? ");

                if (sicher == "Ja"){
                    //While-Schleife falls Titel nicht gefunden wurde
                    while(true){
                    if(bibliothek.entfernen(Titel, dateipfad)){
                        break;
                    }
                    else{
                        Titel = getInputLine("Geben Sie einen vorhandenen Titel ein: ");
                        }
                }
                }
                else if(sicher == "Nein"){
                    break;
                }
                else{
                    sicher = getInputLine("Fehlerhafte Eingabe. Geben Sie Ja oder Nein ein. ");
                }

                std::string wahl = getInputLine("Möchten Sie noch weitere Titel entfernen? Ja oder Nein: ");

                while(wahl != "Ja" && wahl != "Nein"){
                    std::cerr << "Fehlerhafte Eingabe. Geben Sie Ja oder Nein ein: ";
                    std::cin >> wahl;
                    }
                if(wahl == "Nein"){
                    break;
                    }
                else if(wahl == "Ja"){
                    Titel = getInputLine("Welchen Titel möchten Sie entfernen? ");
                }
                }
            }

            //Playlist erstellen
            else if(auswahl == 6){
                std::cin.ignore();
                std::string name = getInputLine("Geben Sie den Namen der Playlist ein: ");

                MusikBibliothek::erstellePlaylist(name, dateipfad);

                std::string wahl = getInputLine("Möchten Sie Titel aus der Bibliothek zur Playlist hinzufügen? ");

                while(!(wahl == "Nein")){
                    if(wahl == "Ja"){
                    std::string Titel = getInputLine("Geben Sie den Titel des Liedes ein: ");

                    bibliothek.TitelzurPlaylist(name, dateipfad, Titel);

                    wahl = getInputLine("Möchten Sie weitere Titel zur Playlist hinzufügen? ");
                    }
                    else{
                        wahl = getInputLine("Falsche Eingabe. Geben Sie Ja oder Nein ein: ");
                        }
                }
            }

            //Titel zu einer Playlist hinzufügen
            else if(auswahl == 7){
                std::cin.ignore();
                std::string playlist = getInputLine("Zu welcher Playlist möchten Sie Titel hinzufügen? ");
                while(!(bibliothek.ExistPlaylist(playlist, dateipfad))){
                        playlist = getInputLine("Geben Sie eine bestehende Playlist ein: ");
                }
                while(true){
                    std::string Titel = getInputLine("Geben Sie den Titel des Liedes ein: ");


                    bibliothek.TitelzurPlaylist(playlist, dateipfad, Titel);

                    std::string wahl = getInputLine("Möchten Sie ein weiteres Lied hinzufügen? ");

                    if(wahl == "Ja"){
                        continue;
                    }
                    else if(wahl == "Nein"){
                        break;
                    }
                    else{
                        wahl = getInputLine("Fehlerhafte Eingabe. Geben Sie Ja oder Nein ein. ");
                    }
                }
            }



            //Ausgabe der Titel in einer Playlist
            else if(auswahl == 8){
                std::cin.ignore();
                std::string playlist = getInputLine("Welche Playlist möchten Sie ausgeben? ");

                while(!(bibliothek.ExistPlaylist(playlist, dateipfad))){
                    playlist = getInputLine("Geben Sie eine existierende Playlist ein: ");
                }

                bibliothek.AusgabePlaylist(playlist, dateipfad);
            }

            //Titel aus einer Playlist entfernen
            else if(auswahl == 9){
                std::cin.ignore();
                std::string playlist = getInputLine("Geben Sie den Namen der Playlist ein: ");

                while(!(bibliothek.ExistPlaylist(playlist, dateipfad))){
                    playlist = getInputLine("Geben Sie eine existierende Playlist ein: ");
                }

                while(true){
                std::string titel = getInputLine("Geben Sie den Titel ein den Sie entfernen möchten: ");
                std::string sicher = getInputLine("Wollen Sie wirklich löschen?");
                while(sicher != "Ja" && sicher != "Nein"){
                    sicher = getInputLine("Fehlerhafte Eingabe. Geben Sie Ja oder Nein ein: ");
                }
                if(sicher == "Ja"){
                    bibliothek.TitelPlaylistentfernen(playlist, dateipfad, titel);
                }
                else{
                    break;
                }

                std::string wahl = getInputLine("Möchten Sie weitere Titel entfernen? ");


                while(wahl != "Nein" && wahl !="Ja"){
                    wahl = getInputLine("Fehlerhafte Eingabe geben Sie Ja oder Nein ein: ");
                    }

                if(wahl == "Ja"){
                    continue;
                    }
                else{
                    break;
                    }
                }
            }

            //Playlist entfernen
            else if(auswahl == 10){
                std::cin.ignore();
                std::string playlist = getInputLine("Welche Playlist möchten Sie entfernen: ");

                while(!(bibliothek.ExistPlaylist(playlist, dateipfad))){
                    playlist = getInputLine("Geben Sie eine existierende Playlist ein: ");
                }

                bibliothek.Playlistentfernen(playlist, dateipfad);
            }

            else {
                std::cerr << "Fehlerhafte Eingabe. Geben Sie 1-10 ein oder 0 für Beenden. ";
                std::cin >> auswahl;
                continue;
            }

            //Ausgabe und Einlesen für weitere Aktionen
            printMenu();
            std::cin >> auswahl;
        }
        }
        else {
            return 0;
        }
    }
    return 0;
};
