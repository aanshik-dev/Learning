import sys

def print_board(board):
    for i, row in enumerate(board):
        print(f" {row[0]} | {row[1]} | {row[2]} ")
        if i < 2:
            print("-----------")

def check_winner(board):
    for i in range(3):
        if board[i][0] == board[i][1] == board[i][2] != ' ':
            return board[i][0]
        if board[0][i] == board[1][i] == board[2][i] != ' ':
            return board[0][i]
    if board[0][0] == board[1][1] == board[2][2] != ' ':
        return board[0][0]
    if board[0][2] == board[1][1] == board[2][0] != ' ':
        return board[0][2]
    
    if all(cell != ' ' for row in board for cell in row):
        return 'draw'
    return None

def minimax(board, is_maximizing):
    res = check_winner(board)
    if res == 'X': return 1
    if res == '0': return -1
    if res == 'draw': return 0

    if is_maximizing:
        best_score = -float('inf')
        for r in range(3):
            for c in range(3):
                if board[r][c] == ' ':
                    board[r][c] = 'X'
                    score = minimax(board, False)
                    board[r][c] = ' '
                    best_score = max(score, best_score)
        return best_score
    else:
        best_score = float('inf')
        for r in range(3):
            for c in range(3):
                if board[r][c] == ' ':
                    board[r][c] = '0'
                    score = minimax(board, True)
                    board[r][c] = ' '
                    best_score = min(score, best_score)
        return best_score

def get_best_move(board, player):
    best_move = None
    if player == 'X':
        best_score = -float('inf')
        for r in range(3):
            for c in range(3):
                if board[r][c] == ' ':
                    board[r][c] = 'X'
                    score = minimax(board, False)
                    board[r][c] = ' '
                    if score > best_score:
                        best_score = score
                        best_move = (r, c)
    else:
        best_score = float('inf')
        for r in range(3):
            for c in range(3):
                if board[r][c] == ' ':
                    board[r][c] = '0'
                    score = minimax(board, True)
                    board[r][c] = ' '
                    if score < best_score:
                        best_score = score
                        best_move = (r, c)
    return best_move


print("Welcome to Tic-Tac-Toe!")
user_symbol = input("Do you want to play as X or 0? ").strip().upper()
while user_symbol not in ['X', '0']:
    user_symbol = input("Invalid choice. Choose X or 0: ").strip().upper()
ai_symbol = '0' if user_symbol == 'X' else 'X'
board = [[' ' for _ in range(3)] for _ in range(3)]
current_player = 'X'
while True:
    print("\nCurrent board:")
    print_board(board)
    
    winner = check_winner(board)
    if winner:
        if winner == 'draw':
            print("It's a draw!")
        else:
            print(f"{winner} wins!")
        break
    if current_player == user_symbol:
        while True:
            try:
                move_input = input("Enter your move (row column): ").split()
                if len(move_input) != 2:
                    raise ValueError("Enter exactly two integers.")
                r, c = int(move_input[0]) - 1, int(move_input[1]) - 1
                if not (0 <= r <= 2 and 0 <= c <= 2):
                    raise ValueError("Out of bounds.")
                if board[r][c] != ' ':
                    raise ValueError("Cell occupied.")
                board[r][c] = user_symbol
                break
            except ValueError as e:
                print(f"Invalid input: {e}")
    else:
        r, c = get_best_move(board, ai_symbol)
        board[r][c] = ai_symbol
        print(f"AI plays at ({r+1}, {c+1})")
    current_player = '0' if current_player == 'X' else 'X'


