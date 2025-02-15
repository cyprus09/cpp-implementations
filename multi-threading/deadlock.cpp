#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1;
std::mutex m2;

// our computer is so fast that it thread1 acquired both m1 and m2 or thread2 acquired both before the other could and then they could do together, but the moment we introduce sleep_for, we can see the deadlock in action
void thread1()
{
  m1.lock();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  m2.lock();
  std::cout << "critical section of thread one\n";
  m1.unlock();
  m2.unlock();
}

void thread2() {
  m2.lock();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  m1.lock();
  std::cout << "critical section of thread two\n";
  m2.unlock();
  m1.unlock();
}

int main() {
  std::thread t1(thread1);
  std::thread t2(thread2);

  t1.join();
  t2.join();

  return 0;
}