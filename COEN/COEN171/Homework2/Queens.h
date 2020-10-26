// Tamir Enkhjargal
// SCU - COEN 171
// Homework 2 - Queens.h

# ifndef QUEENS_H
# define QUEENS_H

#include <cstdlib>
#include <iostream>

using namespace std;

class Piece {
	protected:
		int _row, _col;

	public:
		int row() const { return _row; }
		int col() const { return _col; }
		void place(int row, int col) {
			_row = row;
			_col = col;
		}
		virtual bool menaces(const Piece *p) const { return ((p->row() == _row) && (p->col() == _col)); }
};

class Knight: public Piece {
	bool menaces(const Piece *p) const {
		if ((abs(p->row() - _row) == 2) && (abs(p->col() - _col) == 1)) { return true; }
		if ((abs(p->row() - _row) == 1) && (abs(p->col() - _col) == 2)) { return true; }
    	return false;
	}
};

class Bishop: public Piece {
	bool menaces(const Piece *p) const {
		if (abs(p->row() - _row) == abs(p->col() - _col)) 	{ return true; }
        return false;
	}
};

class Rook: public Piece {
	bool menaces(const Piece *p) const {
		if ((p->col() == _col) || (p->row() == _row)) 		{ return true; }
		return false;
	}
};

class Queen: public Piece {
	bool menaces(const Piece *p) const {
		if (abs(p->row() - _row) == abs(p->col() - _col)) 	{ return true; }
        if ((p->row() == _row) || (p->col() == _col)) 		{ return true; }
        return false;
	}
};

class Amazon: public Piece {
	bool menaces(const Piece *p) const {
		if (abs(p->row() - _row) == abs(p->col() - _col)) 				{ return true; }
		if ((p->row() == _row) 	|| (p->col() == _col))					{ return true; }
		if ((abs(p->row() - _row) == 2) && (abs(p->col() - _col) == 1)) { return true; }
		if ((abs(p->row() - _row) == 1) && (abs(p->col() - _col) == 2)) { return true; }
		return false;
	}
};

# endif /* QUEENS_H */
