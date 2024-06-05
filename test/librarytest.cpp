#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "library.hpp"

TEST_CASE("Erstellung einer JSON-Datei"){
    REQUIRE(MusikBibliothek::erstelleJSON("test.json") == true);
};

TEST_CASE("Keine Erstellung einer JSON-Datei"){
    REQUIRE(MusikBibliothek::erstelleJSON("") == false);
};

TEST_CASE("Lied hinzufügen"){
    MusikBibliothek bibliothek("test.json");

    Lied neuesLied;
    neuesLied.Titel = "Titel";
    neuesLied.Kuenstler = "Künstler";
    neuesLied.Album = "Album";
    neuesLied.Erscheinungsjahr = 2024;
    neuesLied.Genre = "Pop";
    neuesLied.Laenge = "02:54";

    REQUIRE(bibliothek.LiedHinzufügen(neuesLied) == true);
};

TEST_CASE("Lied Speichern"){
    MusikBibliothek bibliothek("test.json");

    Lied neuesLied;
    neuesLied.Titel = "Titel 1";
    neuesLied.Kuenstler = "Künstler 1";
    neuesLied.Album = "Album 1";
    neuesLied.Erscheinungsjahr = 2024;
    neuesLied.Genre = "Pop";
    neuesLied.Laenge = "03:34";

    bibliothek.LiedHinzufügen(neuesLied);

    REQUIRE(bibliothek.speichern("test.json") == true);
    REQUIRE(bibliothek.speichern("") == false);
};