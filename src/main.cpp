#include <curl/curl.h>
#include <unistd.h>

#include <csignal>
#include <iostream>
#include <sstream>

#include "DisplayData.hpp"
#include "PeriodicRequest.hpp"

void termination_signal_handler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    // cleanup and close up stuff here
    // terminate program
    exit(signum);
}

void config_terminate_program() {
    std::signal(SIGINT, termination_signal_handler);
    std::signal(SIGTERM, termination_signal_handler);
}

void execute_periodic_task(const uint64_t periodic_time_us,
                           const uint64_t n_requests,
                           const bool is_n_requests_infinite) {
    const std::string url_api =
        "https://api.open-meteo.com/v1/"
        "forecast?latitude=52.52&longitude=13.41&current_weather=true&"
        "hourly="
        "temperature_2m,relativehumidity_2m,windspeed_10m";

    METEO_TOP::PeriodicRequest periodicRequest(
        url_api, &METEO_TOP::DisplayOpenMeteoData::show_data, periodic_time_us,
        n_requests, is_n_requests_infinite);
    periodicRequest.startup_settings();
    periodicRequest.PeriodicTask::run();
}

uint64_t get_integer(char* cnum) {
    // This function cast char* to integer considering exponential form
    std::stringstream ss;
    long double temp;
    ss << optarg;
    ss >> temp;
    return static_cast<uint64_t>(temp);
}

std::string get_help_text() {
    return "usage: meteo-top [-t <periodic_time_us>] [-n <number_of_requests>] "
           "\n"
           "                 [-i] [-a] [-h]\n"
           "  options:\n"
           "    -t <periodic_time_us>   = Time interval between requests in "
           "microseconds\n"
           "    -n <number_of_requests> = Number of requests to perform\n"
           "    -i                      = Enable makes infinite requests and "
           "ignores any\n"
           "                              input with -n\n"
           "    -a                      = Display the full response to the GET "
           "request\n"
           "    -h                      = Print help\n"
           "Note: -t and either -n or -i options are required to run the "
           "program\n";
}

int main(int argc, char* argv[]) {
    config_terminate_program();

    int ch;
    uint64_t periodic_time_us = 0;
    uint64_t n_requests = 0;
    bool is_n_requests_infinite = false;
    std::string help_text = get_help_text();
    int mask_opts = 0;
    METEO_TOP::DisplayOpenMeteoData::show_full_data = false;

    while ((ch = getopt(argc, argv, "aht:n:i")) != -1) {
        switch (ch) {
            case 't':
                periodic_time_us = get_integer(optarg);
                mask_opts |= 1 << 0;
                break;
            case 'n':
                n_requests = get_integer(optarg);
                mask_opts |= 1 << 1;
                break;
            case 'i':
                is_n_requests_infinite = true;
                mask_opts |= 1 << 1;
                break;
            case 'a':
                METEO_TOP::DisplayOpenMeteoData::show_full_data = true;
                mask_opts |= 1 << 2;
                break;
            case 'h':
                printf("%s\n", help_text.c_str());
                mask_opts |= 1 << 3;
                break;
        }
    }

    if ((mask_opts & 3) != 3) {
        if (((mask_opts >> 3) & 1) == 0) {
            printf("%s\n", help_text.c_str());
        }
        return 0;
    }

    if (is_n_requests_infinite) {
        n_requests = 0;
    }

    execute_periodic_task(periodic_time_us, n_requests, is_n_requests_infinite);

    return 0;
}