#include "library.hpp"

MusikBibliothek::MusikBibliothek(const std::string& dateiname){
    std::ifstream bibliothek(dateiname);                 //Einlesen der JSON-Datei

    if(bibliothek.is_open()){
        std::cout << "Datei " << dateiname << " wurde erfolgreich geöffnet." <<std::endl;        //Überprüfung ob Datei geöffnet werden konnte
    }
    else {
        std::cerr << "Fehler: Datei " << dateiname << " konnte nicht geöffnet werden." << std::endl;     //Fehlermeldung, dass Datei nicht geöffnet werden konnte.
    }
}
