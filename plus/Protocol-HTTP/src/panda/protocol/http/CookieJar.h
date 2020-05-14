#pragma once

#include <panda/string.h>
#include <unordered_map>
#include <algorithm>
#include "Request.h"
#include "Response.h"

namespace panda { namespace protocol { namespace http {

struct CookieJar {
    using Cookie = Response::Cookie;
    using Cookies = Response::Cookies;
    using DomainCookies = std::unordered_map<std::string, Cookies>;

    using Date = Response::Date;

    CookieJar(const string& data = "");

    void add(const string& name, const Cookie& cookie, const Date& now = Date::now()) noexcept;
    Cookies find(const URISP& uri, const Date& now = Date::now()) noexcept;
    void clear() noexcept { domain_cookies.clear(); }

    void collect(const Response& response) noexcept;
    void populate(Request& request) noexcept;

    string to_string(bool include_session = false) const noexcept;

    DomainCookies domain_cookies;
private:
    template<typename Fn> void match(const URISP& uri, Fn&& fn, const Date& now) const noexcept;
};

template<typename Fn>
void CookieJar::match(const URISP& uri, Fn&& fn, const Date& now) const noexcept {
    Cookies result;
    auto& host = uri->host();
    auto& path = uri->path();
    string idomain(host.size() + 1);
    idomain[0] = '.';
    std::transform(host.begin(), host.end(), idomain.begin() + 1,[](auto c){ return std::tolower(c); });
    idomain.length(host.size() + 1);

    for(auto& pair: domain_cookies) {
        auto& domain = pair.first;
        // xxx.yyy.com [idomain] (from URI) should pull-in cookies for
        //     yyy.com [domain]
        // do backward search than
        auto match_r = std::mismatch(domain.rbegin(), domain.rend(), idomain.rbegin());
        if (match_r.first != domain.rend()) continue;
        //if (std::search())

        for(auto& coo: pair.second) {
            auto& value = coo.value;
            auto& p = value.path();
            bool ignore =  (value.secure() && !uri->secure())
                        || (std::mismatch(p.begin(), p.end(), path.begin()).second != path.end())
                        || (value.http_only() && uri->scheme() != "http");
//                        || (!std::includes(p.begin(), p.end(), path.cbegin(), path.cend()))
            if (ignore) continue;

            auto exipres = value.expires();
            if (exipres && exipres.value() < now) continue;

            result.add(coo.name, value);
        }
    }
    std::stable_sort(result.begin(), result.end(), [](auto& a, auto& b) {
        return b.value.path().length() < a.value.path().length();
    });
    for(auto& it: result) fn(it);
}


}}}
