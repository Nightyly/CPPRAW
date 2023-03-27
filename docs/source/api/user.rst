User
=====

This class allows you to interact with a redditor

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.is_employee() << std::endl; //prints "false" as of now

Member functions
-----------------

.. contents::
    :local:

-----------

get_name
~~~~~~~~~
Gets the username of the redditor.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`std::string`

.. code-block:: cpp

    cppraw::user user = reddit.user("dAelI_sMilE");
    std::cout << user.get_name() << std::endl; //prints "Daeli_Smile"

-----------

is_friend
~~~~~~~~~~
Gets whether the redditor is a friend of the bot. (https://www.reddit.com/prefs/friends/)

.. admonition::
    Parameters
    
    None

Returns :guilabel:`bool`

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.is_friend() << std::endl; //output depends

-----------

is_employee
~~~~~~~~~~~~
Gets whether the redditor is a reddit employee.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`bool`

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.is_employee() << std::endl; //prints "false"

-----------

get_karma
~~~~~~~~~~
Gets the total karma of the redditor.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`int64_t`

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_karma() << std::endl; // output depends

-----------

get_link_karma
~~~~~~~~~~~~~~
Gets the link karma of the redditor.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`int64_t`

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_link_karma() << std::endl //output depends

-----------

get_awarder_karma
~~~~~~~~~~~~~~~~~
Gets the awarder karma of the redditor.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`int64_t`

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_awarder_karma() << std::endl //output depends

-----------

get_awardee_karma
~~~~~~~~~~~~~~~~~
Gets the awardee karma of the redditor.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`int64_t`

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_awardee_karma() << std::endl //output depends

-----------

get_comment_karma
~~~~~~~~~~~~~~~~~
Gets the comment karma of the redditor.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`int64_t`

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_comment_karma() << std::endl //output depends

-----------

has_verified_email
~~~~~~~~~~~~~~~~~~
Returs whether the redditor has a verified email.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`bool`

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.has_verified_email() << std::endl //prints "true"

-----------

get_creation_millis
~~~~~~~~~~~~~~~~~~~
Gets the time when the redditor's account was created in unix millis.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`uint64_t`

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_creation_millis() << std::endl //prints "1588297297000"

-----------

get_snoovatar_url
~~~~~~~~~~~~~~~~~~
Gets the snoovatar url.

.. admonition::
    Parameters
    
    None

Returns :guilabel:`std::string`

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.get_snoovatar_url() << std::endl; // prints "https://i.redd.it/snoovatar/avatars/nftv2_bmZ0X2VpcDE1NToxMzdfNmFjYjhmYjgyODgwZDM5YzJiODQ0NmY4Nzc4YTE0ZDM0ZWU2Y2ZiN18xNTM4_rare_fc87c224-e736-4656-aec7-713e66987ac1.png"

-----------

accepts_pms
~~~~~~~~~~~
Gets whether the redditor accepts pms. If the redditor requested is the bot itself, returns false

.. admonition::
    Parameters
    
    None

Returns :guilabel:`bool`

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    std::cout << user.accepts_pms() << std::endl; // output depends

-----------

send_pm
~~~~~~~
Sends a private message to the redditor. Appears on https://www.reddit.com/message/sent/

.. admonition::
    Parameters

    ``std::string title``
        The subject of the message.
    ``std::string content``
        The body of the message.

Returns :guilabel:`void`

.. code-block:: cpp

    cppraw::user user = reddit.user("Daeli_Smile");
    user.send_pm("Hello from CPPRAW!", "This message was sent using CPPRAW");