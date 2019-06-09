/*
 * File:	pack.h
 *
 * Copyright:	2017, Darren C. Atkinson
 */

# ifndef PACK_H
# define PACK_H

struct node {
    struct node *parent;
    int count;
};

void pack(char *infile, char *outfile, struct node *leaves[257]);

# endif /* PACK_H */
