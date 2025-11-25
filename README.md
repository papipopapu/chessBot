# ChessBot

A chess engine implementation using bitboard representation and alpha-beta pruning search algorithm.

## Features

- **Bitboard Representation**: Efficient 64-bit board representation for fast move generation
- **Magic Bitboards**: Pre-computed sliding piece attacks using magic multiplication
- **Alpha-Beta Search**: Minimax algorithm with alpha-beta pruning
- **PeSTO Evaluation**: Piece-square tables for position evaluation
- **FEN Support**: Parse and output positions in Forsyth-Edwards Notation

## Project Structure

```
chessBot/
├── CMakeLists.txt      # CMake build configuration
├── README.md           # This file
├── .gitignore          # Git ignore rules
└── core/               # Source code
    ├── bot.cpp         # Main entry point and search algorithm
    ├── position.h      # Position class and move generation
    ├── position.cpp    # Position implementation
    ├── tables.h        # Lookup tables declarations
    ├── tables.cpp      # Magic bitboard tables and initialization
    ├── types.h         # Type definitions (pieces, squares, moves)
    ├── types.cpp       # Type implementations
    └── eval.h          # Position evaluation (PeSTO tables)
```

## Building

### Requirements

- CMake 3.14 or higher
- C++17 compatible compiler (GCC, Clang, MSVC)

### Build Instructions

```bash
# Create build directory
mkdir build && cd build

# Configure
cmake ..

# Build
cmake --build .

# The executable will be in build/bin/chessbot
```

## Usage

```bash
./chessbot <depth> "<FEN>"
```

### Parameters

- `depth`: Search depth (0-10). Higher values produce stronger play but take longer.
- `FEN`: Chess position in Forsyth-Edwards Notation.

### Example

```bash
# Starting position with depth 4
./chessbot 4 "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

# Specific position
./chessbot 3 "r1bqkb1r/pppp1ppp/2n2n2/4p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 1"
```

**Note**: The FEN string must include all 6 fields: piece placement, side to move, castling rights, en passant square, halfmove clock, and fullmove number.

## Technical Details

### Move Generation

The engine uses legal move generation with:
- Pre-computed attack tables for leaping pieces (knights, kings)
- Magic bitboard technique for sliding pieces (bishops, rooks, queens)
- Special handling for en passant, castling, and promotions

### Search Algorithm

- Alpha-beta pruning to reduce the search tree
- Template-based depth implementation for compile-time optimization

### Evaluation

Uses PeSTO (Piece-Square Tables Only) evaluation:
- Separate middlegame and endgame piece-square tables
- Tapered evaluation based on game phase

## License

This project is provided as-is for educational purposes.
