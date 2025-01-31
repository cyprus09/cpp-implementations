// mutex in c++ threading | why use mutex | what is race condition and how to solve it? | what is critical section of a code?

// mutex : mutual exclusion

// race condition
// 1. is a situation where two or more threads/processes happen to change a common data at the same time
// 2. if there is a race condition then we have to protect it and the protected section is called critical section/region

// mutex
// 1. mutex is used to avoid race condition
// 2. we use lock(), unlock() on mutex to avoid race condition

// main example of race condition would be:
// t1 and t2 both load and increment x by 1, int x = 1 finally and not x = 2

#include <iostream>
#include <thread>
#include <mutex>

int myAmount = 0;
// initialise mutex object
std::mutex m;

void addMoney()
{
  // introduce mutex lock
  m.lock();
  // critical section of the code since both threads can access at the same time and will have potential race condition
  ++myAmount;
  // mutex unlock to let other threads access this section
  m.unlock();
}

int main()
{
  std::thread t1(addMoney);
  std::thread t2(addMoney);

  t1.join();
  t2.join();

  std::cout << myAmount << std::endl;

  return 0;
}