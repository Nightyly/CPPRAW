#ifndef REQUEST_INCLUDED
#define REQUEST_INCLUDED

#include <chrono>
#include <cpr/cpr.h>

namespace cppraw::request{
    struct pack{
        cpr::Bearer _bearer{""};
        cpr::UserAgent _user_agent{""};
        cpr::Authentication _auth{"", "", cpr::AuthMode::BASIC};
        cpr::Url _url{""};
        cpr::Parameters _params{{}};
        pack();
        pack& bearer(cpr::Bearer const& bearer);
        pack& user_agent(cpr::UserAgent const& user_agent);
        pack& auth(cpr::Authentication const& auth);
        pack& url(cpr::Url const& url);
        pack& params(cpr::Parameters const& params);
    };

    cpr::Response Get(pack const& p);
    cpr::Response Post(pack const& p);
};

#endif // REQUEST_INCLUDED