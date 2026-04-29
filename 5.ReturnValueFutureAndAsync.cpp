#include<iostream>
#include<thread>
#include<mutex>
#include<future>
#include<vector>
#include<unistd.h>
#include<chrono>

using namespace std;

mutex m;

int task(int id)
{
    {
        lock_guard<mutex> l(m);
        cout << "User id : " << id << " Thread id : " << this_thread::get_id() << endl;
    }
    this_thread::sleep_for(chrono::seconds(1));
    return id * 10;

}


int main()
{
    vector<future<int>> results;

    for (int i = 0; i < 5; i++ )
    {
        results.push_back(async(task, i));  // we used async here because it can return a value, thread is a void worker, it can not return any value, async returns a future, async and future not only handles the return
        // value but also handle fault tolerance, it can catch exception using like future<int> result = async(launch::async, task, id);
    }

    for (auto &re : results)
    {
        int val = re.get();
        lock_guard<mutex> l(m);
        cout << "Results are : " << val << endl; // Need to use mutex for this result statment too
    }
}