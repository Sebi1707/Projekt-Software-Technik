#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

//Festlegung der Struktur für Lieder
struct Lied{
    std::string Titel;          //Musiktitel
    std::string Kuenstler;      //Name des Künstler
    std::string Album;          //Name des Albums
    int Erscheinungsjahr;       //Erscheinungsjahr des Liedes; Format "XXXX" z.B. "2024"
    std::string Genre;          //Genre des Liedes
    std::string Laenge;         //Länge des Liedes; Format: "MM:SS" z.B. "02:56" für 2 Minuten und 56 Sekunden
};
