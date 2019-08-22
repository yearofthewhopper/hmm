#pragma once

#include <vector>

#include "triangle.h"

class Queue {
public:
    void Push(const std::shared_ptr<Triangle> &t) {
        const int i = m_Queue.size();
        t->SetQueueIndex(i);
        m_Queue.push_back(t);
        Up(i);
    }

    std::shared_ptr<Triangle> Pop() {
        const int n = m_Queue.size() - 1;
        Swap(0, n);
        Down(0, n);
        return PopBack();
    }

    std::shared_ptr<Triangle> Remove(const int i) {
        const int n = m_Queue.size() - 1;
        if (n != i) {
            Swap(i, n);
            if (!Down(i, n)) {
                Up(i);
            }
        }
        return PopBack();
    }

    std::shared_ptr<Triangle> Head() const {
        return m_Queue.front();
    }

private:
    bool Less(const int i, const int j) const {
        return -m_Queue[i]->Error() < -m_Queue[j]->Error();
    }

    std::shared_ptr<Triangle> PopBack() {
        auto t = m_Queue.back();
        m_Queue.pop_back();
        t->SetQueueIndex(-1);
        return t;
    }

    void Swap(const int i, const int j) {
        auto temp = m_Queue[i];
        m_Queue[i] = m_Queue[j];
        m_Queue[j] = temp;
        m_Queue[i]->SetQueueIndex(i);
        m_Queue[j]->SetQueueIndex(j);
    }

    void Up(int j) {
        while (1) {
            int i = (j - 1) / 2;
            if (i == j || !Less(j, i)) {
                break;
            }
            Swap(i, j);
            j = i;
        }
    }

    bool Down(const int i0, const int n) {
        int i = i0;
        while (1) {
            int j1 = 2 * i + 1;
            if (j1 >= n) {
                break;
            }
            int j2 = j1 + 1;
            int j = j1;
            if (j2 < n && Less(j2, j1)) {
                j = j2;
            }
            if (!Less(j, i)) {
                break;
            }
            Swap(i, j);
            i = j;
        }
        return i > i0;
    }

    std::vector<std::shared_ptr<Triangle>> m_Queue;
};