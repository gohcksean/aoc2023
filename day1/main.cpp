#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

vector<string> readData() {
    ifstream file;
    file.open("input.txt");
    vector<string> data{};
    while (!file.eof()) {
        string line;
        getline(file, line);
        data.push_back(line);
    }
    file.close();
    return data;
}

int getDigit(string line) {
    int firstIdx{-1};
    int lastIdx{-1};
    for (int i = 0; i < line.size(); i++) {
        if (isdigit(line[i])) {
            firstIdx = firstIdx == -1 ? i : firstIdx;
            lastIdx = i;
        }
    }
    string s {line[firstIdx], line[lastIdx]};
    return stoi(s);
}

int getDigitWithStrings(string line) {
    const unordered_map<string, char> DIGITS {
        {"nine", '9'}, {"eight", '8'}, {"seven", '7'},
        {"six", '6'}, {"five", '5'}, {"four", '4'},
        {"three", '3'}, {"two", '2'}, {"one", '1'}
    };
    char firstNum{};
    char lastNum{};
    for (int i = 0; i < line.size(); i++) {
        if (isdigit(line[i])) {
            firstNum = firstNum == '\0' ? line[i] : firstNum;
            lastNum = line[i];
        } else {
            for (auto [digit, value]: DIGITS) {
                if (line.substr(i, digit.size()) == digit) {
                    firstNum = firstNum == '\0' ? value : firstNum;
                    lastNum = value;
                    break;
                }
            }
        }
    }
    string s{firstNum, lastNum};
    return stoi(s);
}

int main()
{
    auto data{readData()};
    int ans{0};
    int ansWithStrings{0};
    for (auto line: data) {
        if (line.empty()) continue;
        ans += getDigit(line);
        ansWithStrings += getDigitWithStrings(line);
    }
    cout << ans << '\n';
    cout << ansWithStrings << '\n';
    return ans;
}