//
// Created by kubat on 5/26/2025.
//

#pragma once
#include "party.h"
#include <vector>

class DHondtAllocator {
public:
    DHondtAllocator(std::vector<Party>& parties, int totalVotes, int mandates);
    void allocate();
private:
    std::vector<Party>& parties;
    int totalVotes;
    int mandates;
};
