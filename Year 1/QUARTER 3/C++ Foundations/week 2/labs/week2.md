# Week 2 - C++

Name: SON CAO

Group: ETI1V.IA

Date: 10/2/2025

# LABS
```cpp
//DEPOSIT.H
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

//MONEY_DATABASE.H
#ifndef MONEY_DATABASE_H
#define MONEY_DATABASE_H

#include <array>
#include <iostream>
#include "deposit.h"


struct MoneyDatabase{
    std::array<Deposit, 100> deposits_{}; //std::array<std::string, 42> my_numbers{}; => Deposit deposits_[100]; (C - style) 
    int size_ = 0; //Change the type of size_ from int to size_t to match the type returned by deposits_.size()

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

//MONEYDATABASE.CPP
#include "money_database.h"

void MoneyDatabase::add(Deposit deposit){
    if(size_ < deposits_.size() && deposit.currency.size() == 3 && deposit.amount >= 0){
        deposits_[size_] = deposit;
        size_++;
    } else{
        std::cerr << "Error: cannot add deposit. Invalid currency code, negative amount, or data base is full.\n";
    }
}

int MoneyDatabase::size() const { //change type to size_t too
    return size_;
}

Deposit MoneyDatabase::get(int index) const {
    if(index >= 0 && index < size_){
        return deposits_[index];
    }
    return Deposit{"INV", 0};
}

double MoneyDatabase::total_of(std::string currency_code) const {
    double total = 0;
    for(int i = 0; i < size_; i++){
        if(deposits_[i].currency == currency_code){
            total += deposits_[i].amount;
        }
    }
    return total;
}

//MAIN.CPP
#include <iostream>
#include "money_database.h"

int main(){
    MoneyDatabase db{};

    std::cout << "Enter a currency code, followed by an amount of money. Enter \"quit\" to stop.\n";
    
    auto should_quit = false;

    while(!should_quit){
        std::string currency{};
        double amount{};

        std::cin >> currency;
        if(currency == "quit"){
            should_quit = true;
        } else if (currency.size() == 3){
            std::cin >> amount;
            db.add(Deposit{currency, amount});
        } else{
            std::cout << "Negative amount is not allowed. Please try again.\n";
        }
    }

    std::string currencycode;
    std::cout << "Enter currency_code u want: ";
    std::cin >> currencycode;
    
    std::cout << "The database contains " << db.size() << " entries.\n";
    std::cout << "The total amount of money in euros is " << db.total_of(currencycode) << ".\n";
    
    return 0;
}
```