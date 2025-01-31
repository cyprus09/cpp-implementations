// std::try_lock(m1, m2, m3, m4...) - tries to lock all the lockable objects passed in it one by one in given order

// -1 on success or 0-based mutex index which cldnt be locked

// if fails to lock any of the mutex, will release all the mutex it locked earlier

// if a call to try_lock results in an exception, unlock is called for any locked objects before rethrowing

#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>

int x = 0, y = 0;
std::mutex m1, m2;

void doSomeWorkforSeconds(int seconds)
{
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void incrementXY(int &XorY, std::mutex &m, const char *desc)
{
  for (int i = 0; i < 5; i++)
  {
    m.lock();
    XorY++;
    std::cout << desc << XorY << '\n';
    m.unlock();
    doSomeWorkforSeconds(1);
  }
}

void consumeXY()
{
  int useCount = 5, XplusY = 0;
  while (1)
  {
    int lockResult = std::try_lock(m1, m2);
    if (lockResult == -1)
    {
      if (x != 0 && y != 0)
      {
        useCount--;
        XplusY += x + y;
        x = 0, y = 0;
        std::cout << "XplusY" << '\n';
      }
      m1.unlock();
      m2.unlock();
      if (useCount == 0)
        break;
    }
  }
}

int main()
{
  std::thread t1(incrementXY, std::ref(x), std::ref(m1), "X ");
  std::thread t2(incrementXY, std::ref(y), std::ref(m2), "Y ");
  std::thread t3(consumeXY);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}