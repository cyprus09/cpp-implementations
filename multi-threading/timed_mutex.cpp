// std::timed_mutex is blocked till timeout_time or the lock is acquired and returns true if success otherwise false
// member_functions:
// lock, try_lock, try_lock_for, try_lock_until, unlock

// try_lock_for: waits until specified timeout_duration has elapsed or the lock is acquired, whichever comes first.
// on successful lock acquisition, returns true, otherwise returns false

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

int myAmount = 0;
std::timed_mutex m;

// try_lock_for
// you should only get amount = 1 since t2 couldnt enter since the time it took was 2 seconds whereas it would wait only for 1 sec
// void increment(int i) {
// 	if(m.try_lock_for(std::chrono::seconds(1))){
// 		++myAmount;
// 		std::this_thread::sleep_for (std::chrono::seconds(2));
// 		cout << "Thread " << i << " Entered" << endl;
// 		m.unlock();
// 	}else{
// 		cout << "Thread " << i << " Couldn't Enter" << endl;
// 	}
// }

// try_lock_until
// same job just can take reference from current time
void increment(int i) {
	auto now=std::chrono::steady_clock::now();
	if(m.try_lock_until(now + std::chrono::seconds(2))){
		++myAmount;
		std::this_thread::sleep_for (std::chrono::seconds(1));
		cout << "Thread " << i << " Entered" << endl;
		m.unlock();	
	}else{
		cout << "Thread " << i << " Couldn't Enter" << endl;
	}
}

int main() {
	std::thread t1(increment, 1);
	std::thread t2(increment, 2);

	t1.join();
	t2.join();

	cout << myAmount << endl;
	return 0;
}
