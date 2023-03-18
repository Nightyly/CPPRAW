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
        user(std::string const& name, std::string const& bearer, std::string const& user_agent);
        std::string get_name() const;
        bool is_friend() const;
        bool is_employee() const;
        int64_t get_karma() const;
        int64_t get_link_karma() const;
        int64_t get_awarder_karma() const;
        int64_t get_awardee_karma() const;
        int64_t get_comment_karma() const;
        bool has_verified_email() const;
        uint64_t get_creation_millis() const;
        std::string get_snoovatar_url() const;
        bool accepts_pms() const;
        void send_pm(std::string const& title, std::string const& content);
    };
}

#endif //USER_INCLUDED_