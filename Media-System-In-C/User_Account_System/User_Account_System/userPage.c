#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "C:\Users\SHnav\OneDrive\Pictures\Documents\Media-Application\Login-Register\input_from_user.h"

// Forward declarations
typedef struct UserPage UserPage;
typedef struct Post Post;

struct Post {
    char title[50];
    char content[150];
    int likeCount;
    int shareCount;
    int dislikeCount;
    char PostPhoto[100];
    FILE *commentsFile;
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
    char ProfilePic[100];
    Post *Posts;            // Pointer to an array of posts
    int postsCount;
    int likesCount;
};

void InputPageBio(UserPage *userPage);
void InputProfileAccessType(UserPage *userPage);
void CreateUserPage(UserPage *userPage,User *user);
void UpdateUserPageBio(UserPage *UserPage, User *user);
void UpdateUserPageAccessType(UserPage *UserPage, User *user);
void UpdateUserPagePic(UserPage *UserPage, User *user);
void DeleteUserPage(UserPage *userPage, User *user);
void CreatePagePost(UserPage *userPage);
void LikeUserPagePost(UserPage *userPage,Post *post);
void ShareUserPagePost(UserPage *userPage,Post *post,User *userToShare);
void DislikeUserPagePost(UserPage *userPage, Post *post);
void EditPagePost(UserPage *userPage,UserPage *newUserPage);
void DeletePagePost(UserPage *userPage, Post *postToDelete);
void UploadImage(UserPage *userPge);
void SearchProfiles();
void FollowUserPage();
void UnFollowUserPage();


//--------HELPING FUNCTIONS

void getCurrentDate(struct UserPage *user);




int main()
{
    return 0;
}


void InputPageBio(UserPage *userPage) {


    printf("write your bio: ");
    fgets(userPage->bio,sizeof(userPage->bio),stdin);

    // Remove the trailing newline character, if present
    userPage->bio[strcspn(userPage->bio, "\n")] = '\0';
}

void InputProfileAccessType(UserPage *userPage) {


    printf("insert your profile access type \n 1: Private 2: Public\n type: ");
    int choice;
    scanf("%d",&choice);

    while(true)
    {
        if(choice == 1)
        {
            printf("your account will be Private.");
            userPage->isPrivate = true;
            break;
        }
        else if(choice == 2)
        {
            printf("your account will be Public.");
            userPage->isPrivate = false;
            break;
        }
        else
        {
            printf("invalid choice , try again later.\n");
        }
    }
}

void getCurrentDate(UserPage *userPage) {
    time_t currentTime;
    struct tm *localTime;

    // Get the current time
    time(&currentTime);

    // Convert the time to local time representation
    localTime = localtime(&currentTime);

    // Format the date in "YYYY-MM-DD" format
    strftime(userPage->Join_Date, sizeof(userPage->Join_Date), "%Y-%m-%d", localTime);
}

void CreateUserPage(UserPage *userPage,User *user) {

    strcpy(userPage->username,user->userName);
    InputPageBio(userPage);
    InputProfileAccessType(userPage);
    getCurrentDate(userPage);

    userPage->followers = NULL;
    userPage->followersCount = 0;
    userPage->following = NULL;
    userPage->followingCount = 0;
    userPage->Posts = NULL;
    userPage->postsCount = 0;
    userPage->likesCount = 0;

}


