#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <functional>
#include <queue>
#include <sstream>

using namespace std;

class ThreadPool {
public:
  ThreadPool(int numThreads) {
    start(numThreads);
  };

  ~ThreadPool() {
    stop();
  }

  void enqueue(function<void()> task) {
    // acquire a lock to be sure that not multiple threads are adding to the queue. Scope is needed for notifying
    {
      unique_lock<mutex> lk(mEventVarLock); // only one thread here
      mTaskQueue.emplace(move(task));
    }
    mEventVar.notify_one();
  }

private:
  vector<thread> mThreads;
  mutex mEventVarLock;
  condition_variable mEventVar;
  bool mStopping = false;

  queue<function<void()>> mTaskQueue;


  void start(int numThreads) {
    for(int i = 0; i < numThreads; i++) {
      mThreads.emplace_back([=]{
        while (true) {
          function<void()> task;
          {
            unique_lock<mutex> lk(mEventVarLock);
            mEventVar.wait(lk, [=]{ return mStopping || !mTaskQueue.empty(); });

            if (mStopping && mTaskQueue.empty()) { break; }

            task = mTaskQueue.front();
            mTaskQueue.pop();
          }
          task();
        }
      });
    }
  }
  
  void stop() {
    mStopping = true;
    mEventVar.notify_all();

    for(auto& thread : mThreads){ thread.join(); }
  }
};

int main() {

  ThreadPool threadPool(8);

  for(int i = 0; i < 72; i++) {
    threadPool.enqueue([i]{
      stringstream ss;
      ss << "Executing thread: " << i << "\n";
      cout << ss.str();
    });
  }  
  return 0;
}