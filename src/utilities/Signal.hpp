#pragma once

#include <functional>
#include <vector>

template <typename T>
class Signal
{
public:
    Signal() = default;

    void subscribe(std::function<void(T updatedVal)> func)
    {
        mSubscribers.push_back(func);
    }

    void notifyAll(T value) const
    {
        for (const auto &f : mSubscribers)
        {
            if (f)
                f(value);
        }
    }

private:
    std::vector<std::function<void(T updatedVal)>> mSubscribers;
};