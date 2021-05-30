// Homework 5
// Testing Sorting Algorithms
// Abrar Mahi

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// Test function that shows how you can time a piece of code.
// Just times a simple loop.
void TestTiming()
{
  cout << "Test Timing" << endl;
  const auto begin = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i)
    sum++;
  // End of piece of code to time.
  const auto end = chrono::high_resolution_clock::now();
  cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns" << endl;
  cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector)
{
  //creating a vector of the size of the param
  vector<int> random(size_of_vector);
  //iterrating through the vector and adding random values to it
  for (auto x : random)
  {
    random.push_back(rand());
  }
  //return the vector of random integers
  return random;
}

vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger)
{
  //create a of vector of the size of the param
  vector<int> sorted(size_of_vector);
  //iterrate through the vector
  for (auto x : sorted) //iterrate through the vector and add random values to it
  {
    sorted.push_back(rand());
  }
  if (!smaller_to_larger) //if the vector is not sorted, than sort it according to its comparator
  {
    SORT(sorted, greater<int>{});
  }
  else
  {
    SORT(sorted, less<int>{});
  }

  return sorted; //return the sorted vector
}

// Generate and returns sorted vector of size @size_of_vector
// If smaller_to_larger is true, returns vector sorted from small to large
// Otherwise returns vector sorted from large to small
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than)
{
  int size = input.size() - 1;
  for (int i = 0; i < size; i++) //c reating an iteration
  {
    if (less_than(input[i + 1], input[i])) //if the next input is less than the current
    {
      if (input[i] != input[i + 1]) //if the current is not the same as the next
      {
        return false; //return false
      }
    }
  }
  return true; //else return true
}

// Computes duration given a start time and a stop time in nano seconds
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time, chrono::high_resolution_clock::time_point end_time)
{
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

void sortTestingWrapper(int argc, char **argv)
{
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small")
  {
    cout << "Invalid input type" << endl;
  }
  if (input_size <= 0)
  {
    cout << "Invalid size" << endl;
  }
  if (comparison_type != "less" && comparison_type != "greater")
  {
    cout << "Invalid comparison type" << endl;
  }

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
  vector<int> input_vector;

  if (input_type == "random")
  {
    input_vector = GenerateRandomVector(input_size);
  }
  else
  {
    if (input_type == "sorted")
    {
      input_vector = GenerateSortedVector(input_size, 1);
    }
    else
    {
      input_vector = GenerateSortedVector(input_size, 0);
    }
  }
  
  //if the comparison isn't "less" execute the following output
  if (comparison_type != "less")
  {
    cout << "Heapsort" << endl
         << endl;
    auto begin = chrono::high_resolution_clock::now();
    HeapSort(input_vector, less<int>{});
    auto end = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin, end) << " ns" << endl
         << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl
         << FE_UNDERFLOW << "MergeSort" << endl
         << endl;
    begin = chrono::high_resolution_clock::now();
    MergeSort(input_vector, less<int>{});
    end = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin, end) << " ns" << endl
         << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl
         << endl
         << "QuickSort" << endl
         << endl;
    begin = chrono::high_resolution_clock::now();
    QuickSort(input_vector, less<int>{});
    end = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin, end) << " ns" << endl
         << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl
         << endl
         << "Testing QuickSort Implementations" << endl
         << endl
         << "Median of Three" << endl
         << endl;
    begin = chrono::high_resolution_clock::now();
    QuickSort(input_vector, less<int>{});
    end = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin, end) << " ns" << endl
         << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl
         << endl
         << "Middle" << endl
         << endl;
    begin = chrono::high_resolution_clock::now();
    QuickSort2(input_vector, less<int>{});
    end = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin, end) << " ns" << endl
         << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl
         << endl
         << "First" << endl
         << endl;
    begin = chrono::high_resolution_clock::now();
    QuickSort3(input_vector, less<int>{});
    end = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin, end) << " ns" << endl
         << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;
  }

  else //else if the comparator is greater
  {
    cout << "Heapsort" << endl
         << endl;
    auto begin = chrono::high_resolution_clock::now();
    HeapSort(input_vector, less<int>{});
    auto end = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin, end) << " ns" << endl
         << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl
         << endl
         << "MergeSort" << endl
         << endl;
    begin = chrono::high_resolution_clock::now();
    MergeSort(input_vector, less<int>{});
    end = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin, end) << " ns" << endl
         << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl
         << endl
         << "QuickSort" << endl
         << endl;
    begin = chrono::high_resolution_clock::now();
    QuickSort(input_vector, less<int>{});
    end = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin, end) << " ns" << endl
         << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl
         << endl
         << "Testing QuickSort Implementations" << endl
         << endl;

    cout << "Median of Three" << endl
         << endl;
    begin = chrono::high_resolution_clock::now();
    QuickSort(input_vector, less<int>{});
    end = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin, end) << " ns" << endl
         << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl
         << endl
         << "Middle" << endl
         << endl;
    begin = chrono::high_resolution_clock::now();
    QuickSort2(input_vector, less<int>{});
    end = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin, end) << " ns" << endl;
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl
         << endl
         << "First" << endl
         << endl;
    begin = chrono::high_resolution_clock::now();
    QuickSort3(input_vector, less<int>{});
    end = chrono::high_resolution_clock::now();
    cout << ComputeDuration(begin, end) << " ns" << endl
         << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;
  }
}

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }

  sortTestingWrapper(argc, argv);

  return 0;
}
