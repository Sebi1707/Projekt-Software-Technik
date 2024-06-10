#include "library.hpp"

//Einlesen einer JSON-Datei
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

//Ausgabe der, in der JSON-Datei, enthaltenden Lieder
void MusikBibliothek::Ausgabe() {
    if (Lieder.empty()) {
        std::cout << "Die Bibliothek enthält keine Lieder." << std::endl;       //Meldung wenn die Datei leer ist
        return;
    }
    else {
        std::cout << "Bibliothek wird ausgegeben.\n" << std::endl;
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

//Erstellung einer neuen JSON-Datei
bool MusikBibliothek::erstelleJSON(const std::string& dateiname){
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

std::vector<Lied> MusikBibliothek::Einlesen(){
    std::vector<Lied> neueLieder;

    while(true){
    Lied neuesLied;

    std::cout << "Geben Sie den Titel des Liedes ein: " << std::endl;
    std::getline (std::cin, neuesLied.Titel);                                   //std::getline und std::cin.ignore() unter zu hilfenahme von KI herausgefunden
    std::cout << "Geben Sie den Künstler ein: " << std::endl;                   //da das Einlesen nicht richtig funktioniert hat und immer wieder ein Buchstaben gefehlt hat oder keine Eingabe möglich war
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

    neueLieder.push_back(neuesLied);

    std::cout << "Möchten Sie ein weiteres Lied hinzufügen? Ja oder Nein: ";
    std::string weiteres;
    std::cin >> weiteres;
    std::cin.ignore();

    if(!(weiteres == "Ja")){
        return neueLieder;
        }
    }
};

//Funktion um ein neues Lied hinzuzufügen
bool MusikBibliothek::LiedHinzufügen(const std::string& dateiname, std::vector<Lied>& neueLieder){

            for(const auto& lied : neueLieder){
                Lied neuesLied;
                neuesLied.Titel = lied.Titel;
                neuesLied.Kuenstler = lied.Kuenstler;
                neuesLied.Album = lied.Album;
                neuesLied.Erscheinungsjahr = lied.Erscheinungsjahr;
                neuesLied.Genre = lied.Genre;
                neuesLied.Laenge = lied.Laenge;

                Lieder.push_back(neuesLied);
            }

            speichern(dateiname);
            if(speichern(dateiname)){
                return true;
            }
            else{
                std::cout << "Hinzufügen neuer Lieder fehlgeschlagen!" << std::endl;
                return false;
            }

            if(neueLieder.empty()){
                return false;
            }
};

//Speicherfunktion
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
    datei << dateien.dump(4);
    datei.close();
    return true;
    }
    else{
        return false;
    }
}

//Suchfunktion
std::vector<Lied> MusikBibliothek::suchen(const std::string& suchkriterium, const std::string& suche){
    std::vector<Lied> gefundeneLieder;

    for(const auto& lied : Lieder){
        if((suchkriterium == "Titel" && lied.Titel == suche) ||
            (suchkriterium == "Künstler" && lied.Kuenstler == suche)||
            (suchkriterium == "Album" && lied.Album == suche) ||
            (suchkriterium == "Erscheinungsjahr" && std::to_string(lied.Erscheinungsjahr) == suche) ||
            (suchkriterium == "Genre" && lied.Genre == suche) ||
            (suchkriterium == "Länge" && lied.Laenge == suche)){
            gefundeneLieder.push_back(lied);
        };
    }

    if(gefundeneLieder.empty()){
        std::cout << "Es wurde kein Lied mit " << suchkriterium << " : " << suche << " gefunden." << std::endl;
    }

    return gefundeneLieder;
};

//Ausgabe der Titel, welche mit der Suchfunktion gefunden wurden
void MusikBibliothek::AusgabeTitel(const std::vector<Lied>& Titel){
    for(const auto& lied : Titel){
        std::cout << "Titel: " << lied.Titel << "\n"
                  << "Künstler: " << lied.Kuenstler << "\n"
                  << "Album: " << lied.Album << "\n"
                  << "Erscheinungsjahr: " << lied.Erscheinungsjahr << "\n"
                  << "Genre: " << lied.Genre << "\n"
                  << "Länge: " << lied.Laenge << "\n\n";
    }
};

//Funktion für Änderung der Meta-Daten und anschließender Speicherung
bool MusikBibliothek::Datenaendern(std::vector<Lied>& Titel, const std::string& MetaDaten, const std::string& neuerWert, const std::string& dateiname){

    if(Titel.empty()){
        std::cout << "Es konnten keine Daten geändert werden." << std::endl;
        return false;
    }

    std::string titel = Titel[0].Titel;

    for(auto& lied : Lieder){
        if(lied.Titel == titel){
            if(MetaDaten == "Titel"){
                lied.Titel = neuerWert;
            }
            else if(MetaDaten == "Künstler"){
                lied.Kuenstler = neuerWert;
            }
            else if(MetaDaten == "Album"){
                lied.Album = neuerWert;
            }
            else if(MetaDaten == "Erscheinungsjahr"){
                lied.Erscheinungsjahr = std::stoi(neuerWert);
            }
            else if(MetaDaten == "Genre"){
                lied.Genre = neuerWert;
            }
            else if(MetaDaten == "Länge"){
                lied.Laenge = neuerWert;
            }
            else{
                std::cout << MetaDaten << " nicht gefunden." << std::endl;
                return false;
                break;
            }
            speichern(dateiname);
            break;
        }
    }
    if(speichern(dateiname)){
        std::cout << MetaDaten << " wurde erfolgreich in " << neuerWert << " geändert." <<std::endl;
        return true;
    }
    else{
        std::cout << "Fehler: Die Daten konnten nicht geändert werden.";
        return false;
    }
};

//Funktion für Entfernung von Titeln
bool MusikBibliothek::entfernen(const std::string& Titel, const std::string& dateiname){
    MusikBibliothek bibliothek(dateiname);

    for(auto lied = Lieder.begin(); lied !=Lieder.end(); lied++){
        if(lied->Titel == Titel){

            Lieder.erase(lied);

            speichern(dateiname);
            std::cout << Titel << " wurde erfolgreich entfernt." << std::endl;
            return true;
        }
    }

    std::cout << "Titel nicht gefunden." << std::endl;
    return false;
};


//Erstellen einer Playlist
bool MusikBibliothek::erstellePlaylist(const std::string& namePlaylist, const std::string& dateiname){
    std::ifstream datei(dateiname);
    json data;

    datei >> data;
    datei.close();

    Playlist neuePlaylist;

    neuePlaylist.Name = namePlaylist;
    neuePlaylist.Titel = {};

    json Playlist = {
        {"Name", neuePlaylist.Name},
        {"Titel", neuePlaylist.Titel}
    };

    data["Playlist"].push_back(Playlist);

    std::ofstream neuedatei(dateiname);
    if(neuedatei.is_open()){
    neuedatei << data.dump(4);
    neuedatei.close();
    std::cout << "Playlist erfolgreich erstellt." <<std::endl;
    return true;
    }
    else{
        std::cerr << "Fehler beim Öffnen der Datei." << std::endl;
        return false;
    }
}
