#ifndef PERIODIC_REQUEST_H_
#define PERIODIC_REQUEST_H_

#include <chrono>
#include <thread>

#include "CURLCommunicationChannel.hpp"

namespace METEO_TOP {

class PeriodicRequest {
   protected:
    CURLCommunicationChannel communcation_channel_;
    const uint64_t periodic_time_us_;
    const uint64_t n_request_;
    bool is_n_request_infinite_;
    void (*call_back_)(size_t, std::string);

   public:
    // Constructor
    PeriodicRequest(const std::string url_api, const uint64_t periodic_time_us,
                    void (*call_back)(size_t, std::string),
                    const uint64_t n_request,
                    const bool is_n_request_infinite = false);

    void startup_settings();

    void run();

    void set_is_n_request_infinite(const bool is_n_request_infinite);
};

}  // namespace METEO_TOP
#endif  // PERIODIC_REQUEST_H_
