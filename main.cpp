//
// Created by kubat on 5/26/2025.
//
#include "Election.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    Election election;
    election.readInput();
    election.distributeSeats();

    const auto& parties = election.getQualifiedParties();
    int numParties = parties.size();
    int windowWidth = 800;
    int windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Wyniki wyborów - Metoda D'Hondta");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Nie znaleziono czcionki arial.ttf\n";
        return 1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear(sf::Color::White);

        int maxSeats = 0;
        for (const auto& p : parties)
            maxSeats = std::max(maxSeats, p.seats);

        int barWidth = windowWidth / (numParties * 2);
        int spacing = barWidth;

        for (size_t i = 0; i < parties.size(); ++i) {
            const auto& party = parties[i];

            float heightRatio = (float)party.seats / maxSeats;
            int barHeight = heightRatio * (windowHeight - 150);

            sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));
            bar.setFillColor(sf::Color(100, 100 + 30 * (i % 5), 200));
            bar.setPosition(i * (barWidth + spacing) + spacing, windowHeight - barHeight - 100);
            window.draw(bar);

            sf::Text label;
            label.setFont(font);
            label.setCharacterSize(16);
            label.setString(party.name + " (" + std::to_string(party.seats) + ")");
            label.setFillColor(sf::Color::Black);
            label.setPosition(bar.getPosition().x, windowHeight - 90);
            window.draw(label);
        }

        window.display();
    }

    return 0;
}
