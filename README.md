# Chess Game

Chess Game is a complete chess implementation in C++, featuring piece movement logic, official rules, and game state management.

## Key Features

- Full chess engine with official rules (castling, check, checkmate, stalemate, promotion, en passant).
- Support for input and output using FEN notation.
- Designed for scalability and maintainability by applying multiple design patterns, including:  
  - **Strategy** for piece movement logic  
  - **Command** for move execution and undo  
  - **State** for managing game and UI states  
  - **Factory** for creating chess pieces  
  - **Flyweight** to efficiently share movement strategies  
  - **Composite** for board and cell hierarchy  
  - **MVC (Model-View-Controller)** architecture for clear separation of concerns
- Text-based console interface for gameplay.
- Modular and extensible for easy future improvements.

## Requirements

- C++14 compatible compiler.  
- Text console environment.

## Build and Run

```bash
mkdir build
cd build
cmake ..
make
./ChessGame
```

## Usage
Run the game and follow on-screen instructions to play a complete chess match.

## License
MIT License – see LICENSE file for details.
