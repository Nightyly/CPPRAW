#ifndef POST_INCLUDED_
#define POST_INCLUDED_

#include <vector>
#include <string>

namespace cppraw{

    class reddit;
    class subreddit;

    enum class post_type{Text, Video, Image};
    class post{
        std::string bearer;
        std::string user_agent;

        std::string title;
        std::string id;
        std::string subreddit;
        std::string author;
        std::string flair;
        std::string downvotes;
        std::string upvotes;
        cppraw::post_type type;
        std::string media;
        std::string parent_id;
    public:
        post(nlohmann::json data, std::string bearer, std::string user_agent);
        post(std::string id, std::string subreddit, std::string bearer, std::string user_agent);

        std::string get_title();
        std::string get_id();
        std::string get_subreddit();
        std::string get_author();
        std::string get_flair();
        std::string get_downvotes();
        std::string get_upvotes();
        cppraw::post_type get_type();
        std::string get_media();
        std::string get_parent_id();
        bool is_crosspost();
    };
}

#endif //POST_INCLUDED_