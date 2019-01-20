#ifndef __QUEUE_STACK_HPP__
#define __QUEUE_STACK_HPP__

#include <queue>
#include <stack>
#include <initializer_list>

/**
 * Implement queue using std::stack
 */
template <typename T>
class Queue
{
public:
    bool empty() const
    {
        return pop_s_.empty() && push_s_.empty();
    }

    void push(std::initializer_list<T> l)
    {
        for (const auto& t : l)
            push_s_.push(t);
    }

    void push(T t)
    {
        push_s_.push(t);
    }

    void pop()
    {
        transfer();
        return pop_s_.pop();
    }

    T top() const
    {
        transfer();
        return pop_s_.top();
    }

private:
    void transfer() const
    {
        if (pop_s_.empty())
        {
            while (!push_s_.empty())
            {
                pop_s_.push(push_s_.top());
                push_s_.pop();
            }
        }
    }

private:
    mutable std::stack<T> push_s_;
    mutable std::stack<T> pop_s_;
};


/**
 * Implement stack using std::queue
 */
template <typename T>
class Stack
{
public:
    void push(T t)
    {
        auto eq = q1.empty() ? &q1 : &q2;
        auto dq = q1.empty() ? &q2 : &q1;
        eq->push(t);
        while (!dq->empty())
        {
            eq->push(dq->front());
            dq->pop();
        }
    }
    void push(std::initializer_list<T> l)
    {
        for (const auto& t: l)
        {
            push(t);
        }
    }
    void pop()
    {
        if (!q1.empty())
        {
            return q1.pop();
        }
        return q2.pop();
    }
    T top() const
    {
        if (!q1.empty())
        {
            return q1.front();
        }
        return q2.front();
    }
    bool empty() const
    {
        return q1.empty() && q2.empty();
    }

private:
    std::queue<T> q1;
    std::queue<T> q2;
};

#endif // __QUEUE_STACK_HPP__
