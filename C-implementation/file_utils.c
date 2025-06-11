#include "file_utils.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>    // mkdir
#include <dirent.h>      // DIR, readdir
#include <errno.h>

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#ifdef _WIN32
#include <direct.h> // For _mkdir
#define MKDIR(path) _mkdir(path)
#define PATH_SEP "\\"
#else
#define MKDIR(path) mkdir(path, 0755)
#define PATH_SEP "/"
#endif

TreeNode* buildTreeFromDir(const char* path) {
    printf("Opening dir: %s\n", path);

    DIR* dir = opendir(path);
    if (!dir) {
        perror("opendir failed");
        return NULL;
    }

    TreeNode* root = createDirNode(path);

    struct dirent* entry;
    while ((entry = readdir(dir))) {
        printf("Found entry: %s\n", entry->d_name);

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[MAX_PATH];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        printf(" -> fullpath: %s\n", fullpath);

        struct stat st;
        if (stat(fullpath, &st) == -1) {
            perror("stat failed");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            TreeNode* subdir = buildTreeFromDir(fullpath);
            addChild(root, subdir);
        } else if (S_ISREG(st.st_mode)) {
            FILE* f = fopen(fullpath, "r");
            if (!f) {
                perror("fopen failed");
                continue;
            }

            char buffer[MAX_CONTENT_LEN] = {0};
            fread(buffer, 1, sizeof(buffer) - 1, f);
            fclose(f);

            TreeNode* fileNode = createFileNode(entry->d_name, buffer);
            addChild(root, fileNode);
        }
    }

    closedir(dir);
    printf("Done reading dir: %s\n", path);
    return root;
}

void writeTreeToDisk(TreeNode* node, const char* basePath) {
    if (!node) return;

    char fullpath[MAX_PATH];
    // If basePath is empty, just use node->name (for root)
    if (basePath[0] == '\0') {
        snprintf(fullpath, sizeof(fullpath), "%s", node->name);
    } else {
        snprintf(fullpath, sizeof(fullpath), "%s%s%s", basePath, PATH_SEP, node->name);
    }

    if (node->type == DIR_NODE) {
        int res = MKDIR(fullpath);
#ifdef _WIN32
        if (res != 0 && errno != EEXIST) {
#else
        if (res != 0 && errno != EEXIST) {
#endif
            perror("mkdir failed");
            return;
        }
        for (int i = 0; i < node->childCount; ++i) {
            writeTreeToDisk(node->children[i], fullpath);
        }
    } else if (node->type == FILE_NODE) {
        FILE* f = fopen(fullpath, "w");
        if (!f) {
            perror("fopen for writing failed");
            return;
        }
        fputs(node->content, f);
        fclose(f);
    }
}
