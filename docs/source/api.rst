API reference
=============

.. toctree::
    :maxdepth: 3

    api

Reddit
=======
Description
-----------
CPPRAW's main class, this must be the first class to be instantiated.

.. code-block:: cpp

    cppraw::reddit reddit("client-id", "client-secret","reddit-user", "reddit-password", "user-agent");

Member functions
----------------
subreddit
~~~~~~~~~
This function returns a subreddit object refering to the subreddit you provided.

Parameters:

    std::string subreddit //the name of the subreddit you wish to look for

.. code-block:: cpp

    cppraw::subreddit subreddit = reddit.subreddit("cpp");

post
~~~~
This function returns a post object refering to the post you provided.

Parameters:

    std::string subreddit // the name of the subreddit

    std::string id // the id of the post you wish to look for

.. code-block:: cpp

    cppraw::post post = reddit.post("cpp", "vgy0rt");

Subreddit
=========
Description
-----------
This class lets you interact with a subreddit.

.. code-block:: cpp

    cppraw::subreddit subreddit = reddit.subreddit("cpp");
Member functions
----------------
recent
~~~~~~~
Gets the most recent posts from the subreddit.

Parameters:

    int limit //the number of posts to return, defaults to 25

    std::string after //the post after which to return posts, defaults to ""

    std::string before //the post before which to return posts, defaults to ""

Returns std::vector of cppraw::post objects

.. code-block:: cpp

    std::vector<cppraw::post> posts = reddit.subreddit("cpp").recent();
    for(auto i: posts){
        std::cout << i.title << std::endl; //prints the title of the 25 most recent posts in the cpp subreddit
    }
hot
~~~~
Gets the hot posts from the subreddit.

Parameters:

    int limit //the number of posts to return, defaults to 25

    std::string after //the post after which to return posts, defaults to ""

    std::string before //the post before which to return posts, defaults to ""

Returns std::vector of cppraw::post objects

.. code-block:: cpp

    std::vector<cppraw::post> posts = reddit.subreddit("cpp").hot();
    for(auto i: posts){
        std::cout << i.title << std::endl; //prints the title of the 25 hottest posts in the cpp subreddit
    }
rising
~~~~~~
Gets the rising posts from the subreddit.

Parameters:

    int limit //the number of posts to return, defaults to 25

    std::string after //the post after which to return posts, defaults to ""

    std::string before //the post before which to return posts, defaults to ""

Returns std::vector of cppraw::post objects

.. code-block:: cpp

    std::vector<cppraw::post> posts = reddit.subreddit("cpp").rising();
    for(auto i: posts){
        std::cout << i.title << std::endl; //prints the title of the 25 rising posts in the cpp subreddit
    }
top
~~~~
Gets the top posts from the subreddit.

Parameters:

    int limit //the number of posts to return, defaults to 25

    std::string after //the post after which to return posts, defaults to ""

    std::string before //the post before which to return posts, defaults to ""

Returns std::vector of cppraw::post objects

.. code-block:: cpp

    std::vector<cppraw::post> posts = reddit.subreddit("cpp").top();
    for(auto i: posts){
        std::cout << i.title << std::endl; //prints the title of the 25 top posts in the cpp subreddit
    }
controversial
~~~~~~~~~~~~~
Gets the most controversial posts from the subreddit.

Parameters:

    int limit //the number of posts to return, defaults to 25

    std::string after //the post after which to return posts, defaults to ""

    std::string before //the post before which to return posts, defaults to ""

Returns std::vector of cppraw::post objects

.. code-block:: cpp

    std::vector<cppraw::post> posts = reddit.subreddit("cpp").controversial();
    for(auto i: posts){
        std::cout << i.title << std::endl; //prints the title of the 25 most controversial posts in the cpp subreddit
    }
random
~~~~~~
Gets a random post from the subreddit.

Parameters:

    none

Returns cppraw::post object

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").random();
    std::cout << post.title << std::endl; //prints the title of a random post in the cpp subreddit
get_post
~~~~~~
Gets a post from the subreddit.

Parameters:

    std::string id //the id of the post you wish to get

Returns cppraw::post object

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.title << std::endl; //prints "C++ Jobs - Q3 2022"
Post
=====

Description
-----------

This class lets you interact with a post.

Member functions
----------------

get_title
~~~~~~~~~~
Gets the title of the post.

Parameters:

    none

Returns std::string

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_title() << std::endl; //prints "C++ Jobs - Q3 2022"
get_id
~~~~~~~
Gets the id of the post.

Parameters:

    none

Returns std::string

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_id() << std::endl; //prints "vqy0rt"
get_subreddit
~~~~~~~~~~~~~
Gets the subreddit of the post.

