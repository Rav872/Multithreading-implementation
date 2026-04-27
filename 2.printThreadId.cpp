#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

using namespace std;

mutex m;

void printID(int id)
{
    lock_guard<mutex> l(m);
    cout << "user defined id: " << id << " Thread Id: " << this_thread::get_id() << endl;
}

int main()
{

    vector<thread> threads;

    for (int i = 0; i < 3; i++)
    {
        threads.push_back(thread(printID, i));
    }

    for (auto &th : threads)
    {
        th.join();
    }
}