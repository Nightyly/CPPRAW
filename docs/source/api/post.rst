Post
=====

This class lets you interact with a post.

.. code-block:: cpp

    cppraw::post post = reddit.post("cpp", "vqy0rt");
    std::cout << post.get_author() << std::endl; // prints "STL"

Member functions
----------------

.. contents::
    :local:

-----------

get_title
~~~~~~~~~~
Gets the title of this post.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`std::string`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_title() << std::endl; // prints "C++ Jobs - Q3 2022"

-----------

get_id
~~~~~~~
Gets the id of this post.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`std::string`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_id() << std::endl; // prints "vqy0rt"

-----------

get_subreddit
~~~~~~~~~~~~~
Gets the subreddit of this post.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`std::string`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_subreddit() << std::endl; // prints "cpp"

-----------

get_author
~~~~~~~~~~
Gets the author of this post.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`std::string`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_author() << std::endl; // prints "STL"

-----------

get_flair
~~~~~~~~~
Gets the flair of this post if it exists.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`std::string`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_flair() << std::endl; // prints nothing since there is no flair

-----------

get_downvotes
~~~~~~~~~~~~~
Gets the downvotes of this post.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`uint64_t`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_downvotes() << std::endl; // prints "3" as of now

-----------

get_upvotes
~~~~~~~~~~~~~
Gets the upvotes of this post.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`uint64_t`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_upvotes() << std::endl; // prints "71" as of now

-----------

get_type
~~~~~~~~~
Gets the type of this post.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`cppraw::post_type`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    cppraw::post_type type = post.get_type(); // cppraw::post_type::Text

cppraw::post_type is an enum class with the following possible values:
{Text, Video, Image, Gallery}

-----------

get_media
~~~~~~~~~
Gets a link to the media of this post.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`std::string`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_media() << std::endl; // prints nothing since there is no media

-----------

get_gallery
~~~~~~~~~~~
Gets the gallery of this post, if it exists.

.. admonition::
    Parameters

    None

Returns :guilabel:`std::vector<std::pair<std::string, std::string>>`

.. code-block:: cpp

    auto v = r.subreddit("196").get_post("11wkyde");
    for(auto i: v.get_gallery())
        std::cout << i.first << " - " << i.second << "\n";

The first element of each pair is a link to the image of the gallery. The second element
is the caption of the image, if it exists.

-----------

get_parent_id
~~~~~~~~~~~~~
Gets the id of the parent of this post if this post is a crosspost.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`std::string`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_parent_id() << std::endl; // prints nothing since this post is not a crosspost
    
-----------

get_parent_subreddit
~~~~~~~~~~~~~~~~~~~~
Gets the subreddit on which the parent of this post was posted if this post
is a crosspost.

.. admonition::
    Parameters

    None

Returns :guilabel:`std::string`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("djs").get_post("11zws4d");
    std::cout << post.get_parent_subreddit() << std::endl; // prints "EDM"

-----------

get_body
~~~~~~~~
Gets the body of this post. The body is the caption if it has media content,
and the body if this post is a selftext post (AKA only text).

.. admonition::
    Parameters

    None

Returns :guilabel:`std::string`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("122udm0");
    std::cout << post.get_body() << std::endl; // prints "https://ddanilov.me/usage-of-shared_ptr"

-----------

is_crosspost
~~~~~~~~~~~~~
Returns whether or not this post is a crosspost.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`bool`

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.is_crosspost() << std::endl; // prints "false"