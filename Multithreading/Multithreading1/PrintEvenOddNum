#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;
mutex mtx; 
condition_variable cv; 
bool oddTurn;
int num=0;

void printOddNum(int start_limit, int end_limit)
{
     for (int i = start_limit; i <= end_limit; i += 2) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return oddTurn; });
        cout << "Odd: " << i << endl;
        sleep(1);
        oddTurn = false;
        cv.notify_all();
    }
}

void printEvenNum(int start_limit, int end_limit)
{
    for (int i = start_limit; i <= end_limit; i += 2) {
        unique_lock<mutex> lock(mtx);
        sleep(1);
        cv.wait(lock, [] { return !oddTurn; });
        cout << "Even: " << i << endl;
        sleep(1);
        oddTurn = true;
        cv.notify_all();
    }
}

int main()
{
    int start_limit, startOdd, startEven, end_limit;
    cin>>start_limit>>end_limit;
    oddTurn = (start_limit%2);
    startOdd = (oddTurn)?start_limit:start_limit+1;
    startEven = !(oddTurn)?start_limit:start_limit+1;
    
    thread t1(printOddNum, startOdd, end_limit);
    thread t2(printEvenNum, startEven, end_limit);

    t1.join();
    t2.join();
}
