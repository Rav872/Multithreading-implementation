#include<iostream>
#include<thread>
#include<mutex>
#include<vector>

using namespace std;

mutex m;

void swapElement(vector<int> &nums, int &left, int &right)
{
    lock_guard<mutex> l(m);
    
    if (nums[left] != nums[right])
    {
        swap(nums[left], nums[right]);
    }
}

int main()
{
    vector<int> nums = {2, 5, 6, 7, 1, 3};
    vector<thread> threads;
    int left = 0;
    int right = nums.size();
    for (int i = 0; i < 5; i++)
    {
        left++;
        right--;
        threads.push_back(thread(swapElement, ref(nums), ref(left), ref(right)));
    }

    for (auto &th : threads)
    {
        th.join();
    }

    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
}