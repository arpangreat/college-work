#include <iostream>
#include <vector>

class HeapSort {
private:
  std::vector<int> data;
  int comparisons;

public:
  HeapSort(const std::vector<int> &arr) : data(arr), comparisons(0) {}

  void sort() {
    buildMaxHeap();
    for (int i = data.size() - 1; i > 0; i--) {
      std::swap(data[0], data[i]);
      heapify(0, i);
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
  void buildMaxHeap() {
    for (int i = data.size() / 2 - 1; i >= 0; i--) {
      heapify(i, data.size());
    }
  }

  void heapify(int i, int size) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && data[left] > data[largest]) {
      comparisons++;
      largest = left;
    }

    if (right < size && data[right] > data[largest]) {
      comparisons++;
      largest = right;
    }

    if (largest != i) {
      std::swap(data[i], data[largest]);
      heapify(largest, size);
    }
  }
};

int main() {
  std::vector<int> arr = {8, 6, 6, 4, 2, 8, 1, 5, 7};
  HeapSort hs(arr);

  std::cout << "Original array: ";
  hs.print();

  hs.sort();

  std::cout << "Sorted array: ";
  hs.print();

  std::cout << "Number of comparisons: " << hs.getComparisons() << std::endl;

  return 0;
}
