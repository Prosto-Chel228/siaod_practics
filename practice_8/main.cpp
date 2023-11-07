#include <iostream>
#include <vector>

using namespace std;
struct Item{
    int weight;
    int cost;
    Item(int weight, int cost) {
        this->weight = weight;
        this->cost = cost;
    }
};
int main() {
    int itemCount, bagCap;
    vector<Item> items;
    cout << "Введите количество предметов: ";
    cin >> itemCount;
    cout << "Введите вместимость рюкзака: ";
    cin >> bagCap;
    for (int i = 0; i < itemCount; i++) {
        int weight;
        int cost;
        cout << "Введите стоимость " << i + 1 << " предмета: ";
        cin >> cost;
        cout << "Введите вес " << i + 1 << " предмета: ";
        cin >> weight;
        cout << "============================================\n";
        items.push_back(Item(weight, cost));
    }
    vector<vector<int> > table(itemCount + 1);
    for (int i = 0; i < itemCount + 1; i++) {
        table[i].resize(bagCap + 1);
        for (int j = 0; j < bagCap + 1; j++) {
            table[i][j] = 0;
        }
    }
    for (int i = 0; i < itemCount + 1; i++) {
        for (int j = 0; j < bagCap + 1; j++) {
            if (i == 0 || j == 0) {
                table[i][j] = 0;
            }
            else if (items[i-1].weight <= j) {
                table[i][j] = max(items[i-1].cost + table[i-1][j - items[i-1].weight], table[i-1][j]);
            }
            else {
                table[i][j] = table[i-1][j];
            }
        }
    }
    int max = 0;
    for (int i = 0; i < bagCap+1; i++) {
        if (table[itemCount][i] > max) {
            max = table[itemCount][i];
        }
    }
    cout << "Максимальная стоимость предметов: " << max;
}