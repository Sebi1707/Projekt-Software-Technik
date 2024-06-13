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
    std::vector<Lied> neueLieder;

    Lied neuesLied;
    neuesLied.Titel = "Titel";
    neuesLied.Kuenstler = "Künstler";
    neuesLied.Album = "Album";
    neuesLied.Erscheinungsjahr = 2024;
    neuesLied.Genre = "Pop";
    neuesLied.Laenge = "02:54";

    neueLieder.push_back(neuesLied);

    REQUIRE(bibliothek.LiedHinzufügen("test.json", neueLieder) == true);
};

TEST_CASE("Lied Speichern"){
    MusikBibliothek bibliothek("test.json");
    std::vector<Lied> neueLieder;

    Lied neuesLied;
    neuesLied.Titel = "Titel 1";
    neuesLied.Kuenstler = "Künstler 1";
    neuesLied.Album = "Album 1";
    neuesLied.Erscheinungsjahr = 2024;
    neuesLied.Genre = "Pop";
    neuesLied.Laenge = "03:34";

    neueLieder.push_back(neuesLied);

    bibliothek.LiedHinzufügen("test.json", neueLieder);

    REQUIRE(bibliothek.speichern("test.json") == true);
    REQUIRE(bibliothek.speichern("") == false);

    MusikBibliothek bibliothek2("test.json");
    std::vector<Lied> hinzugefügtesLied = bibliothek2.suchen("Titel", "Titel 1");

    REQUIRE(hinzugefügtesLied[0].Titel == "Titel 1");
    REQUIRE(hinzugefügtesLied[0].Kuenstler == "Künstler 1");
    REQUIRE(hinzugefügtesLied[0].Album == "Album 1");
    REQUIRE(hinzugefügtesLied[0].Erscheinungsjahr == 2024);
    REQUIRE(hinzugefügtesLied[0].Genre == "Pop");
    REQUIRE(hinzugefügtesLied[0].Laenge == "03:34");
};

TEST_CASE("Meta-Daten ändern"){
    MusikBibliothek bibliothek("test.json");
    std::vector<Lied> songs = bibliothek.suchen("Titel", "Titel 1");

    REQUIRE(bibliothek.Datenaendern(songs, "Künstler", "artist", "test.json")==true);
    MusikBibliothek bibliothek2("test.json");
    songs = bibliothek2.suchen("Titel", "Titel 1");
    REQUIRE(songs[0].Kuenstler == "artist");
    REQUIRE(!(songs[0].Kuenstler == " artist"));
};

TEST_CASE("Titel entfernen"){
    MusikBibliothek bibliothek("test.json");
    REQUIRE(bibliothek.entfernen("Titel 1", "test.json") == true);
    REQUIRE(bibliothek.entfernen("Unbekannter Titel", "test.json") == false);
};

TEST_CASE("Playlist erstellen"){
    REQUIRE(MusikBibliothek::erstellePlaylist("Test_Playlist", "test.json") == true);
    REQUIRE(MusikBibliothek::erstellePlaylist("Test_Playlist", "") == false);
};

TEST_CASE("Existiert Playlist"){
    MusikBibliothek bibliothek("test.json");
    REQUIRE(bibliothek.ExistPlaylist("Test_Playlist", "test.json") == true);
    REQUIRE(bibliothek.ExistPlaylist("Nicht vorhandene Playlist", "test.json") == false);
}

TEST_CASE("Titel zur Playlist hinzufügen"){
    MusikBibliothek bibliothek("test.json");
    REQUIRE(bibliothek.TitelzurPlaylist("Test_Playlist", "test.json", "Titel") == true);
    REQUIRE(bibliothek.TitelzurPlaylist("Test_Playlist", "test.json", "Unbekannter Titel") == false);

    std::ifstream datei("test.json");
    json data;
    datei >> data;

    bool gefunden = false;

    for(auto& playlist : data["Playlist"]){
        if(playlist["Name"] == "Test_Playlist"){
            for(auto& titel : playlist["Titel"]){
                if(titel=="Titel"){
                gefunden = true;
                break;
                }
            }
        }
    }

    REQUIRE(gefunden == true);
};

TEST_CASE("Titel aus Playlist entfernen"){
    MusikBibliothek bibliothek("test.json");
    REQUIRE(bibliothek.TitelPlaylistentfernen("Test_Playlist", "test.json", "Titel") == true);
    REQUIRE(bibliothek.TitelPlaylistentfernen("Test_Playlist", "test.json", "Nicht vorhandener Titel") == false);
    REQUIRE(bibliothek.TitelPlaylistentfernen("Nicht vorhandene Playlist", "test.json", "Titel") == false);
};

TEST_CASE("Playlist entfernen"){
    MusikBibliothek bibliothek("test.json");
    REQUIRE(bibliothek.Playlistentfernen("Test_Playlist", "test.json") == true);
};

