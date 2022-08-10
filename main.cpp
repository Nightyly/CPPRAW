#include <cpr/cpr.h>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "CPPRAW/CPPRAW.hpp"

std::string getEnvVar(std::string const& key){
    std::fstream file;
    file.open("../.env", std::ios::in);
    std::string line;
    while(std::getline(file, line)){
        if(line.find(key) != std::string::npos){
            return line.substr(line.find("=") + 1);
        }
    }
    return std::string();
}

int main(){
    cppraw::reddit r(getEnvVar("client_id"), getEnvVar("client_secret"), getEnvVar("username"), getEnvVar("password"), getEnvVar("user_agent"));
    cppraw::post p = r.subreddit("Mujico").get_post("wk5web");
    std::cout << p.get_title() << std::endl;
}