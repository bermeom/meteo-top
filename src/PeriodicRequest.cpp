#include "PeriodicRequest.hpp"

namespace METEO_TOP {

PeriodicRequest::PeriodicRequest(const std::string url_api,
                                 void (*callback)(size_t, std::string),
                                 const uint64_t periodic_time_us,
                                 const uint64_t n_iterations,
                                 const bool are_infinite_iterations)
    : communcation_channel_(url_api),
      callback_(callback),
      PeriodicTask(periodic_time_us, n_iterations, are_infinite_iterations) {}

void PeriodicRequest::startup_settings() {
    this->communcation_channel_.startup_settings();
}

void PeriodicRequest::task(size_t iterartion) {
    this->callback_(iterartion, this->communcation_channel_.request_get());
}

}  // namespace METEO_TOP
