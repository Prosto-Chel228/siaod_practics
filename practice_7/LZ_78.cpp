#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isKeyInMap(string &buffer, vector<pair<string, long> > &map) {
    for (auto & i : map) {
        if (i.first == buffer) {
            return true;
        }
    }
    return false;
}
void setValueToKey(string key, long value, vector<pair<string, long> > &map) {
    map.push_back(make_pair(key, value));
}
int findLastKey(string &buffer, vector<pair<string, long> > &map) {
    int i;
    for (i = 0; i < map.size(); i++) {
        if (map[i].first == buffer) {
            return i+1;
        }
    }
    return -1;
}
void LZ_78(string &input) {
    vector<pair<string, long> > map;
    string buffer;
    int offset = 0;
    int countLength = 0;
    for (int i = 0; i < input.length(); i++) {
        buffer += input[i];
        if (isKeyInMap(buffer, map)) {
            countLength++;
            offset = findLastKey(buffer, map);
        }
        else if (!isKeyInMap(buffer, map) && i != input.length()-1) {
            countLength = 0;
            setValueToKey(buffer, offset, map);
            offset = 0;
            buffer = "";
        }
        else if (!isKeyInMap(buffer, map) && i == input.length()-1) {
            countLength = 0;
            buffer += "*";
            setValueToKey(buffer, offset, map);
            offset = 0;
            buffer = "";
        }
    }
    for (int i = 0; i < map.size(); i++) {
        cout << "( " << map[i].second << " , " << map[i].first[map[i].first.length()-1] << " )" << endl;
    }
}

int main() {
    string input;
    cout << "Введите строку для сжатия: ";
    input = "abracadabrarabarabara";
    cout << input << endl;
    LZ_78(input);
    return 0;
}

