
#include <random>
#include <vector>
#include <iostream>
using namespace std;

struct Node{
    long phone_number;
    string adress;

    Node(long n, string adr){
        this->adress = adr;
        this->phone_number = n;
    }
};
class HashMap{
    int capacity = 5;
    int amount_of_elems = 0;
    vector<Node*> table;
public:
    HashMap(){
        table.resize(capacity);
        for (int i = 0; i < capacity; i++){
            table[i] = nullptr;
        }
    }
    long hashcode(long key){
        return key % capacity;
    }

    void insertNode(long key, string adress){
        Node *node = new Node(key, adress);
        if (amount_of_elems == capacity){
            capacity += 100;
            vector<Node*> temp;
            temp.resize(capacity);
            for (int i = 0; i < capacity; i++){
                temp[i] = nullptr;
            }
            for (int i = 0; i < capacity-100; i++){
                long hashInd = hashcode(table[i]->phone_number);
                while (temp[hashInd] != nullptr
                       && temp[hashInd]->phone_number != table[i]->phone_number
                       && temp[hashInd]->phone_number != -1){
                    hashInd++;
                    hashInd %= capacity;
                }
                temp[hashInd] = table[i];
            }
            table = temp;
        }
        long hashIndex = hashcode(key);
        while (table[hashIndex] != nullptr
               && table[hashIndex]->phone_number != key
               && table[hashIndex]->phone_number != -1){
            hashIndex++;
            hashIndex %= capacity;
        }
        if (table[hashIndex] == nullptr || table[hashIndex]->phone_number == -1){
            amount_of_elems ++;
        }
        table[hashIndex] = node;
    }

    Node* deleteNode(long key){
        long hashInd = hashcode(key);
        while (table[hashInd] != nullptr){
            if (table[hashInd]->phone_number == key){
                Node* temp = table[hashInd];
                table[hashInd] = new Node(-1, "");
                amount_of_elems--;
                return temp;
            }
            hashInd++;
            hashInd %= capacity;
        }
        return nullptr;
    }
    Node* getNode(long key){
        long hashInd = hashcode(key);
        int count = 0;
        while (table[hashInd] != nullptr){
            if (count++ > capacity){
                return nullptr;
            }
            if (table[hashInd]->phone_number == key){
                return table[hashInd];
            }
            hashInd++;
            hashInd %= capacity;
        }
        return nullptr;
    }
    int sizeOfTable() const{
        return amount_of_elems;
    }
    void coutTable(){
        for (int i = 0; i < capacity; i++) {
            if (table[i] != nullptr && table[i]->phone_number != -1){
                cout << "Phone number is " << table[i]->phone_number << ", address is " << table[i]->adress << endl;
            }
        }
    }
};

int main(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 9);
    for (int k = 0; k < 100; k++){
        long temp;
        auto* table = new HashMap;
        for (int i = 0; i < 7; i++){
            string phone_number = "9";
            for (int j = 0; j < 9; j++){
                phone_number += to_string(dist(gen));
            }
            long number = stol(phone_number);
            temp = number;
            table->insertNode(number, "moscow");
        }

        table->coutTable();
    }

}
