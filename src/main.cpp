#include <curl/curl.h>

#include <iostream>

#include "DisplayData.hpp"
#include "PeriodicRequest.hpp"

int main(int argc, char *argv[]) {
    std::cout << "HELLO METEO!!" << std::endl;
    const std::string url_api =
        "https://api.open-meteo.com/v1/"
        "forecast?latitude=52.52&longitude=13.41&current_weather=true&"
        "hourly="
        "temperature_2m,relativehumidity_2m,windspeed_10m";
    const uint64_t periodic_time_us = 1e6;

    const uint64_t n_request = 5;
    const bool is_n_request_infinite = false;
    METEO_TOP::DisplayOpenMeteoData::show_full_data = false;
    METEO_TOP::PeriodicRequest periodicRequest(
        url_api, &METEO_TOP::DisplayOpenMeteoData::show_data, periodic_time_us,
        n_request, is_n_request_infinite);
    periodicRequest.startup_settings();

    periodicRequest.PeriodicTask::run();
    return 0;
}