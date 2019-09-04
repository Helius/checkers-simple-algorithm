#include <iostream>
#include <string>

int AISelect (int pa[], int pb[], int ka[], int kb[], int left);
int modSelect (int pa[], int pb[], int ka[], int kb[], int left);

//these four arrays are the playing board - the position of each piece and whether that piece is a king

enum Fld {
	Empty,
	White,
	Black,
	WhiteKing,
	BlackKing
};

class Board {
public:
	int piecesA[12] = {0, 2, 4, 6, 9, 11, 13, 15, 16, 18, 20, 22};
	int piecesB[12] = {63, 61, 59, 57, 54, 52, 50, 48, 47, 45, 43, 41};
	int kingsA[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int kingsB[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int x = 0;

	Fld whoIsThere(int ind) const
	{
		for(int i = 0; i < 12; ++i) {
			if(piecesA[i] == ind) {
				if(kingsA[i] == 1)
					return WhiteKing;
				else
					return White;
			}
		}
		for(int i = 0; i < 12; ++i) {
			if(piecesB[i] == ind) {
				if(kingsB[i] == 1)
					return BlackKing;
				else
					return Black;
			}
		}
	
		return Empty;
	}

	void reset()
	{
		//this function resets the game
		//a iterates through pieces
		int a = 0;
		while (a < 12) {
			//this marks all pieces as not kings
			kingsA[a] = 0;
			kingsB[a] = 0;
			a++;
		}
		//this places all pieces in the starting position
		piecesA[0] = 0;
		piecesA[1] = 2;
		piecesA[2] = 4;
		piecesA[3] = 6;
		piecesA[4] = 9;
		piecesA[5] = 11;
		piecesA[6] = 13;
		piecesA[7] = 15;
		piecesA[8] = 16;
		piecesA[9] = 18;
		piecesA[10] = 20;
		piecesA[11] = 22;
		piecesB[0] = 63;
		piecesB[1] = 61;
		piecesB[2] = 59;
		piecesB[3] = 57;
		piecesB[4] = 54;
		piecesB[5] = 52;
		piecesB[6] = 50;
		piecesB[7] = 48;
		piecesB[8] = 47;
		piecesB[9] = 45;
		piecesB[10] = 43;
		piecesB[11] = 41;
	}
};


int options(int l, int m[], const int pa[], const int pb[], const int ka[], const int kb[], int t) {
  //this function finds all possible moves for a selected piece.
  //it returns the number of legal moves, but the argument m is where possible moves are written
  //entries in m are the locations the move piece can end at
  //l marks which piece is selected, m is set as an array of moves, pa, pb, ka and kb are a board, and t denotes whose turn it is
  //z records how many legal moves this piece has, a stores whether the piece can move forward, and which team it is on, b stores the position of the moving piece
  int z = 0;
  int a = 0;
  int b = 0;
  //this checks whether there is a spot forwards and to the right of the piece
  if (t == -1 && pa[l]%8 != 7 && pa[l] < 56) {
    a = -1;
    b = pa[l];
  } if (t == 1 && pb[l]%8 != 7 && pb[l] > 7) {
    a = 1;
    b = pb[l];
  }
  if (a != 0) {
    //c iterates through all enemy pieces, d records whether there is a piece in the way, and which side that piece is on
    //0 means no piece, -1 a human piece, 1 an AI piece
    int c = 0;
    int d = 0;
    while (c < 12) {
      if (pa[c] == b+1-(8*t)) {
        d = -1;
      } if (pb[c] == b+1-(8*t)) {
        d = 1;
      }
      c++;
    }
    if (d == 0) {
      //if the space is open, record moving to that space as an option, and that there was an option
      m[z] = b+1-(8*t);
      z++;
    } else if (d != t && b%8 < 6 && b*t >= 32*t-16) {
      //if there is an enemy piece in that space, and there is a space on the far side of that piece, jumping may be possible
      //c iterates through pieces, if any of them are in the space on the far side of the jumped spot, increase d
      c = 0;
      d = 0;
      while (c <12) {
        if (pb[c] == b+2-(16*t) || pa[c] == b+2-(16*t)) {
          d++;
        }c++;
      }
      if (d == 0) {
        //if the jump is available, record the end point of the jump as an option, and that there was an option
        m[z] = b+2-(16*t);
        z++;
      }
    }
  }
  a = 0;
  b = 0;
  if (t == -1 && pa[l]%8 != 0 && pa[l] < 56) {
    a = -1;
    b = pa[l];
  } if (t == 1 && pb[l]%8 != 0  && pb[l] > 7) {
    a = 1;
    b = pb[l];
  }
  if (a != 0) {
    int c = 0;
    int d = 0;
    while (c < 12) {
      if (pa[c] == b-1-(8*t)) {
        d = -1;
      } if (pb[c] == b-1-(8*t)) {
        d = 1;
      }
      c++;
    }
    if (d == 0) {
      m[z] = b-1-(8*t);
      z++;
    } else if (d != t && b%8 > 1 && b*t >= 32*t-16) {
      c = 0;
      d = 0;
      while (c <12) {
        if (pb[c] == b-2-(16*t) || pa[c] == b-2-(16*t)) {
          d++;
        }c++;
      }
      if (d == 0) {
        m[z] = b-2-(16*t);
        z++;
      }
    }
  }
  if (t == -1 && ka[l] == 1) {
    if (pa[l]%8 > 0 && pa[l] > 7) {
      int e = 0;
      a = 0;
      while (a < 12) {
        if (pa[a] == pa[l]-9 || pb[a] == pa[l]-9) {
          e = 1;
        }a++;
      } if (e == 0) {
        m[z] = pa[l]-9;
        z++;
      } else if (pa[l]%8 > 1 && pa[l] > 15) {
        e = 0;
        int f = 0;
        a =0;
        while (a < 12) {
          if (pb[a] == pa[l]-9) {
            e = 1;
          } if (pb[a] == pa[l]-18 || pa[a] == pa[l]-18) {
            f = 1;
          } a++;
        } if (e == 1 && f == 0) {
          m[z] = pa[l]-18;
          z++;
        }
      }
    }
    if (pa[l]%8 < 7 && pa[l] > 7) {
      int e = 0;
      a = 0;
      while (a < 12) {
        if (pa[a] == pa[l]-7 || pb[a] == pa[l]-7) {
          e = 1;
        }a++;
      } if (e == 0) {
        m[z] = pa[l]-7;
        z++;
      } else if (pa[l]%8 < 6 && pa[l] > 15) {
        e = 0;
        int f = 0;
        a =0;
        while (a < 12) {
          if (pb[a] == pa[l]-7) {
            e = 1;
          } if (pb[a] == pa[l]-14 || pa[a] == pa[l]-14) {
            f = 1;
          } a++;
        } if (e == 1 && f == 0) {
          m[z] = pa[l]-14;
          z++;
        }
      }
    }
  } else if (t == 1 && kb[l] == 1) {
    if (pb[l]%8 > 0 && pb[l] < 56) {
      int e = 0;
      a = 0;
      while (a < 12) {
        if (pa[a] == pb[l]+7 || pb[a] == pb[l]+7) {
          e = 1;
        }a++;
      } if (e == 0) {
        m[z] = pb[l]+7;
        z++;
      } else if (pb[l]%8 > 1 && pb[l] <48) {
        e = 0;
        int f = 0;
        a =0;
        while (a < 12) {
          if (pa[a] == pb[l]+7) {
            e = 1;
          } if (pb[a] == pb[l]+14 || pa[a] == pb[l]+14) {
            f = 1;
          } a++;
        } if (e == 1 && f == 0) {
          m[z] = pb[l]+14;
          z++;
        }
      }
    }
    if (pb[l]%8 < 7 && pb[l] < 56) {
      int e = 0;
      a = 0;
      while (a < 12) {
        if (pa[a] == pb[l]+9 || pb[a] == pb[l]+9) {
          e = 1;
        }a++;
      } if (e == 0) {
        m[z] = pb[l]+9;
        z++;
      } else if (pb[l]%8 < 6 && pb[l] < 48) {
        e = 0;
        int f = 0;
        a =0;
        while (a < 12) {
          if (pa[a] == pb[l]+9) {
            e = 1;
          } if (pb[a] == pb[l]+18 || pa[a] == pb[l]+18) {
            f = 1;
          } a++;
        } if (e == 1 && f == 0) {
          m[z] = pb[l]+18;
          z++;
        }
      }
    }
  }
  return z;
}

void StartSelect (Board & brd) {
  //this function looks at all possible moves for the AI, and chooses which has the best result
  //creates a replica of the board to model possible moves
  int placesA[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int placesB[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int monarchA[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int monarchB[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int a = 0;
  while (a < 12) {
    placesA[a] = brd.piecesA[a];
    placesB[a] = brd.piecesB[a];
    monarchA[a] = brd.kingsA[a];
    monarchB[a] = brd.kingsB[a];
    a++;
  }
  //this loop goes through each piece and considers possible moves
  //a records what piece is being looked at
  //b records how good the current best move is
  //c records which piece was moved in the current best move
  //d records how it was moved
  //x records whether a move was found
  a = 0;
  int b = -24;
  int c = 0;
  int d = 0;
  int x = 0;
  while (a < 12) {
    if (placesB[a] != -1) {
      //z records whether the moved piece was a king, so the replica board can be reset
      //e records where the moved place was at the start of the move, so the replica board can be reset
      //n records how many possible moves there are for this piece
      //k records where each possible move ends up
      int z = 0;
      int e = 0;
      int n = 0;
      int k[4] = {0, 0, 0, 0};
      n = options(a, k, placesA, placesB, monarchA, monarchB, 1);
      if (n > 0) {
        //f records which move is being considered
      int f = n-1;
      while (f >= 0) {
        //looks at each possible move
        e = placesB[a];
        placesB[a] = k[f];
        z = monarchB[a];
        if (placesB[a] < 8) {
          //tests if the currently moving piece should be kinged
          monarchB[a] = 1;
        }
        //g is used to iterates through the human's pieces
        int g = 12;
        //h stores the location of the any human's piece that is changed, so that the replica board can be reset
        int h = 0;
        if (placesB[a]%8 == e%8+2) {
          // checks if the move being considered is a jump to the right
          g = 0;
          while (g < 12) {
            //looks through enemy pieces to find the one being jumped
            if (placesA[g] == (e+placesB[a])/2) {
              h = placesA[g];
              placesA[g] = -1;
              break;
            } g++;
          }
        } else if (placesB[a]%8 == e%8-2) {
          //checks if the move being considered is a jump to the left
          g = 0;
          while (g < 12) {
          //looks through enemy pieces to find the one being jumped
            if (placesA[g] == (e+placesB[a])/2) {
              h = placesA[g];
              placesA[g] = -1;
              break;
            } g++;
          }
        }
        //m is the value of the expected end-state of this move
        int m = modSelect(placesA, placesB, monarchA, monarchB, 6);
        //checks all possible moves for each player extending from the current move being considered, recording the value of the best available board state
        if (m > b) {
          //checks if this is better then the current best board state, if so update the current best board state
          b = m;
          c = a;
          d = f;
        }
        //these all reset the replica board
        if (g < 12) {
          placesA[g] = h;
        }
        placesB[a] = e;
        monarchB[a] = z;
        //go to next move, record that there was a move
        f--;
        x++;
      }
      }
    }
    //go to next piece
    a++;
  }
  if (x > 0) {
    //if there was a legal move, enact the best one
    //c is the piece with the best moves, moves stores the possible moves for c, n stores how many moves c can make, d stores which of these was found to be the best
    int moves[4] = {0, 0, 0, 0};
    int n = options(c, moves, brd.piecesA, brd.piecesB, brd.kingsA, brd.kingsB, 1);
    if (brd.piecesB[c]%8 == moves[d]%8+2 || brd.piecesB[c]%8 == moves[d]%8-2) {
      //checks if the chosen move is a jump
      //i iterates through all the human's pieces
      int i = 0;
      while (i < 12) {
        if (brd.piecesA[i] == (moves[d]+brd.piecesB[c])/2) {
          //when the jumped piece is found, it is deleted
          brd.piecesA[i] = -1;
        } 
        i++;
      }
    }
    //the moved piece is moved
		std::cout << "My move from " << brd.piecesB[c] << " to " << moves[d] << std::endl;
    brd.piecesB[c] = moves[d];
    if (brd.piecesB[c] < 8) {
      //the moved piece is kinged if necessary
      brd.kingsB[c] = 1;
			std::cout << "it's king! " << brd.kingsB[c] << std::endl;
    }
  } else {
    //if there are no legal moves, the game ends
    a = 0;
    //q records what the end state is
    int q = 0;
    while (a < 12) {
      if (brd.piecesB[a] != -1) {
        //if any of the AI's pieces remain, q is set to 1
        //otherwise, q is 0
        q = 1;
      }
      a++;
    }
    a = 0;
    //this graually light up the board, with a color based on the end state
    while (a < 63) {
      int y = 0;
      while (y < 64) {
        //strip.setPixelColor(y, 0, a*2*(1-q), a*2*q);
        y++;
      }
      //strip.show();
      a++;
      //TODO: delay(20);
    } 
    //this restarts the game
    //TODO: reset();
  }
}
  

int AISelect (int pa[], int pb[], int ka[], int kb[], int left) {
  //returns how valuable the current board state, recorded by pa, pb, ka, and kb is.
  //runs only if the next move is the AI's
  //used to decide between possible moves for the ai
  //left tells it how far into the future to look
  if (left <= 0) {
    //this part is if it does not look into the future at all
    //a iterates through all piees, n records the total value of the board
    //add the difference in pieces between the two sides to the difference in kings. Positive numbers are good for the ai, negative numbers are good for the human
    int a = 0;
    int n = 0;
    while (a < 12) {
      if (pa[a] != -1) {
        n--;
        if (ka[a] == 1) {
          n--;
        }
      } if (pb[a] != -1) {
        n++;
        if (kb[a] == 1) {
          n++;
        }
      }
      a++;
    }
    return n;
  }
  //if it is to look into the future, it models each possible move for the ai, and evaluates the potential board state using modSelect. AISelect then returns the value of the best board state found.
  //a iterates through the AI's pieces, b stores the value of the best board state so far
  int a = 0;
  int b = -24;
  while (a < 12) {
    //iterating through each AI piece
    if (pb[a] != -1) {
      //if the piece still exists, look at the options
      //c records the options, d records the number of options, e records the current state of the moving piece, so the replica board can be reset, k stores if the current piece is a king, so the replica board can be reset.
      //f iterates through the possible moves
      int c[4] = {0, 0, 0, 0};
      int d = options(a, c, pa, pb, ka, kb, 1);
      int e = pb[a];
      int f = 0;
      int k = 0;
      while (f < d) {
        //looks at each possible move
        pb[a] = c[f];
        k = kb[a];
        if (pb[a] > 56) {
          //if necessary, kings the piece
          kb[a] = 1;
        }
        //check to see if any human pieces are jumped over
        //g stores where that piece is, h stores which piece was jumpted
        int g = 0;
        int h = -1;
        int j = -1;
        if (pb[a]%8 == e%8+2 || pb[a]%8 == e%8-2) {
          int i = 0;
          while (i < 12) {
            if (pa[i] == (e+pb[a])/2) {
              g = pa[i];
              pa[i] = -1;
              h = i;
            } i++;
          }
          //evaluates the boardstateof this move
          j = modSelect(pa, pb, ka, kb, left-1);
        }
        if (j < 0) {
          j = modSelect(pa, pb, ka, kb, left-2);
        }
        if (j > b) {
          b = j;
        }
        //resets the board to run again
        pb[a] = e;
        if (h >= 0) {
          pa[h] = g;
        }
        kb[a] = k;
        f++;
      }
    } a++;
  }
  return b;
}

int modSelect (int pa[], int pb[], int ka[], int kb[], int left) {
  //returns how valuable the current board state, recorded by pa, pb, ka, and kb is.
  //runs only if the next move is the Humans's
  //used to decide between possible moves for the ai
  //left tells it how far into the future to look
  if (left <= 0) {
    //a iterates through pieces, n ends up as the sum of difference in number of pieces and the number of kings between the two players
    int a = 0;
    int n = 0;
    while (a < 12) {
      if (pa[a] != -1) {
        n--;
        if (ka[a] == 1) {
          n--;
        }
      } if (pb[a] != -1) {
        n++;
        if (kb[a] == 1) {
          n++;
        }
      }
      a++;
    }
    return n;
  }
  //a iterates through the human's pieces, looking for the best move for the human. b evaluates how good the current best move is for the human
  int a = 0;
  int b = 24;
  while (a < 12) {
    if (pa[a] != -1) {
      //c stores all possible moves of the current moving piece, d counts how many moves there are, e stores where the current moving piece is so the replica board can be reset, f counts through moves, k stores whether the current moving piecde is a king so the replica board can be reset
      int c[4] = {0, 0, 0, 0};
      int d = options(a, c, pa, pb, ka, kb, -1);
      int e = pa[a];
      int f = 0;
      int k = 0;
      while (f < d) {
        //this iterates through possible moves for the current piece
        pa[a] = c[f];
        k = ka[a];
        if (pa[a] > 56) {
          ka[a] = 1;
        }
        //checking if an AI piece is jumped. If so, g stores where that piece is, h stores which piece it is
        int g = 0;
        int h = -1;
        int j = -1;
        if (pa[a]%8 == e%8+2 || pa[a]%8 == e%8-2) {
          int i = 0;
          while (i < 12) {
            if (pb[i] == (e+pa[a])/2) {
              g = pb[i];
              pb[i] = -1;
              h = i;
            } i++;
          }
          //evaluates how good the new boardstate is
          j = AISelect(pa, pb, ka, kb, left-1);
        }
        if (j < 0) {
          j = AISelect(pa, pb, ka, kb, left-2);
        }
        //compares to previous best board state, changes that to the new best board state if this is better
        if (j < b) {
          b = j;
        }
        //resets the replica board
        pa[a] = e;
        if (h >= 0) {
          pb[h] = g;
        }
        ka[a] = k;
        f++;
      }
    } a++;
  }
  return b;
}

void printLine(int ind, const Board & b)
{
	std::cout << "\u2503";

	if((ind % 2)) 
	{
		std::cout << "   ";
		std::cout << "\u2503";
	}

	for(int i = 0; i < 4; ++i)
	{
		switch(b.whoIsThere(ind*8 + i*2 + ind%2))
		{
			case Empty:
				std::cout << "   ";
				std::cout << "\u2503";
				break;
			case WhiteKing:
				std::cout << " @ ";
				std::cout << "\u2503";
				break;
			case BlackKing:
				std::cout << " H ";
				std::cout << "\u2503";
				break;
			case White:
				std::cout << " O ";
				std::cout << "\u2503";
				break;
			case Black:
				std::cout << " # ";
				std::cout << "\u2503";
				break;
		}
		
		if(i < 3) {
			std::cout << "   ";
			std::cout << "\u2503";
		}
	}
	if(!(ind % 2)) 
	{
		std::cout << "   ";
		std::cout << "\u2503";
	}
	
	std::cout << std::endl;
}

void printBoard(const Board & b)
{
	std::cout << std::endl << "\033[90m";

	std::cout << "  \u250F";
	for(int i = 0; i < 15; ++i)
	{
		std::cout << (!(i%2) ? "\u2501\u2501\u2501" : "\u2533");
	}
	std::cout << "\u2513";
	std::cout << std::endl;

	for(int i = 8; i > 0; --i)
	{
		std::cout << (char)('a'+ i - 1) << " ";
		printLine(i-1, b);	
		std::cout << "  ";
		std::cout << "\u2523";
		if(i < 7) {
			for(int i = 0; i < 15; ++i)
			{
				std::cout << (!(i%2) ? "\u2501\u2501\u2501" : "\u254b");
			}
			std::cout << "\u252B";
			std::cout << std::endl;
		}
		else
		{
			for(int i = 0; i < 15; ++i)
			{
				std::cout << (!(i%2) ? "\u2501\u2501\u2501" : "\u253B");
			}
			std::cout << "\u252B";
			std::cout << std::endl;

		}
	}
	std::cout << "  ";
	for(int i = 0; i < 8; ++i)
	{
		std::cout << "  " << i+1 << " ";
	}
	std::cout << std::endl;
}

/*
void loop () {
  if (part == 0) {
    x = map(analogRead(14), 0, 1024, 0, 12);
    //boardWriteChoose(x);
    if (digitalRead(INP) == LOW) {
      if (brd.piecesA[x] != -1) {
        part = 1;
        delay(500);
      }
    }
  } else {
    int k[4] = {0, 0, 0, 0};
    int n = options(x, k, brd.piecesA, brd.piecesB, brd.kingsA, brd.kingsB, -1);
    if (n == 0) {
      part = 0;
    } else {
			// x - from
			// y - to
      int y = map(analogRead(14), 0, 1024, 0, n);
      //boardWriteChoose(k[y]);
      if (digitalRead(INP) == LOW) {
        y = k[y];
        int m = 0;
        m = brd.piecesA[x];
        if (y%8 == m%8+1 || y%8 == m%8-1) {
          brd.piecesA[x] = y;
          if (y > 55) {
            brd.kingsA[x] = 1;
          }
        } else if (y%8 == m%8+2) {
          int a = 0;
          if (m < y) {
            while (a < 12) {
              if (brd.piecesB[a] == y-9) {
                brd.piecesB[a] = -1;
              }
              a++;
            }
          } else {
            while (a < 12) {
              if (brd.piecesB[a] == y+7) {
                brd.piecesB[a] = -1;
              } a++;
            }
          }
          brd.piecesA[x] = y;
          if (y > 55) {
            brd.kingsA[x] = 1;
          }
        }  else if (y%8 == m%8-2) {
          int a = 0;
          if (m < y) { 
            while (a < 12) {
              if (brd.piecesB[a] == y-7) {
                brd.piecesB[a] = -1;
              }
              a++;
            }
          } else {
            while (a < 12) {
              if (brd.piecesB[a] == y+9) {
                brd.piecesB[a] = -1;
              }
              a++;
            }
          }
          brd.piecesA[x] = y;
          if (y > 55) {
            brd.kingsA[x] = 1;
          }
        } 
        part = 0;
        StartSelect();
      }
    }
  }
}*/

#include <vector>

int main(void) 
{
	Board brd;

	std::string in;

	std::cout << "Hi, let's play!" << std::endl;
	std::cout << "Enter your move" << std::endl << "> ";

	printBoard(brd);

	while (getline(std::cin, in)) 
	{
		printBoard(brd);
		std::cout << std::endl << "your move:" << in << std::endl;
		

		const char * str = in.c_str();

		int from = (str[0]-'a')*8 + str[1] - '1';
		int to = (str[2]-'a')*8 + str[3] - '1';
		std::vector<int> remove;

		for(int i = 0; i < (in.size()-4)/2; ++i)
		{
			remove.push_back((str[i+4]-'a')*8 + str[i+1+4] - '1');
		}

		std::cout << "you move from " << from << " to " << to << ", you fight ";
		for(int a: remove)
		{
			std::cout << a << " ";
		}
		std::cout << std::endl;

		if(from >= 0 && from < 64 && to >= 0 && to < 64) {
			for(int i = 0; i < 12; ++i) {
				if(brd.piecesA[i] == from) {
					brd.piecesA[i] = to;
				}
			}
			for(int a: remove) 
			{
				for(int i = 0; i < 12; ++i) {
					if(brd.piecesB[i] == a) {
						brd.piecesB[i] = -1;
					}
				}
			}
				
			StartSelect(brd);
			printBoard(brd);
		} else {
			std::cout << "wrong cmd ( try again" << std::endl;
			continue;
		}
	}

	return 0;
}
