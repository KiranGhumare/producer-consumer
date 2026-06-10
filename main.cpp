#include <iostream>
#include <queue>
#include <string>
#include <thread>

struct Message {
    int id;
    std::string message;

    public:
    Message(int id, std::string message) {
        this->id = id;
        this->message = message;
    }
};

std::queue<Message> buffer;
int CAPACITY = 100;
int N = 20;
bool done = false;

void producer() {
    for (int i=0;i<N;i++) {
        Message m = Message(i, "This is a message");
        buffer.push(m);
        std::cout<<"Pushed messsage "<<i<<" to the queue"<<std::endl;
    }
    done = true;
}

void consumer() {
    while (true) {
        if (buffer.size()) {
            Message m = buffer.front();
            buffer.pop();
            std::cout<<"Consumed messsage "<<m.id<<" from the queue"<<std::endl;
        }
        else if (!buffer.size() && done) {
            return;
        }
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}