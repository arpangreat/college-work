#include <iostream>
#include <vector>

class BinarySort {
private:
  std::vector<int> data;
  int comparisons;

public:
  BinarySort(const std::vector<int> &arr) : data(arr), comparisons(0) {}

  void sort() { binarySort(0, data.size() - 1); }

  void print() const {
    for (int num : data) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }

  [[nodiscard]] int getComparisons() const { return comparisons; }

private:
  void binarySort(int left, int right) {
    if (left >= right) {
      return;
    }

    int mid = left + (right - left) / 2;
    binarySort(left, mid);
    binarySort(mid + 1, right);
    merge(left, mid, right);
  }

  void merge(int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
      comparisons++;
      if (data[i] < data[j]) {
        temp[k++] = data[i++];
      } else {
        temp[k++] = data[j++];
      }
    }

    while (i <= mid) {
      temp[k++] = data[i++];
    }

    while (j <= right) {
      temp[k++] = data[j++];
    }

    for (int l = 0; l < temp.size(); l++) {
      data[left + l] = temp[l];
    }
  }
};

int main() {
  std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  BinarySort bs(arr);

  std::cout << "Original array: ";
  bs.print();

  bs.sort();

  std::cout << "Sorted array: ";
  bs.print();

  std::cout << "Number of comparisons: " << bs.getComparisons() << std::endl;

  return 0;
}
