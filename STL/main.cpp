#include <iostream>
#include <chrono>
#include <queue>
#include <functional>

#include <thread>
#include <mutex>
#include <semaphore.h>
#include <condition_variable>
#include <atomic>

class Something {
public:
    int m_data;

    Something() : m_data(0) {
    }

    void operator()() {
        ++m_data;
    }
};

void TestFunc(int& counts) {
    double sum = 0;
    for (int i = 0; i < counts; i++) {
        for (int j = 0; j < 10000; j++) {
            sum += i * j;
        }
    }

    std::cout << "sum: " << sum << std::endl;
}

std::queue<int> q1;
std::queue<int>::size_type q1_size;
void FirstThreadJob(int x) {
    q1.push(x);

    if (x == 10) {
        q1.push(22);
    }

    std::cout << "FirstThreadJob: " << x << std::endl;
}

std::mutex mu;
void SecondThreadJob() {
    // Mutex
//    mu.lock();
//    std::cout << "Yo Mutex!" << std::endl;
//    mu.unlock();

    // Lock Guard (Using RAII)
//    std::lock_guard<std::mutex> lock(mu);
//    std::cout << "Yo Lock Guard Mutex!" << std::endl;

    // Unique Guard
    std::unique_lock<std::mutex> unique(mu);
    std::cout << "Yo Lock Guard Mutex!" << std::endl;
}

sem_t binary_sem;
int counter;
void SemThreadJob1() {
    sem_wait(&binary_sem);
    for (int i = 0; i < 3; i++) {
        counter++;
        std::cout << "The counter 1: " << counter << std::endl;
    }
}

void SemThreadJob2() {
    for (int i = 0; i < 3; i++) {
        counter--;
        std::cout << "The counter 2: " << counter << std::endl;
    }
    sem_post(&binary_sem);
}

std::condition_variable cond_var;
std::mutex cond_mu;
bool ready = false;

void CVThreadJob1() {
    std::unique_lock<std::mutex> lock(cond_mu);

    std::cout << "Thread Wait: " << std::endl;
    cond_var.wait(lock);

    std::cout << "This is Thread 1. \n";
}

void CVThreadJob2() {
    std::unique_lock<std::mutex> lock(cond_mu);

    std::cout << "Thread Wait: " << std::endl;
    cond_var.wait(lock, [](){ return ready; });

    std::cout << "This is Thread 2. \n";
}

std::atomic_int atomic_a(0);
void AtomicTestFunc() {
    for (int i = 0; i < 3; i++) {
        atomic_a ++;
        std::cout << "This is atomic function: " << atomic_a << std::endl;
    }
}

int main(int argc, char** argv) {

    int n = 100000;

    std::cout << "With Out Using Thread." << std::endl;
    auto start = std::chrono::steady_clock::now();
    TestFunc(n);
    std::cout << "Hello World!" << std::endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> delta = end - start;
    std::cout << "cost time: " << delta.count() << " seconds." << std::endl;

    std::cout << "====================" << std::endl;
    std::cout << std::endl;

    std::cout << "Using Thread." << std::endl;
    start = std::chrono::steady_clock::now();
    std::thread my_thread(TestFunc, std::ref(n));
    std::cout << "Hello World!" << std::endl;
    std::cout << "Current Thread ID: " << my_thread.get_id() << std::endl;
    my_thread.join();
    end = std::chrono::steady_clock::now();
    delta = end - start;
    std::cout << "cost time: " << delta.count() << " seconds." << std::endl;

    std::cout << "====================" << std::endl;
    std::cout << std::endl;

    Something sth;

    // Copy
    std::thread my_thread1(sth);
    std::cout << "Current Thread ID: " << my_thread1.get_id() << std::endl;
    my_thread1.join();
    std::cout << "copy object: " << sth.m_data << std::endl;

    // Ref
    std::thread my_thread2(std::ref(sth));
    std::cout << "Current Thread ID: " << my_thread2.get_id() << std::endl;
    my_thread2.join();
    std::cout << "ref object: " << sth.m_data << std::endl << std::endl;

    std::cout << "this Thread ID: " << std::this_thread::get_id() << std::endl;

    std::cout << "Hardware Concurrency: " << std::thread::hardware_concurrency() << std::endl;

    std::cout << "====================" << std::endl;
    std::cout << std::endl;

    std::thread my_thread3(FirstThreadJob, 10);
    my_thread3.join();

    int a = q1.front();
    std::cout << "The first element is: " << a << std::endl;
    q1_size = q1.size();
    std::cout << "The queue length is: " << q1_size << std::endl;

    q1.pop();
    q1_size = q1.size();
    std::cout << "The queue length is: " << q1_size << std::endl;

    std::cout << "====================" << std::endl;
    std::cout << std::endl;

    std::thread my_thread4(SecondThreadJob);
    my_thread4.join();

    std::cout << "====================" << std::endl;
    std::cout << std::endl;

    int res;
    res = sem_init(&binary_sem, 0, 0);

    std::thread my_thread5(SemThreadJob1);
    std::thread my_thread6(SemThreadJob2);
    my_thread5.join();
    my_thread6.join();

    std::cout << "====================" << std::endl;
    std::cout << std::endl;

    std::thread my_thread7(CVThreadJob1);
    std::thread my_thread8(CVThreadJob2);

    std::cout << "Wait 3 seconds..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Thread notify one" << std::endl;
    cond_var.notify_one();

    ready = true;

    std::cout << "Thread notify one" << std::endl;
    cond_var.notify_one();

    my_thread7.join();
    my_thread8.join();

    std::cout << "====================" << std::endl;
    std::cout << std::endl;

    std::thread my_thread9(AtomicTestFunc);
    my_thread9.join();

    return 0;
}
