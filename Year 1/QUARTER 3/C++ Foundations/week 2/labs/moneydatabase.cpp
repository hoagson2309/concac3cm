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