#include "CPPRAW.hpp"
#include "subreddit.hpp"
#include "post.hpp"
#include "user.hpp"
#include "request.hpp"

namespace cppraw{

    reddit::reddit(std::string const& client_id, std::string const& client_secret, std::string const& username, std::string const& password, std::string const& user_agent){
        std::ifstream token_file;
        token_file.open(TOKEN_FILE);
        token_file >> this -> bearer;
        int64_t limit;
        token_file >> limit;
        token_file.close();
        
        if(limit < std::chrono::system_clock::now().time_since_epoch().count()){ //request a token again since the previous one is not valid
            cpr::Response r = cppraw::request::Post(cppraw::request::pack()
                .user_agent(user_agent)
                .auth(cpr::Authentication{client_id, client_secret, cpr::AuthMode::BASIC})
                .url("https://www.reddit.com/api/v1/access_token")
                .params({{"grant_type", "password"}, {"username", username}, {"password", password}})
            );
            if(r.status_code == 429){
                throw std::invalid_argument(r.text + "\nMaybe your credentials are bad?"
                                                   + "\nclient_id: " + client_id
                                                   + "\nclient_secret: " + client_secret
                                                   + "\nusername: " + username
                                                   + "\npassword: " + password
                                                   + "\nuser_agent" + user_agent);
            }
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

    cppraw::subreddit reddit::subreddit(std::string const& sub) const{
        return cppraw::subreddit(sub, bearer, user_agent);
    }
    cppraw::post reddit::post(std::string const& subreddit, std::string const& id) const{
        return cppraw::post(subreddit, id, bearer, user_agent);
    }
    cppraw::user reddit::user(std::string const& name) const{
        return cppraw::user(name, bearer, user_agent);
    }
}