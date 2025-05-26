//
// Created by kubat on 5/26/2025.
//
#include "d_hondt_allocator.h"
#include <QRandomGenerator>
#include <algorithm>

DHondtAllocator::DHondtAllocator(std::vector<Party>& parties, int totalVotes, int mandates)
    : parties(parties), totalVotes(totalVotes), mandates(mandates) {}

void DHondtAllocator::allocate() {
    std::vector<Party*> qualified;

    // Apply 5% threshold
    for (auto& p : parties)
        if (p.getVotes() * 100.0 / totalVotes >= 5.0)
            qualified.push_back(&p);

    struct Quotient {
        Party* party;
        double value;
    };

    std::vector<Quotient> quotients;

    for (int i = 0; i < mandates; ++i) {
        quotients.clear();

        for (Party* p : qualified) {
            int div = p->getMandates() + 1;
            quotients.push_back({p, static_cast<double>(p->getVotes()) / div});
        }

        // Find max
        auto max_it = std::max_element(quotients.begin(), quotients.end(), [](auto& a, auto& b) {
            return a.value < b.value;
        });

        // Handle ties
        double maxVal = max_it->value;
        std::vector<Party*> tied;
        for (const auto& q : quotients)
            if (q.value == maxVal)
                tied.push_back(q.party);

        Party* winner = tied.size() == 1 ? tied[0] : tied[QRandomGenerator::global()->bounded(tied.size())];
        winner->addMandate();
    }
}
