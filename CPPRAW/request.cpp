#include "CPPRAW.hpp"
#include "subreddit.hpp"
#include "post.hpp"
#include "user.hpp"
#include "request.hpp"

namespace cppraw::request{
    pack::pack() = default;
    pack& pack::bearer(cpr::Bearer const& set){
        this -> _bearer = set;
        return *this;
    }
    pack& pack::user_agent(cpr::UserAgent const& set){
        this -> _user_agent = set;
        return *this;
    }
    pack& pack::auth(cpr::Authentication const& set){
        this -> _auth = set;
        return *this;
    }
    pack& pack::url(cpr::Url const& set){
        this -> _url = set;
        return *this;
    }
    pack& pack::params(cpr::Parameters const& set){
        this -> _params = set;
        return *this;
    }

    cpr::Response Get(pack const& p){
        static uint64_t timeout = 0;
        static std::string session = "";
        static auto then = std::chrono::system_clock::now();

        cpr::Session s;
        if(cpr::Url{p._url} != cpr::Url{""})
            s.SetUrl(cpr::Url{p._url});
        if(std::string(p._auth.GetAuthString()) != ":")
            s.SetAuth(p._auth);
        if(std::string(p._bearer.GetToken()) != std::string(cpr::Bearer{""}.GetToken()))
            s.SetBearer(p._bearer);
        if(p._user_agent != cpr::UserAgent{""})
            s.SetUserAgent(p._user_agent);
        if(p._params.GetContent(cpr::CurlHolder()) != cpr::Parameters{{}}.GetContent(cpr::CurlHolder()))
            s.SetParameters(p._params);

        cpr::Response r = s.Get();

        std::this_thread::sleep_until(then + std::chrono::nanoseconds(timeout));
        try{
            uint64_t remaining = std::stoull(r.header["X-Ratelimit-Remaining"]);
            uint64_t reset = std::stoull(r.header["X-Ratelimit-Reset"]);
            if(remaining == 0) remaining = 1;
            if(reset == 0) reset = 1;
            then = std::chrono::system_clock::now();
            timeout = (reset * 1000000000) / remaining;
            return r;
        }
        catch(std::invalid_argument&){
            timeout = 0;
            return r;
        }
    }

    cpr::Response Post(pack const& p){
        static uint64_t timeout = 0;
        static std::string session = "";
        static auto then = std::chrono::system_clock::now();

         cpr::Session s;
        if(cpr::Url{p._url} != cpr::Url{""})
            s.SetUrl(cpr::Url{p._url});
        if(std::string(p._auth.GetAuthString()) != ":")
            s.SetAuth(p._auth);
        if(std::string(p._bearer.GetToken()) != std::string(cpr::Bearer{""}.GetToken()))
            s.SetBearer(p._bearer);
        if(p._user_agent != cpr::UserAgent{""})
            s.SetUserAgent(p._user_agent);
        if(p._params.GetContent(cpr::CurlHolder()) != cpr::Parameters{{}}.GetContent(cpr::CurlHolder()))
            s.SetParameters(p._params);

        cpr::Response r = s.Post();

        std::this_thread::sleep_until(then + std::chrono::nanoseconds(timeout));
        try{
            uint64_t remaining = std::stoull(r.header["X-Ratelimit-Remaining"]);
            uint64_t reset = std::stoull(r.header["X-Ratelimit-Reset"]);
            if(remaining == 0) remaining = 1;
            if(reset == 0) reset = 1;
            then = std::chrono::system_clock::now();
            timeout = (reset * 1000000000) / remaining;
            return r;
        }
        catch(std::invalid_argument&){
            timeout = 0;
            return r;
        }
    }
};