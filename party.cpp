//
// Created by kubat on 5/26/2025.
//
#include "party.h"

Party::Party(const QString& name, int votes)
    : name(name), votes(votes), mandates(0) {}

QString Party::getName() const { return name; }
int Party::getVotes() const { return votes; }
int Party::getMandates() const { return mandates; }
void Party::addMandate() { ++mandates; }
void Party::resetMandates() { mandates = 0; }

