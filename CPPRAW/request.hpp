#ifndef REQUEST_INCLUDED
#define REQUEST_INCLUDED

#include <chrono>
#include <cpr/cpr.h>

#include <iostream>

namespace cppraw::request{
    struct pack{
        cpr::Bearer bearer{""};
        cpr::UserAgent user_agent{""};
        cpr::Authentication auth{"", "", cpr::AuthMode::BASIC};
        cpr::Url url{""};
        cpr::Body body{""};
        cpr::Parameters params{{}};
        pack(cpr::Bearer bearer, cpr::UserAgent user_agent, cpr::Authentication auth, cpr::Url url, cpr::Body body, cpr::Parameters params);
    };

    cpr::Response Get(pack p);
    cpr::Response Post(pack p);
};

#endif // REQUEST_INCLUDED