#include <iostream>
#include <vector>

class QuickSort {
private:
  std::vector<int> data;
  int comparisons;

public:
  QuickSort(const std::vector<int> &arr) : data(arr), comparisons(0) {}

  void sort() { quickSort(0, data.size() - 1); }

  void print() const {
    for (int num : data) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }

  [[nodiscard]] int getComparisons() const { return comparisons; }

private:
  void quickSort(int left, int right) {
    if (left >= right) {
      return;
    }

    int pivotIndex = partition(left, right);
    quickSort(left, pivotIndex - 1);
    quickSort(pivotIndex + 1, right);
  }

  int partition(int left, int right) {
    int pivot = data[left];
    int i = left + 1;
    int j = right;

    while (true) {
      comparisons++;
      while (i <= j && data[i] <= pivot) {
        i++;
      }
      comparisons++;
      while (i <= j && data[j] > pivot) {
        j--;
      }
      if (i > j) {
        break;
      }
      std::swap(data[i], data[j]);
    }
    std::swap(data[left], data[j]);
    return j;
  }
};

int main() {
  std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  QuickSort qs(arr);

  std::cout << "Original array: ";
  qs.print();

  qs.sort();

  std::cout << "Sorted array: ";
  qs.print();

  std::cout << "Number of comparisons: " << qs.getComparisons() << std::endl;

  return 0;
}
