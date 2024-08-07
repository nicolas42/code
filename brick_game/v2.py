import random

# Constants for the board size
WIDTH = 10
HEIGHT = 20

# Representation of Tetriminos
Tetriminos = {
    'I': [(0,1), (1,1), (2,1), (3,1)],
    'O': [(0,0), (0,1), (1,0), (1,1)],
    'T': [(1,0), (0,1), (1,1), (2,1)],
    'S': [(0,1), (1,1), (1,0), (2,0)],
    'Z': [(0,0), (1,0), (1,1), (2,1)],
    'J': [(0,1), (1,1), (2,1), (2,0)],
    'L': [(0,1), (1,1), (2,1), (2,2)]
}

# Initialize the board
board = [[0] * WIDTH for _ in range(HEIGHT)]

def spawn_tetrimino():
    tetrimino = random.choice(list(Tetriminos.values()))
    position = (0, WIDTH // 2)  # Starting position at the middle of the board top
    return tetrimino, position

def valid_position(tetrimino, position):
    x, y = position
    for dx, dy in tetrimino:
        nx, ny = x + dx, y + dy
        if nx >= HEIGHT or ny >= WIDTH or ny < 0 or board[nx][ny] != 0:
            return False
    return True

def place_tetrimino(tetrimino, position):
    x, y = position
    for dx, dy in tetrimino:
        board[x + dx][y + dy] = 1  # Replace 1 with different numbers for different colors

def print_board():
    for row in board:
        print(' '.join(str(x) for x in row))

# Example usage
tetrimino, position = spawn_tetrimino()
if valid_position(tetrimino, position):
    place_tetrimino(tetrimino, position)
print_board()
