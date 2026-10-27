#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <chrono>

struct PriceLevel {
    double price;
    long total_volume;
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream file("trades.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open trades.csv!\n";
        return 1;
    }

    std::string line;
    std::getline(file, line);

    std::unordered_map<double, long> volume_by_price;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string temp;

        std::getline(ss, temp, ',');

        std::getline(ss, temp, ',');
        double price = std::stod(temp);

        std::getline(ss, temp, ',');
        long quantity = std::stol(temp);

        volume_by_price[price] += quantity;
    }
    file.close();

    std::vector<PriceLevel> levels;
    for (const auto& pair : volume_by_price) {
        levels.push_back({pair.first, pair.second});
    }

    std::sort(levels.begin(), levels.end(), [](const PriceLevel& a, const PriceLevel& b) {
        return a.total_volume > b.total_volume;
    });

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "--- Top Price Levels by Volume ---\n";
    for (size_t i = 0; i < 3 && i < levels.size(); i++) {
        std::cout << "Price:  " << levels[i].price << " | Volume:  " << levels[i].total_volume << "\n";
    }

    std::cout << "\nExecution time:  " << duration.count() << "ms\n";

    return 0;
}