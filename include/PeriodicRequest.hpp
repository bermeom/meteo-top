#ifndef PERIODIC_REQUEST_H_
#define PERIODIC_REQUEST_H_

#include "CURLCommunicationChannel.hpp"
#include "PeriodicTask.hpp"

namespace METEO_TOP {

class PeriodicRequest : public PeriodicTask {
   protected:
    CURLCommunicationChannel communcation_channel_;
    void (*callback_)(size_t, std::string);

   public:
    // Constructor
    PeriodicRequest(const std::string url_api,
                    void (*callback)(size_t, std::string),
                    const uint64_t periodic_time_us,
                    const uint64_t n_iterations,
                    const bool are_infinite_iterations = false);

    void startup_settings();

    void run();

    void task(size_t iterartion) override;
};

}  // namespace METEO_TOP

//*/
#endif  // PERIODIC_REQUEST_H_
