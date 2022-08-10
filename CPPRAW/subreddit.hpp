#ifndef SUBREDDIT_INCLUDED_
#define SUBREDDIT_INCLUDED_

#include <vector>
#include <string>

namespace cppraw{

    class reddit;
    class post;

    class subreddit{
        std::string sub;
        std::string bearer;
        std::string user_agent;
    public:
        subreddit(std::string sub, std::string bearer, std::string user_agent);
        std::vector<cppraw::post> recent(int limit = 25, std::string after = "", std::string before = "");
        std::vector<cppraw::post> hot(int limit = 25);
        std::vector<cppraw::post> rising(int limit = 25);
        std::vector<cppraw::post> top(int limit = 25);
        std::vector<cppraw::post> controversial(int limit = 25);
        cppraw::post random();
        cppraw::post get_post(std::string id);
    };

}

#endif //SUBREDDIT_INCLUDED_