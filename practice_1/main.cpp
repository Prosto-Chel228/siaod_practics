#include <iostream>
#include <bitset>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <ctime>
using namespace std;
void first_a(){
    unsigned char x = 255;
    unsigned char maska = 1;
    x = x & (~(maska<<4));
    cout << (int)x << endl;
    //ответ 239.
    x = 167; //10100111
    x = x & (~(maska<<4)); //(~maska<<4) = 11101111
    cout << (int)x;
    //ответ 167.
}
void first_b(){
    unsigned char x = 255;
    unsigned char maska = 1;
    x = x & (~(maska<<6));
    cout << (int)x;
    //ответ 191
}
void first_c(){
    unsigned int x = 25;
    const int n = sizeof(int)*8; //размер типа int в байтах умножаем на 8, чтобы узнать количество бит
    unsigned maska = (1 << (n-1)); //сдвигаем 1 влево так, чтобы длина всего числа в 2 СС была такой же, как у int
    cout << "Начальный вид маски: " << bitset<n> (maska) << endl; //выводим маску в 2 СС
    cout << "Результат: ";
    for (int i = 1; i <= n; i++){
        cout << ((x & maska) >> (n-i)); //если значение бита в "x" и в маске равны 1 (ноль), то эту единицу (ноль)
        // сдвигаем влево до конца.
        maska = maska >> 1; //укорачиваем маску на один разряд справа
    }
    cout << endl;

}
void second_a(){
    unsigned char maska = (0 << 7);
    short int x, n;
    cout << "Введите количество чисел: ";
    while (true){
        cin >> n;
        if (n > 0 && n < 9) break;
        else{
            cout << "Повторите ввод!";
        }
    }
    cout << "Введите далее " << n << " чисел, каждое >= 0 и <= 7:" << endl;
    for (int i = 0; i < n; i++){
        cout << "Введите " << i+1 << " число: ";
        cin >> x;
        maska = (maska | (1 << (x-1)));
    }
    cout << "Отсортированный набор: ";
    for (int i = 0; i < 8; i++) {
        if (((maska >> i) & 1) == 1) {
            cout << i + 1 << " ";
        }
    }
}
void second_b(){
    unsigned long long int maska = 0ULL << 63;
    short int x, n;
    cout << "Введите количество чисел: ";
    while (true){
        cin >> n;
        if (n > 0 && n < 65) break;
        else{
            cout << "Повторите ввод!";
        }
    }
    cout << "Введите далее " << n << " чисел, каждое >= 0 и <= 63:" << endl;
    for (int i = 0; i < n; i++){
        cout << "Введите " << i+1 << " число: ";
        cin >> x;
        maska = (maska | (1ULL << (x-1)));
    }
    cout << "Отсортированный набор: ";
    for (int i = 0; i < 64; i++) {
        if (((maska >> i) & 1) == 1) {
            cout << i + 1 << " ";
        }
    }
}
void second_c(){
    unsigned char maska[8];
    for (int i = 0; i < 8; i++){
        maska[i] = (0 << 7);
    }
    short int x, n;
    cout << "Введите количество чисел: ";
    while (true){
        cin >> n;
        if (n > 0 && n < 65) break;
        else{
            cout << "Повторите ввод!" << endl;
            cout << "Введите количество чисел: ";
        }
    }
    cout << "Введите далее " << n << " чисел, каждое >= 0 и <= 63:" << endl;
    for (int i = 0; i < n; i++){
        cout << "Введите " << i+1 << " число: ";
        cin >> x;
        maska[x/8] = maska[x/8] | (1 << (((x/8) * 8 + 7)-x));
    }
    for (int i = 0; i < 8; i++){
        for (int j = 7; j >= 0; j--){
            if (((maska[i] >> j) & 1) == 1){
                cout << (i*8 + 7 - j) << " ";
            }
        }
    }
}
void third(){
    vector<bool> maska(10000000);

    ifstream fin;
    fin.open("/Users/evgenij/siaod_1/test.txt");
    short int x;

    while(!fin.eof()){
        fin >> x;
        maska[x] = 1;
    }
    fin.close();
    ofstream fout;
    fout.open("/Users/evgenij/siaod_1/test.txt");
    clock_t start = clock();
    for (int i = 0; i < 10000000; i++){
        if (maska[i] == 1){
            fout << i << endl;
        }
    }
    fout.close();
    clock_t end = clock();
    double time = (double)(end - start)/CLOCKS_PER_SEC;
    cout << "Время работы: " << time << endl;
    cout << "Занимаемая память: " << sizeof(maska)*8 << " бит";
}
int main() {
    third();
    return 0;
}
