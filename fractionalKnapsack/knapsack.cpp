#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Item {
  int value, weight;

  Item(int value, int weight) : value(value), weight(weight) {}
};

bool cmp(Item a, Item b) {
  double r1 = (double)a.value / a.weight;
  double r2 = (double)b.value / b.weight;
  return r1 > r2;
}

double fractionalKnapsack(int W, vector<Item> &items) {
  sort(items.begin(), items.end(), cmp);

  int curWeight = 0;
  double finalValue = 0.0;
  for (auto &item : items) {
    if (curWeight + item.weight <= W) {
      curWeight += item.weight;
      finalValue += item.value;
    } else {
      int remain = W - curWeight;
      finalValue += item.value * ((double)remain / item.weight);
      break;
    }
  }

  return finalValue;
}

int main() {
  int n, W;
  cout << "Enter the number of items: ";
  cin >> n;

  vector<Item> items;
  cout << "Enter the value and weight of each item:\n";
  for (int i = 0; i < n; ++i) {
    int value, weight;
    cout << "Item " << i + 1 << " value: ";
    cin >> value;
    cout << "Item " << i + 1 << " weight: ";
    cin >> weight;
    items.emplace_back(value, weight);
  }

  cout << "Enter the maximum weight of the knapsack: ";
  cin >> W;

  double maxValue = fractionalKnapsack(W, items);
  cout << "Maximum value in Knapsack = " << maxValue << endl;

  return 0;
}
