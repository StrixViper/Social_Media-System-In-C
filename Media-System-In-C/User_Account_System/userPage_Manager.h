#ifndef USERPAGE_MANAGERT_H_INCLUDED
#define USERPAGE_MANAGERT_H_INCLUDED

#include "UserPage.h"

#include "C:\Users\SHnav\OneDrive\Pictures\Documents\Media-System-In-C\User_Account_System\includes\stb_image.h"


void InputPageBio(UserPage *userPage);
void InputProfileAccessType(UserPage *userPage);
void getCurrentDate(UserPage *userPage);
void CreateUserPage(UserPage *userPage,User *user);
int getAccountID();
void printUserPage(UserPage* userPage);
int getPostID();
void CreatePagePost(UserPage *userPage);
void DeletePagePost(UserPage *userPage,int postId);
void SuspendUserPage(UserPage *userPage);
void DeleteUserPage(UserPage *userPage);
void LikeUserPagePost(UserPage *userPage,Post *post);
void ShareUserPagePost(UserPage *userPage,Post *post,User *userToShare);
void DislikeUserPagePost(UserPage *userPage, Post *post);
void EditPagePost(UserPage *userPage,UserPage *newUserPage);
void UploadImage(UserPage *userPge);
void SearchProfiles();
void FollowUserPage();
void UnFollowUserPage();

//--------HELPING FUNCTIONS

void getCurrentDate(struct UserPage *userPage);


//-------=Function Implamantation-------//

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

    userPage->PageNumber = getAccountID();

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
    userPage->isSuspended = false;

}

int getAccountID() {

    static int currentID = 1;
    return currentID++;

}

void printUserPage(UserPage *userPage) {
    printf("\n============================================\n");
    printf("              USER PROFILE                 \n");
    printf("============================================\n");
    printf("| Page Number  : %-26d |\n", userPage->PageNumber);
    printf("| Username     : %-26s |\n", userPage->username);
    printf("| Bio          : %-26s |\n", userPage->bio);
    printf("| Profile Type : %-26s |\n", userPage->isPrivate ? "Private" : "Public");
    printf("| Joined       : %-26s |\n", userPage->Join_Date);
    printf("--------------------------------------------\n");
    printf("| Followers   : %-4d | Following  : %-4d |\n", userPage->followersCount, userPage->followingCount);
    printf("| Likes       : %-4d | Posts      : %-4d |\n", userPage->likesCount, userPage->postsCount);
    printf("============================================\n");
    printf("                 POSTS                      \n");
    printf("--------------------------------------------\n");

    if (userPage->postsCount > 0) {
        for (int i = 0; i < userPage->postsCount; i++) {
            printf("| Title    : %-31s |\n", userPage->Posts[i].title);
            printf("| Content  : %-31s |\n", userPage->Posts[i].content);
            printf("| Likes    : %-4d | Dislikes : %-4d |\n", userPage->Posts[i].postLikeCount, userPage->Posts[i].dislikeCount);
            printf("| Shares   : %-4d                         |\n", userPage->Posts[i].shareCount);
            printf("--------------------------------------------\n");
        }
    } else {
        printf("| No posts available.                      |\n");
        printf("--------------------------------------------\n");
    }
}

int getPostID() {

    static int currentPostID = 1;
    return currentPostID++;

}

void CreatePagePost(UserPage *userPage) {

    if (userPage->postsCount >= 100) {
        printf("Cannot add more posts. Maximum limit reached.\n");
        return;
    }

    userPage->Posts[userPage->postsCount].postID = getPostID();
    // Input title
    printf("Page title: ");
    fgets(userPage->Posts[userPage->postsCount].title, sizeof(userPage->Posts[userPage->postsCount].title), stdin);
    userPage->Posts[userPage->postsCount].title[strcspn(userPage->Posts[userPage->postsCount].title, "\n")] = '\0';  // Remove newline character if present

    // Input content
    printf("Page content: ");
    fgets(userPage->Posts[userPage->postsCount].content, sizeof(userPage->Posts[userPage->postsCount].content), stdin);
    userPage->Posts[userPage->postsCount].content[strcspn(userPage->Posts[userPage->postsCount].content, "\n")] = '\0';  // Remove newline character if present

    // Initialize other fields for the post
    userPage->Posts[userPage->postsCount].postLikeCount = 0;
    userPage->Posts[userPage->postsCount].shareCount = 0;
    userPage->Posts[userPage->postsCount].dislikeCount = 0;

    userPage->postsCount++;

    printf("Post Created successfully!\n");

}

void DeletePagePost(UserPage *userPage, int postId) {

    for (int i = 0; i < userPage->postsCount; i++) {
        if (userPage->Posts[i].postID == postId) {
            // Shift elements left
            for (int j = i; j < userPage->postsCount - 1; j++) {
                userPage->Posts[j] = userPage->Posts[j + 1];
            }

            userPage->postsCount--;

            // Resize the array to free unused memory (if dynamically allocated)
            if (userPage->postsCount > 0) {
                userPage->Posts = realloc(userPage->Posts, userPage->postsCount * sizeof(Post));
                if (userPage->Posts == NULL) {
                    printf("Memory reallocation failed!\n");
                    return;
                }
            } else {
                // If no posts left, free the array
                free(userPage->Posts);
                userPage->Posts = NULL;
            }

            return;
        }
    }
    printf("No Post That Matches Your ID Was Found!\n");
}

void SuspendUserPage(UserPage *userPage) {

    userPage->isSuspended = true;
}

void DeleteUserPage(UserPage *userPage) {
    if (userPage == NULL) return;

    // Free dynamically allocated Posts
    if (userPage->Posts != NULL) {
        free(userPage->Posts);
        userPage->Posts = NULL;
    }

    // Free dynamically allocated Followers
    if (userPage->followers != NULL) {
        free(userPage->followers);
        userPage->followers = NULL;
    }

    // Free dynamically allocated Following
    if (userPage->following != NULL) {
        free(userPage->following);
        userPage->following = NULL;
    }

    // Finally, free the UserPage itself
    free(userPage);
    printf("UserPage has been completely deleted (hard delete).\n");
}

void LikePost(UserPage *userPage, Post *post) {
    if (post == NULL || userPage == NULL) return;

    // Resize memory to store the new user ID (PageNumber of user who liked it)
    post->likedByUsers = realloc(post->likedByUsers, (post->postLikeCount + 1) * sizeof(int));
    if (post->likedByUsers == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    post->likedByUsers[post->postLikeCount] = userPage->PageNumber;  // Use postLikeCount as index
    post->postLikeCount++;  //Increase like count

    printf("User %d liked Post %d! Total Likes: %d\n", userPage->PageNumber, post->postID, post->postLikeCount);
}



#endif // USERPAGE_MANAGERT_H_INCLUDED
