#include "CPPRAW.hpp"
#include "subreddit.hpp"
#include "post.hpp"
#include "user.hpp"
#include "request.hpp"

namespace cppraw{
    post::post(nlohmann::json data, std::string bearer, std::string user_agent){
        this -> bearer = bearer;
        this -> user_agent = user_agent;
        
        this -> title = data["title"];
        this -> id = std::string(data["name"]).substr(3);
        this -> subreddit = data["subreddit"];
        this -> author = data["author"];
        uint64_t aux = data["downs"];
        this -> downvotes = std::to_string(aux);
        aux = data["ups"];
        this -> upvotes = std::to_string(aux);

        try{
            this -> flair = data["link_flair_text"]; //some posts may not have a flair
        }
        catch(nlohmann::detail::type_error&){
            this -> flair = "";
        }

        if(data["post_hint"] == "hosted:video"){
            this -> type = cppraw::post_type::Video;
        }
        else if(data["post_hint"] == "image"){
            this -> type = cppraw::post_type::Image;
        }
        else if(data["post_hint"] == "link"){
            if(data.contains("crosspost_parent_list")){
                this -> type = cppraw::post(data["crosspost_parent_list"][0], bearer, user_agent).get_type();
                this -> media = cppraw::post(data["crosspost_parent_list"][0], bearer, user_agent).get_media();
                this -> parent_id = cppraw::post(data["crosspost_parent_list"][0], bearer, user_agent).get_id();
            }
            else{
                this -> type = cppraw::post_type::Text;
            }
        }
    }

    post::post(std::string subreddit, std::string id, std::string bearer, std::string user_agent){
        cppraw::subreddit s(subreddit, bearer, user_agent);
        cppraw::post p = s.get_post(id);
        this -> bearer = p.bearer;
        this -> user_agent = p.user_agent;
        this -> title = p.title;
        this -> id = p.id;
        this -> subreddit = p.subreddit;
        this -> author = p.author;
        this -> flair = p.flair;
        this -> downvotes = p.downvotes;
        this -> upvotes = p.upvotes;
        this -> type = p.type;
        this -> media = p.media;
        this -> parent_id = p.parent_id;
    }

    std::string post::get_title(){
        return this -> title;
    }
    std::string post::get_id(){
        return this -> id;
    }
    std::string post::get_subreddit(){
        return this -> subreddit;
    }
    std::string post::get_author(){
        return this -> author;
    }
    std::string post::get_flair(){
        return this -> flair;
    }
    std::string post::get_downvotes(){
        return this -> downvotes;
    }
    std::string post::get_upvotes(){
        return this -> upvotes;
    }
    cppraw::post_type post::get_type(){
        return this -> type;
    }
    std::string post::get_media(){
        return this -> media;
    }
    std::string post::get_parent_id(){
        return this -> parent_id;
    }
    bool post::is_crosspost(){
        return this -> parent_id != "";
    }
}