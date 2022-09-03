#include "CPPRAW.hpp"
#include "subreddit.hpp"
#include "post.hpp"
#include "request.hpp"

namespace cppraw{

    subreddit::subreddit(std::string sub, std::string bearer, std::string user_agent){
        this -> sub = sub;
        this -> bearer = bearer;
        this -> user_agent = user_agent;
        cpr::Response r = cppraw::request::Get(cppraw::request::pack(
            cpr::Bearer{bearer},
            cpr::UserAgent{user_agent},
            cpr::Authentication{"", "", cpr::AuthMode::BASIC},
            cpr::Url("https://oauth.reddit.com/r/" + sub + "/about/moderators"),
            cpr::Body{""},
            cpr::Parameters{{}}
        ));
        nlohmann::json j = nlohmann::json::parse(r.text);
        if(j["kind"] != "UserList")
            throw std::invalid_argument("Unknown subreddit.");
    }

    std::vector<cppraw::post> subreddit::recent(int limit, std::string after, std::string before){
        std::vector<cppraw::post> v;
        if(limit > 100) limit = 100;
        cpr::Parameters params;
        if(after == "" && before != "")
            params = cpr::Parameters{{"limit", std::to_string(limit)}, {"before", before}};
        else if(after != "" && before == "")
            params = cpr::Parameters{{"limit", std::to_string(limit)}, {"after", after}};
        else
            params = cpr::Parameters{{"limit", std::to_string(limit)}};

        cpr::Response r = cppraw::request::Get(cppraw::request::pack(
            cpr::Bearer{bearer},
            cpr::UserAgent{user_agent},
            cpr::Authentication{"", "", cpr::AuthMode::BASIC},
            cpr::Url("https://oauth.reddit.com/r/" + sub + "/new"),
            cpr::Body{""},
            params
        ));

        if(r.status_code != 200){
            throw std::invalid_argument(r.text);
        }
        nlohmann::json j = nlohmann::json::parse(r.text);
        for(int i = 0; i != j["data"]["children"].size(); i++){
            v.push_back(cppraw::post(j["data"]["children"][i]["data"], bearer, user_agent));
        }

        return v;
    }

    cppraw::post subreddit::get_post(std::string id){
        cpr::Response r = cppraw::request::Get(cppraw::request::pack(
            cpr::Bearer{bearer},
            cpr::UserAgent{user_agent},
            cpr::Authentication{"", "", cpr::AuthMode::BASIC},
            cpr::Url("https://oauth.reddit.com/r/" + sub + "/comments/" + id),
            cpr::Body{""},
            cpr::Parameters{{}}
        ));
        if(r.status_code != 200){
            throw std::invalid_argument(r.text);
        }
        nlohmann::json j = nlohmann::json::parse(r.text);
        return cppraw::post(j[0]["data"]["children"][0]["data"], bearer, user_agent);
    }
}