#ifndef CPPRAW_INCLUDED
#define CPPRAW_INCLUDED

#ifndef TOKEN_FILE
#define TOKEN_FILE "token.txt"
#endif // TOKEN_FILE

#include <cpr/cpr.h>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

#include "subreddit.hpp"
#include "post.hpp"

namespace cppraw{

    class subreddit;
    class post;

    class reddit{
    private:
        std::string user_agent;
        std::string bearer;
    public:
        reddit(std::string client_id, std::string client_secret, std::string username, std::string password, std::string user_agent);
        cppraw::subreddit subreddit(std::string sub);
    };
}

#endif //CPPRAW_INCLUDED