#include <algorithm>
#include <iostream>
#include <vector>

class RadixSort {
private:
  std::vector<int> data;
  int comparisons;

public:
  RadixSort(const std::vector<int> &arr) : data(arr), comparisons(0) {}

  void sort() {
    int max = *std::max_element(data.begin(), data.end());

    for (int exp = 1; max / exp > 0; exp *= 10) {
      countSort(exp);
    }
  }

  void print() const {
    for (int num : data) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }

  [[nodiscard]] int getComparisons() const { return comparisons; }

private:
  void countSort(int exp) {
    std::vector<int> output(data.size());
    std::vector<int> count(10, 0);

    for (int i : data) {
      comparisons++;
      count[(i / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
      count[i] += count[i - 1];
    }

    for (int i = data.size() - 1; i >= 0; i--) {
      comparisons++;
      output[count[(data[i] / exp) % 10] - 1] = data[i];
      count[(data[i] / exp) % 10]--;
    }

    for (int i = 0; i < data.size(); i++) {
      data[i] = output[i];
    }
  }
};

int main() {
  std::vector<int> arr = {9, 1, 5, 5, 3, 7, 6, 2, 4};
  RadixSort rs(arr);

  std::cout << "Original array: ";
  rs.print();

  rs.sort();

  std::cout << "Sorted array: ";
  rs.print();

  std::cout << "Number of comparisons: " << rs.getComparisons() << std::endl;

  return 0;
}
