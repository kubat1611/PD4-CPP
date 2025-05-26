//
// Created by kubat on 5/26/2025.
//
#pragma once
#include <string>
#include <vector>
#include <map>

struct Party {
    std::string name;
    int votes;
    int seats = 0;
};

class Election {
public:
    void readInput();
    void distributeSeats();
    const std::vector<Party>& getQualifiedParties() const;
    int getTotalSeats() const;

private:
    std::vector<Party> parties;
    int totalVotes = 0;
    int totalSeats = 0;

    void applyThreshold();
};
