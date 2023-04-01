#include "CPPRAW.hpp"
#include "subreddit.hpp"
#include "post.hpp"
#include "user.hpp"
#include "request.hpp"

namespace cppraw{
    user::user(std::string const& name, std::string const& bearer, std::string const& user_agent){
        cpr::Response r = cppraw::request::Get(cppraw::request::pack()
            .bearer(bearer)
            .user_agent(user_agent)
            .url("https://oauth.reddit.com/user/" + name + "/about/")
        );

        if(r.status_code != 200)
            throw std::invalid_argument(r.text);

        nlohmann::json j = nlohmann::json::parse(r.text);
        this -> name = j["data"]["name"];
        this -> friendship = j["data"]["is_friend"];
        this -> employee = j["data"]["is_employee"];
        this -> karma = j["data"]["total_karma"];
        this -> link_karma = j["data"]["link_karma"];
        this -> awarder_karma = j["data"]["awarder_karma"];
        this -> awardee_karma = j["data"]["awardee_karma"];
        this -> comment_karma = j["data"]["comment_karma"];
        this -> verified_email = j["data"]["has_verified_email"];
        this -> created_on = j["data"]["created_utc"];
        this -> snoovatar = j["data"]["snoovatar_img"];
        if(j["data"].contains("accept_pms"))
            this -> accepts_pm = j["data"]["accept_pms"];
        this -> bearer = bearer;
        this -> user_agent = user_agent;
    }

    std::string user::get_name() const{
        return this -> name;
    }
    bool user::is_friend() const{
        return this -> friendship;
    }
    bool user::is_employee() const{
        return this -> employee;
    }
    int64_t user::get_karma() const{
        return this -> karma;
    }
    int64_t user::get_link_karma() const{
        return this -> link_karma;
    }
    int64_t user::get_awarder_karma() const{
        return this -> awarder_karma;
    }
    int64_t user::get_awardee_karma() const{
        return this -> awardee_karma;
    }
    int64_t user::get_comment_karma() const{
        return this -> comment_karma;
    }
    bool user::has_verified_email() const{
        return this -> verified_email;
    }
    uint64_t user::get_creation_millis() const{
        return this -> created_on * 1000;
    }
    std::string user::get_snoovatar_url() const{
        return this -> snoovatar;
    }
    bool user::accepts_pms() const{
        return this -> accepts_pm;
    }
    void user::send_pm(std::string const& title, std::string const& content) const{
        cpr::Response r = cppraw::request::Post(cppraw::request::pack()
            .bearer(bearer)
            .user_agent(user_agent)
            .url("https://oauth.reddit.com/api/compose")
            .params({{"to", get_name()}, {"subject", title}, {"text", content}})
        );
        if(r.status_code != 200)
            throw std::invalid_argument(r.text);
    }
}