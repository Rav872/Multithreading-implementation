#include <iostream>
#include <thread>
#include <vector>
#include <semaphore> // C++20 only!
#include <chrono>

using namespace std;

// This semaphore starts with 3 "permits"
counting_semaphore<3> bouncer(3);

void enterClub(int id) {
    cout << "Guest " << id << " is waiting in line..." << endl;
    
    bouncer.acquire(); // Take a permit (Wait if none are available)
    
    cout << "Guest " << id << " is inside the club! [Capacity -1]" << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Party!
    
    cout << "Guest " << id << " is leaving. [Capacity +1]" << endl;
    bouncer.release(); // Give the permit back
}

int main() {
    vector<thread> guests;
    for (int i = 0; i < 6; i++) {
        guests.push_back(thread(enterClub, i));
    }
    for (auto &g : guests) g.join();
}