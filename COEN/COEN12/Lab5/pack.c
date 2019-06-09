/*
 * File:	pack.c
 *
 * Copyright:	2017, Darren C. Atkinson
 */

# include <stdio.h>
# include <ctype.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/stat.h>
# include "pack.h"

# define END 256
# define MAX_LEVELS 24

void pack(char *infile, char *outfile, struct node *leaves[END + 1])
{
    unsigned char byte;
    int i, c, bitsleft, length[END + 1], levcount[MAX_LEVELS + 1], maxlev, len;
    unsigned long bits[END + 1], word;
    struct node *root, *np;
    struct stat buf;
    FILE *in, *out;
    int sum;


    if ((in = fopen(infile, "rb")) == NULL) {
	perror(infile);
	exit(errno);
    }

    if ((out = fopen(outfile, "wb")) == NULL) {
	perror(outfile);
	exit(errno);
    }

    if (stat(infile, &buf)) {
	perror(infile);
	exit(errno);
    }

    root = leaves[END];

    while (root->parent != NULL)
	root = root->parent;

    if (root->count != buf.st_size) {
	fprintf(stderr, "Sizes from file and tree mismatch.\n");
	exit(EXIT_FAILURE);
    }

    if (buf.st_size == 0) {
	fprintf(stderr, "Cannot compress empty file.\n");
	exit(EXIT_FAILURE);
    }

    sum = 0;
    maxlev = 0;

    for (i = 0; i <= MAX_LEVELS; i ++)
	levcount[i] = 0;

    for (c = 0; c <= END; c ++) {
	if (leaves[c] != NULL) {
	    length[c] = 0;

	    for (np = leaves[c]; np != root; np = np->parent)
		length[c] ++;

	    sum += length[c] * leaves[c]->count;

	    if (length[c] > MAX_LEVELS) {
		fprintf(stderr, "Huffman tree has too many levels\n");
		exit(EXIT_FAILURE);
	    } else {
		levcount[length[c]] ++;

		if (length[c] > maxlev)
		    maxlev = length[c];
	    }
	} else
	    length[c] = 0;
    }

    printf("total bits required = %d\n", sum);

    word = 0;

    for (i = maxlev; i > 0; i --) {
	for (c = 0; c <= END; c ++)
	    if (length[c] == i)
		bits[c] = word ++;

	word = word >> 1;
    }

    putc(037, out);
    putc(036, out);

    putc((buf.st_size >> 24) & 0xff, out);
    putc((buf.st_size >> 16) & 0xff, out);
    putc((buf.st_size >> 8) & 0xff, out);
    putc(buf.st_size & 0xff, out);

    putc(maxlev, out);

    for (i = 1; i < maxlev; i ++)
	putc(levcount[i], out);

    putc(levcount[maxlev] - 2, out);

    for (i = 1; i <= maxlev; i ++)
	for (c = 0; c < END; c ++)
	    if (length[c] == i)
		putc(c, out);

    byte = 0;
    bitsleft = 8;

    do {
	if ((c = getc(in)) == EOF)
	    c = END;

	word = bits[c];
	len = length[c];

	while (len >= bitsleft) {
	    len = len - bitsleft;
	    byte = (byte << bitsleft) | (word >> len);
	    putc(byte, out);
	    bitsleft = 8;
	}

	byte = (byte << len) | word;
	bitsleft = bitsleft - len;
    } while (c != END);

    if (len > 0) {
	byte = byte << bitsleft;
	putc(byte, out);
    }

    fclose(in);
    fclose(out);
}
