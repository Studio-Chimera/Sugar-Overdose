#include "Store.h"

Store* Store::pinstance_{ nullptr };
std::mutex Store::mutex_;

Store::Store()
{
}

Store* Store::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new Store();
    }
    return pinstance_;
}
