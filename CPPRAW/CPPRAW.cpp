#include "CPPRAW.hpp"
#include "subreddit.hpp"
#include "post.hpp"

namespace cppraw{

reddit::reddit(std::string client_id, std::string client_secret, std::string username, std::string password, std::string user_agent){
        std::ifstream token_file;
        token_file.open(TOKEN_FILE);
        token_file >> this -> bearer;
        uint64_t limit;
        token_file >> limit;
        token_file.close();
        
        if(limit < std::chrono::system_clock::now().time_since_epoch().count()){ //request a token again since the previous one is not valid
            cpr::Response r = cpr::Post(cpr::Url("https://www.reddit.com/api/v1/access_token"),
                                        cpr::Authentication{client_id, client_secret, cpr::AuthMode::BASIC},
                                        cpr::Body{"grant_type=password&username=" + username + "&password=" + password});
            if(r.status_code != 200){
                throw std::invalid_argument(r.text);
            }
            
            nlohmann::json j = nlohmann::json::parse(r.text);
            this -> bearer = j["access_token"];

            const auto now = std::chrono::system_clock::now();
            const auto end = now + std::chrono::seconds(j["expires_in"]);

            std::fstream file;
            file.open(TOKEN_FILE, std::ios::out);
            file << this -> bearer << "\n" << end.time_since_epoch().count();
            file.close();
        }
        this -> user_agent = user_agent;
    }

    cppraw::subreddit reddit::subreddit(std::string sub){
        return cppraw::subreddit(sub, bearer, user_agent);
    }
}