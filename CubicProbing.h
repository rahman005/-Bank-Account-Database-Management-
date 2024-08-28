#ifndef CUBICPROBING_H
#define CUBICPROBING_H

#include "BaseClass.h"
#include <iostream>

class CubicProbing : public BaseClass {
public:
    CubicProbing();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    void merge_cubProb(std::vector<int>& vec, int l, int m, int r);
    void mergeSort_cubProb(std::vector<int>& balances, int l, int r);
    int no_of_accountsInBank;
    std::vector<int> status;
    // Other data members and functions specific to Quadratic Probing
};

#endif // CUBICPROBING_H
