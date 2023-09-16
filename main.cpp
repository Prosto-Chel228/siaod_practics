#include <iostream>
#include <fstream>
#include <random>
#include "vector"
#include <ctime>
using namespace std;

struct polis{
    string number, surname, company = "Капитал МС";
    polis(string number, string surname){
        this->number = number;
        this->surname = surname;
    }
    polis(){}
};

bool compare(const pair<string, int>& p1, const pair<string, int>& p2){
    return (p1.first < p2.first);
}

struct table_polis{
    vector<pair<string, int>> tab;
    void sort_table(){
        sort(tab.begin(), tab.end(), compare);
    }
};

int fibMonaccianSearch(vector<pair<string, int>> table, const string& x)
{
    int n = table.size();
    int fibMMm2 = 0; // (m-2)'th Fibonacci No.
    int fibMMm1 = 1; // (m-1)'th Fibonacci No.
    int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (stoll(table[i].first) < stoll(x)) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }

        else if (stoll(table[i].first) > stoll(x)) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }

        else
            return table[i].second;
    }

    if (fibMMm1 && stoll(table[offset + 1].first) == stoll(x))
        return table[offset + 1].second;

    return -1;
}

void linearSearch(const string& path, string &key){
    polis obj;
    ifstream fin;
    fin.open(path, ios::in | ios::binary);
    while(!fin.eof()){
        fin.read((char*)&obj, sizeof obj);
        if (obj.number == key){
            cout << "Result: " << obj.number << ", " << obj.surname << ", " << obj.company << endl;
            fin.close();
            return;
        }
    }
    fin.close();
    cout << "Object was not found" << endl;
}

string recordInFile(int offset, ifstream& fin){
    polis obj;
    fin.seekg(offset, fin.beg);
    fin.read((char*)&obj, sizeof obj);
    return "Result: " + obj.number + ", " + obj.surname + ", " + obj.company;
}

int main() {
    table_polis table;
    ofstream fout, txtfile;
    fout.open("/Users/evgenij/siaod_2/Polis_bin.dat", ios::binary);
    txtfile.open("/Users/evgenij/Desktop/Polis.txt");
    random_device rd;
    mt19937 gen(rd());
    string surnames[] = {"Дроздов", "Гаврилов", "Гулякин", "Крупнов", "Петров", "Устинов"};
    uniform_int_distribution<> dist(0, 9);
    for (int i = 0; i < 10000; i++){
        string number;
        for (int j = 0; j < 16; j++){
            number += to_string(dist(gen));
        }
        polis obj(number, surnames[gen()%6]);
        pair<string, int> p(number, i*sizeof(obj));
        table.tab.push_back(p);
        fout.write((char*)&obj, sizeof(obj));
        txtfile << obj.number << ", " << obj.surname << ", " << obj.company << endl;
    }
    clock_t sort_start = clock();
    table.sort_table();
    clock_t sort_end = clock();
    double sort_time = (double) (sort_end - sort_start)/CLOCKS_PER_SEC;
    fout.close();
    txtfile.close();
    string key;
    int n;
    cout << "Enter key: ";
    cin >> key;
    cout << "Choose the way you want to find the object: 1 - linear search, 2 - Fibonachi search. Your choice: ";
    cin >> n;
    if (n == 1) {
        clock_t linSearch_start = clock();
        linearSearch("/Users/evgenij/siaod_2/Polis_bin.dat", key);
        clock_t linSearch_end = clock();
        double linSearch_time = (double) (linSearch_end - linSearch_start) / CLOCKS_PER_SEC;
        cout << "Work time: " << linSearch_time;
    }
    else if (n == 2) {
        clock_t fibSearch_start = clock();
        int offset = fibMonaccianSearch(table.tab, key);
        clock_t fibSearch_end = clock();
        double fibSearch_time = (double) (fibSearch_end - fibSearch_start) / CLOCKS_PER_SEC;
        if (offset != -1){
            ifstream fin;
            fin.open("/Users/evgenij/siaod_2/Polis_bin.dat");
            cout << recordInFile(offset, fin) << endl;
            cout << "Work time: " << fibSearch_time + sort_time;
        }
        else{
            cout << "Object was not found." << endl;
            return 0;
        }
    }
    else {
        cout << "Incorrect input! Restart the program.";
        return 0;
    }
    return 0;
}
