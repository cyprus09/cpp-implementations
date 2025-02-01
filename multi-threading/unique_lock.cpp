// std::unique_lock<mutex> lock(m1)

// the class unique_lock is a mutex ownership wrapper
// it allows:
//    1. can have different locking strategies
//    2. time-constrained attempts at locking (try_lock_for, try_lock_until)
//    3. recursive locking
//    4. transfer of lock ownership (move not copy)
//    5. condition variables

// locking strategies
//    TYPE            EFFECTS
// 1. defer_lock      do not acquire ownership of the mutex
// 2. try_to_lock     try to acquire ownership of the mutex without blocking
// 3. adapt lock      assume the calling thread already has ownership of the mutex

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1;
int buffer = 0;

void task(const char *threadNumber, int loopFor)
{
  // example-1
  // std::unique_lock<std::mutex> lock(m1); // automatically calls lock on mutex m1 
  // example-2
  // does not call lock on mutex m1, because used defer_lock
  // however we have to explicitly tell when to lock m1
  std::unique_lock<std::mutex> lock(m1, std::defer_lock);
  lock.lock();
  for (int i = 0; i < loopFor; i++)
  {
    buffer++;
    std::cout << threadNumber << buffer << std::endl;
  }
}

int main()
{
  std::thread t1(task, "T1 ", 10);
  std::thread t2(task, "T2 ", 10);

  t1.join();
  t2.join();

  return 0;
}