#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

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

std::vector<std::vector<std::unordered_map<std::string, int>>> readData() {
    std::ifstream file;
    file.open("input.txt");
    std::vector<std::vector<std::unordered_map<std::string, int>>> data{};
    std::string line;
    while (getline(file, line)) {
        auto tokens{ssplit(line, ':')};
        auto sets{ssplit(tokens[1], ';')};
        std::vector<std::unordered_map<std::string, int>> game{};
        for (auto set: sets) {
            std::unordered_map<std::string, int> cubeCount{};
            auto parts{ssplit(set, ',')};
            for (auto part: parts) {
                auto count{ssplit(part, ' ')};
                cubeCount[count[2]] += stoi(count[1]);
            }
            game.push_back(cubeCount);
        }
        data.push_back(game);

    }
    return data;
}

bool isGamePossible(std::vector<std::unordered_map<std::string, int>> game) {
    for (auto set: game) {
        if (set["red"] > 12 || set["green"] > 13 || set["blue"] > 14) return false;
    }
    return true;
}

int getCubePower(std::vector<std::unordered_map<std::string, int>> game) {
    std::unordered_map<std::string, int> minCubeCount{
        {"red", 0}, {"green", 0}, {"blue", 0}
    };
    for (auto set: game) {
        minCubeCount["red"] = std::max(minCubeCount["red"], set["red"]);
        minCubeCount["green"] = std::max(minCubeCount["green"], set["green"]);
        minCubeCount["blue"] = std::max(minCubeCount["blue"], set["blue"]);
    }
    return minCubeCount["red"] * minCubeCount["green"] * minCubeCount["blue"];
}

int main() {
    auto data{readData()};
    int possibleGames{0};
    int cubePowerSum{0};
    int id{1};
    for (auto game: data) {
        possibleGames += isGamePossible(game) ? id : 0;
        cubePowerSum += getCubePower(game);
        id++;
        
    }
    std::cout << possibleGames << '\n';
    std::cout << cubePowerSum << '\n';
    return 1;
}