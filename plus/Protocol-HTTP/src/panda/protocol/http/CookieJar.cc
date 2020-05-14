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

CookieJar::CookieJar(const string& data) {

}

void CookieJar::add(const string& name, const Cookie& cookie, const Date& now) noexcept {
    auto domain = cookie.domain();
    if (!domain) return;

    string idomain(domain.length() + 1);
    idomain[0] = '.';
    std::transform(domain.begin(), domain.end(), idomain.begin() + 1,[](auto c){ return std::tolower(c); });
    idomain.length(domain.length() + 1);

    auto remove_same = [&](bool cleanup) {
        auto& cookies = domain_cookies[idomain];
        auto& fields = cookies.fields;
        for (auto it = fields.cbegin(); it != fields.cend();) {
            if (it->name == name && it->value.path() == cookie.path()) it = fields.erase(it);
            else                                                       ++it;
        }
        if (cleanup && cookies.empty()) domain_cookies.erase(idomain);
    };
    auto add = [&](auto& coo) {
        remove_same(false);
        auto& cookies = domain_cookies[idomain];
        cookies.add(name, coo);
        return cookies.fields.back();
    };

    if (!cookie.path())   { return; }
    if (cookie.session()) { add(cookie); return; }
    if (cookie.expires()) {
        if (*cookie.expires() > now) add(cookie);
        else remove_same(true);
        return;
    }

    auto expires = now.epoch() + cookie.max_age();
    auto coo = Cookie (
        cookie.value(),
        cookie.domain(),
        cookie.path(),
        0,
        cookie.secure(),
        cookie.http_only(),
        cookie.same_site()
    );
    add(coo).value.expires(Date(expires));
}

CookieJar::Cookies CookieJar::find(const URISP& uri, const Date& now) noexcept {
    Cookies result;
    match(uri, [&](auto& coo){ result.add(coo.name, coo.value); }, now );
    return result;
}



}}}