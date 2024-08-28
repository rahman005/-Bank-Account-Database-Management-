#include "Chaining.h"


Chaining::Chaining(){
    bankStorage2d.resize(100003);
    no_of_account = 0;

}


void Chaining::merge_ch(std::vector<int>& vec, int l, int m, int r){
    int leftLen = m - l + 1;
    int rightLen = r - m;

    std::vector<int> rightVec(rightLen);
    std::vector<int> leftVec(leftLen);

    for (int i = 0; i < leftLen; i++)
    {
        leftVec[i] = vec[l + i];
    }
    for (int j = 0; j < rightLen; j++){
        rightVec[j] = vec[m + 1 + j];
    }

    int leftSI = 0, rightSI = 0, k = l;

    while (leftSI < leftLen && rightSI < rightLen) {
        if (leftVec[leftSI] >= rightVec[rightSI]) {
            vec[k] = leftVec[leftSI];
            leftSI++;
        }
        else {
            vec[k] = rightVec[rightSI];
            rightSI++;
        }
        k++;
    }

    while (leftSI < leftLen) {
        vec[k] = leftVec[leftSI];
        leftSI++;
        k++;
    }

    while (rightSI < rightLen) {
        vec[k] = rightVec[rightSI];
        rightSI++;
        k++;
    }
}


void Chaining::mergeSort_ch(std::vector<int>& balances, int l, int r) {
    if (l < r) {
        int m = l + ((r - l) / 2);

        mergeSort_ch(balances, l, m);
        mergeSort_ch(balances, m + 1, r);

        merge_ch(balances, l, m, r);
    }
}



void Chaining::createAccount(std::string id, int count) {
    Account new_ac;
    new_ac.id = id;
    new_ac.balance = count;
    int h = hash(id);
    bankStorage2d[h].push_back(new_ac);
    no_of_account++;
}




std::vector<int> Chaining::getTopK(int k){
    std::vector<int> allBalances;
    std::vector<int> topKBalances;
    for(int i = 0; i<100003;i++){
        int l = bankStorage2d[i].size();
        for(int j =0;j<l;j++){
            if(bankStorage2d[i][j].id != ""){
                allBalances.push_back(bankStorage2d[i][j].balance);
            }
        }
    }

    mergeSort_ch(allBalances,0,allBalances.size() - 1);

    if(k > no_of_account){
        for(int p = 0; p<no_of_account; p++){
            topKBalances.push_back(allBalances[p]);
        }
        return topKBalances;
    }

    else{
        for(int p = 0; p<k; p++){
            topKBalances.push_back(allBalances[p]);
        }
        return topKBalances;
    }
}



int Chaining::getBalance(std::string id) {
    int h = hash(id);
    int sizeOfH = bankStorage2d[h].size();
    for(int i = 0;i<sizeOfH;i++){
        if(bankStorage2d[h][i].id == id){
            return bankStorage2d[h][i].balance;
        }
    }
    return -1;
}


void Chaining::addTransaction(std::string id, int count) {
    bool flag = false;
    int h = hash(id);
    int sizeOfH = bankStorage2d[h].size();
    for(int i = 0;i<sizeOfH;i++){
        if(bankStorage2d[h][i].id == id){
            bankStorage2d[h][i].balance += count;
            flag = true;
            break;
        }
    }
    if(!flag){
        createAccount(id,count);
    }
}


bool Chaining::doesExist(std::string id) {
    int h = hash(id);
    int sizeOfH = bankStorage2d[h].size();
    for(int i = 0;i<sizeOfH;i++){
        if(bankStorage2d[h][i].id == id){
            return true;
        }
    }
    return false; 
}


bool Chaining::deleteAccount(std::string id) {
    int h = hash(id);
    int sizeOfH = bankStorage2d[h].size();
    for(int i = 0;i<sizeOfH;i++){
        if(bankStorage2d[h][i].id == id){
            bankStorage2d[h].erase(bankStorage2d[h].begin() + i);
            no_of_account--;
            return true;
        }
    }
    return false;
}


int Chaining::databaseSize() {
    return no_of_account;
}


int Chaining::hash(std::string id) {
    int ha =0;
    int len_str = id.length();
    for(int i =0;i<len_str;i++){
        ha += (id[i])*(id[i])*(i+1);
    }
    return ha%100003;
}
