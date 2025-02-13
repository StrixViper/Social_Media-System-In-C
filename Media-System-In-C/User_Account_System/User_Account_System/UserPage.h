#ifndef USERPAGE_H_INCLUDED
#define USERPAGE_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define commentsFile comments.txt

// Forward declarations
typedef struct UserPage UserPage;
typedef struct Post Post;


struct Post {
    char title[50];
    char content[150];
    int postLikeCount;
    int shareCount;
    int dislikeCount;
    int postID;
    int *likedByUsers; // array for storing the users id that like your post
    int likedByCount;
    //char PostPhoto[100];
};

struct UserPage {
    char username[50];
    char bio[100];
    int PageNumber;
    bool isPrivate;
    char Join_Date[20];
    UserPage *followers;    // Pointer to an array of followers
    int followersCount;
    UserPage *following;    // Pointer to an array of following
    int followingCount;
    //char ProfilePic[100];
    Post *Posts;            // Pointer to an array of posts
    int postsCount;
    int likesCount;
    bool isSuspended;
};


#endif // USERPAGE_H_INCLUDED
