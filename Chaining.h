#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    Chaining();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    

private:
    int no_of_account;
    void merge_ch(std::vector<int>& vec, int l, int m, int r);
    void mergeSort_ch(std::vector<int>& balances, int l, int r);
    // Other data members and functions specific to Chaining
};

#endif // CHAINING_H