Parameters:

    none

Returns std::string

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_subreddit() << std::endl; //prints "cpp"
get_author
~~~~~~~~~~
Gets the author of the post.

Parameters:

    none

Returns std::string (for now, will be changed to cppraw::user)

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_author() << std::endl; //prints "STL"
get_flair
~~~~~~~~~
Gets the flair of the post if it exists.

Parameters:

    none

Returns std::string

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_flair() << std::endl; //prints nothing since there is no flair
get_downvotes
~~~~~~~~~~~~~
Gets the downvotes of the post.

Parameters:

    none

Returns uint64_t

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_downvotes() << std::endl; //prints "3" as of now
get_upvotes
~~~~~~~~~~~~~
Gets the upvotes of the post.

Parameters:

    none

Returns uint64_t

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_upvotes() << std::endl; //prints "71" as of now
get_type
~~~~~~~~~
Gets the type of the post.

Parameters:

    none

Returns std::string

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    cppraw::post_type type = post.get_type(); //cppraw::post_type::Text
                                            //cppraw::post_type is an enum class with the following values:
                                            //Text, Video, Image
get_media
~~~~~~~~~
Gets a link to the media of the post.

Parameters:

    none

Returns std::string

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_media() << std::endl; //prints nothing since there is no media
get_parent_id
~~~~~~~~~~~~~
Gets the id of the parent of the post if the post is a crosspost.

Parameters:

    none

Returns std::string

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_parent_id() << std::endl; //prints nothing since this post is not a crosspost
is_crosspost
~~~~~~~~~~~~~
Returns whether or not the post is a crosspost.

Parameters:

    none

Returns bool

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.is_crosspost() << std::endl; //prints "false"

User
=====

Description
------------
This class allows you to interact with a redditor

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.is_employee() << std::endl; //prints "false" as of now

Member functions
-----------------

get_name
~~~~~~~~~
Returns the username of the redditor.

Parameters:
    
    none

Returns std::string

.. code-block:: cpp

    cppraw::user user = reddit.user("dAelI_sMilE");
    std::cout << user.get_name() << std::endl; //prints "Daeli_Smile"

is_friend
~~~~~~~~~~
Returns whether the redditor is a friend of the bot. (https://www.reddit.com/prefs/friends/)

Parameters:
    
    none

Returns bool

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.is_friend() << std::endl; //output depends

is_employee
~~~~~~~~~~~~
Returns whether the redditor is a reddit employee.

Parameters:

    none

Returns bool

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.is_employee() << std::endl; //prints "false"

get_karma
~~~~~~~~~~
Returns the total karma of the redditor.

Parameters:

    none

Returns int64_t

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_karma() << std::endl; // output depends

get_link_karma
~~~~~~~~~~~~~~
Returns the link karma of the redditor.

Parameters:

    none

Returns int64_t

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_link_karma() << std::endl //output depends

get_awarder_karma
~~~~~~~~~~~~~~
Returns the awarder karma of the redditor.

Parameters:

    none

Returns int64_t

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_awarder_karma() << std::endl //output depends

get_awardee_karma
~~~~~~~~~~~~~~
Returns the awardee karma of the redditor.

Parameters:

    none

Returns int64_t

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_awardee_karma() << std::endl //output depends

get_comment_karma
~~~~~~~~~~~~~~
Returns the comment karma of the redditor.

Parameters:

    none

Returns int64_t

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_comment_karma() << std::endl //output depends

has_verified_email
~~~~~~~~~~~~~~
Returs whether the redditor has a verified email.

Parameters:

    none

Returns bool

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.has_verified_email() << std::endl //prints "true"

get_creation_millis
~~~~~~~~~~~~~~~~~~~
Returns the time when the redditor's account was created in unix millis.

Parameters:

    none

Returns uint64_t

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_creation_millis() << std::endl //prints "1588297297000"

get_snoovatar_url
~~~~~~~~~~~~~~~~~~
Returns the snoovatar url.

Parameters:

    none

Returns std::string

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_snoovatar_url() << std::endl; // prints "https://i.redd.it/snoovatar/avatars/nftv2_bmZ0X2VpcDE1NToxMzdfNmFjYjhmYjgyODgwZDM5YzJiODQ0NmY4Nzc4YTE0ZDM0ZWU2Y2ZiN18xNTM4_rare_fc87c224-e736-4656-aec7-713e66987ac1.png"

accepts_pms
~~~~~~~~~~~
Returns whether the redditor accepts pms. If the redditor requested is the bot, returns false

Parameters:

    none

Returns bool