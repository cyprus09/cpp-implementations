// conditional variables are used for two purposes:
// 1. to notfy other threads
// 2. to wait for a condition to be true

// 1. conditional variables allows running threads to wait on some conditions and once those conditions are met, the waiting thread is notified using:
//    void notify_one() - notifies one waiting thread
//    void notify_all() - notifies all waiting threads

// 2. you need mutex to use conditional variables

// 3. if some thread wants to wait on some condition, then it should:
//    a. acquire the mutex lock using std::unique_lock<std::mutex> lock(m);
//    b. execute wait, wait_for, or wait_until. the wait operations automatically release the mutex and suspend the execution of the thread
//    c. when the condition variable is notified, the thread is awakened, and the mutex is automatically reacquired. the thread checks the condition and resumes operation accordingly

// Note:
// 1. condirtional variables are used to synchronize threads based on some condition
// 2. best use case would be the producer/consumer problem

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::mutex m;
long balance = 0;

// helps prevent double spending in a way
void addMoney(int money)
{
  std::lock_guard<std::mutex> lg(m);
  balance += money;
  std::cout << "amount added to current balance: " << balance << std::endl;
  cv.notify_one();
}

void withdrawMoney(int money)
{
  std::unique_lock<std::mutex> ul(m);
  cv.wait(ul, []
          { return (balance != 0) ? true : false; });

  if (balance >= money)
  {
    balance -= money;
    std::cout << "amount deducted: " << money << std::endl;
  }
  else
  {
    std::cout << "amount cannot be deducted, current balance is less than " << money << std::endl;
  }
  std::cout << "current balance is: " << balance << std::endl;
}

int main()
{
  std::thread t1(withdrawMoney, 500);
  std::thread t2(addMoney, 500);
  t1.join();
  t2.join();

  return 0;
}