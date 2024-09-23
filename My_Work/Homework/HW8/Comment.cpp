#include "Comment.h"
#include <iostream>
#include <algorithm>

// Constructor definition
Comment::Comment(const std::string& video_id, const std::string& author, const std::string& comment_id, int like_count, int reply_count, bool is_reply, const std::string& parent_comment_id, const std::string& published_date, const std::string& crawled_date, bool is_video_owner, const std::string& comment)
    : video_id(video_id), author(author), comment_id(comment_id), like_count(like_count), reply_count(reply_count), is_reply(is_reply), parent_comment_id(parent_comment_id), published_date(published_date), crawled_date(crawled_date), is_video_owner(is_video_owner), comment(comment) {}
//Defult constructor
Comment::Comment()
    : video_id(""), author(""), comment_id(""), like_count(0), reply_count(0), is_reply(false), parent_comment_id(""), published_date(""), crawled_date(""), is_video_owner(false), comment(""), replies() {}

// Function to add a reply to the comment with consideration of parent comment ID
void Comment::addReply2(Comment* new_comment) {
    // first check if this comment is the perent 

    if (new_comment->parent_comment_id == comment_id) {
      //  std::cout << "Found id and adding replies" << std::endl;
        replies.push_back(new_comment);
        reply_count++;
        sortTimeVector(replies);
        return;
    }

    // Otherwise, recursively search for the parent_comment_id in the replies of this comment
    for (Comment* & reply : replies) {
        reply->addReply2(new_comment);
    }
}

Comment* Comment::findComment(const std::string& id) {
    if (comment_id == id) {
        return this; // Return this comment if the ID matches
    }

    // Recursively search for the comment in the replies
   for (std::vector<Comment*>::iterator it = replies.begin(); it != replies.end(); ++it) {
        Comment* foundComment = ( *it ) -> findComment(id);
        if (foundComment != NULL) {
            return foundComment; // Return the found comment
        }
    }

    // Return nullptr if the comment is not found
    return NULL;
}
// Function to convert time strings like '7 hours ago' to integer representation
int Comment::convertToMinutes(const std::string& timeStr) {
    size_t found = timeStr.find("hours ago");
    if (found != std::string::npos) {
        return stoi(timeStr.substr(0, found)) * 60;
    }

    found = timeStr.find("minutes ago");
    if (found != std::string::npos) {
        return stoi(timeStr.substr(0, found));
    }

    found = timeStr.find("days ago");
    if (found != std::string::npos) {
        return stoi(timeStr.substr(0, found)) * 24 * 60;
    }

    found = timeStr.find("months ago");
    if (found != std::string::npos) {
        return stoi(timeStr.substr(0, found)) * 30 * 24 * 60;
    }

    found = timeStr.find("years ago");
    if (found != std::string::npos) {
        return stoi(timeStr.substr(0, found)) * 365 * 24 * 60;
    }

    return 0;
}

// Custom comparator function to sort time strings from latest to earliest
bool Comment::compareTime(const Comment* a, const Comment* b) {
    // Create instances of Comment to call convertToMinutes
    Comment commentA, commentB;

    return commentA.convertToMinutes(a->published_date) > commentB.convertToMinutes(b->published_date);
}

// Function to sort the vector of time strings
void Comment::sortTimeVector(std::vector<Comment*>& timeVec) {
    sort(timeVec.begin(), timeVec.end(), Comment::compareTime);
}


void Comment::addReply(Comment* reply)
{
    // Add the new reply to the 'replies' vector
    replies.push_back(reply);

    // Update the 'reply_count' member of the current comment
    reply_count++;
}
// Function to check if the comment has replies
bool Comment::hasReplies() const {
    return !replies.empty();
}

void Comment::addLike(const std::string& id) {
        // Check if this comment has the same id
        if (comment_id == id) {
           //  std::cout << "Found id and adding a like" << std::endl;
            like_count++;
            return;
        }

        // Recursively search in replies for a comment with the same id
        for (Comment* reply : replies) {
            reply->addLike(id);
        }
    }


 void Comment::removeComment(const std::string& id) {

    for (std::vector<Comment*>::iterator it = replies.begin(); it != replies.end();) {
        if ((*it)->comment_id == id) {
            // Delete the comment and remove from vector
            delete *it;
            it = replies.erase(it);
        } else {
            // Recursively remove from replies
            (*it)->removeComment(id);
            ++it;
        }
    }
}

bool Comment::isPublishedNow() const {
    return published_date == "";
}
