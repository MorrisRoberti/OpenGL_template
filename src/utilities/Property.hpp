#pragma once

#include <functional>
#include <vector>

template <typename T>
class Property
{
public:
    Property(T startingVal) : mValue(startingVal) {}

    void subscribe(std::function<void(T updatedVal)> func)
    {
        mSubscribers.push_back(func);
    }

    const T getValue() const
    {
        return mValue;
    }

    void setValue(T newValue)
    {
        mValue = newValue;
        notifyAll();
    }

private:
    T mValue;
    std::vector<std::function<void(T updatedVal)>> mSubscribers;

    void notifyAll() const
    {
        for (auto &f : mSubscribers)
        {
            if (f)
                f(mValue);
        }
    }
};