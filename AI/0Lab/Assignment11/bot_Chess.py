import os
import pygame
import chess
import random
import sys
import time
import math

# Constants for the board dimensions and colors
WIDTH = HEIGHT = 640  # Board size in pixels (8x8 squares)
SQ_SIZE = WIDTH // 8
FPS = 15

# Colors for the squares
LIGHT_COLOR = (240, 217, 181)
DARK_COLOR = (181, 136, 99)
HIGHLIGHT_COLOR = (186, 202, 68)
MOVE_HIGHLIGHT_COLOR = (170, 200, 100)  # Color for highlighting possible moves

# Piece square tables for positional evaluation
# These tables give bonus/penalty for pieces on specific squares
PAWN_TABLE = [
    0,  0,  0,  0,  0,  0,  0,  0,
    5, 10, 10,-20,-20, 10, 10,  5,
    2,  4,  8, 12, 12,  8,  4,  2,
    0,  2,  4,  8,  8,  4,  2,  0,
    0,  0,  2,  6,  6,  2,  0,  0,
    0,  0,  0,  2,  2,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0
]

KNIGHT_TABLE = [
    -5, -4, -3, -2, -2, -3, -4, -5,
    -4, -2,  0,  1,  1,  0, -2, -4,
    -3,  1,  2,  3,  3,  2,  1, -3,
    -2,  1,  3,  4,  4,  3,  1, -2,
    -2,  1,  3,  4,  4,  3,  1, -2,
    -3,  1,  2,  3,  3,  2,  1, -3,
    -4, -2,  0,  1,  1,  0, -2, -4,
    -5, -4, -3, -2, -2, -3, -4, -5
]

BISHOP_TABLE = [
    -2, -1, -1, -1, -1, -1, -1, -2,
    -1,  0,  0,  0,  0,  0,  0, -1,
    -1,  0,  1,  2,  2,  1,  0, -1,
    -1,  1,  2,  3,  3,  2,  1, -1,
    -1,  1,  2,  3,  3,  2,  1, -1,
    -1,  0,  1,  2,  2,  1,  0, -1,
    -1,  0,  0,  0,  0,  0,  0, -1,
    -2, -1, -1, -1, -1, -1, -1, -2
]

ROOK_TABLE = [
    0,  0,  1,  2,  2,  1,  0,  0,
    0,  0,  1,  2,  2,  1,  0,  0,
    0,  0,  1,  2,  2,  1,  0,  0,
    0,  0,  1,  2,  2,  1,  0,  0,
    0,  0,  1,  2,  2,  1,  0,  0,
    0,  0,  1,  2,  2,  1,  0,  0,
    0,  0,  1,  2,  2,  1,  0,  0,
    0,  0,  1,  2,  2,  1,  0,  0
]

QUEEN_TABLE = [
    -2, -1, -1,  0,  0, -1, -1, -2,
    -1,  0,  0,  1,  1,  0,  0, -1,
    -1,  0,  1,  2,  2,  1,  0, -1,
    0,  1,  2,  3,  3,  2,  1,  0,
    0,  1,  2,  3,  3,  2,  1,  0,
    -1,  0,  1,  2,  2,  1,  0, -1,
    -1,  0,  0,  1,  1,  0,  0, -1,
    -2, -1, -1,  0,  0, -1, -1, -2
]

KING_MIDDLE_TABLE = [
    -3, -4, -4, -5, -5, -4, -4, -3,
    -3, -4, -4, -5, -5, -4, -4, -3,
    -3, -4, -4, -5, -5, -4, -4, -3,
    -3, -4, -4, -5, -5, -4, -4, -3,
    -2, -3, -3, -4, -4, -3, -3, -2,
    -1, -2, -2, -2, -2, -2, -2, -1,
    1,  1,  0,  0,  0,  0,  1,  1,
    2,  3,  1,  0,  0,  1,  3,  2
]

# Material weights
PIECE_VALUES = {
    chess.PAWN: 100,
    chess.KNIGHT: 320,
    chess.BISHOP: 330,
    chess.ROOK: 500,
    chess.QUEEN: 900,
    chess.KING: 20000  # King value for checkmate detection
}

# Global dictionary to store images
IMAGES = {}











BASE_DIR = os.path.dirname(os.path.abspath(__file__))

