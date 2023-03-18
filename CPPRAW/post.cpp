#include "CPPRAW.hpp"
#include "subreddit.hpp"
#include "post.hpp"
#include "user.hpp"
#include "request.hpp"

namespace cppraw{
    post::post(nlohmann::json data, std::string const& bearer, std::string const& user_agent)
    : bearer(bearer), user_agent(user_agent){
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

    post::post(std::string const& subreddit, std::string const& id, std::string const& bearer, std::string const& user_agent){
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

    std::string post::get_title() const{
        return this -> title;
    }
    std::string post::get_id() const{
        return this -> id;
    }
    std::string post::get_subreddit() const{
        return this -> subreddit;
    }
    std::string post::get_author() const{
        return this -> author;
    }
    std::string post::get_flair() const{
        return this -> flair;
    }
    std::string post::get_downvotes() const{
        return this -> downvotes;
    }
    std::string post::get_upvotes() const{
        return this -> upvotes;
    }
    cppraw::post_type post::get_type() const{
        return this -> type;
    }
    std::string post::get_media() const{
        return this -> media;
    }
    std::string post::get_parent_id() const{
        return this -> parent_id;
    }
    bool post::is_crosspost() const{
        return this -> parent_id != "";
    }
}