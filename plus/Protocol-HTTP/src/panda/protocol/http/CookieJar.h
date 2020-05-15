#pragma once

#include <panda/string.h>
#include <unordered_map>
#include <algorithm>
#include <boost/container/small_vector.hpp>
//#include <iostream>
#include "Request.h"
#include "Response.h"

namespace panda { namespace protocol { namespace http {

struct CookieJar {
    using Date = Response::Date;

    struct Cookie : Response::Cookie {
        Cookie(const string& name, const Response::Cookie& original, const URISP& origin, const Date& now) noexcept;

        const URISP& origin() const noexcept { return _origin; }
        const string& name()  const noexcept { return _name;   }

        void origin(const URISP& origin) noexcept { _origin = origin; }
        void name(const string& name)    noexcept { _name = name;     }

        bool allowed_by_same_site(const URISP& request, bool lax_context) const noexcept;

    private:
        string _name;
        URISP _origin;
    };

    using Cookies = boost::container::small_vector<Cookie, 15>;
    using DomainCookies = std::unordered_map<string, Cookies>;


    CookieJar(const string& data = "");

    void add(const string& name, const Response::Cookie& cookie, const URISP& origin, const Date& now = Date::now()) noexcept;
    Cookies find(const URISP& uri, const Date& now = Date::now(), bool lax_context = false) noexcept;
    void clear() noexcept { domain_cookies.clear(); }

    static bool sub_match(const string& cookie_domain, const string& request_domain) noexcept;

    void collect(const Response& response) noexcept;
    void populate(Request& request) noexcept;

    string to_string(bool include_session = false) const noexcept;

    DomainCookies domain_cookies;

private:
    template<typename Fn> void match(const URISP& uri, Fn&& fn, const Date& now, bool lax_context) const noexcept;
};

template<typename Fn>
void CookieJar::match(const URISP& uri, Fn&& fn, const Date& now, bool lax_context) const noexcept {
    Cookies result;
    auto& host = uri->host();
    auto& path = uri->path();
    string request_domain(host.size() + 1);
    request_domain[0] = '.';
    std::transform(host.begin(), host.end(), request_domain.begin() + 1,[](auto c){ return std::tolower(c); });
    request_domain.length(host.size() + 1);

    for(auto& pair: domain_cookies) {
        auto& domain = pair.first;
        if (!sub_match(domain, request_domain)) continue;

        for(auto& coo: pair.second) {
            auto& p = coo.path();
            bool ignore =  (coo.secure() && !uri->secure())
                        || (std::mismatch(p.begin(), p.end(), path.begin()).second != path.end());
            // we ignore http-only flag, i.e. provide API-access to that cookie
            if (ignore) continue;

            auto exipres = coo.expires();
            if (exipres && exipres.value() < now) continue;

            if (!coo.allowed_by_same_site(uri, lax_context)) continue;

            result.emplace_back(coo);
        }
    }
    std::stable_sort(result.begin(), result.end(), [](auto& a, auto& b) {
        return b.path().length() < a.path().length();
    });
    for(auto& it: result) fn(it);
}


}}}
