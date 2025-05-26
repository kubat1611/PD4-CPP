//
// Created by kubat on 5/26/2025.
//

#pragma once
#include <QString>

class Party {
public:
    Party(const QString& name, int votes);

    QString getName() const;
    int getVotes() const;
    int getMandates() const;
    void addMandate();
    void resetMandates();

private:
    QString name;
    int votes;
    int mandates;
};

