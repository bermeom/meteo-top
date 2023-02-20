#include "PeriodicTask.hpp"

namespace METEO_TOP {

PeriodicTask::PeriodicTask(const uint64_t periodic_time_us,
                           const uint64_t n_iterations,
                           const bool are_infinite_iterations)
    : periodic_time_us_(periodic_time_us),
      n_iterations_(n_iterations),
      are_infinite_iterations_(are_infinite_iterations) {}

void PeriodicTask::run() {
    for (size_t i = 0;
         i < this->n_iterations_ or this->are_infinite_iterations_; ++i) {
        this->task(i);
        std::this_thread::sleep_for(
            std::chrono::microseconds(this->periodic_time_us_));
    }
}

void PeriodicTask::set_are_infinite_iterations(
    const bool are_infinite_iterations) {
    this->are_infinite_iterations_ = are_infinite_iterations;
}

}  // namespace METEO_TOP
