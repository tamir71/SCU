/*  Tamir Enkhjargal
    COEN 12 Lab 5
    June 2, 2019

    Creating Lab 5. Huffman encoding implementation */

/* Calling necessary libraries */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.h"
#include "pack.h"
#include <ctype.h>
#include <assert.h>

#define NODE struct node

/* ---------------------------------------------------------------------- */

/* Making a node (and optional connecting to two children). O(1) runtime. */

static NODE *makeNode(int count, NODE *left, NODE *right) {
    NODE *root = malloc(sizeof(NODE));                          // Make a node pointer
    assert(root != NULL);                                       // Check if successful
    root->count = count;                                        
    root->parent = NULL;                                        // Since this is root, no parent needed
    if(left != NULL) {                                          // If there is a left child, set root as its parent
        left->parent = root;
    }
    if(right != NULL) {                                         // If there is a right child, set root as its parent
        right->parent = root;
    }
    return root;
}

/* ---------------------------------------------------------------------- */

/* Node compare function between two leaves. O(1) runtime. */ 

static int nodeCmp(NODE *node1, NODE *node2) {
    assert(node1 != NULL && node2 != NULL); 
    return (node1->count < node2->count) ? -1: (node1->count > node2->count); // This ternary conditional operator checks if node1 or node2 is larger
}

/* ---------------------------------------------------------------------- */

/* Finding depth of a node. O(h) runtime worst case with recursion. */

static int depth(NODE *node) {
    if(node->parent == NULL) {                                  // Base case: node is empty
        return 0;                                               // return 0
    }
    else {
        return 1 + depth(node->parent);                         // Recursive step: 1 + depth of parent (until hits root)
    }
}

/* ---------------------------------------------------------------------- */

/* Main function that needs five basic steps:
 * 1. Count the number of occurrences of each character in the file
 * 2. Create a binary tree of leaves with counts of each character with nonzero counts.
 * 3. While the priority queue has more than 1 tree, remove the two lowest priority trees.
 *        Create new trees with these trees as subtrees. Count is sum of the two previous.
 * 4. At the end only one tree will remain. This is the Huffman tree. The count should be
 *        equal to the amount of characterse in the file.
 * 5. Then use the pack() function. */

int main(int argc, char *argv[]) {
    /* Step 1. */
    int ascii[257];                                             // Initialize a 257 size array for all printable ascii characters
    NODE *leaves[257];                                          // Initialize an array for each possible ascii character
    int i, j, k, l;

    for(i = 0; i < 257; i++) {                                  // For all 257 indices
        ascii[i] = 0;                                           // Set ascii[i] = 0
        leaves[i] = NULL;                                       // Set leaves[i] empty
    }

    if(argc != 3) {                                             // Check if user input two text files (input, output)
        printf("Missing file or arguments!\n");
        return 0;
    }

    FILE *fp = fopen(argv[1], "rb");                            // Open the input file on read-binary
    assert(fp != NULL);
    while((j = getc(fp)) != EOF) {                              // Loop through and get each character until hits EndOfFile
        ascii[j]++;                                             // j is the character it gets, then increment number of occurrences
    }
    fclose(fp);                                                 // Close file pointer

    /* Step 2. */
    PQ *pq = createQueue(*nodeCmp);                             // Create a priority queue
    for(k = 0; k < 257; k++) {                                  // Loop through the 257 indices
        if(ascii[k] > 0) {                                      // If there are nonzero amount of that character
            leaves[k] = makeNode(ascii[k], NULL, NULL);             // Create a node for that character
            addEntry(pq, leaves[k]);                                // and add it into the leaves[] array
        }
    }

    NODE *endfile = malloc(sizeof(NODE));                       // Make sure to keep one counter for the EOF character
    assert(endfile != NULL);
    endfile->count = 0;                                         // and set the count as 0
    endfile->parent = NULL;
    leaves[256] = endfile;
    addEntry(pq, leaves[256]);                                  // and then add it as the last leaf

    /* Step 3. */
    while(numEntries(pq) > 1) {                                 // Now looking at the priority queue we've made through addEntry function calls
        NODE *left = removeEntry(pq);                           // We want to 'connect' leaves of the same size (preferably)
        NODE *right = removeEntry(pq);                          // So we choose a left node and right node
        NODE *parent = makeNode(left->count + right->count, left, right);   // And add them together and summing the occurrence count together
        addEntry(pq, parent);                                   // Add the new combined parent
    }

    /* Step 4. */
    int ndepth, counter;                                        // For each leaf, we want a depth and total bit counter
    for(l = 0; l < 257; l++) {                                  // Loop through the whole array
        if(leaves[l] != NULL) {                                 // And check if the leaf is not empty
            ndepth = depth(leaves[l]);                          // Find the depth on a leaf with depth()
            counter = ndepth*leaves[l]->count;                  // Counter = depth x # of occurrences
            int printable = isprint(l);                         // Call isprint() function to see if asciiprintable
            printf(printable ? "%c" : "%03o", l);               // If printable, then print:
            printf(": %d times %d bits = %d bits\n", ascii[l], ndepth, counter);    // Print the 1) character 2) depth 3) counter
        }
    }

    /* Step 5. */
    pack(argv[1], argv[2], leaves);                             // Call the pack() function
    return 0;
}

/* ---------------------------------------------------------------------- */
