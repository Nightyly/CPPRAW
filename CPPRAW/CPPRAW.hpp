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
#include "request.hpp"
#include "user.hpp"

namespace cppraw{

    class subreddit;
    class post;
    class user;

    class reddit{
    private:
        std::string user_agent;
        std::string bearer;
    public:
        reddit(std::string const& client_id, std::string const& client_secret, std::string const& username, std::string const& password, std::string const& user_agent);
        cppraw::subreddit subreddit(std::string const& sub) const;
        cppraw::post post(std::string const& subreddit, std::string const& id) const;
        cppraw::user user(std::string const& name) const;
    };
}

#endif //CPPRAW_INCLUDED