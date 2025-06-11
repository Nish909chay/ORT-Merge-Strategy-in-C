#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "tree.h"

TreeNode* buildTreeFromDir(const char* path);
void writeTreeToDisk(TreeNode* node, const char* path);

#endif
