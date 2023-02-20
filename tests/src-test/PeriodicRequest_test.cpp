#include "PeriodicRequest.hpp"

#include <catch2/catch_all.hpp>

namespace PRT {

auto start = std::chrono::steady_clock::now();
double average_periodic_time_us = 0;
uint64_t count = 0;
METEO_TOP::PeriodicRequest *periodicRequest = nullptr;

}  // namespace PRT

TEST_CASE("Test periodic request", "[unit]") {
    const std::string url_api =
        "https://api.open-meteo.com/v1/"
        "forecast?latitude=52.52&longitude=13.41&current_weather=true&hourly="
        "temperature_2m,relativehumidity_2m,windspeed_10m";
    const uint64_t periodic_time_us = 1e6;

    SECTION("Periodicity") {
        const uint64_t n_request = 5;
        const bool is_n_request_infinite = false;
        PRT::start = std::chrono::steady_clock::now();
        PRT::count = 0;

        METEO_TOP::PeriodicRequest periodicRequest(
            url_api, periodic_time_us,
            [](size_t iterartion, std::string result) {
                auto current = std::chrono::steady_clock::now();
                std::chrono::duration<double, std::micro> diff =
                    current - PRT::start;
                double time_us = diff.count();
                PRT::start = current;
                if (PRT::count >= 1) {
                    PRT::average_periodic_time_us =
                        (PRT::average_periodic_time_us * (PRT::count - 1) +
                         time_us) /
                        PRT::count;
                }
                ++PRT::count;
            },
            n_request, is_n_request_infinite);
        periodicRequest.startup_settings();

        periodicRequest.run();
        const double MIN_ERROR = 0.1;
        const double error_rate =
            (PRT::average_periodic_time_us / periodic_time_us - 1);
        REQUIRE((error_rate <= MIN_ERROR && PRT::count == n_request));
    }

    SECTION("Infinite periodicity") {
        const uint64_t n_request = 0;
        const bool is_n_request_infinite = true;
        PRT::start = std::chrono::steady_clock::now();
        PRT::count = 0;
        METEO_TOP::PeriodicRequest periodicRequest(
            url_api, periodic_time_us,
            [](size_t iterartion, std::string result) {
                REQUIRE(true);
                PRT::periodicRequest->set_is_n_request_infinite(false);
            },
            n_request, is_n_request_infinite);
        periodicRequest.startup_settings();
        PRT::periodicRequest = &periodicRequest;
        periodicRequest.run();
    }
}
