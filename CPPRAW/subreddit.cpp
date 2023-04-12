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
        if(r.status_code != 200)
            throw std::invalid_argument(r.text);
        nlohmann::json j = nlohmann::json::parse(r.text);
        if(j["kind"] != "UserList")
            throw std::invalid_argument("Unknown subreddit \"" + sub + "\".");
    }

    std::vector<cppraw::post> subreddit::get(std::string const& what, int limit, std::string* after, std::string* before){
        std::vector<cppraw::post> v;
        std::vector<cppraw::post> prev;
        if(limit > 100){
            prev = subreddit::get(what, limit - 100, after, before);
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
            .url("https://oauth.reddit.com/r/" + sub + "/" + what)
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

    std::vector<cppraw::post> subreddit::recent(int limit, std::string const& after, std::string const& before){
        if(after != "" && before != "")
            throw std::invalid_argument("After and before cannot be set at the same time.\nAfter: " + after + "\nBefore: " + before);
        std::string _after = after;
        std::string _before = before;
        return get("new", limit, &_after, &_before);
    }

    std::vector<cppraw::post> subreddit::hot(int limit, std::string const& after, std::string const& before){
        if(after != "" && before != "")
            throw std::invalid_argument("After and before cannot be set at the same time.\nAfter: " + after + "\nBefore: " + before);
        std::string _after = after;
        std::string _before = before;
        return get("hot", limit, &_after, &_before);
    }
    
    std::vector<cppraw::post> subreddit::rising(int limit, std::string const& after, std::string const& before){
        if(after != "" && before != "")
            throw std::invalid_argument("After and before cannot be set at the same time.\nAfter: " + after + "\nBefore: " + before);
        std::string _after = after;
        std::string _before = before;
        return get("rising", limit, &_after, &_before);
    }

    std::vector<cppraw::post> subreddit::top(int limit, std::string const& after, std::string const& before){
        if(after != "" && before != "")
            throw std::invalid_argument("After and before cannot be set at the same time.\nAfter: " + after + "\nBefore: " + before);
        std::string _after = after;
        std::string _before = before;
        return get("top", limit, &_after, &_before);
    }

    std::vector<cppraw::post> subreddit::controversial(int limit, std::string const& after, std::string const& before){
        if(after != "" && before != "")
            throw std::invalid_argument("After and before cannot be set at the same time.\nAfter: " + after + "\nBefore: " + before);
        std::string _after = after;
        std::string _before = before;
        return get("controversial", limit, &_after, &_before);
    }

    std::vector<cppraw::post> subreddit::random() const{
        cpr::Response r = cppraw::request::Get(cppraw::request::pack()
            .bearer(bearer)
            .user_agent(user_agent)
            .url("https://oauth.reddit.com/r/" + sub + "/random")
        );
        if(r.status_code != 200){
            throw std::invalid_argument(r.text);
        }
        nlohmann::json j = nlohmann::json::parse(r.text);
        
        std::vector<cppraw::post> ret;
        for(auto const& i: j["data"]["children"])
            ret.emplace_back(i["data"], bearer, user_agent);
        return ret;
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