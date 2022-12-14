#include "CPPRAW.hpp"
#include "subreddit.hpp"
#include "post.hpp"
#include "user.hpp"
#include "request.hpp"

namespace cppraw{
    user::user(std::string name, std::string bearer, std::string user_agent){
        cpr::Response r = cppraw::request::Get(cppraw::request::pack(
            bearer,
            user_agent,
            cpr::Authentication{"", "", cpr::AuthMode::BASIC},
            cpr::Url("https://oauth.reddit.com/user/" + name + "/about/"),
            cpr::Body{""},
            cpr::Parameters{{}}
        ));
        nlohmann::json j = nlohmann::json::parse(r.text);
        this -> name = j["data"]["name"];
        this -> mFriend = j["data"]["is_friend"];
        this -> employee = j["data"]["is_employee"];
        this -> karma = j["data"]["total_karma"];
        this -> link_karma = j["data"]["link_karma"];
        this -> awarder_karma = j["data"]["awarder_karma"];
        this -> awardee_karma = j["data"]["awardee_karma"];
        this -> comment_karma = j["data"]["comment_karma"];
        this -> verified_email = j["data"]["has_verified_email"];
        this -> created_on = j["data"]["created_utc"];
        this -> snoovatar = j["data"]["snoovatar_img"];
        try{
            this -> accepts_pm = j["data"]["accept_pms"];
        }
        catch(nlohmann::json_v3_11_1::detail::type_error& e){ //if the bot gets its own profile, the accpets_pms field is not found
            this -> accepts_pm = false;
        }
    }

    std::string user::get_name(){
        return this -> name;
    }
    bool user::is_friend(){
        return this -> mFriend;
    }
    bool user::is_employee(){
        return this -> employee;
    }
    int64_t user::get_karma(){
        return this -> karma;
    }
    int64_t user::get_link_karma(){
        return this -> link_karma;
    }
    int64_t user::get_awarder_karma(){
        return this -> awarder_karma;
    }
    int64_t user::get_awardee_karma(){
        return this -> awardee_karma;
    }
    int64_t user::get_comment_karma(){
        return this -> comment_karma;
    }
    bool user::has_verified_email(){
        return this -> verified_email;
    }
    uint64_t user::get_creation_millis(){
        return this -> created_on * 1000;
    }
    std::string user::get_snoovatar_url(){
        return this -> snoovatar;
    }
    bool user::accepts_pms(){
        return this -> accepts_pm;
    }
}