def load_images():
    pieces = {
        "P": "white-pawn.png",
        "N": "white-knight.png",
        "B": "white-bishop.png",
        "R": "white-rook.png",
        "Q": "white-queen.png",
        "K": "white-king.png",
        "p": "black-pawn.png",
        "n": "black-knight.png",
        "b": "black-bishop.png",
        "r": "black-rook.png",
        "q": "black-queen.png",
        "k": "black-king.png"
    }

    for symbol, filename in pieces.items():
        path = os.path.join(BASE_DIR, "Chess_engine", "images", filename)
        image = pygame.image.load(path)
        IMAGES[symbol] = pygame.transform.scale(image, (SQ_SIZE, SQ_SIZE))


def get_piece_square_value(piece, square, is_middlegame=True):
    """
    Get positional value for a piece on a specific square.
    Returns 0 if no positional table exists for the piece.
    """
    # For black pieces, mirror the square index
    if piece.color == chess.BLACK:
        square = chess.square_mirror(square)
    
    piece_type = piece.piece_type
    
    if piece_type == chess.PAWN:
        return PAWN_TABLE[square]
    elif piece_type == chess.KNIGHT:
        return KNIGHT_TABLE[square]
    elif piece_type == chess.BISHOP:
        return BISHOP_TABLE[square]
    elif piece_type == chess.ROOK:
        return ROOK_TABLE[square]
    elif piece_type == chess.QUEEN:
        return QUEEN_TABLE[square]
    elif piece_type == chess.KING:
        return KING_MIDDLE_TABLE[square] if is_middlegame else 0
    
    return 0

def evaluate_board(board):
    """
    Evaluate the board state from White's perspective.
    Positive score favors White, negative favors Black.
    """
    if board.is_checkmate():
        # If the current player is in checkmate, they lose
        return -20000 if board.turn == chess.WHITE else 20000
    
    if board.is_stalemate() or board.is_insufficient_material():
        return 0  # Draw
    
    score = 0
    total_pieces = 0
    total_pawns = 0
    
    # Evaluate material and position for each piece
    for square in chess.SQUARES:
        piece = board.piece_at(square)
        if piece:
            total_pieces += 1
            if piece.piece_type == chess.PAWN:
                total_pawns += 1
            
            # Material value
            value = PIECE_VALUES[piece.piece_type]
            
            # Positional value
            # Determine if it's middlegame (more pieces on board)
            is_middlegame = total_pieces > 10
            positional_value = get_piece_square_value(piece, square, is_middlegame)
            
            # Combine material and positional value
            piece_score = value + positional_value
            
            # Add or subtract based on piece color
            if piece.color == chess.WHITE:
                score += piece_score
            else:
                score -= piece_score
    
    # Add small bonus for having the move
    if board.turn == chess.WHITE:
        score += 5
    else:
        score -= 5
    
    return score

def order_moves(board, moves):
    """
    Order moves to improve alpha-beta pruning efficiency.
    Captures and checks are evaluated first.
    """
    def move_score(move):
        score = 0
        # Prioritize captures (MVV-LVA - Most Valuable Victim - Least Valuable Aggressor)
        if board.is_capture(move):
            victim = board.piece_at(move.to_square)
            if victim:
                attacker = board.piece_at(move.from_square)
                if attacker:
                    # Value of victim minus value of attacker
                    score = PIECE_VALUES[victim.piece_type] - PIECE_VALUES[attacker.piece_type] / 100
                else:
                    score = PIECE_VALUES[victim.piece_type]
        
        # Prioritize promotions
        if move.promotion:
            score += PIECE_VALUES[move.promotion]
        
        # Prioritize checks (rough estimate)
        board.push(move)
        if board.is_check():
            score += 50
        board.pop()
        
        return score
    
    return sorted(moves, key=move_score, reverse=True)

def minimax(board, depth, alpha, beta, maximizing_player, ai_is_white):
    """
    Minimax algorithm with alpha-beta pruning.
    Returns the best evaluation score.
    """
    if depth == 0 or board.is_game_over():
        return evaluate_board(board)
    
    if maximizing_player:
        max_eval = -math.inf
        moves = order_moves(board, list(board.legal_moves))
        
        for move in moves:
            board.push(move)
            eval = minimax(board, depth - 1, alpha, beta, False, ai_is_white)
            board.pop()
            
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:
                break  # Beta cutoff
        
        return max_eval
    else:
        min_eval = math.inf
        moves = order_moves(board, list(board.legal_moves))
        
        for move in moves:
            board.push(move)
            eval = minimax(board, depth - 1, alpha, beta, True, ai_is_white)
            board.pop()
            
            min_eval = min(min_eval, eval)
            beta = min(beta, eval)
            if beta <= alpha:
                break  # Alpha cutoff
        
        return min_eval

