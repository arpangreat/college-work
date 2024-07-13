#include <iostream>
#include <map>
#include <vector>

class CountSort {
private:
  std::vector<int> data;
  int comparisons;

public:
  CountSort(const std::vector<int> &arr) : data(arr), comparisons(0) {}

  void sort() {
    std::map<int, int> count;
    for (int num : data) {
      comparisons++;
      count[num]++;
    }

    int index = 0;
    for (const auto &pair : count) {
      for (int i = 0; i < pair.second; i++) {
        data[index++] = pair.first;
      }
    }
  }

  void print() const {
    for (int num : data) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }

  [[nodiscard]] int getComparisons() const { return comparisons; }
};

int main() {
  std::vector<int> arr = {9, 1, 6, 2, 5, 4, 8, 3, 6};
  CountSort cs(arr);

  std::cout << "Original array: ";
  cs.print();

  cs.sort();

  std::cout << "Sorted array: ";
  cs.print();

  std::cout << "Number of comparisons: " << cs.getComparisons() << std::endl;

  return 0;
}
