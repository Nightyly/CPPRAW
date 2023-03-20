#include "CPPRAW.hpp"
#include "subreddit.hpp"
#include "post.hpp"
#include "user.hpp"
#include "request.hpp"

namespace cppraw{
    subreddit::subreddit(std::string const& sub, std::string const& bearer, std::string const& user_agent)
    : sub(sub), bearer(bearer), user_agent(user_agent){
        cpr::Response r = cppraw::request::Get(cppraw::request::pack()
            .bearer(bearer)
            .user_agent(user_agent)
            .url("https://oauth.reddit.com/r/" + sub + "/about/moderators")
        );
        nlohmann::json j = nlohmann::json::parse(r.text);
        if(j["kind"] != "UserList")
            throw std::invalid_argument("Unknown subreddit.");
    }

    std::vector<cppraw::post> subreddit::recent(int limit, std::string* after, std::string* before){
        std::vector<cppraw::post> v;
        std::vector<cppraw::post> prev;
        if(limit > 100){
            prev = subreddit::recent(limit - 100, after, before);
            limit = 100;
        }
        
        auto params = cpr::Parameters{{"limit", std::to_string(limit)}};
        
        if(*after != "")
            params.Add({"after", "t3_" + *after});

        else if(*before != "")
            params.Add({"before", "t3_" + *before});

        cpr::Response r = cppraw::request::Get(cppraw::request::pack()
            .bearer(bearer)
            .user_agent(user_agent)
            .url("https://oauth.reddit.com/r/" + sub + "/new")
            .params(params)
        );

        if(r.status_code != 200){
            throw std::invalid_argument(r.text);
        }
        nlohmann::json j = nlohmann::json::parse(r.text);
        std::for_each(j["data"]["children"].begin(), j["data"]["children"].end(), [&](nlohmann::json const& child){v.emplace_back(child["data"], bearer, user_agent);});

        // Because of the way pagination works, if we used the 'before' parameter, we have to insert the previous vector at the end of the new vector
        if(*before != "")
            v.insert(v.end(), prev.begin(), prev.end());
        else
            v.insert(v.begin(), prev.begin(), prev.end());

        if(*before != "")
            *before = v.front().get_id();
        else
            *after = v.back().get_id();

        return v;
    }

    std::vector<cppraw::post> subreddit::recent(int limit, std::string after, std::string before){
        if(after != "" && before != "") throw std::invalid_argument("After and before cannot be set at the same time.\nAfter: " + after + "\nBefore: " + before);
        std::vector<cppraw::post> v;
        std::vector<cppraw::post> prev;
        if(limit > 100){
            prev = subreddit::recent(limit - 100, &after, &before);
            limit = 100;
        }

        auto params = cpr::Parameters{{"limit", std::to_string(limit)}};
        if(before != "")
            params.Add({"before", "t3_" + before});
        else if(after != "")
            params.Add({"after", "t3_" + after});

        cpr::Response r = cppraw::request::Get(cppraw::request::pack()
            .bearer(bearer)
            .user_agent(user_agent)
            .url("https://oauth.reddit.com/r/" + sub + "/new")
            .params(params)
        );

        if(r.status_code != 200){
            throw std::invalid_argument(r.text);
        }
        nlohmann::json j = nlohmann::json::parse(r.text);
        std::for_each(j["data"]["children"].begin(), j["data"]["children"].end(), [&](nlohmann::json const& child){v.emplace_back(child["data"], bearer, user_agent);});

        // Because of the way pagination works, if we used the 'before' parameter, we have to insert the previous vector at the end of the new vector
        if(before != "")
            v.insert(v.end(), prev.begin(), prev.end());
        else
            v.insert(v.begin(), prev.begin(), prev.end());
        
        return v;
    }

    cppraw::post subreddit::get_post(std::string const& id) const{
        cpr::Response r = cppraw::request::Get(cppraw::request::pack()
            .bearer(bearer)
            .user_agent(user_agent)
            .url("https://oauth.reddit.com/r/" + sub + "/comments/" + id)
        );
        if(r.status_code != 200){
            throw std::invalid_argument(r.text);
        }
        nlohmann::json j = nlohmann::json::parse(r.text);
        return cppraw::post(j[0]["data"]["children"][0]["data"], bearer, user_agent);
    }
}