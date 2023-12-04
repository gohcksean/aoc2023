#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

std::vector<std::string> ssplit(std::string line, char delimiter) {
    std::stringstream ss(line);
    std::vector<std::string> tokens{};
    std::string token;
    while (!ss.eof()) {
        getline(ss, token, delimiter);
        tokens.push_back(token);
    }
    return tokens;
}

struct Game {
    std::unordered_set<int> winningNumbers;
    std::vector<int> presentNumbers;
    Game(std::unordered_set<int> w, std::vector<int>p) : winningNumbers(w), presentNumbers(p) {};
};

std::vector<Game> readData() {
    std::ifstream file;
    file.open("input.txt");
    std::vector<Game> data{};
    std::string line;
    while (getline(file, line)) {
        auto numbers{ssplit(line, ':')};
        auto lists{ssplit(numbers[1], '|')};
        auto w{ssplit(lists[0], ' ')};
        auto p{ssplit(lists[1], ' ')};
        std::unordered_set<int> winningNumbers{};
        for (auto num: w) {
            if (num.empty()) continue;
            winningNumbers.insert(stoi(num));
        }
        std::vector<int> presentNumbers{};
        for (auto num: p) {
            if (num.empty()) continue;
            presentNumbers.push_back(stoi(num));
        }
        data.emplace_back(winningNumbers, presentNumbers);
    }
    return data;
}

int calculateTotalPoints
(
    const std::vector<Game>& games
)
{
    int totalPoints{0};
    for (auto game: games) {
        int currPoints{0};
        for (auto num: game.presentNumbers) {
            if (game.winningNumbers.find(num) != game.winningNumbers.end()) {
                currPoints = currPoints == 0 ? 1 : currPoints * 2;
            }
        }
        totalPoints += currPoints;
    }
    return totalPoints;
}

int countMatches(const Game& game) {
    int matches{0};
    for (auto num: game.presentNumbers) {
        if (game.winningNumbers.find(num) != game.winningNumbers.end()) {
            matches++;
        }
    }
    return matches;
}

int calculateTotalCards
(
    const std::vector<Game>& games
)
{
    int totalCards{0};
    std::unordered_map<int, int> cardCounts{};
    for (int i=0; i < games.size(); i++) {
        cardCounts[i]++;
        auto matches{countMatches(games[i])};
        for (int c = i+1; c < i+matches+1; c++) {
            cardCounts[c] += cardCounts[i];
        }
        totalCards += cardCounts[i];
    }
    return totalCards;
}

int main() {
    auto data{readData()};
    auto totalPoints{calculateTotalPoints(data)};
    auto totalCards{calculateTotalCards(data)};
    std::cout << "Part 1 ans: " << totalPoints << '\n';
    std::cout << "Part 2 ans: " << totalCards << '\n';
    return 0;
}