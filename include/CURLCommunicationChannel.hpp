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
    CURLCommunicationChannel(const std::string url_api)
        : url_api_(url_api), curl_(curl_easy_init()), buffer_("") {}

    void startup_settings() {
        if (this->curl_) {
            curl_easy_setopt(this->curl_, CURLOPT_URL, this->url_api_.c_str());
            curl_easy_setopt(this->curl_, CURLOPT_WRITEFUNCTION,
                             CURLCommunicationChannel::write_string_callback);
            curl_easy_setopt(this->curl_, CURLOPT_WRITEDATA, &this->buffer_);
        }
    }

    static size_t write_string_callback(void *contents, size_t size,
                                        size_t nmemb, void *userdata) {
        static_cast<std::string *>(userdata)->append(
            static_cast<char *>(contents), size * nmemb);
        return size * nmemb;
    }

    std::string &request_get() {
        if (this->curl_) {
            this->res_ = curl_easy_perform(this->curl_);
            curl_easy_cleanup(this->curl_);
            if (this->res_ != CURLE_OK) {
                fprintf(stderr, "Get request failed: %s\n",
                        curl_easy_strerror(this->res_));
            }
        }
        return this->buffer_;
    }
};

}  // namespace METEO_TOP
#endif  // COMMUNICATION_CHANNEL_H_
