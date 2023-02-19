#include <curl/curl.h>

#include <iostream>

#include "CURLCommunicationChannel.hpp"

int main(int argc, char *argv[]) {
    std::cout << "HELLO METEO!!" << std::endl;
    METEO_TOP::CURLCommunicationChannel communcation_channel(
        "https://api.open-meteo.com/v1/"
        "forecast?latitude=52.52&longitude=13.41&current_weather=true&hourly="
        "temperature_2m,relativehumidity_2m,windspeed_10m");
    communcation_channel.startup_settings();
    std::cout << communcation_channel.request_get() << std::endl;
    return 0;
}