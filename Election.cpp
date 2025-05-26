//
// Created by kubat on 5/26/2025.
//
#include "Election.h"
#include <iostream>
#include <algorithm>
#include <random>

void Election::readInput() {
    int numParties;
    std::cout << "Liczba partii: ";
    std::cin >> numParties;

    for (int i = 0; i < numParties; ++i) {
        Party p;
        std::cout << "Nazwa partii #" << i+1 << ": ";
        std::cin >> p.name;
        std::cout << "Liczba głosów: ";
        std::cin >> p.votes;
        totalVotes += p.votes;
        parties.push_back(p);
    }

    std::cout << "Liczba mandatów do przydzielenia: ";
    std::cin >> totalSeats;

    applyThreshold();
}

void Election::applyThreshold() {
    parties.erase(std::remove_if(parties.begin(), parties.end(), [&](const Party& p) {
        return (double)p.votes / totalVotes < 0.05;
    }), parties.end());
}

void Election::distributeSeats() {
    struct Quotient {
        double value;
        int partyIndex;
    };

    std::vector<Quotient> quotients;

    for (int i = 0; i < totalSeats; ++i) {
        quotients.clear();
        for (size_t j = 0; j < parties.size(); ++j) {
            double q = static_cast<double>(parties[j].votes) / (parties[j].seats + 1);
            quotients.push_back({q, (int)j});
        }

        auto maxIt = std::max_element(quotients.begin(), quotients.end(), [](auto& a, auto& b) {
            return a.value < b.value;
        });

        // Zbieramy wszystkie największe wartości
        double maxValue = maxIt->value;
        std::vector<int> candidates;
        for (const auto& q : quotients) {
            if (q.value == maxValue)
                candidates.push_back(q.partyIndex);
        }

        // Losujemy jeśli remis
        int winner = candidates.size() == 1 ? candidates[0] :
                     candidates[rand() % candidates.size()];
        parties[winner].seats++;
    }
}

const std::vector<Party>& Election::getQualifiedParties() const {
    return parties;
}

int Election::getTotalSeats() const {
    return totalSeats;
}
