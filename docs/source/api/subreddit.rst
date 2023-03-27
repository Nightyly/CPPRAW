Subreddit
=========

This class lets you interact with a subreddit.

.. code-block:: cpp

    cppraw::subreddit subreddit = reddit.subreddit("cpp");
    for(auto i: subreddit.recent(30))
        std::cout << i.get_title() << std::endl;

Member functions
----------------

.. contents::
    :local:

-----------

recent
~~~~~~~
Gets the most recent posts from the subreddit.

.. admonition::
    Parameters

    ``int limit``
        The number of posts to return, defaults to 25
    ``std::string after``
        The id of the post after which to return posts, defaults to ""
    ``std::string before``
        The id of the post before which to return posts, defaults to ""

Returns :guilabel:`std::vector<cppraw::post>`

Throws :guilabel:`std::invalid_argument` if there was an error while requesting the data to
the reddit API.

.. code-block:: cpp

    std::vector<cppraw::post> posts = reddit.subreddit("cpp").recent();
    for(auto i: posts)
        std::cout << i.get_title() << std::endl; //prints the title of the 25 most recent posts in the cpp subreddit
    

-----------

hot
~~~~
Gets the hot posts from the subreddit.

.. admonition::
    Parameters

    ``int limit``
        The number of posts to return, defaults to 25
    ``std::string after``
        The id of the post after which to return posts, defaults to ""
    ``std::string before``
        The id of the post before which to return posts, defaults to ""

Returns :guilabel:`std::vector<cppraw::post>`

Throws :guilabel:`std::invalid_argument` if there was an error while requesting the data to
the reddit API.

.. code-block:: cpp

    std::vector<cppraw::post> posts = reddit.subreddit("cpp").hot();
    for(auto i: posts)
        std::cout << i.get_title() << std::endl; //prints the title of the 25 hot posts in the cpp subreddit
    
-----------

rising
~~~~~~
Gets the rising posts from the subreddit.

.. admonition::
    Parameters

    ``int limit``
        The number of posts to return, defaults to 25
    ``std::string after``
        The id of the post after which to return posts, defaults to ""
    ``std::string before``
        The id of the post before which to return posts, defaults to ""

Returns :guilabel:`std::vector<cppraw::post>`

Throws :guilabel:`std::invalid_argument` if there was an error while requesting the data to
the reddit API.

.. code-block:: cpp

    std::vector<cppraw::post> posts = reddit.subreddit("cpp").rising();
    for(auto i: posts)
        std::cout << i.get_title() << std::endl; //prints the title of the 25 rising posts in the cpp subreddit
    
-----------

top
~~~~
Gets the top posts from the subreddit.

.. admonition::
    Parameters

    ``int limit``
        The number of posts to return, defaults to 25
    ``std::string after``
        The id of the post after which to return posts, defaults to ""
    ``std::string before``
        The id of the post before which to return posts, defaults to ""

Returns :guilabel:`std::vector<cppraw::post>`

Throws :guilabel:`std::invalid_argument` if there was an error while requesting the data to
the reddit API.

.. code-block:: cpp

    std::vector<cppraw::post> posts = reddit.subreddit("cpp").top();
    for(auto i: posts)
        std::cout << i.get_title() << std::endl; //prints the title of the 25 top posts in the cpp subreddit
    
-----------

controversial
~~~~~~~~~~~~~
Gets the most controversial posts from the subreddit.

.. admonition::
    Parameters

    ``int limit``
        The number of posts to return, defaults to 25
    ``std::string after``
        The id of the post after which to return posts, defaults to ""
    ``std::string before``
        The id of the post before which to return posts, defaults to ""

Returns :guilabel:`std::vector<cppraw::post>`

Throws :guilabel:`std::invalid_argument` if there was an error while requesting the data to
the reddit API.

.. code-block:: cpp

    std::vector<cppraw::post> posts = reddit.subreddit("cpp").controversial();
    for(auto i: posts)
        std::cout << i.get_title() << std::endl; //prints the title of the 25 most controversial posts in the cpp subreddit
    
-----------

random
~~~~~~
Gets a random post from the subreddit.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`cppraw::post` object

Throws :guilabel:`std::invalid_argument` if there was an error while requesting the data to
the reddit API.

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").random();
    std::cout << post.get_title() << std::endl; //prints the title of a random post in the cpp subreddit

-----------

get_post
~~~~~~~~
Gets a post from the subreddit.

.. admonition::
    Parameters

    ``std::string id``
        The id of the post you wish to get

Returns :guilabel:`cppraw::post` object

Throws :guilabel:`std::invalid_argument` if there was an error while requesting the data to
the reddit API.

.. code-block:: cpp

    cppraw::post post = reddit.subreddit("cpp").get_post("vqy0rt");
    std::cout << post.get_title() << std::endl; //prints "C++ Jobs - Q3 2022"