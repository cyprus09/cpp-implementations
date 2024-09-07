#include <iostream>
#include <thread>
#include <map>
#include <string>

#include <chrono>
using namespace std::chrono_literals;

// void function1(char symbol)
// {
//   for (int i = 0; i < 200; i++)
//   {
//     std::cout << symbol;
//   }
// }

// void function2()
// {
//   for (int i = 0; i < 200; i++)
//     std::cout << '-';
// }

void refreshForecast(std::map<std::string, int> forecastMap)
{
  while (true)
  {
    for (auto& item : forecastMap)
    {
      item.second++;
      std::cout << item.first << " - " << item.second << std::endl;
    }
    std::this_thread::sleep_for(2000ms);
  }
}

int main()
{
  // std::thread worker1(function1, static_cast<char>('+'));
  // std::thread worker1([]()
  //                     { function1('+'); });
  // std::thread worker2(function2);
  // worker1.join();
  // worker2.join();

  std::map<std::string, int> forecastMap = {
      {"NYC", 15},
      {"Mumbai", 20},
      {"Berlin", 12}};

  std::thread bgWorker(refreshForecast, std::ref(forecastMap));

  bgWorker.join();

  return 0;
}