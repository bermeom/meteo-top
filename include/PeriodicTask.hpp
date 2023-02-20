#ifndef PERIODIC_TASK_H_
#define PERIODIC_TASK_H_

#include <chrono>
#include <thread>

namespace METEO_TOP {

class PeriodicTask {
   protected:
    const uint64_t periodic_time_us_;
    const uint64_t n_iterations_;
    bool are_infinite_iterations_;

   public:
    // Constructor
    PeriodicTask(const uint64_t periodic_time_us, const uint64_t n_iterations,
                 const bool are_infinite_iterations = false);

    void run();

    void set_are_infinite_iterations(const bool are_infinite_iterations);

    virtual void task(size_t iterartion) {}
};

}  // namespace METEO_TOP
#endif  // PERIODIC_TASK_H_
