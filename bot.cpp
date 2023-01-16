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
            std::cout << move << " " << score << std::endl;
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
            std::cout << move << " " << score << std::endl;
            if (score < bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }
    }
    return bestMove;
}

int main() {
    




    // program that recieves a fen string, and a depth and returns the eval by the model_ser_mid.json
    initialise_all_databases();
	zobrist::initialise_zobrist_keys();
    init_eval_tables();

    std::string input;
    int depth;
    Move engine_move;
    Position pos;
    
    for (;;) {

        std::cin.clear();
        std::cin.sync();
        std::string depth_str;
        std::cout << "Input (fen): ";
        std::getline(std::cin, input);
        
        if (input == "quit") {
            break;
        }  else {
            Position::set(input, pos); // this function is not well implemented
            std::cout << "Depth: ";
            std::getline(std::cin, input);
            depth = std::stoi(input);
            switch (depth) {
            case 0:
            engine_move = getBestMove<0U>(pos);
            break;
            case 1:
            engine_move = getBestMove<1U>(pos);
            break;
            case 2:
            engine_move = getBestMove<2U>(pos);
            break;
            case 3:
            engine_move = getBestMove<3U>(pos);
            break;
            case 4:
            engine_move = getBestMove<4U>(pos);
            break;
            case 5:
            engine_move = getBestMove<5U>(pos);
            break;
            case 6:
            engine_move = getBestMove<6U>(pos);
            break;
            case 7:
            engine_move = getBestMove<6U>(pos);
            break;
            case 8:
            engine_move = getBestMove<8U>(pos);
            break;
            case 9:
            engine_move = getBestMove<9U>(pos);
            break;
            case 10:
            engine_move = getBestMove<10U>(pos);
            break;
            default:
            std::cout << "too deep!"<< std::endl;
            }     
            if (pos.turn() == WHITE) {pos.play<WHITE>(engine_move);}
            else {pos.play<BLACK>(engine_move);}
            std::cout << "Best move: " << engine_move << std::endl;

        }

        

    }
    return 0;
}