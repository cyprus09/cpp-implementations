// use of join(), detach() and joinable() in Thread in C++ (C++11)

// Join notes
// 0. once a thread is started, we wait for this thread to finish by calling join() function on thread object
// 1. double join will result into program termination
// 2. if we have a detached thread and main function is returning, then the detached thread execution is suspended

// detach:
// 0. detach a newly created thread from the main() parent thread
// 1. always make sure the thread being detached is joinable else an instance of double detach will suspend the program
// 2. if the main function is running while we detach, the thread execution is suspended
// 3. When you call detach() on a thread, the thread is separated from the parent and allowed to execute independently. The thread will run in the background, and the main thread (or calling thread) will not wait for it to finish.

// notes:
// either join() or detach() should be called on the thread object, or else during it's destructor, it will terminate the program. it checks within the destructor if the thread is still joinable? if yes, it terminates the program

#include <iostream>
#include <chrono>
#include <thread>

void run(int count)
{
  while (count-- > 0)
    std::cout << "mayank" << std::endl;
  // sleed this thread for a while to simulate it takes a while to process
  std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main()
{
  std::thread t1(run, 10);
  std::cout << "main() before" << std::endl;
  // t1.join();

  // make sure to write joinable() before joining or detaching
  // if(t1.joinable())
  //   t1.join();
  // always make sure to write detach or join
  t1.detach();
  if (t1.joinable())
    t1.detach();

  std::cout << "main() after" << std::endl;
  return 0;
}