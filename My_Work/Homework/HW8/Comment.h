#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <vector>

class Comment {
public:
    std::string video_id;
    std::string author;
    std::string comment_id;
    int like_count;
    int reply_count;
    bool is_reply;
    std::string parent_comment_id;
    std::string published_date;
    std::string crawled_date;
    bool is_video_owner;
    std::string comment;
    std::vector<Comment*> replies; // Vector to store replies to the comment

    // Constructor
    Comment(const std::string& video_id, const std::string& author, const std::string& comment_id, int like_count, int reply_count, bool is_reply, const std::string& parent_comment_id, const std::string& published_date, const std::string& crawled_date, bool is_video_owner, const std::string& comment);

    // Default constructor
    Comment();

    // Function to add a reply to the comment
    void addReply(Comment* reply);

    void addReply2(Comment* reply);

    // Function to check if the comment has replies
    bool hasReplies() const;

    // Function to find a comment by ID in the tree
    Comment* findComment(const std::string& id);

    void addLike(const std::string& id) ;

    // Function to remove a comment from the tree
    void removeComment(const std::string& id);

     // Function to check if the comment was published now
    bool isPublishedNow() const;

   static bool compareTime(const Comment* a, const Comment* b);

    int convertToMinutes(const std::string& timeStr);

    void sortTimeVector(std::vector<Comment*>& timeVec);

   

};

#endif // COMMENT_H
