#include "net/base.hpp"
#include <regex>

#include <string>
#include <regex>

namespace net {

bool is_url(const std::string& str) { return str.find("https://") != std::string::npos; }
void check_url(const std::string& url) {
    if (url.empty()) {
        throw NetException("URL cannot be empty");
    }

    const std::regex url_regex(R"(^(https?|ftp)://([a-zA-Z0-9\-\.]+)(:[0-9]+)?(/[\w\-/]*)?$)",
                               std::regex::extended);

    if (!std::regex_match(url, url_regex)) {
        throw NetException("Invalid URL format");
    }

    const std::string forbidden_chars = " <>\"{}|\\^`";
    for (char c : url) {
        if (forbidden_chars.find(c) != std::string::npos) {
            throw NetException("URL contains invalid characters");
        }
    }

    if (url.length() > 2048) {
        throw NetException("URL exceeds maximum allowed length");
    }

    size_t scheme_end = url.find("://");
    size_t host_start = scheme_end + 3;
    size_t host_end = url.find('/', host_start);
    std::string host = url.substr(host_start, host_end - host_start);

    if (host.empty() || host.find_first_not_of(
                            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-") !=
                            std::string::npos) {
        throw NetException("URL contains invalid host");
    }

    if (url.substr(0, 5) != "https") {
        throw NetException("Only HTTPS URLs are allowed");
    }
}
} // namespace net
