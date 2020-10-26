/*
 * Solve the n-Pieces problem of trying to place n identical pieces on
 * an n x n chessboard.
 *
 * 		Knights			Bishops			Rooks		Queens		Amazons
 * 2	6				4				2			0			0
 * 3	36				26				6			0			0
 * 4	412				260				24			2			0
 * 5	9386			3368			120			10			0
 * 6	257318			53744			720			4			0
 * 7	8891854			1022320			5040		40			0
 * 8	379978716		22522960		40320		92			0
 * 9	19206532478		565532992		362880		352			0
 * 10	1120204619108	15915225216		3628800		724			4
 */

# include <iostream>
# include "Queens.h"

# ifndef PIECE
# define PIECE Amazon
# endif

int n;
Piece **pieces;
unsigned long long numsolns;


/*
 * Function:	place
 *
 * Description:	Place the current piece on the chessboard starting at the
 *		specified starting row and column.  We only move forward
 *		along the rows and columns because we don't want to repeat
 *		previous solutions.
 */

void place(int start_row, int start_col, int current)
{
    int row, col, i;


    for (row = start_row; row < n; row ++) {
	for (col = start_col; col < n; col ++) {
	    pieces[current]->place(row, col);

	    for (i = 0; i < current; i ++)
		if (pieces[i]->menaces(pieces[current]))
		    break;

	    if (i == current) {
		if (current + 1 != n)
		    place(row, col + 1, current + 1);
		else
		    numsolns ++;
	    }
	}

	start_col = 0;
    }
}


int main()
{
    std::cin >> n;
    pieces = new Piece *[n];

    for (int i = 0; i < n; i ++)
	pieces[i] = new PIECE;

    place(0, 0, 0);
    std::cout << numsolns << std::endl;
}
