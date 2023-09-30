#include "iostream"
#include "map"
#include "vector"
#include "algorithm"
using namespace std;
void first_task(){
    string sentence;
    cout << "Enter your sentence: ";
    getline(cin, sentence);
    map<int, vector<string>> words;
    string temp;
    for (int i = 0; i < sentence.length(); i++){
        if (sentence[i] != ' ' && sentence[i] != ','){
            temp += sentence[i];
            if (i == sentence.length()-1){
                if (temp.length() != 0)
                    words[temp.length()].push_back(temp);
            }
        }
        else{
            if (temp.length() != 0)
                words[temp.length()].push_back(temp);
            temp = "";
        }
    }

    int min = 2e9;
    map<int, vector<pair<string, string>>> mins;
    for (const auto& [length, word] : words){
        if (word.size() > 1){
            for (int j = 0; j < word.size(); j++){
                for (int k = j+1; k < word.size(); k++){
                    int count = 0;
                    for (int l = 0; l < length; l++){
                        if (word[j][l] != word[k][l]){
                            count++;
                        }
                    }
                    if (count <= min){
                        min = count;
                        pair<string, string> pair;
                        pair.first = word[j];
                        pair.second = word[k];
                        mins[min].push_back(pair);
                    }
                }
            }
        }
    }
    if (!mins.empty()){
        vector<pair<string, string>> pairs = mins.begin()->second;
        for (int i = 0; i < pairs.size(); i++){
            cout << pairs[i].first << " " << pairs[i].second << endl;
        }
    }


}


vector<int> calculateBadMatchTable(const string& pattern) {
    vector<int> badMatchTable(256, -1);
    int patternLength = pattern.length();

    for (int i = 0; i < patternLength; i++) {
        badMatchTable[pattern[i]] = i;
    }

    return badMatchTable;
}

vector<int> calculateGoodSuffixTable(const string& pattern) {
    int patternLength = pattern.length();
    vector<int> border(patternLength + 1, 0);
    vector<bool> suffix(patternLength + 1, false);

    int j = patternLength;
    int k = j + 1;
    border[j] = k;

    while (j > 0) {
        while (k <= patternLength && pattern[j - 1] != pattern[k - 1]) {
            if (!suffix[k]) {
                border[k] = max(border[k], k - j);
            }

            k = border[k];
        }

        j--;
        k--;
        suffix[j] = (k > 0 && pattern[j - 1] == pattern[k - 1]);
        border[j] = k;
    }
    k = border[0];

    for (j = 0; j <= patternLength; j++) {
        if (!suffix[j]) {
            border[j] = max(border[j], k);
        }

        if (j == k) {
            k = border[k];
        }
    }
    for (int i = 0; i < border.size(); i++){
        cout << border[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < suffix.size(); i++){
        cout << suffix[i] << " ";
    }
    cout << endl;
    return border;
}

vector<int> boyerMoore(const string& text, const string& pattern) {
    vector<int> answer;
    int textLength = text.length();
    int patternLength = pattern.length();

    vector<int> badMatchTable = calculateBadMatchTable(pattern);
    vector<int> goodSuffixTable = calculateGoodSuffixTable(pattern);

    int shift = 0;
    while (shift <= textLength - patternLength) {
        int j = patternLength - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            answer.push_back(shift);
            shift += (shift + patternLength < textLength) ? patternLength - badMatchTable[text[shift + patternLength]] : 1;
        } else {

            int badMatchShift = max(1, j - badMatchTable[text[shift + j]]);
            int goodSuffixShift = goodSuffixTable[j + 1];

            int turboShift = min(badMatchShift, goodSuffixShift);

            if (turboShift == 0) {
                turboShift = 1;
            }
            shift += turboShift;
        }
    }
    return answer;
}
int main(){
//    string text = "ABAAABCDABCFF";
//    string pattern = "ABC";
//
//    vector<int> inds = boyerMoore(text, pattern);
//    for (int i = 0; i < inds.size(); i++){
//        cout << inds[i] << endl;
//    }
    first_task();
}
