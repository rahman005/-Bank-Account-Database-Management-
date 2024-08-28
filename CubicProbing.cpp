#include "CubicProbing.h"

void CubicProbing::merge_cubProb(std::vector<int>& vec, int l, int m, int r){
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



void CubicProbing::mergeSort_cubProb(std::vector<int>& balances, int l, int r) {
    if (l < r) {
        int m = l + ((r - l) / 2);

        mergeSort_cubProb(balances, l, m);
        mergeSort_cubProb(balances, m + 1, r);

        merge_cubProb(balances, l, m, r);
    }
}


CubicProbing::CubicProbing(){
    no_of_accountsInBank = 0;
    bankStorage1d.resize(100003);
    for(int i = 0;i<100003;i++){
        status.push_back(0);
    }
}
void CubicProbing::createAccount(std::string id, int count) {
    Account new_ac;
    new_ac.id = id;
    new_ac.balance = count;
    long long int h = hash(id);
    if((status[h] == 0) || (status[h] == -1)){
        bankStorage1d[h] = new_ac;
        no_of_accountsInBank++;
        status[h] = 1;
    }
    else{
        long long int i = 1;
        while(status[h] == 1 ){
            h += i*i*i;
            h = h%100003;
            i++;
        }
        bankStorage1d[h] = new_ac;
        no_of_accountsInBank++;
        status[h] =1;
    }
}

std::vector<int> CubicProbing::getTopK(int k) {
    std::vector<int> allBalances;
    std::vector<int> topKBalances;
    for(int i = 0; i<100003;i++){
        if(bankStorage1d[i].id!="")
            allBalances.push_back(bankStorage1d[i].balance);    
    }
    mergeSort_cubProb(allBalances,0,allBalances.size() - 1);
    

    if (k > no_of_accountsInBank){
        for(int p = 0; p<no_of_accountsInBank; p++){
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

int CubicProbing::getBalance(std::string id) {
    long long int h = hash(id);
    if (doesExist(id) == false){
        return -1;
    }
    else{
        int i = 1;
        while(true){
        if(bankStorage1d[h].id == id){
            return bankStorage1d[h].balance;
        }
        h += i*i*i;
        h = h%100003;
        i++;
    }
    }
}

void CubicProbing::addTransaction(std::string id, int count) {
    long long int h = hash(id);
    if (doesExist(id) == false){
        createAccount(id,count);
    }
    else{
        while(true){
            int i = 1;
        if(bankStorage1d[h].id == id){
            bankStorage1d[h].balance += count;
            break;
        }
        h += i*i*i;
        h = h%100003;
        i++;
    }
    }
}

bool CubicProbing::doesExist(std::string id) {
    long long int h = hash(id);
    int a = h;
    int i = 1;
    if(bankStorage1d[h].id == id){
            return true;
    }
    h += i*i*i;
    i++;
    h = h%100003;
    while(((status[h] == 1) || (status[h] == -1)) && (a!=h)){
        if(bankStorage1d[h].id == id){
            return true;
        }
        h += i*i*i;
        i++;
        h = h%100003;
    }
    return false;
}

bool CubicProbing::deleteAccount(std::string id) {
    long long int h = hash(id);
    if (doesExist(id) == false){
        return false;
    }
    else{
        while(true){
        int i = 1;
        if(bankStorage1d[h].id == id){
            status[h] = -1;
            bankStorage1d[h].id="";
            bankStorage1d[h].balance = 0;
            no_of_accountsInBank--;
            return true;
        }
        h += i*i*i;
        i++;
        h = h%100003;
    }
    }
}
int CubicProbing::databaseSize() {
    return no_of_accountsInBank;
}

int CubicProbing::hash(std::string id) {
    long long int ha =0;
    int len_str = id.length();
    for(int i =0;i<len_str;i++){
        ha += (id[i])*(id[i])*(i+1);
    }
    return ha % 100003;
}
