#include "PeriodicRequest.hpp"

namespace METEO_TOP {

PeriodicRequest::PeriodicRequest(const std::string url_api,
                                 const uint64_t periodic_time_us,
                                 void (*call_back)(size_t, std::string),
                                 const uint64_t n_request,
                                 const bool is_n_request_infinite)
    : communcation_channel_(url_api),
      periodic_time_us_(periodic_time_us),
      call_back_(call_back),
      n_request_(n_request),
      is_n_request_infinite_(is_n_request_infinite) {}

void PeriodicRequest::startup_settings() {
    this->communcation_channel_.startup_settings();
}

void PeriodicRequest::run() {
    std::string result;
    for (size_t i = 0; i < this->n_request_ or this->is_n_request_infinite_;
         ++i) {
        this->call_back_(i, this->communcation_channel_.request_get());
        std::this_thread::sleep_for(
            std::chrono::microseconds(this->periodic_time_us_));
    }
}

}  // namespace METEO_TOP
