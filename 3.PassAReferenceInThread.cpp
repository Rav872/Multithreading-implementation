#include<iostream>
#include<vector>
#include<thread>
#include<mutex>

using namespace std;

mutex m;

void increment(int &localCounter)
{
    lock_guard<mutex> l(m);
    localCounter++;
}

int main()
{

    int localCounter = 0;

    vector<thread> threads;

    for (int i = 0; i < 5; i++)
    {
        threads.push_back(thread(increment, ref(localCounter)));
    }

    for (auto &th : threads)
    {
        th.join();
    }

    cout << "Counter : " << localCounter << endl;
}
