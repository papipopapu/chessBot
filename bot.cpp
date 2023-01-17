#include <cstring>
#include "position.h"
#include "tables.h"
#include "types.h"
#include "eval.h"
#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>
const int INF = 1000000;

template<unsigned int depth>
int alphaBetaMax(Position &pos, int alpha, int beta ) {
    MoveList<WHITE> legals(pos);
    if (legals.size() == 0) {
        // we include checkmate here
        if (pos.in_check<WHITE>()) return -INF;
        return std::max(alpha, eval(pos));
    }
    int score = -INF;
    for (Move move : legals) {
        pos.play<WHITE>(move);
        score = std::max(score, alphaBetaMin<depth-1>(pos, alpha, beta)); // busca entre todos los movimientos del opononenete el que mas le beneficia
        pos.undo<WHITE>(move); 
        alpha = std::max(alpha, score);
        if (beta <= alpha) break; 
    }

    return score;
}
template<>
int alphaBetaMax<0U>(Position &pos, int alpha, int beta ) {
    return eval(pos); 
}
template<unsigned int depth>
int alphaBetaMin(Position &pos, int alpha, int beta ) {
    MoveList<BLACK> legals(pos);
    if (legals.size() == 0) {
        // we include checkmate here
        if (pos.in_check<BLACK>()) return INF;
        return std::min(beta, eval(pos));
    }
    int score = INF;
    for (Move move : legals) {
        pos.play<BLACK>(move);
        score = std::min(score, alphaBetaMax<depth-1>(pos, alpha, beta ));
        pos.undo<BLACK>(move);
        beta = std::min(beta, score);
        if (beta <= alpha) break; 
    }
    return score;
}
template<>
int alphaBetaMin<0U>(Position &pos, int alpha, int beta ) {
    return eval(pos);
}


template<unsigned int depth>
Move getBestMove(Position &pos) { // profundidad minima es 1, pero se le asigna depth 0
    int bestScore, score;
    Move bestMove;
    if (pos.turn() == WHITE) {
        bestScore = -INF;
        MoveList<WHITE> legals(pos);
        if (legals.size() == 0) {
            std::cout << "End of game!" << std::endl;
            exit(0);
        }
        for (Move move : legals) {
            pos.play<WHITE>(move);
            score = alphaBetaMin<depth>(pos, bestScore, INF);
            pos.undo<WHITE>(move);
            // print move and score
            // std::cout << move << " " << score << std::endl;
            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }
    } else {
        bestScore = INF;
        MoveList<BLACK> legals(pos);
        if (legals.size() == 0) {
            std::cout << "End of game!" << std::endl;
            exit(0);
        }
        for (Move move : legals) {
            pos.play<BLACK>(move);
            score = alphaBetaMax<depth>(pos, -INF, bestScore);
            pos.undo<BLACK>(move);
            //std::cout << move << " " << score << std::endl;
            if (score < bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }
    }
    return bestMove;
}

int main(int argc, char **argv) {
    // fen returned by library is shit
    // receive depth and fen from command line, return fen after making
    // best move
    initialise_all_databases();
	zobrist::initialise_zobrist_keys();
    init_eval_tables();

    // check commmand line arguments are correct
    if (argc != 3) {
        std::cout << "Usage: ./bot <depth> <fen>" << std::endl;
        return 1;
    }
    int depth = std::stoi(argv[1]);
    std::string fen = argv[2];
    
    // create position object
    Position pos;
    Position::set(fen, pos);
    Move bestMove;
    // get best move
   switch(depth) {
        case 0:
            bestMove = getBestMove<0>(pos);
            break;
        case 1:
            bestMove = getBestMove<1>(pos);
            break;
        case 2:
            bestMove = getBestMove<2>(pos);
            break;
        case 3:
            bestMove = getBestMove<3>(pos);
            break;
        case 4:
            bestMove = getBestMove<4>(pos);
            break;
        case 5:
            bestMove = getBestMove<5>(pos);
            break;
        case 6:
            bestMove = getBestMove<6>(pos);
            break;
        case 7:
            bestMove = getBestMove<7>(pos);
            break;
        case 8:
            bestMove = getBestMove<8>(pos);
            break;
        case 9:
            bestMove = getBestMove<9>(pos);
            break;
        case 10:
            bestMove = getBestMove<10>(pos);
            break;
   }
   switch(pos.turn()) {
        case WHITE:
            pos.play<WHITE>(bestMove);
            break;
        case BLACK:
            pos.play<BLACK>(bestMove);
            break;
   }
    std::cout << pos.fen() << std::endl;

   
    return 0;
}