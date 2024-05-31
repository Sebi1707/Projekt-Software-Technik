#include "library.hpp"

int main(){

    std::cout << "Geben Sie den Dateipfad der JSON-Datei ein, welche Sie öffnen möchten: ";     //Bildschirmausgabe
    std::string dateipfad;
    std::cin >> dateipfad;                  //Einlesen des Dateipfades

    MusikBibliothek bibliothek(dateipfad);  //Übergabe des Dateipfades an die MusikBibliothek-Funktion

    return 0;

};
