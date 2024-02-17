#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

using namespace std::chrono;

// Function to generate random values for a given array
void randomVector(int vector[], int size) {
  for (int i = 0; i < size; i++) {
    vector[i] = rand() % 100;
  }
}

// Function to perform vector addition for a portion of the vectors
void vectorAddition(int *v1, int *v2, int *v3, int start, int end) {
  for (int i = start; i < end; i++) {
    v3[i] = v1[i] + v2[i];
  }
}

int main() {
  // Size of the vectors
  unsigned long size = 100000000;
  // Number of threads to use
  int num_threads = 4; // You can change this value

  // Seed the random number generator
  srand(time(0));

  int *v1, *v2, *v3;
  auto start = high_resolution_clock::now();

  // Allocate memory for the vectors
  v1 = (int *)malloc(size * sizeof(int));
  v2 = (int *)malloc(size * sizeof(int));
  v3 = (int *)malloc(size * sizeof(int));

  // Generate random values for the vectors
  randomVector(v1, size);
  randomVector(v2, size);

  // Vector to hold thread objects
  std::vector<std::thread> threads;

  // Partition the data and perform addition in parallel
  int partition_size = size / num_threads;
  for (int i = 0; i < num_threads; ++i) {
    int start_index = i * partition_size;
    int end_index = (i == num_threads - 1) ? size : (i + 1) * partition_size;
    threads.push_back(std::thread(vectorAddition, v1, v2, v3, start_index, end_index));
  }

  // Join all threads
  for (auto &t : threads) {
    t.join();
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);

  // Output the execution time
  cout << "Time taken by function :" << duration.count() << " microseconds" << endl;

  // Free memory
  free(v1);
  free(v2);
  free(v3);

  return 0;
}
