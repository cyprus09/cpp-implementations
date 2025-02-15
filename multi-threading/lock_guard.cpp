// it is a very lightweight wrapper for owning mutex on scoped basis
// it acquires mutex lock the moment you create the object of lock_guard
// it automatically removes the lock while it goes out of scope
// you cannot explicitly unlock the lock_guard
// you cannot copy lock_guard
// lock_guard in c++ (std::lock_guard<mutex> lock(m1))

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1;
int buffer = 0;

void task(const char *threadNumber, int loopFor)
{
  std::lock_guard<std::mutex> lock(m1);
  for (int i = 0; i < loopFor; i++)
  {
    buffer++;
    std::cout << threadNumber << buffer << std::endl;
  }
}

int main()
{
  std::thread t1(task, "T0 ", 10);
  std::thread t2(task, "T1 ", 10);

  t1.join();
  t2.join();

  return 0;
}