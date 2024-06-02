#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "library.hpp"

TEST_CASE("Erstellung einer JSON-Datei"){
    REQUIRE(MusikBibliothek::erstelleJSON("library.json") == true);
};

TEST_CASE("Keine Erstellung einer JSON-Datei"){
    REQUIRE(MusikBibliothek::erstelleJSON("") == false);
};
