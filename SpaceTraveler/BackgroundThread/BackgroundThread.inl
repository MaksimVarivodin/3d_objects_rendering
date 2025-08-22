#include <exception>
#include <type_traits>
#include <tuple>
#include <utility>


namespace SpaceEngine
{
    template <class ReturnType, typename... Args>
    BackgroundThread<ReturnType, Args...>::~BackgroundThread()
    {
        stop();
    }

    template <class ReturnType, typename... Args>
    void BackgroundThread<ReturnType, Args...>::start(Args... args)
    {
        if (isRunning())
            stop();
        // Mark running immediately to avoid race where main thread sees not running before worker starts
        isRunning_.store(true);
        // Start the background worker and return immediately to allow the main thread to continue
        loop_(std::forward<Args>(args)...);
    }

    template <class ReturnType, typename... Args>
    void BackgroundThread<ReturnType, Args...>::stop()
    {
        // Request stop and notify
        if (thread_.joinable())
        {
            thread_.request_stop();
            cv_.notify_all();
            thread_.join(); // Explicit join for control
        }
        // Ensure running flag is cleared even if already stopped
        isRunning_.store(false);
    }

    template <class ReturnType, typename... Args>
    bool BackgroundThread<ReturnType, Args...>::isRunning() const noexcept
    {
        return isRunning_.load();
    }

    template <class ReturnType, typename... Args>
    bool BackgroundThread<ReturnType, Args...>::isSingleTask() const noexcept
    {
        unique_lock<std::mutex> lock(mutex_);
        return isSingleTask_;
    }

    template <class ReturnType, typename... Args>
    void BackgroundThread<ReturnType, Args...>::setSingleTask(bool singleTask)
    {
        unique_lock<std::mutex> lock(mutex_);
        isSingleTask_ = singleTask;
    }

    template <class ReturnType, typename... Args>
    void BackgroundThread<ReturnType, Args...>::setFunction(Func func, Args... args)
    {
        stop();
        {
            unique_lock<std::mutex> lock(mutex_);
            toExecute_ = func;
        }
        start(args...);
    }

    template <class ReturnType, typename... Args>
    const typename BackgroundThread<ReturnType, Args...>::Func& BackgroundThread<ReturnType, Args...>::
    getFunction() const noexcept
    {
        unique_lock<std::mutex> lock(mutex_);
        return toExecute_;
    }

    template <class ReturnType, typename... Args>
    void BackgroundThread<ReturnType, Args...>::setInterval(Millis interval)
    {
        unique_lock<std::mutex> lock(mutex_);
        interval_ = interval;
    }

    template <class ReturnType, typename... Args>
    typename BackgroundThread<ReturnType, Args...>::Millis BackgroundThread<ReturnType, Args...>::
    getInterval() const noexcept
    {
        unique_lock<std::mutex> lock(mutex_);
        return interval_;
    }

    template <class ReturnType, typename... Args>
    std::optional<typename BackgroundThread<ReturnType, Args...>::ResultStorage> BackgroundThread<ReturnType, Args...>::
    getLastResult() const
    {
        unique_lock<std::mutex> lock(mutex_);
        return lastResult_;
    }

    template <class ReturnType, typename... Args>
    void BackgroundThread<ReturnType, Args...>::loop_(Args... args)
    {
        auto argsTuple = std::make_tuple(std::forward<Args>(args)...);
        thread_ = std::jthread([this, argsTuple = std::move(argsTuple)](std::stop_token stoken) mutable
        {
            // Mark running at the start of the worker
            isRunning_.store(true);
            // Ensure we clear the running flag on any exit path
            auto clearRunning = [&]() noexcept { isRunning_.store(false); };
            try
            {
                while (!stoken.stop_requested())
                {
                    Func funcCopy;
                    Millis waitInterval;
                    {
                        unique_lock<std::mutex> lock(mutex_);
                        funcCopy = toExecute_;
                        waitInterval = interval_;
                    }

                    if constexpr (std::is_same_v<ReturnType, void>)
                    {
                        std::apply(funcCopy, argsTuple);
                        {
                            unique_lock<std::mutex> lock(mutex_);
                            lastResult_ = std::monostate{};
                        }
                    }
                    else
                    {
                        auto res = std::apply(funcCopy, argsTuple);
                        {
                            unique_lock<std::mutex> lock(mutex_);
                            lastResult_ = std::optional<ReturnType>{std::move(res)};
                        }
                    }
                    unique_lock<std::mutex> lock(mutex_);
                    if (isSingleTask_)
                    {
                        break; // perform only a single run
                    }
                    if (cv_.wait_for(lock, waitInterval, [&stoken] { return stoken.stop_requested(); }))
                        break;
                }
            }
            catch (...)
            {
                clearRunning();
                throw;
            }
            clearRunning();
        });
    }
}
