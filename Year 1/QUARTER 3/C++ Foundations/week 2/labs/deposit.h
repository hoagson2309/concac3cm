#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <iostream>
#include <iomanip>
#include <string>

struct Deposit {
    std::string currency;
    double amount;
};

inline std::ostream& operator<<(std::ostream& out, Deposit const& dep) {
    return out << dep.currency << ' ' << std::fixed << std::setprecision(2) << dep.amount;
}

#endif // DEPOSIT_H