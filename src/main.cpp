#include <curl/curl.h>

#include <iostream>

#include "PeriodicRequest.hpp"

void display_result(size_t iterartion, std::string result) {
    std::cout << iterartion << " " << result << std::endl;
}

int main(int argc, char *argv[]) {
    std::cout << "HELLO METEO!!" << std::endl;
    const std::string url_api =
        "https://api.open-meteo.com/v1/"
        "forecast?latitude=52.52&longitude=13.41&current_weather=true&hourly="
        "temperature_2m,relativehumidity_2m,windspeed_10m";
    const uint64_t periodic_time_us = 1e6;
    const uint64_t n_request = 2;
    const bool is_n_request_infinite = false;
    METEO_TOP::PeriodicRequest periodicRequest(url_api, periodic_time_us,
                                               &display_result, n_request,
                                               is_n_request_infinite);
    periodicRequest.startup_settings();
    periodicRequest.run();

    return 0;
}