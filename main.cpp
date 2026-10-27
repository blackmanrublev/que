#include <iostream>
#include <vector>
#include <string>
#include <numeric>

int main() {
    std::vector<double> prices = {100.5, 101.2, 99.8, 100.9};

    double total = 0.0;
    for (double p : prices) {
        total += p;
    }

    double average = total / prices.size();

    std::cout << "Prices: ";
    for (double p : prices) {
        std::cout << p << " ";
    }
    std::cout << "\n";
    std::cout << "Total:    " << total << "\n";
    std::cout << "Average   " << average << "\n";
    std::cout << "Count:    " << prices.size() << "\n";

    return 0;
}