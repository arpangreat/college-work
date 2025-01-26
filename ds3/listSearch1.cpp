#include "iostream"
#include <algorithm>
#include <cstddef>
#include <vector>

template <typename T> int linearSearch(const std::vector<T> &list, T key) {
  for (std::size_t i = 0; i < list.size(); i++) {
    if (list[i] == key) {
      return static_cast<int>(i);
    }
  }
  return -1;
}

template <typename T> int binarySearch(const std::vector<T> &list, T key) {
  std::size_t left = 0, right = list.size() - 1;
  while (left <= right) {
    std::size_t mid = left + (right - left) / 2;

    if (list[mid] == key) {
      return static_cast<int>(mid);
    } else if (list[mid] < key) {
      left = mid + 1;
    } else {
      right = mid + 1;
    }
  }

  return -1;
}

int main(int argc, char *argv[]) {
  std::vector<int> list;

  int choice, n, key;

  std::cout << "Enter the number of element in the list: ";
  std::cin >> n;

  std::cout << "Enter the elements of the list: ";
  for (int i = 0; i < n; ++i) {
    int element;
    std::cin >> element;
    list.push_back(element);
  }

  std::cout << "Enter the element to search for: ";
  std::cin >> key;

  std::cout << "Choose search method:\n1. Linear Search\n2. Binary "
               "Search\nYour choice: ";
  std::cin >> choice;

  int result = -1;

  switch (choice) {
  case 1:
    result = linearSearch(list, key);
    break;
  case 2:
    std::sort(list.begin(), list.end()); // Ensure the list is sorted
    result = binarySearch(list, key);
    break;
  default:
    std::cout << "Invalid choice!" << std::endl;
    return 1;
  }

  if (result != -1) {
    std::cout << "Element found at index: " << result << std::endl;
  } else {
    std::cout << "Element not found." << std::endl;
  }
  return 0;
}
