#include <iostream>
#include <vector>

class InsertionSort {
private:
  std::vector<int> data;
  int comparisons;

public:
  InsertionSort(const std::vector<int> &arr) : data(arr), comparisons(0) {}

  void sort() {
    for (int i = 1; i < data.size(); i++) {
      int key = data[i];
      int j = i - 1;

      while (j >= 0 && data[j] > key) {
        comparisons++;
        data[j + 1] = data[j];
        j--;
      }

      data[j + 1] = key;
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
  std::vector<int> arr = {4, 2, 5, 1, 9, 3, 5, 8, 6};
  InsertionSort is(arr);

  std::cout << "Original array: ";
  is.print();

  is.sort();

  std::cout << "Sorted array: ";
  is.print();

  std::cout << "Number of comparisons: " << is.getComparisons() << std::endl;

  return 0;
}
