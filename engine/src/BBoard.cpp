// Board.cpp
#include <string>
#include <climits>

#include "BBoard.h"


#ifdef _WIN32
int __builtin_ffsll(unsigned long long x) {
    if (x == 0) {
        return 0;  // No bits set
    }

    int position = 1;
    while ((x & 1) == 0) {
        x >>= 1;
        position++;
    }
    return position;
}
#endif

namespace BBoard {

    // Generation
    BBOARD fromIdx(int idx) {
        return 1ULL << idx;
    }
    BBOARD fromRank(int idx) {
        return BBoard::rank1 << (8*idx);
    }
    BBOARD fromFile(int idx) {
        return BBoard::file1 << idx;
    }
    BBOARD LS1B(BBOARD board) {
        return board & -board;
    }

    // Mutation
    BBOARD resetLS1B(BBOARD board) {
        return board & (board - 1);
    }
    BBOARD popLS1B(BBOARD* board) {
        if ( !*board ) return static_cast<BBOARD>(0);
        BBOARD ls1 = LS1B(*board);
        *board = resetLS1B(*board);
        return ls1;
    }
    BBOARD shiftN(BBOARD board) {
        return board << 8;
    }
    // BBOARD shiftNE(BBOARD board) {}
    // BBOARD shiftE(BBOARD board) {}
    // BBOARD shiftSE(BBOARD board) {}
    // BBOARD shiftS(BBOARD board) {}
    // BBOARD shiftSW(BBOARD board) {}
    // BBOARD shiftW(BBOARD board) {}
    // BBOARD shiftNW(BBOARD board) {}

    // Eval
    int MS1Idx(BBOARD board) {
        int result = 0;
        while ( board ) {
            result = LS1Idx(popLS1B(&board));
        }
        return result;
    }
    int LS1Idx(BBOARD board) {
        // Many thanks to https://stackoverflow.com/a/21439175
        return __builtin_ffsll( board ) - 1;
    }
    bool isEmpty(BBOARD board) {
        return board == 0;
    }
    bool isSinglyOccupied(BBOARD board) {
        return board != 0 && (board & (board-1)) == 0;
    }
    int popCount(BBOARD board) {
        int count = 0;
        while ( board ) {
            count++; 
            board &= (board - 1);
        }
        return count;
    }

    // Rendering
    std::string toString(BBOARD board) {
        return toString(board, "1");
    }
    std::string toString(BBOARD board, std::string fill) {
        std::string output = "";
        for ( int i = 7; i >= 0; i-- ) {
            for ( int j = 0; j < 8; j++ ) {
                int idx = 8*i + j; 
                if ( (board >> idx) & 1 ) {
                    output.append(fill);
                } else {
                    output.append(".");
                }
                output.append(" ");
            }
            output.append("\n");
        }

        return output;
    }

}
