#include <iostream>
#include <string>
#include <unordered_map>

class PriceDivergenceMonitor {
public:
  int threshold{};
  std::unordered_map<std::string, int> stocks{};
  std::unordered_map<std::string, std::string> pairs{};

  PriceDivergenceMonitor(int threshold) { this->threshold = threshold; }

  void RegisterPair(const std::string &stockOne, const std::string &stockTwo) {
    if (pairs.find(stockOne) != pairs.end()) {
      return;
    }

    pairs[stockOne] = stockTwo;

    if (stocks.find(stockOne) == stocks.end()) {
      stocks[stockOne] = -1;
    }

    if (stocks.find(stockTwo) == stocks.end()) {
      stocks[stockOne] = -1;
    }
  }

  void UpdatePrice(const std::string &stockName, int newPrice) {
    if (pairs.find(stockName) == pairs.end()) {
      return;
    }

    std::string otherStock = pairs[stockName];

    if (stocks[stockName] == -1 || stocks[otherStock] == -1) {
      stocks[stockName] = newPrice;
      return;
    }

    int difference{std::abs(newPrice - stocks[otherStock])};
    if (difference > this->threshold) {
      ReportDivergence(stockName, newPrice, otherStock, stocks[otherStock]);
    }

    stocks[stockName] = newPrice;
  }

private:
  void ReportDivergence(const std::string &stockOne, int updatedStockPrice,
                        const std::string &otherStock, int otherStockPrice);
};

int main() {
  std::cout << "Hello World!\n";
  return 0;
}
