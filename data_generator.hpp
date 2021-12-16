#pragma once
#include <vector>
#include <string>
#include "person.hpp"

class DataGenerator {
public:

    size_t randomNumber(const size_t& rangeMin, const size_t& rangeMax) const; 
    std::string randomFirstName() const;
    std::string randomLastName() const;
    std::string randomPeselPrototype() const;
    std::string randomCity() const;
    std::string randomStreetAndNumber() const;
    std::string randomPostalCode() const;
    Sex randomSex() const;
    Person::PersonType randomPersonType() const;
    
private:
    std::string randomNumberWithZeros(const int& rangeMin, int rangeMax) const;

    std::vector<std::string> firstNames_ {"Alicja", "Anna", "Artur", "Alozjy",
    "Adam", "Bartosz", "Bruno", "Ben", "Barbara", "Cezary", "Celina", "Danuta",
    "Dawid", "Ewa", "Frank", "Gustaw", "Han", "Igor", "Kazik", "Karolina",
    "Katarzyna", "Luke", "Leia", "Monika", "Marek", "Natalia", "Nikodem", "Oskar",
    "Oliwia",  "John", "Paul", "George", "Ringo", "Paulina", "Rod", "Rozalia",
    "Steve", "Tadeusz", "Wladyslaw", "Wanda", "Zenon", "Konrad", "Mateusz",
    "Jerzy", "Andrzej", "Seweryn", "Maja", "Zbigniew", "Bogdan", "Bartlomiej"};

    std::vector<std::string> lastNames_ {"Nowak", "Kowalski", "Kowalczyk", "Kowal",
    "Jobs", "Wozniak", "Gates", "Touring", "Banach", "Zaremba", "Borewicz",
    "Lennon", "McCarntey", "Harrison", "Starr", "Jusilajnen", "Malysz", "Johnson",
    "Skywalker", "Kruszynski", "Kruszewski", "Wielgosz", "Korzecki", "Jarzabek",
    "Szymczyszyn", "Franusiak", "Kondeja", "Kozik", "Debski", "Drzewiecki"};

    std::vector<std::string> cities_ {"Rybnik", "Gliwice", "Wroclaw", "Warszawa",
    "Krakow", "Gdansk", "Liverpool", "Poznan", "Dublin", "Katowice", "Lomza",
    "Szczecin", "Kielce", "Swinoujscie", "Gniezno", "Berlin", "Rzeszow", "Siedlce",
    "Wladyslawowo", "Sieradz", "Lublin", "Tarnow", "Raciborz", "Plock", "Gdynia",
    "Torun", "Bydgoszcz", "Manchester", "Myslowice", "Jaworzno", "Chrzanow",};

    std::vector<std::string> streets_ {"Sezamkowa", "Mandarynki", "Nowy swiat",
    "Grochowska", "Francuska", "Zwyciezcow", "Dworcowa", "Stawowa", "Gliwicka",
    "Andersa", "Paderewskiego", "Lotnikow", "Meksykanska", "Saska", "Paryska",
    "Pawia", "Polna", "Zamkowa", "Chrobrego", "Kokoryczki", "Bednarska", "Krucza",
    "Miedziana", "Nowogrodzka", "Pulawska", "Marszalkowska", "Ostrobramska",
    "Piekna", "Chmielna", "Kasprzaka", "Jagielonska", "Odolanska", "Stawki"};

};