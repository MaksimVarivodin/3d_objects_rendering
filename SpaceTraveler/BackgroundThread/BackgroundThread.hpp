#pragma once
#include <functional>
#include <optional>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <type_traits>
#include <variant>

namespace SpaceEngine
{
    using namespace std;
};

namespace SpaceEngine
{
    template <class ReturnType, typename... Args>
    class BackgroundThread
    {
    public:
        using Func = std::function<ReturnType(Args...)>;
        using Millis = std::chrono::milliseconds;
        using ResultStorage = std::conditional_t<std::is_void_v<ReturnType>, std::monostate, std::optional<ReturnType>>;

        BackgroundThread(Func func, Millis interval)
            : toExecute_(func), interval_(interval), isSingleTask_(false), isRunning_(false)
        {
        }

        ~BackgroundThread();

        void start(Args... args);

        void stop();

        bool isRunning() const noexcept;

        bool isSingleTask() const noexcept;

        void setSingleTask(bool singleTask);

        void setFunction(Func func, Args...);

        const Func& getFunction() const noexcept;

        void setInterval(Millis interval);

        Millis getInterval() const noexcept;

        std::optional<ResultStorage> getLastResult() const;

    private:
        void loop_(Args... args);


        Func toExecute_;
        Millis interval_;
        std::optional<ResultStorage> lastResult_;
        mutable std::mutex mutex_;
        std::condition_variable cv_;
        
        std::atomic<bool> isSingleTask_;
        std::atomic<bool> isRunning_;
        std::jthread thread_;
    };
}
;

#include "BackgroundThread.inl"

namespace se = SpaceEngine;
