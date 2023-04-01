#include "CPPRAW.hpp"
#include "subreddit.hpp"
#include "post.hpp"
#include "user.hpp"
#include "request.hpp"

namespace cppraw{
    post::post(nlohmann::json data, std::string const& bearer, std::string const& user_agent)
    : bearer(bearer), user_agent(user_agent){
        this -> title = data["title"];
        this -> id = data["id"];
        this -> subreddit = data["subreddit"];
        this -> author = data["author"];
        if(data.contains("link_flair_text"))
            this -> flair = data["link_flair_text"];
        this -> downvotes = std::to_string(int64_t(data["downs"]));
        this -> upvotes = std::to_string(int64_t(data["ups"]));

        if(data.contains("crosspost_parent")) data = data["crosspost_parent_list"][0];// if this post is a crosspost, the data relevant to its
                                                                                      // contents are in "crosspost_parent_list"
        if(data.contains("post_hint")){
            if(data["post_hint"] == "hosted:video")
                this -> type = cppraw::post_type::Video;
            else
                this -> type = cppraw::post_type::Image;
            this -> media = data["url"];
            this -> body = data["selftext"];
        }
        else{
            this -> body = data["selftext"];
            if(data.contains("gallery_data")){
                this -> type = cppraw::post_type::Gallery;
                std::for_each(data["gallery_data"]["items"].begin(), data["gallery_data"]["items"].end(), [&](auto const& child){
                    std::string media_id = child["media_id"];
                    std::string mime_type = data["media_metadata"][media_id]["m"];
                    std::string url = "https://" + mime_type.substr(0, 1) + ".redd.it/";
                    mime_type = mime_type.substr(mime_type.find('/') + 1);
                    if(child.contains("caption"))
                        this -> gallery.emplace_back(url + media_id + "." + mime_type, child["caption"]);
                    else
                        this -> gallery.emplace_back(url + media_id + "." + mime_type, "");
                });
            }
            else
                this -> type = cppraw::post_type::Text;
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
        this -> gallery = p.gallery;
        this -> parent_id = p.parent_id;
        this -> parent_subreddit = p.parent_subreddit;
        this -> body = p.body;
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
    std::vector<std::pair<std::string, std::string>> post::get_gallery() const{
        return this -> gallery;
    }
    std::string post::get_parent_id() const{
        return this -> parent_id;
    }
    std::string post::get_parent_subreddit() const{
        return this -> parent_subreddit;
    }
    std::string post::get_body() const{
        return this -> body;
    }
    bool post::is_crosspost() const{
        return this -> parent_id != "";
    }
}