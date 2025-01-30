// types of thread creation in cpp+11
// there are 5 different types we can create threads in cpp11 using callable objects

// note: if we create multiple threads, there's no guarantee which one will start first

// 1. function pointers
// most basic form of thread creation

#include <iostream>
#include <thread>

// void fun(int x)
// {
//   while (x-- > 0)
//   {
//     std::cout << x << std::endl;
//   }
// }

// int main()
// {
//   std::thread t1(fun, 10);
//   std::thread t2(fun, 11);
//   t1.join();
//   t2.join();
//   return 0;
// }

// 2. lambda function

// int main()
// {
//   // we can directly inject lambda at the thread creation time
//   // auto fun = [] (int x) {
//   //   while(x-->0) {
//   //     std::cout << x << std::endl;
//   //   }
//   // };

//   // can directly pass the lambda function within the thread method (return the lambda itself)
//   std::thread t([](int x)
//                 {
//     while (x-- > 0)
//     {
//       std::cout << x << std::endl;
//     } }, 10);
//   t.join();
//   return 0;
// }


// 3. functor (function object)

class Base {
  public:
    void operator () (int x) {
      while(x--> 0) {
        std::cout << x << std::endl;
      }
    }
};

int main() {
  std::thread t((Base()), 10);
  t.join();
  return 0;
}