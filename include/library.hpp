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

    static bool erstelleJSON(const std::string& dateiname);
    bool LiedHinzufügen(const Lied& neuesLied);
    bool speichern(const std::string& dateiname);
    std::vector<Lied> suchen(const std::string& suchkriterium, const std::string& suche);
    void AusgabeTitel(const std::vector<Lied>& Titel);

private:
std::vector<Lied> Lieder;                               //Erstellung Vektor Lieder mit der Struktur "Lied"
};
