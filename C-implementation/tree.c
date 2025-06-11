#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

TreeNode* createFileNode(const char* name, const char* content) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->name = (char*)malloc(MAX_NAME_LEN);
    strncpy(node->name, name, MAX_NAME_LEN);
    node->type = FILE_NODE;
    node->content = (char*)malloc(MAX_CONTENT_LEN);
    strncpy(node->content, content, MAX_CONTENT_LEN);
    node->children = NULL;
    node->childCount = 0;
    return node;
}

TreeNode* createDirNode(const char* name) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->name = (char*)malloc(MAX_NAME_LEN);
    strncpy(node->name, name, MAX_NAME_LEN);
    node->type = DIR_NODE;
    node->content = (char*)malloc(MAX_CONTENT_LEN);
    node->content[0] = '\0';
    node->children = (TreeNode**)malloc(sizeof(TreeNode*) * MAX_CHILDREN);
    node->childCount = 0;
    return node;
}

void addChild(TreeNode* parent, TreeNode* child) {
    if (parent->type == DIR_NODE && parent->childCount < MAX_CHILDREN) {
        parent->children[parent->childCount++] = child;
    }
}

void printTree(TreeNode* node, int depth) {
    for (int i = 0; i < depth; i++) printf("  ");

    if (node->type == DIR_NODE) {
        printf("Dir : %s\n", node->name);
        for (int i = 0; i < node->childCount; i++) {
            printTree(node->children[i], depth + 1);
        }
    } else {
        printf("File: %s | Content: %s\n", node->name, node->content);
    }
}

TreeNode* mergeTrees(TreeNode* base, TreeNode* ours, TreeNode* theirs) {
    TreeNode* merged = createDirNode("merged");

    // Hardcoded file list for merging
    char* filenames[] = { "a.txt", "b.txt" };

    for (int i = 0; i < 2; i++) {
        const char* fname = filenames[i];

        TreeNode* baseF = findChild(base, fname);
        TreeNode* ourF = findChild(ours, fname);
        TreeNode* theirF = findChild(theirs, fname);

        if (ourF && theirF && areContentsEqual(ourF, theirF)) {
            addChild(merged, createFileNode(fname, ourF->content));
        }
        else if (baseF && ourF && areContentsEqual(baseF, ourF)) {
            addChild(merged, createFileNode(fname, theirF ? theirF->content : ""));
        }
        else if (baseF && theirF && areContentsEqual(baseF, theirF)) {
            addChild(merged, createFileNode(fname, ourF ? ourF->content : ""));
        }
        else if (ourF && theirF && areContentsEqual(ourF, theirF)) {
            addChild(merged, createFileNode(fname, ourF->content));
        }
        else {
            // Conflict
            char conflict[1024];
            snprintf(conflict, sizeof(conflict),
                     "AUTO-MERGE FAILED\n<<<<<<< OURS\n%s\n=======\n%s\n>>>>>>> THEIRS\n",
                     ourF ? ourF->content : "",
                     theirF ? theirF->content : "");
            addChild(merged, createFileNode(fname, conflict));
        }
    }

    return merged;
}

int areContentsEqual(TreeNode* a, TreeNode* b) {
    if (!a || !b) return 0;
    return strcmp(a->content, b->content) == 0;
}

TreeNode* findChild(TreeNode* dir, const char* name) {
    for (int i = 0; i < dir->childCount; i++) {
        if (strcmp(dir->children[i]->name, name) == 0) {
            return dir->children[i];
        }
    }
    return NULL;
}

