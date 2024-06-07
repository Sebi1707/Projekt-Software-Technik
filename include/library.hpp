#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

//Festlegung der Struktur für Lieder
struct Lied{
    std::string Album;          //Name des Albums
    int Erscheinungsjahr;       //Erscheinungsjahr des Liedes; Format "XXXX" z.B. "2024"
    std::string Genre;          //Genre des Liedes
    std::string Kuenstler;      //Name des Künstler
    std::string Laenge;         //Länge des Liedes; Format: "MM:SS" z.B. "02:56" für 2 Minuten und 56 Sekunden
    std::string Titel;          //Musiktitel
};

//Erstellen der Klasse MusikBibliothek
class MusikBibliothek {

public:
    MusikBibliothek(const std::string& dateiname);      //Konstruktor für die Initialisierung der Musikbiliothek aus einer JSON-Datei
    void Ausgabe();

    static bool erstelleJSON(const std::string& dateiname);         //Funktion um neue JSON-Datei zu erstellen
    std::vector<Lied> Einlesen();                                   //Funktion für Einlesen neuer Lieder
    bool LiedHinzufügen(const std::string& dateiname, std::vector<Lied>& neueLieder);              //Funktion um ein Lied hinzuzufügen
    bool speichern(const std::string& dateiname);                   //Funktion um die neuen Lieder zu speichern
    std::vector<Lied> suchen(const std::string& suchkriterium, const std::string& suche);           //Funktion um nach Titeln oder anderen Daten zu suchen
    void AusgabeTitel(const std::vector<Lied>& Titel);                                              //Funktion für Ausgabe der gefundenen Titeln
    bool Datenaendern(std::vector<Lied>& Titel, const std::string& MetaDaten,const std::string& neuerWert, const std::string& dateiname);         //Funktion um Meta-Daten zu ändern
    bool entfernen(const std::string& Titel, const std::string& dateiname);

private:
std::vector<Lied> Lieder;                               //Erstellung Vektor Lieder mit der Struktur "Lied"
};
