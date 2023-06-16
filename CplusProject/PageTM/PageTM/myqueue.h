#include<list>
#include<unordered_map>
#include "node.h"
class myqueue {
private:
    std::unordered_map<int, int> map;
    int frontIndex;
    int backIndex;
    int queueSize;

public:
    myqueue() : frontIndex(0), backIndex(0), queueSize(0) {}

    void push(int value) {
        map[backIndex++] = value;
        queueSize++;
    }

    void pop() {
        if (!empty()) {
            map.erase(frontIndex++);
            queueSize--;
        }
    }

    int front() {
        if (!empty()) {
            return map[frontIndex];
        }
        return -1; // 队列为空，返回-1或抛出异常等处理方式
    }

    int back() {
        if (!empty()) {
            return map[backIndex - 1];
        }
        return -1; // 队列为空，返回-1或抛出异常等处理方式
    }

    bool empty() {
        return queueSize == 0;
    }

    bool used(int value) {
        for (auto& pair : map) {
            if (pair.second == value) {
                map[backIndex++] = pair.second;
                map.erase(pair.first);
                return true;
            }
        }
        return false;
    }

    bool find(int value) {
        for (auto& pair : map) {
            if (pair.second == value) {
                return true;
            }
        }
        return false;
    }

    int size() {
        return queueSize;
    }
};