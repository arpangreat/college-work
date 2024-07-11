#include <iostream>
#include <vector>

class MergeSort {
private:
  std::vector<int> data;
  int comparisons;

public:
  MergeSort(const std::vector<int> &arr) : data(arr), comparisons(0) {}

  void sort() { mergeSort(0, data.size() - 1); }

  void print() const {
    for (int num : data) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }

  [[nodiscard]] int getComparisons() const { return comparisons; }

private:
  void mergeSort(int left, int right) {
    if (left >= right) {
      return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(left, mid);
    mergeSort(mid + 1, right);

    merge(left, mid, right);
  }

  void merge(int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
      comparisons++;
      if (data[i] <= data[j]) {
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
  MergeSort ms(arr);

  std::cout << "Original array: ";
  ms.print();

  ms.sort();

  std::cout << "Sorted array: ";
  ms.print();

  std::cout << "Number of comparisons: " << ms.getComparisons() << std::endl;

  return 0;
}
