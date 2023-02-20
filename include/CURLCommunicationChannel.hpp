#ifndef CURL_COMMUNICATION_CHANNEL_H_
#define CURL_COMMUNICATION_CHANNEL_H_

#include <curl/curl.h>

#include <iostream>
#include <string>

namespace METEO_TOP {

class CURLCommunicationChannel {
   protected:
    CURL *curl_;
    CURLcode res_;
    std::string buffer_;
    const std::string url_api_;

   public:
    // Constructor
    CURLCommunicationChannel(const std::string url_api);
    // Destructor
    ~CURLCommunicationChannel();
    // Methods
    void startup_settings();

    static size_t write_string_callback(void *contents, size_t size,
                                        size_t nmemb, void *userdata);

    std::string &request_get();
};

}  // namespace METEO_TOP
#endif  // COMMUNICATION_CHANNEL_H_
