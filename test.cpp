#include <bits/stdc++.h>
#include <thread>
#include <future>

using namespace std;

int N = 0;

void threadFunction(future<void> futureObj)
{
    cout << "Thread Start" << endl;
    while (futureObj.wait_for(chrono::milliseconds(1)) == future_status::timeout)
    {
        N++;
    }
    cout << "Thread End" << endl;
}

int main()
{
    // promise<void> exitSignal;
    // future<void> futureObj = exitSignal.get_future();
    // thread th(&threadFunction, move(futureObj));
    // this_thread::sleep_for(chrono::seconds(1));
    // exitSignal.set_value();
    // th.join();
    atomic<bool> done(false);

    thread t([&done] {
        this_thread::sleep_for(chrono::seconds(1));
        done = true;
    });

    while (!done) N++;
    t.join();
    cout << N;
    return 0;
}
