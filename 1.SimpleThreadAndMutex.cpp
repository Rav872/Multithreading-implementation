#include<iostream>
#include<thread>
#include<mutex>
#include<vector>

using namespace std;

int counter = 0;
mutex m;
void increment()
{
    lock_guard<mutex> l(m);
    counter++;
    
}

int main()
{
   vector<thread> threads;

   // created multiple threads which will store in vector of thread types
   for (int i = 0; i < 5; i++)
   {
        threads.push_back(thread(increment));
   }

   for (auto &t : threads)
   {
        t.join();
   }

   cout << "Counter : " << counter << endl;
}