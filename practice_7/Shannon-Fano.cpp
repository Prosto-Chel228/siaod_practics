
#include <iostream>
#include "vector"
#include "map"
using namespace std;

struct node {
    char letter;
    string code;
    double probability;
};
void sortByProbability(vector<node> &nodes) {
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = i+1; j < nodes.size(); j++) {
            if (nodes[i].probability < nodes[j].probability) {
                node tmp = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = tmp;
            }
        }
    }
}
void shannonFano(int leftBorder, int rightBorder, vector<node> &nodes) {
    if (leftBorder == rightBorder - 1) {
        return;
    }
    int start = leftBorder;
    int end = rightBorder-1;
    int endOfLeftPart = 0;
    int startOfRightPart = 0;
    double leftSum = 0;
    double rightSum;
    double sum = 0;
    for (int i = start; i <= end; i++) {
        sum += nodes[i].probability;
    }
    double minDiff = sum;
    for (int i = start; i <= end; i++) {
        leftSum += nodes[i].probability;
        rightSum = sum - leftSum;
        if (abs(leftSum - rightSum) < minDiff) {
            minDiff = abs(leftSum - rightSum);
        }
        else {
            startOfRightPart = i;
            endOfLeftPart = i-1;
            break;
        }
    }
    for (int i = start; i <= endOfLeftPart; i++) {
        nodes[i].code += "0";
    }
    for (int i = startOfRightPart; i <= end; i++) {
        nodes[i].code += "1";
    }
    shannonFano(start, endOfLeftPart+1, nodes);
    shannonFano(startOfRightPart, end+1, nodes);
}
int main()
{
    vector<node> nodes;
    int n;
    node temp;
    //string str = "Кони-кони, коникони, Мы сидели на балконе, Чай пили, воду пили, По-турецки говорили.";
    string str = "Koni-koni, konikoni, Mi sideli na balkone, Chai pili, vodu pili, Po-turetsky govorili.";
    map<char, double> letters;
    for (char k : str) {
        letters[k] = 0;
    }
    for (char k : str) {
        letters[k] += 1;
    }
    n = letters.size();
    cout << "Number of symbols: " << n << endl;
    nodes.resize(n);
    int counter = 0;
    for (const auto& [letter, count] : letters) {
        cout << "Symbol " << counter + 1 << ": ";
        cout << letter << endl;
        nodes[counter].letter = letter;
        nodes[counter].probability = count / str.length();
        counter++;
    }

    for (int i = 0; i < n; i++) {
        cout << "\nProbability of " << nodes[i].letter << ": ";
        cout << nodes[i].probability << endl;

    }
    sortByProbability(nodes);
    shannonFano(0, n, nodes);
    cout << "\n\nSymbol     code" << endl;
    for (node i : nodes) {
        cout << "  " << i.letter << "        " << i.code << endl;
    }
    return 0;
}
