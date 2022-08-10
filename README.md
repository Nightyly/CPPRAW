# CPPRAW
C Plus Plus Reddit API Wrapper

(Yes this is a blatant copy of the [praw project](https://github.com/praw-dev/praw)).
But, we have something that the praw folks dont: support from Gordon Ramsay himself!

![a](https://res.cloudinary.com/teepublic/image/private/s--hvlnclk3--/t_Preview/b_rgb:484849,c_limit,f_jpg,h_630,q_90,w_630/v1495300391/production/designs/1614407_1.jpg)

## Installation
This project depends on libcpr and nlohmann/json, grab the CMakeLists.txt file from this repository, as well as everything under the CPPRAW folder, then you can #include "CPPRAW/CPPRAW.hpp" and you are set.
```
mkdir build
cd build
cmake ..
make
```
## Quick start
When you have your client id, secret and reddit username and password, you can do
```c++
cppraw::reddit r("client id", "client secret", "reddit username", "reddit password", "user agent");
```

Currently, the library is very limited, but there are somethings you can do

```c++
std::vector<cppraw::post> v = r.subreddit("cpp").recent(30); //get the 30 most recent posts from the r/cpp subreddit
for(auto p: v){
    std::cout << p.get_title() << std::endl;
}

cppraw::post p = r.subreddit("cpp").get_post("vqy0rt") //get a specific post from a subreddit using its id (https://www.reddit.com/r/cpp/comments/vqy0rt/c_jobs_q3_2022/)
```

Further documentation can be found on https://cppraw.readthedocs.io/en/latest/
