// into to thread in c++ (only available in C++11 and later)

// in every application there's a main thread that runs the main () which is our entry point and also called the default thread
// we can create multiple threads to run concurrently with the main thread

// thread is a lightweight process that runs concurrently with other threads
// threads run in the same memory space, so they can access the same data

// ways to create a thread:
// 1. function pointer
// 2. lambda function
// 3. functors
// 4. member function
// 5. static member function

// find the sum of all odd and even numbers from 1 to 1900000000

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;
// typdef so we don't have to write unsigned long long every time
typedef unsigned long long ull;

ull oddSum = 0, evenSum = 0;

void findEven(ull start, ull end) {
  for(ull i = start; i <= end; i++) {
    if(i % 2 == 0) {
      evenSum += i;
    }
  }
}

void findOdd(ull start, ull end) {
  for(ull i = start; i <= end; i++) {
    if(i % 2 != 0) {
      oddSum += i;
    }
  }
}

int main() {
  ull start = 1, end = 1900000000;

  auto startTime = high_resolution_clock::now();
  
  std::thread t1(findEven, start,  end);
  std::thread t2(findOdd, start, end);
  // Odd sum: 902500000000000000
  // Even sum: 902500000950000000
  // Time taken: 3

  t1.join();
  t2.join();

  // findOdd(start, end);
  // findEven(start, end);
  // Odd sum: 902500000000000000
  // Even sum: 902500000950000000
  // Time taken: 6
  // took double the time for each function to run consecutively

  auto stopTime = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stopTime - startTime);

  cout << "Odd sum: " << oddSum << endl;
  cout << "Even sum: " << evenSum << endl;

  cout << duration.count()/1000000 << endl;

  return 0;
}