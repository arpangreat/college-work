#include <algorithm>
#include <iostream>
#include <vector>

// Template function for quick sort
template <typename T> void quickSort(std::vector<T> &list, int low, int high) {
  if (low < high) {
    T pivot = list[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
      if (list[j] <= pivot) {
        ++i;
        std::swap(list[i], list[j]);
      }
    }
    std::swap(list[i + 1], list[high]);
    int pi = i + 1;
    quickSort(list, low, pi - 1);
    quickSort(list, pi + 1, high);
  }
}

// Template function for selection sort
template <typename T> void selectionSort(std::vector<T> &list) {
  for (size_t i = 0; i < list.size() - 1; ++i) {
    size_t minIndex = i;
    for (size_t j = i + 1; j < list.size(); ++j) {
      if (list[j] < list[minIndex]) {
        minIndex = j;
      }
    }
    std::swap(list[i], list[minIndex]);
  }
}

// Template function for insertion sort
template <typename T> void insertionSort(std::vector<T> &list) {
  for (size_t i = 1; i < list.size(); ++i) {
    T key = list[i];
    int j = i - 1;
    while (j >= 0 && list[j] > key) {
      list[j + 1] = list[j];
      --j;
    }
    list[j + 1] = key;
  }
}

// Template function for binary sort (std::sort as a placeholder for binary
// sort)
template <typename T> void binarySort(std::vector<T> &list) {
  std::sort(list.begin(), list.end());
}

int main() {
  std::vector<int> list;
  int n, choice;

  std::cout << "Enter the number of elements in the list: ";
  std::cin >> n;

  std::cout << "Enter the elements of the list: ";
  for (int i = 0; i < n; ++i) {
    int element;
    std::cin >> element;
    list.push_back(element);
  }

  std::cout << "Choose sorting method:\n1. Quick Sort\n2. Binary Sort\n3. "
               "Selection Sort\n4. Insertion Sort\nYour choice: ";
  std::cin >> choice;

  switch (choice) {
  case 1:
    quickSort(list, 0, list.size() - 1);
    break;
  case 2:
    binarySort(list);
    break;
  case 3:
    selectionSort(list);
    break;
  case 4:
    insertionSort(list);
    break;
  default:
    std::cout << "Invalid choice!" << std::endl;
    return 1;
  }

  std::cout << "Sorted list: ";
  for (const auto &element : list) {
    std::cout << element << " ";
  }
  std::cout << std::endl;

  return 0;
}