def get_best_move(board, depth, ai_is_white):
    """
    Find the best move for the AI using minimax with alpha-beta pruning.
    """
    best_move = None
    best_value = -math.inf if ai_is_white else math.inf
    
    moves = order_moves(board, list(board.legal_moves))
    
    for move in moves:
        board.push(move)
        if ai_is_white:
            # AI plays as White (maximizing)
            move_value = minimax(board, depth - 1, -math.inf, math.inf, False, ai_is_white)
            if move_value > best_value:
                best_value = move_value
                best_move = move
        else:
            # AI plays as Black (minimizing)
            move_value = minimax(board, depth - 1, -math.inf, math.inf, True, ai_is_white)
            if move_value < best_value:
                best_value = move_value
                best_move = move
        board.pop()
    
    return best_move

def draw_board(screen, flip_board, selected_sq, possible_moves):
    """
    Draw the chess board with optional highlight for the selected square and possible moves.
    """
    for rank in range(8):
        for file in range(8):
            # Adjust square positions if board is flipped.
            draw_file = file if not flip_board else 7 - file
            draw_rank = rank if not flip_board else 7 - rank

            x = draw_file * SQ_SIZE
            y = (7 - draw_rank) * SQ_SIZE

            color = LIGHT_COLOR if (file + rank) % 2 == 0 else DARK_COLOR
            rect = pygame.Rect(x, y, SQ_SIZE, SQ_SIZE)
            pygame.draw.rect(screen, color, rect)

            # Highlight possible moves for the selected square
            if selected_sq is not None and possible_moves:
                current_square = chess.square(file, rank)
                if current_square in possible_moves:
                    highlight_rect = pygame.Rect(x, y, SQ_SIZE, SQ_SIZE)
                    pygame.draw.rect(screen, MOVE_HIGHLIGHT_COLOR, highlight_rect, 4)
            
            # Highlight the selected square if applicable.
            if selected_sq is not None:
                sel_file = chess.square_file(selected_sq)
                sel_rank = chess.square_rank(selected_sq)
                if flip_board:
                    sel_file = 7 - sel_file
                    sel_rank = 7 - sel_rank
                if sel_file == file and sel_rank == rank:
                    pygame.draw.rect(screen, HIGHLIGHT_COLOR, rect, 5)

def draw_pieces(screen, board, flip_board):
    """
    Draw all pieces on the board based on the current board state.
    """
    for square in chess.SQUARES:
        piece = board.piece_at(square)
        if piece:
            file = chess.square_file(square)
            rank = chess.square_rank(square)
            if flip_board:
                file = 7 - file
                rank = 7 - rank
            x = file * SQ_SIZE
            y = (7 - rank) * SQ_SIZE
            symbol = piece.symbol()
            screen.blit(IMAGES[symbol], pygame.Rect(x, y, SQ_SIZE, SQ_SIZE))

