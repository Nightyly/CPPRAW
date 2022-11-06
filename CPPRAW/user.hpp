#ifndef USER_INCLUDED_
#define USER_INCLUDED_

#include <string>

namespace cppraw{
    class reddit;
    class subreddit;
    class post;

    class user{
        std::string bearer;
        std::string user_agent;
        
        std::string name;
        bool mFriend;
        bool employee;
        int64_t karma;
        int64_t link_karma;
        int64_t awarder_karma;
        int64_t awardee_karma;
        int64_t comment_karma;
        bool verified_email;
        uint64_t created_on;
        std::string snoovatar;
        bool accepts_pm;
    public:
        user(std::string name, std::string bearer, std::string user_agent);
        std::string get_name();
        bool is_friend();
        bool is_employee();
        int64_t get_karma();
        int64_t get_link_karma();
        int64_t get_awarder_karma();
        int64_t get_awardee_karma();
        int64_t get_comment_karma();
        bool has_verified_email();
        uint64_t get_creation_millis();
        std::string get_snoovatar_url();
        bool accepts_pms();
    };
}

#endif //USER_INCLUDED_