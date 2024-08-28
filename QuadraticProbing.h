#ifndef QUADRATICPROBING_H
#define QUADRATICPROBING_H

#include "BaseClass.h"
#include <iostream>

class QuadraticProbing : public BaseClass {
public:
    QuadraticProbing();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;

private:
    void merge_quadProb(std::vector<int>& vec, int l, int m, int r);
    void mergeSort_quadProb(std::vector<int>& balances, int l, int r);
    int no_of_acc;
    std::vector<int> status;
    // Other data members and functions specific to Quadratic Probing
};

#endif // QUADRATICPROBING_H
