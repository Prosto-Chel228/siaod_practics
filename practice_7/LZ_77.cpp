#include <iostream>
#include <vector>
#include <string>
using namespace std;
void LZ77_alg(string input) {
    #define maxWindow 10
    struct code {
        int off;
        int len;
        char nextChar;
    };
    vector<code> vt;
    string str = input;
    int window1, window2;

    for(int i = 0; i < str.length(); i++) {
        if(i + 1 <= maxWindow) {
            window1 = i;
        }
        else {
            window1 = maxWindow;
        }

        if(i + window1 < str.length()) {
            window2 = window1;
        }
        else {
            window2 = str.length() - i;
        }
        string str1 = str.substr(i - window1, window1);
        string str2 = str.substr(i, window2);

        int off = -1;
        while(true) {
            if(window2 == 0) {
                break;
            }
            string str3 = str2.substr(0, window2);
            off = str1.find(str3);
            if(off != -1) {
                break;
            }
            window2--;
            if(window2 <= 0) {
                break;
            }
        }

        if(off != -1) {
            code cd;
            cd.len = window2;
            cd.off = window1 - off;
            cd.nextChar = str[i + window2];
            vt.push_back(cd);
            i += window2;
        } else {
            code cd;
            cd.len = 0;
            cd.off = 0;
            cd.nextChar = str[i + window2];
            vt.push_back(cd);
        }
    }

    for(auto & i : vt) {
        printf("(%d,%d,%c)", i.off, i.len, i.nextChar);
    }
    cout << endl;
}


int main() {
    LZ77_alg("0100001000000100001");
    return 0;
}