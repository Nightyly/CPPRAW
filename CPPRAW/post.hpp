#ifndef POST_INCLUDED_
#define POST_INCLUDED_

#include <vector>
#include <string>

namespace cppraw{

    class reddit;
    class subreddit;
    class user;

    enum class post_type{Text, Video, Image, Gallery};
    class post{
        std::string bearer;
        std::string user_agent;

        std::string title = "";
        std::string id = "";
        std::string subreddit = "";
        std::string author = "";
        std::string flair = "";
        std::string downvotes = "";
        std::string upvotes = "";
        cppraw::post_type type;
        std::string media = "";
        std::vector<std::pair<std::string, std::string>> gallery;
        std::string parent_id = "";
        std::string parent_subreddit = "";
        std::string body = "";
    public:
        post(nlohmann::json data, std::string const& bearer, std::string const& user_agent);
        post(std::string const& subreddit, std::string const& id, std::string const& bearer, std::string const& user_agent);

        std::string get_title() const;
        std::string get_id() const;
        std::string get_subreddit() const;
        std::string get_author() const;
        std::string get_flair() const;
        std::string get_downvotes() const;
        std::string get_upvotes() const;
        cppraw::post_type get_type() const;
        std::string get_media() const;
        std::vector<std::pair<std::string, std::string>> get_gallery() const;
        std::string get_parent_id() const;
        std::string get_parent_subreddit() const;
        std::string get_body() const;
        bool is_crosspost() const;

    };
}

#endif //POST_INCLUDED_