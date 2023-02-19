#include "CURLCommunicationChannel.hpp"

#include <catch2/catch_all.hpp>

TEST_CASE("Test a GET request", "[unit]") {
    METEO_TOP::CURLCommunicationChannel communcation_channel(
        "https://rickandmortyapi.com/api/character/380");
    communcation_channel.startup_settings();
    std::string answer = communcation_channel.request_get();
    const std::string expected_answer =
        "{\"id\":380,\"name\":\"Unknown "
        "Rick\",\"status\":\"unknown\",\"species\":\"Human\",\"type\":\"\","
        "\"gender\":\"Male\",\"origin\":{\"name\":\"unknown\",\"url\":\"\"},"
        "\"location\":{\"name\":\"unknown\",\"url\":\"\"},\"image\":\"https://"
        "rickandmortyapi.com/api/character/avatar/"
        "380.jpeg\",\"episode\":[\"https://rickandmortyapi.com/api/episode/"
        "22\",\"https://rickandmortyapi.com/api/episode/51\"],\"url\":\"https:/"
        "/rickandmortyapi.com/api/character/"
        "380\",\"created\":\"2018-01-10T19:44:22.262Z\"}";
    REQUIRE(expected_answer.compare(answer) == 0);
}
