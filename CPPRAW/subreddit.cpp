#include "CPPRAW.hpp"
#include "subreddit.hpp"
#include "post.hpp"
#include "user.hpp"
#include "request.hpp"

namespace cppraw{

    subreddit::subreddit(std::string const& sub, std::string const& bearer, std::string const& user_agent){
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

    std::vector<cppraw::post> subreddit::recent(int limit, std::string* after){
        std::vector<cppraw::post> v;
        if(limit > 100){
            v = subreddit::recent(limit - 100, after);
            limit = 100;
        }
        
        cpr::Parameters params = cpr::Parameters{{"limit", std::to_string(limit)}};
        
        if(*after != "") params.Add({"after", "t3_" + *after});

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
        for(uint64_t i = 0; i != j["data"]["children"].size(); i++){
            v.push_back(cppraw::post(j["data"]["children"][i]["data"], bearer, user_agent));
        }
        *after = std::string(j["data"]["after"]).substr(3);
        return v;
    }

    std::vector<cppraw::post> subreddit::recent(int limit, std::string after, std::string before){
        std::vector<cppraw::post> v;
        if(limit > 100){
            v = subreddit::recent(limit - 100, &after);
            before = "";
            limit = 100;
        }
        cpr::Parameters params;
        if(after == "" && before != "")
            params = cpr::Parameters{{"limit", std::to_string(limit)}, {"before", "t3_" + before}};
        else if(after != "" && before == "")
            params = cpr::Parameters{{"limit", std::to_string(limit)}, {"after", "t3_" + after}};
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
        for(uint64_t i = 0; i != j["data"]["children"].size(); i++){
            v.push_back(cppraw::post(j["data"]["children"][i]["data"], bearer, user_agent));
        }

        return v;
    }

    cppraw::post subreddit::get_post(std::string const& id){
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