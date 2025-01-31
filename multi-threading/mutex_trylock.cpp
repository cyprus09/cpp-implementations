// mutex::try_lock() in cpp11 threading , is a member function of mutex class

// 0. try_lock(): tries to lock the mutex. returns immediately. on successful lock acquisition, returns true else false
// 1. if try_lock() is not able to lock mutex, then it doesnt get blocked, that's why it is called non-blocking and the loop keeps on going
// 2. if try_lock() is called again by the same thread which owns the mutex, the behaviour is undefined. It is a dead lock situation with undefined behaviour. (if you want to be able to lock the same mutex by the same thread more than one time, then use recursive_mutex)

/* ways to define try_lock():
1. std::try_lock() - tries to lock all the lockable objects passed in it one by one in given order, -1 on success or 0-based mutex index which cldnt be locked
2. std::mutex::try_lock() - different from try_lock()
3. std::shared_lock::try_lock() - multiple threads read-only access to the shared resource 
4. std::timed_mutex::try_lock() - a timed mutex is a time lockable object that is designed to signal when critical sections of code need exclusive access
5. std::unique_lock::try_lock() - only allows a single thread to modify the shared resources while blocking the other threads
6. std::shared_mutex::try_lock() - lets several threads use a shared resource simultaneously for reading while guaranteeing exclusive writing access
7. std::recursive_mutex::try_lock()
8. std::shared_timed_mutex::try_lock()
9. std::recursive_timed_mutex::try_lock()
*/

#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex m;

void increaseTheCounterFor100000Time()
{
  for (int i = 0; i < 100000; i++)
  {
    // safety incase a thread locked the section already
    // t1 keeps increasing but t2 keeps on looping without getting access to counter hence weird responses
    // but if we use lock(), it will work since t2 will only run after t1 is done
    if (m.try_lock())
    {
      counter++;
      m.unlock();
    }
  }
}

int main()
{
  std::thread t1(increaseTheCounterFor100000Time);
  std::thread t2(increaseTheCounterFor100000Time);

  t1.join();
  t2.join();

  std::cout << "counter could increase only upto: " << counter << std::endl;

  return 0;
}