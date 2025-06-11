#ifndef TREE_H
#define TREE_H

#define MAX_NAME_LEN 100
#define MAX_CONTENT_LEN 1024
#define MAX_CHILDREN 100

typedef enum { FILE_NODE, DIR_NODE } NodeType;

typedef struct TreeNode {
    char* name;
    NodeType type;
    char* content;
    struct TreeNode** children;
    int childCount;
} TreeNode;

TreeNode* createFileNode(const char* name, const char* content);
TreeNode* createDirNode(const char* name);
void addChild(TreeNode* parent, TreeNode* child);
void printTree(TreeNode* root, int depth);
TreeNode* buildTreeFromDir(const char* path);
TreeNode* mergeTrees(TreeNode* base, TreeNode* ours, TreeNode* theirs);
int areContentsEqual(TreeNode* a, TreeNode* b);
TreeNode* findChild(TreeNode* dir, const char* name);

#endif
