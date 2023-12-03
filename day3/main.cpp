#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <array>

std::vector<std::vector<char>> readData() {
    std::ifstream file;
    file.open("input.txt");
    std::vector<std::vector<char>> data{};
    std::string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        std::vector<char> row{};
        for (auto c: line) {
            row.push_back(c);
        }
        data.push_back(row);
    }
    return data;
}

struct Coordinates {
    int x;
    int y;
    constexpr Coordinates(int x, int y) : x(x), y(y) {};
    constexpr bool operator==(const Coordinates& other) const {
        return x == other.x && y == other.y;
    }
};

struct CoordinatesHash {
    std::size_t operator()(const Coordinates& c) const {
        return std::hash<int>()(c.x) * std::hash<int>()(c.y);
    }
};


bool isPart(const std::vector<Coordinates>& currNumIdxs, const std::vector<std::vector<char>>& grid) {
    const std::array<Coordinates, 8> directions {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}}};
    for (auto [x, y]: currNumIdxs) {
        for (auto [dx, dy]: directions) {
            auto nr {dx + x};
            auto nc {dy + y};
            if (nr < 0 || nr >= grid.size() || nc< 0 || nc >= grid[0].size()) continue;
            if (!isdigit(grid[nr][nc]) && grid[nr][nc] != '.') {
                return true;
            }
        }
    }
    return false;
}

int getPartsSum(const std::vector<std::vector<char>>& grid) {
    std::vector<Coordinates> currNumIdxs{};
    std::string currNum{""};
    int totalPartsSum{0};
    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            if (isdigit(grid[r][c])) {
                currNumIdxs.emplace_back(r, c);
                currNum += grid[r][c];
            } else if (!currNum.empty()) {
                totalPartsSum += isPart(currNumIdxs, grid) ? stoi(currNum) : 0;
                currNumIdxs = {};
                currNum = "";
            }
        }
    }
    totalPartsSum += isPart(currNumIdxs, grid) ? stoi(currNum) : 0;
    return totalPartsSum;
}

void incrementPart(
    std::unordered_map<Coordinates, std::unordered_set<int>, CoordinatesHash>& adjacentPartCount,
    const std::vector<Coordinates>& currNumIdxs, 
    const std::vector<std::vector<char>>& grid,
    const int& numId
) 
{
    const std::array<Coordinates, 8> directions {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}}};
    for (auto [x, y]: currNumIdxs) {
        for (auto [dx, dy]: directions) {
            auto nr {dx + x};
            auto nc {dy + y};
            if (nr < 0 || nr >= grid.size() || nc< 0 || nc >= grid[0].size()) continue;
            if (grid[nr][nc] == '*') {
                adjacentPartCount[{nr, nc}].insert(numId);
            }
        }
    }
}

int getPartsRatio(const std::vector<std::vector<char>>& grid) {
    std::unordered_map<Coordinates, std::unordered_set<int>, CoordinatesHash> adjacentPartCount{};
    std::vector<Coordinates> currNumIdxs{};
    std::string currNum{""};
    int totalPartsRatio{0};
    std::unordered_map<int, int> idToNum{};
    int numId{0};
    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            if (isdigit(grid[r][c])) {
                currNumIdxs.emplace_back(r, c);
                currNum += grid[r][c];
            } else if (!currNum.empty()) {
                incrementPart(adjacentPartCount, currNumIdxs, grid, numId);
                idToNum[numId] = stoi(currNum);
                currNumIdxs = {};
                currNum = "";
                numId++;
            }
        }
    }
    if (!currNum.empty()) {
        incrementPart(adjacentPartCount, currNumIdxs, grid, numId);
        idToNum[numId] = stoi(currNum);
    }

    for (auto [star, idList]: adjacentPartCount) {
        if (idList.size() == 2) {
            int gearRatio{1};
            for (auto id: idList) {
                gearRatio *= idToNum[id];
            }
            totalPartsRatio += gearRatio;
        }
    }
    return totalPartsRatio;
}

int main() {
    auto data {readData()};
    int totalPartsSum(getPartsSum(data));
    int totalPartsRatio(getPartsRatio(data));
    std::cout << "Part 1 ans: " <<  totalPartsSum << '\n';
    std::cout << "Part 2 ans: " << totalPartsRatio << '\n';
    return 0;
}