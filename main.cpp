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
            std::string ret = line.substr(line.find("=") + 2);
            return ret.substr(0, ret.size() - 1);
        }
    }
    return std::string();
}

int main(){
    cppraw::reddit r(getEnvVar("client_id"), getEnvVar("client_secret"), getEnvVar("username"), getEnvVar("password"), getEnvVar("user_agent"));
    for(auto i: r.subreddit("ElCalifato").recent(105)){
        std::cout << i.get_title() << std::endl;
    }
}