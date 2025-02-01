// it is same as mutex, but the same thread can lock one mutex multiple times using recursive mutex
// if the thread t1 calls lock/try_lock first on a recursive mutex m1, then m1 is locked by t1, now as t1 is running in recursion t1 can call lock/try_lock as many times as it wants
// but if t1 has acquired the mutex 10 time times, it has to unlock it 10 times or else no other thread will be able to enter the critical section. in brief, recursive_mutex keeps track of how many times was the section was locked
// we should always try to avoid recursive_mutex since it leads to a lot of stack overhead buildup

#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex m1;
int buffer = 0;

// method-1: call using recursion
void recursion(char c, int loopFor)
{
  if (loopFor < 0)
    return;

  // will lock from 0 - 10, followed by 11 - 21 by thread t1 and t2 respectively
  // but after 0 - 10, it will respectively unlock all locks before going to t2
  m1.lock();
  std::cout << "THREAD-ID " << c << ": " << buffer++ << std::endl;

  recursion(c, --loopFor);

  m1.unlock();
  std::cout << "unlock by thread " << c << std::endl;
}

int main()
{
  std::thread t1(recursion, '0', 10);
  std::thread t2(recursion, '1', 10);
  t1.join();
  t2.join();

  return 0;
}

// method-2: using loop
// int main()
// {
//   for (int i = 0; i < 5; i++)
//   {
//     m1.lock();
//     std::cout << "locked " << i << std::endl;
//   }

//   for (int i = 0; i < 5; i++)
//   {
//     m1.unlock();
//     std::cout << "unlocked " << i << std::endl;
//   }

//   return 0;
// }