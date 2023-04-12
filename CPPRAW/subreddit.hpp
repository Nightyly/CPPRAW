#ifndef SUBREDDIT_INCLUDED_
#define SUBREDDIT_INCLUDED_

#include <vector>
#include <string>

namespace cppraw{

    class reddit;
    class post;
    class user;

    class subreddit{
        std::string sub;
        std::string bearer;
        std::string user_agent;
        std::vector<cppraw::post> get(std::string const& what, int limit, std::string* after, std::string* before);
    public:
        subreddit(std::string const& sub, std::string const& bearer, std::string const& user_agent);
        std::vector<cppraw::post> recent(int limit = 25, std::string const& after = "", std::string const& before = "");
        std::vector<cppraw::post> hot(int limit = 25, std::string const& after = "", std::string const& before = "");
        std::vector<cppraw::post> rising(int limit = 25, std::string const& after = "", std::string const& before = "");
        std::vector<cppraw::post> top(int limit = 25, std::string const& after = "", std::string const& before = "");
        std::vector<cppraw::post> controversial(int limit = 25, std::string const& after = "", std::string const& before = "");
        std::vector<cppraw::post> random() const;
        cppraw::post get_post(std::string const& id) const;
    };

}

#endif //SUBREDDIT_INCLUDED_