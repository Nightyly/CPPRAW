Reddit
=======

This is CPPRAW's main class, this must be the first class to be instantiated.

.. admonition::
    Parameters

    ``std::string client_id``
        Your client id.
    ``std::string client_secret``
        Your client secret.
    ``std::string username``
        Your reddit's account username.
    ``std::string password``
        Your reddit's account password.
    ``std::string user_agent``
        Your user agent.

Throws :guilabel:`std::invalid_argument` if there was an error getting the bearer token from
the reddit API.

.. code-block:: cpp

    cppraw::reddit reddit("client-id", "client-secret","reddit-user", "reddit-password", "user-agent");

Both the client-id and the client-secret can be obtained in https://www.reddit.com/prefs/apps/

The user-agent is a string that tells the server what your application is. It can be anything,
but it is not recommended to spoof a web browser or other application. For example, a user agent
can be "CPPRAW v0.0.4 by u/Daeli_Smile".

By default, your bearer token is saved to a macro-defined file called TOKEN_FILE, which is set to "token.txt".
If you wish to change the file in which it is stored, you can :code:`#define TOKEN_FILE "another_file.txt"` 
before including CPPRAW/CPPRAW.hpp.

The token is saved with its expiration date, so that you dont have to get a new token every time your
application is run.

Member functions
----------------

.. contents::
    :local:

-----------

subreddit
~~~~~~~~~

This function returns a subreddit object refering to the subreddit you provided.

.. admonition::
    Parameters
    
    ``std::string subreddit``
        The name of the subreddit you wish to look for.

Returns :guilabel:`cppraw::subreddit` object.

Throws :guilabel:`std::invalid_argument` either if the subreddit is not found or if there was
an error while getting the subreddit information from the reddit API.

.. code-block:: cpp

    cppraw::subreddit subreddit = reddit.subreddit("cpp");

-----------

post
~~~~
This function returns a post object refering to the post you provided.

.. admonition::
    Parameters

    ``std::string subreddit``
        The name of the subreddit.
    ``std::string id``
        The id of the post you wish to look for.

Returns :guilabel:`cppraw::post` object.

Throws :guilabel:`std::invalid_argument` either if the subreddit is not found or if
there was an error getting the subreddit or post information from the reddit API.

.. code-block:: cpp

    cppraw::post post = reddit.post("cpp", "vgy0rt");

-----------

user
~~~~
This function returns a cppraw::user object refering to the user you provided.

.. admonition::
    Parameters

    ``std::string name``
        The name of the user you wish to look for. Case insensitive.

Returns :guilabel:`cppraw::user` object.

Throws :guilabel:`std::invalid_argument` if there was an error getting the user's
information from the reddit API.

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");