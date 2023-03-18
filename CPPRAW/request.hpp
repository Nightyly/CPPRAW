#ifndef REQUEST_INCLUDED
#define REQUEST_INCLUDED

#include <chrono>
#include <cpr/cpr.h>

namespace cppraw::request{
    struct pack{
        cpr::Bearer bearer{""};
        cpr::UserAgent user_agent{""};
        cpr::Authentication auth{"", "", cpr::AuthMode::BASIC};
        cpr::Url url{""};
        cpr::Body body{""};
        cpr::Parameters params{{}};
        pack(cpr::Bearer const& bearer, cpr::UserAgent const& user_agent, cpr::Authentication const& auth, cpr::Url const& url, cpr::Body const& body, cpr::Parameters const& params);
    };

    cpr::Response Get(pack const& p);
    cpr::Response Post(pack const& p);
};

#endif // REQUEST_INCLUDED