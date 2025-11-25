#include <cstring>
#include "position.h"
#include "tables.h"
#include "types.h"
#include "eval.h"
#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>

// Infinity value for alpha-beta search
const int INF = 1000000;

// Forward declarations for template functions (required due to cross-references)
template<unsigned int depth>
int alphaBetaMin(Position &pos, int alpha, int beta);

template<unsigned int depth>
int alphaBetaMax(Position &pos, int alpha, int beta);

/**
 * Alpha-Beta search for maximizing player (WHITE)
 * @param pos Current position
 * @param alpha Best value the maximizer can guarantee
 * @param beta Best value the minimizer can guarantee
 * @return Evaluation score
 */
template<unsigned int depth>
int alphaBetaMax(Position &pos, int alpha, int beta) {
    MoveList<WHITE> legals(pos);
    if (legals.size() == 0) {
        // Checkmate or stalemate detection
        if (pos.in_check<WHITE>()) return -INF;
        return std::max(alpha, eval(pos));
    }
    int score = -INF;
    for (Move move : legals) {
        pos.play<WHITE>(move);
        score = std::max(score, alphaBetaMin<depth-1>(pos, alpha, beta));
        pos.undo<WHITE>(move); 
        alpha = std::max(alpha, score);
        if (beta <= alpha) break;  // Beta cutoff
    }
    return score;
}

// Base case: depth 0, just return evaluation
template<>
int alphaBetaMax<0U>(Position &pos, int /*alpha*/, int /*beta*/) {
    return eval(pos); 
}

/**
 * Alpha-Beta search for minimizing player (BLACK)
 * @param pos Current position
 * @param alpha Best value the maximizer can guarantee
 * @param beta Best value the minimizer can guarantee
 * @return Evaluation score
 */
template<unsigned int depth>
int alphaBetaMin(Position &pos, int alpha, int beta) {
    MoveList<BLACK> legals(pos);
    if (legals.size() == 0) {
        // Checkmate or stalemate detection
        if (pos.in_check<BLACK>()) return INF;
        return std::min(beta, eval(pos));
    }
    int score = INF;
    for (Move move : legals) {
        pos.play<BLACK>(move);
        score = std::min(score, alphaBetaMax<depth-1>(pos, alpha, beta));
        pos.undo<BLACK>(move);
        beta = std::min(beta, score);
        if (beta <= alpha) break;  // Alpha cutoff
    }
    return score;
}

// Base case: depth 0, just return evaluation
template<>
int alphaBetaMin<0U>(Position &pos, int /*alpha*/, int /*beta*/) {
    return eval(pos);
}

/**
 * Find the best move for the current position
 * @param pos Current position
 * @return Best move found at the given search depth
 */
template<unsigned int depth>
Move getBestMove(Position &pos) {
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
            if (score < bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }
    }
    return bestMove;
}

/**
 * Main entry point for the chess bot
 * Usage: chessbot <depth> <FEN>
 */
int main(int argc, char **argv) {
    // Initialize all lookup tables
    initialise_all_databases();
    zobrist::initialise_zobrist_keys();
    init_eval_tables();

    // Validate command line arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <depth> <fen>" << std::endl;
        return 1;
    }
    
    int depth = std::stoi(argv[1]);
    std::string fen = argv[2];
    
    // Create and set up position
    Position pos;
    Position::set(fen, pos);
    std::cout << "Set fen: " << pos.fen() << std::endl;
    
    // Find best move at the specified depth
    Move bestMove;
    switch(depth) {
        case 0:  bestMove = getBestMove<0>(pos);  break;
        case 1:  bestMove = getBestMove<1>(pos);  break;
        case 2:  bestMove = getBestMove<2>(pos);  break;
        case 3:  bestMove = getBestMove<3>(pos);  break;
        case 4:  bestMove = getBestMove<4>(pos);  break;
        case 5:  bestMove = getBestMove<5>(pos);  break;
        case 6:  bestMove = getBestMove<6>(pos);  break;
        case 7:  bestMove = getBestMove<7>(pos);  break;
        case 8:  bestMove = getBestMove<8>(pos);  break;
        case 9:  bestMove = getBestMove<9>(pos);  break;
        case 10: bestMove = getBestMove<10>(pos); break;
        default:
            std::cout << "Error: depth must be between 0 and 10" << std::endl;
            return 1;
    }
    
    // Apply the best move
    switch(pos.turn()) {
        case WHITE: pos.play<WHITE>(bestMove); break;
        case BLACK: pos.play<BLACK>(bestMove); break;
    }
    
    // Output the resulting position
    std::cout << pos.fen() << std::endl;
    
    return 0;
}