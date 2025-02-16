// thread pool in c++11
// we use thread pool to schedule tasks with the same set of threads
// saves the time taken with creation/destroy of threads also
// let's suppose there are there are four threads in a thread pool waiting to be given tasks to finish
// TP Pool(4) will have four elements to support its implementation
// 1. enqueue --> queue jobs as well as signal to the thread to take these jobs
// 2. mutex --> to guard this queue from threads
// 3. queue --> the physical data structure to hold the tasks/jobs
// 4. vector --> the data structure to hold the physical threads

// Output:
// Thread pool created
// Enqueue (assign) some tasks to work on
// Task 0 0x16d023000 executed by thread
// Task 1 0x16d0af000 executed by thread
// Task 2 0x16d1c7000 executed by thread
// Task 3 0x16d13b000 executed by thread
// Task 5 0x16d0af000 executed by thread
// Task 4 0x16d13b000 executed by thread
// Task 6 0x16d023000 executed by thread
// Task 7 0x16d1c7000 executed by thread
// you can notice the thread id is getting repeated

#include <thread>
#include <iostream>
#include <mutex>
#include <queue>
#include <functional>
#include <sstream>
#include <condition_variable>

class ThreadPool
{
public:
  ThreadPool(size_t numThreads) : stop(false)
  {
    for (size_t i = 0; i < numThreads; i++)
    {
      workers.emplace_back([this]
                           {
          for(;;) {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] {return stop || !tasks.empty();});
            if (stop && tasks.empty())
              return;
            auto task = std::move(tasks.front()); // extract task from tasks list
            tasks.pop(); // remove task from list since we will be executing it
            lock.unlock(); // unlock the mutex, so another thread can accept the tasks
            task(); // run the task
          } });
    }
  }

  template <class F>
  void enqueue(F &&task)
  {
    std::unique_lock<std::mutex> lock(queueMutex);
    tasks.emplace(std::forward<F>(task));
    lock.unlock();
    condition.notify_one();
  }

  ~ThreadPool()
  {
    std::unique_lock<std::mutex> lock(queueMutex);
    stop = true;
    lock.unlock();
    condition.notify_all();
    for (std::thread &worker : workers)
      worker.join();
  }

private:
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;
  std::mutex queueMutex;
  std::condition_variable condition;
  bool stop;
};

std::string get_thread_id()
{
  auto myid = std::this_thread::get_id();
  std::stringstream ss;
  ss << myid;
  std::string mystr = ss.str();
  return mystr;
}

int main()
{
  ThreadPool pool(4); // create a pool with N number of worker threads

  std::cout << "Thread pool created\n";
  std::cout << "Enqueue (assign) some tasks to work on\n";

  for (int i = 0; i < 8; ++i)
  {
    pool.enqueue([i]
                 {
                   printf("Task %d %s executed by thread \n", i, get_thread_id().c_str());
                   std::this_thread::sleep_for(std::chrono::seconds(1)); // simulating work
                 });
  }

  // main thread continues to do other things while the tasks are being executed in the background

  return 0;
}