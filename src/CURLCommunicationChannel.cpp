
#include "CURLCommunicationChannel.hpp"

#include <curl/curl.h>

#include <iostream>
#include <string>

namespace METEO_TOP {

CURLCommunicationChannel::CURLCommunicationChannel(const std::string url_api)
    : url_api_(url_api), curl_(curl_easy_init()), buffer_("") {}

void CURLCommunicationChannel::startup_settings() {
    if (this->curl_) {
        curl_easy_setopt(this->curl_, CURLOPT_URL, this->url_api_.c_str());
        curl_easy_setopt(this->curl_, CURLOPT_WRITEFUNCTION,
                         CURLCommunicationChannel::write_string_callback);
        curl_easy_setopt(this->curl_, CURLOPT_WRITEDATA, &this->buffer_);
        curl_easy_setopt(this->curl_, CURLOPT_TIMEOUT, 5);
    }
}

size_t CURLCommunicationChannel::write_string_callback(void *contents,
                                                       size_t size,
                                                       size_t nmemb,
                                                       void *userdata) {
    static_cast<std::string *>(userdata)->append(static_cast<char *>(contents),
                                                 size * nmemb);
    return size * nmemb;
}

std::string &CURLCommunicationChannel::request_get() {
    if (this->curl_) {
        this->res_ = curl_easy_perform(this->curl_);

        if (this->res_ != CURLE_OK) {
            fprintf(stderr, "Get request failed: %s\n",
                    curl_easy_strerror(this->res_));
        }
    }
    return this->buffer_;
}

CURLCommunicationChannel::~CURLCommunicationChannel() {
    if (this->curl_) {
        curl_easy_cleanup(this->curl_);
    }
}

}  // namespace METEO_TOP
