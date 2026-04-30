#include<iostream>
#include<condition_variable>
#include<thread>
#include<mutex>
#include<thread>
#include<queue>

using namespace std;

mutex m;
bool isFinished = false;

condition_variable cv;
queue<int> q;

void worker(int workerId)
{
    while (true) // the infinite loop
    {
        unique_lock<mutex> ul(m);

        // wait condition
        cv.wait(ul, []{ return !q.empty() || isFinished;});

        // the exit strategy
        if (q.empty() && isFinished)
        {
            break;
        }

        // The retrieval

        int val = q.front();
        q.pop();

        ul.unlock();

        cout << "Worker " << workerId << " Value : " << val << endl;
    }

}

int main()
{

    // creates the threads

    vector<thread> workers;

    for (int i= 0; i < 3; i++)
    {
        workers.push_back(thread(worker, i));
    }

    // Writing data or producer is producing the data
    for (int i =0; i < 10; i++)
    {
        {
            lock_guard<mutex> l(m);
            q.push(i);
        }
        cv.notify_one();
    }

    // task has been done
    {
        lock_guard<mutex> l(m);
        isFinished = true;
    }
    cv.notify_all();

    for (auto &w : workers)
    {
        w.join();
    }
}