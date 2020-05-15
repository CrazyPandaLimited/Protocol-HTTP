#include "CookieJar.h"

/* I don't think it is needed:

NOTE: For security reasons, many user agents are configured to reject
   Domain attributes that correspond to "public suffixes".  For example,
   some user agents will reject Domain attributes of "com" or "co.uk".
   (See Section 5.3 for more information.)

https://publicsuffix.org/list/

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
    /* rfc6265
       If the server omits the Path attribute, the user
       agent will use the "directory" of the request-uri's path component as
       the default value.  (See Section 5.1.4 for more details.)
    */
    if (!path()) { path(origin->path()); }

    /* rfc6265
     If the server omits the Domain attribute, the user
     agent will return the cookie only to the origin server.

      WARNING: Some existing user agents treat an absent Domain
      attribute as if the Domain attribute were present and contained
      the current host name.  For example, if example.com returns a Set-
      Cookie header without a Domain attribute, these user agents will
      erroneously send the cookie to www.example.com as well.
    */
    if (!domain()) {
        domain(origin->host());
        _host_only = true;
    }

    auto ss = same_site();
    if (ss == SameSite::None || ss == SameSite::disabled) {
        _origin.reset(); // no need to store origin, discard it early
    }
}

bool CookieJar::Cookie::allowed_by_same_site(const URISP& request, bool lax_context) const noexcept {
    bool r = true;
    switch (same_site()) {
    case SameSite::Strict: r = is_same(origin()->host(), request->host()); break;
    case SameSite::Lax:    r = lax_context || is_same(origin()->host(), request->host()); break;
    default:               break;
    }
    return r;
}

CookieJar::CookieJar(const string& data) {

}

void CookieJar::add(const string& name, const Response::Cookie& cookie, const URISP& origin, const Date& now) noexcept {
    auto domain = cookie.domain();
    if (!domain) domain = origin->host();

    string idomain = canonize(domain);

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

    if (cookie.session()) { add(cookie); return; }
    if (cookie.expires()) {
        if (*cookie.expires() > now) add(cookie);
        else remove_same(true);
        return;
    }

    add(cookie);
}

bool CookieJar::sub_match(const string& cookie_domain, const string& request_domain) noexcept {
    assert(cookie_domain[0] == '.');
    assert(request_domain[0] == '.');
    // xxx.yyy.com [idomain] (from URI) should pull-in cookies for
    //     yyy.com [domain]
    // do backward search than
    auto r = std::mismatch(cookie_domain.rbegin(), cookie_domain.rend(), request_domain.rbegin());
    if (r.first != cookie_domain.rend()) return false;
    return true;
}


CookieJar::Cookies CookieJar::find(const URISP& uri, const Date& now, bool lax_context) noexcept {
    Cookies result;
    match(uri, [&](auto& coo){ result.emplace_back(coo); }, now, lax_context );
    return result;
}

void CookieJar::collect(const Response &res, const Request &req, const Date& now) noexcept {
    string req_domain = canonize(req.uri->host());
    for(auto& wrapped_coo: res.cookies) {
        auto& coo = wrapped_coo.value;

        bool ignore = (coo.domain() && !sub_match(canonize(coo.domain()), req_domain))
                   || (ignore_predicate && ignore_predicate(coo));

        if (ignore) continue;

        add(wrapped_coo.name, coo, req.uri, now);
    }
}



}}}
