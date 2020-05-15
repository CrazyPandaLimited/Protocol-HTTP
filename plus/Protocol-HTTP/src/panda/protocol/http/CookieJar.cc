#include "CookieJar.h"

// 1. If a CGI script wishes to delete a cookie, it can do so by returning a cookie with the same name, and an expires time which is in the past.
// The path and name must match exactly in order for the expiring cookie to replace the valid cookie.
// This requirement makes it difficult for anyone but the originator of a cookie to delete a cookie.

// 2. If an explicitly specified value does not start with a dot, the user agent supplies a leading dot.

/* 3.
.   If the cookie-attribute-list contains an attribute with an
     attribute-name of "Path", set the cookie's path to attribute-
     value of the last attribute in the cookie-attribute-list with an
     attribute-name of "Path".  Otherwise, set the cookie's path to
     the default-path of the request-uri.
*/

namespace panda { namespace protocol { namespace http {

static bool is_same(const string& original_host, const string& request_host) noexcept {
    return original_host == request_host;
}

CookieJar::Cookie::Cookie(const string& name, const Response::Cookie& original, const URISP& origin, const Date& now) noexcept
    : Response::Cookie{original}, _name{name}, _origin{origin}
{
    if (max_age()) {
        auto deadline = now.epoch() + max_age();
        expires(Date(deadline));
        max_age(0);
    }
    auto ss = same_site();
    if (ss == SameSite::None || ss == SameSite::disabled) {
        _origin.reset(); // no need to store origin, discard it early
    }
}

bool CookieJar::Cookie::allowed_by_same_site(const URISP& request, bool lax_context) const noexcept {
    switch (same_site()) {
    case SameSite::Strict: return is_same(origin()->host(), request->host());
    case SameSite::Lax:    return lax_context || is_same(origin()->host(), request->host());
    case SameSite::disabled:  /* fall thought */
    case SameSite::None:      return true;
    }
}


CookieJar::CookieJar(const string& data) {

}

void CookieJar::add(const string& name, const Response::Cookie& cookie, const URISP& origin, const Date& now) noexcept {
    auto domain = cookie.domain();
    if (!domain) return;

    string idomain(domain.length() + 1);
    idomain[0] = '.';
    std::transform(domain.begin(), domain.end(), idomain.begin() + 1,[](auto c){ return std::tolower(c); });
    idomain.length(domain.length() + 1);

    auto remove_same = [&](bool cleanup) {
        auto& cookies = domain_cookies[idomain];
        for (auto it = cookies.cbegin(); it != cookies.cend();) {
            if (it->name() == name && it->path() == cookie.path()) it = cookies.erase(it);
            else                                                 ++it;
        }
        if (cleanup && cookies.empty()) domain_cookies.erase(idomain);
    };
    auto add = [&](auto& coo) {
        remove_same(false);
        auto& cookies = domain_cookies[idomain];
        cookies.emplace_back(Cookie(name, coo, origin, now));
    };

    if (!cookie.path())   { return; }
    if (cookie.session()) { add(cookie); return; }
    if (cookie.expires()) {
        if (*cookie.expires() > now) add(cookie);
        else remove_same(true);
        return;
    }

    add(cookie);
}

CookieJar::Cookies CookieJar::find(const URISP& uri, const Date& now, bool lax_context) noexcept {
    Cookies result;
    match(uri, [&](auto& coo){ result.emplace_back(coo); }, now, lax_context );
    return result;
}



}}}