def get_square_from_mouse(pos, flip_board):
    """
    Convert the mouse position (x, y) to a chess square index.
    """
    x, y = pos
    file = x // SQ_SIZE
    rank = 7 - (y // SQ_SIZE)
    if flip_board:
        file = 7 - file
        rank = 7 - rank
    # Ensure file and rank are within bounds
    file = max(0, min(7, file))
    rank = max(0, min(7, rank))
    return chess.square(file, rank)

def get_valid_moves_from_square(board, square, human_is_white):
    """
    Get all valid moves from a selected square for the human player.
    """
    piece = board.piece_at(square)
    if not piece:
        return []
    
    # Check if the piece belongs to the human player
    if (piece.color == chess.WHITE and not human_is_white) or (piece.color == chess.BLACK and human_is_white):
        return []
    
    valid_moves = []
    for move in board.legal_moves:
        if move.from_square == square:
            valid_moves.append(move.to_square)
    
    return valid_moves

def get_promotion_move(from_sq, to_sq):
    """
    Create a promotion move (default to Queen).
    """
    return chess.Move(from_sq, to_sq, promotion=chess.QUEEN)

def main():
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("Chess Game: Human vs. AI (Minimax with Alpha-Beta)")
    clock = pygame.time.Clock()
    load_images()

    board = chess.Board()

    # Ask the player to choose a color
    print("Welcome to Chess!")
    print("You'll be playing against an AI using Minimax with Alpha-Beta pruning (depth 3)")
    player_color = input("Choose your color (white/black): ").strip().lower()
    if player_color not in ['white', 'black']:
        print("Invalid choice. Defaulting to white.")
        player_color = 'white'
    
    human_is_white = (player_color == 'white')
    ai_is_white = not human_is_white
    
    # Flip the board so that the human's pieces appear at the bottom
    flip_board = not human_is_white
    
    # Set AI search depth
    ai_depth = 3
    
    print(f"\nYou are playing as {player_color.upper()}")
    print(f"AI is playing as {'WHITE' if ai_is_white else 'BLACK'}")
    print(f"AI search depth: {ai_depth}")
    print("\nGame started!\n")

    selected_sq = None
    possible_moves = []
    game_over = False

    running = True
    while running:
        # Determine whose turn it is
        human_turn = (board.turn == chess.WHITE and human_is_white) or (board.turn == chess.BLACK and not human_is_white)

        # Check for game over
        if board.is_game_over() and not game_over:
            game_over = True
            print("\n" + "="*50)
            print("GAME OVER!")
            if board.is_checkmate():
                winner = "Black" if board.turn == chess.WHITE else "White"
                print(f"Checkmate! {winner} wins!")
            elif board.is_stalemate():
                print("Stalemate! It's a draw!")
            elif board.is_insufficient_material():
                print("Insufficient material! It's a draw!")
            else:
                print(f"Game over. Result: {board.result()}")
            print("="*50)
            
            # Wait a few seconds then close
            pygame.display.flip()
            time.sleep(5)
            running = False
            break

        if human_turn and not game_over:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                    pygame.quit()
                    sys.exit()
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    pos = pygame.mouse.get_pos()
                    sq = get_square_from_mouse(pos, flip_board)
                    
                    if selected_sq is None:
                        # First click: try to select a square
                        piece = board.piece_at(sq)
                        if piece and ((piece.color == chess.WHITE and human_is_white) or (piece.color == chess.BLACK and not human_is_white)):
                            selected_sq = sq
                            possible_moves = get_valid_moves_from_square(board, sq, human_is_white)
                    else:
                        # Second click: attempt to make a move
                        move = None
                        
                        # Check if it's a promotion move (pawn reaching last rank)
                        piece = board.piece_at(selected_sq)
                        if piece and piece.piece_type == chess.PAWN:
                            to_rank = chess.square_rank(sq)
                            if (piece.color == chess.WHITE and to_rank == 7) or (piece.color == chess.BLACK and to_rank == 0):
                                move = get_promotion_move(selected_sq, sq)
                        
                        # If not a promotion, create normal move
                        if move is None:
                            move = chess.Move(selected_sq, sq)
                        
                        if move in board.legal_moves:
                            board.push(move)
                            print(f"You played: {move.uci()}")
                        else:
                            print("Illegal move, try again.")
                        
                        selected_sq = None
                        possible_moves = []
        
        elif not game_over:
            # AI's turn
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                    pygame.quit()
                    sys.exit()
            
            # Small delay to make it easier to see AI's move
            time.sleep(0.3)
            
            start_time = time.time()
            ai_move = get_best_move(board, ai_depth, ai_is_white)
            end_time = time.time()
            
            if ai_move:
                board.push(ai_move)
                print(f"AI played: {ai_move.uci()} (took {end_time - start_time:.2f} seconds)")
                print(f"Board evaluation: {evaluate_board(board):.2f}")
            else:
                print("AI has no valid moves!")
                break

        # Redraw board and pieces
        draw_board(screen, flip_board, selected_sq, possible_moves)
        draw_pieces(screen, board, flip_board)
        
        # Display turn information
        font = pygame.font.Font(None, 36)
        if not game_over:
            turn_text = "Your turn" if human_turn else "AI is thinking..."
            text_surface = font.render(turn_text, True, (0, 0, 0))
            screen.blit(text_surface, (10, HEIGHT - 30))
        
        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()