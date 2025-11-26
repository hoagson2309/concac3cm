#ifndef MONEY_DATABASE_H
#define MONEY_DATABASE_H

#include <array>
#include <iostream>
#include "deposit.h"


struct MoneyDatabase{
    std::array<Deposit, 100> deposits_{}; //std::array<std::string, 42> my_numbers{}; => Deposit deposits_[100]; (C - style) 
    int size_ = 0; 

    void add(Deposit deposit);
    int size() const;
    Deposit get(int index) const;
    double total_of(std::string currency_code) const;
};

inline std::ostream& operator<<(std::ostream& out, MoneyDatabase const& db) //function making it faster to print to the output
{
  out << "Database with size " << db.size_ << " and capacity " << db.deposits_.size() << '\n';
  out << "Deposits are:\n[\n";
  auto comma = "  ";
  for (auto i{0}; i < db.size_; ++i)
  {
    out << comma << db.deposits_[i];
    comma = ",\n  ";
  }

  return out << "\n]";
}

#endif //MONEY_DATABASE_H
