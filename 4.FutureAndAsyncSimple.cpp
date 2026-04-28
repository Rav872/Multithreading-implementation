#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<future>

using namespace std;

mutex m;

int squareOfNumber(int x)
{
    lock_guard<mutex> l(m);
    return x * x;
}

int main()
{
    int x = 23;
    // thread t(squareOfNumber, x); It won't return anything
    future<int> result = async(squareOfNumber, x);
    cout << "Square of a number is : " << result.get() << endl; // we don't need to join anything, main will stop until get the result, can only call get once, future is empty once get called
}