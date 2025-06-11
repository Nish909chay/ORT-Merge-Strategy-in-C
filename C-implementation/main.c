#include <stdio.h>
#include <direct.h>  // For _mkdir on Windows

#include "tree.h"
#include "file_utils.h"

int main() {
    TreeNode* base = buildTreeFromDir("base");
    printf("Loaded base:\n");
    printTree(base, 0);

    TreeNode* ours = buildTreeFromDir("ours");
    printf("Loaded ours:\n");
    printTree(ours, 0);

    TreeNode* theirs = buildTreeFromDir("theirs");
    printf("Loaded theirs:\n");
    printTree(theirs, 0);

    TreeNode* merged = mergeTrees(base, ours, theirs);
    printf("Merged tree:\n");
    printTree(merged, 0);
    writeTreeToDisk(merged, "merged_output");

    return 0;
}
