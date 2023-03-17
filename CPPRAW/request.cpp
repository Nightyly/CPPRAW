#include "CPPRAW.hpp"
#include "subreddit.hpp"
#include "post.hpp"
#include "user.hpp"
#include "request.hpp"

namespace cppraw::request{
    pack::pack(cpr::Bearer bearer, cpr::UserAgent user_agent, cpr::Authentication auth, cpr::Url url, cpr::Body body, cpr::Parameters params){
        this -> bearer = bearer;
        this -> user_agent = user_agent;
        this -> auth = auth;
        this -> url = url;
        this -> body = body;
        this -> params = params;
    }

    cpr::Response Get(pack p){
        static uint64_t timeout = 0;
        static std::string session = "";
        static auto then = std::chrono::system_clock::now();

        cpr::Session s;
        if(cpr::Url{p.url} != cpr::Url{""})
            s.SetUrl(cpr::Url{p.url});
        if(std::string(p.auth.GetAuthString()) != ":")
            s.SetAuth(p.auth);
        if(std::string(p.bearer.GetToken()) != std::string(cpr::Bearer{""}.GetToken()))
            s.SetBearer(p.bearer);
        if(p.user_agent != cpr::UserAgent{""})
            s.SetUserAgent(p.user_agent);
        if(p.params.GetContent(cpr::CurlHolder()) != cpr::Parameters{{}}.GetContent(cpr::CurlHolder()))
            s.SetParameters(p.params);
        if(p.body != cpr::Body{""})
            s.SetBody(p.body);

        cpr::Response r = s.Get();

        std::this_thread::sleep_until(then + std::chrono::nanoseconds(timeout));
        for(const auto &cookie : r.cookies) {
            if(cookie.GetName() != "session_tracker") continue;
            session = cookie.GetValue();
        }
        try{
            uint64_t remaining = std::stoull(r.header["X-Ratelimit-Remaining"]);
            uint64_t reset = std::stoull(r.header["X-Ratelimit-Reset"]);
            if(remaining == 0) remaining = 1;
            if(reset == 0) reset = 1;
            then = std::chrono::system_clock::now();
            timeout = (reset * 1000000000) / (remaining);
            return r;
        }
        catch(std::invalid_argument&){
            timeout = 0;
            return r;
        }
    }

    cpr::Response Post(pack p){
        static uint64_t timeout = 0;
        static std::string session = "";
        static auto then = std::chrono::system_clock::now();

        cpr::Session s;
        if(cpr::Url{p.url} != cpr::Url{""})
            s.SetUrl(cpr::Url{p.url});
        if(std::string(p.auth.GetAuthString()) != ":")
            s.SetAuth(p.auth);
        if(std::string(p.bearer.GetToken()) != std::string(cpr::Bearer{""}.GetToken()))
            s.SetBearer(p.bearer);
        if(p.user_agent != cpr::UserAgent{""})
            s.SetUserAgent(p.user_agent);
        if(p.params.GetContent(cpr::CurlHolder()) != cpr::Parameters{{}}.GetContent(cpr::CurlHolder()))
            s.SetParameters(p.params);
        if(p.body != cpr::Body{""})
            s.SetBody(p.body);

        cpr::Response r = s.Post();

        std::this_thread::sleep_until(then + std::chrono::nanoseconds(timeout));
        for(const auto &cookie : r.cookies) {
            if(cookie.GetName() != "session_tracker") continue;
            session = cookie.GetValue();
        }
        try{
            uint64_t remaining = std::stoull(r.header["X-Ratelimit-Remaining"]);
            uint64_t reset = std::stoull(r.header["X-Ratelimit-Reset"]);
            if(remaining == 0) remaining = 1;
            if(reset == 0) reset = 1;
            then = std::chrono::system_clock::now();
            timeout = (reset * 1000000000) / (remaining);
            return r;
        }
        catch(std::invalid_argument&){
            timeout = 0;
            return r;
        }
    }
};