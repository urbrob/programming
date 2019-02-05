from tkinter import Tk, Canvas, Button
from functools import partial


class TicTacToe(Tk):
    WINDOW_SIZE = 600
    EMPTY = 0
    CELL_SIZE = WINDOW_SIZE / 3
    GRID_COLOR = 'white'

    def __init__(self):
        Tk.__init__(self)
        self.canvas = Canvas(height=self.WINDOW_SIZE, width=self.WINDOW_SIZE, bg='Black')
        self.title_screen()
        self.turn = 'X'
        self.board = [
            ['-', '-', '-'],
            ['-', '-', '-'],
            ['-', '-', '-'],
        ]
        self.canvas.pack()

    def user_won(self):
        board = self.board
        board_with_horizontals = board + [[i[0] for i in board]] + [[i[1] for i in board]] + [[i[2] for i in board]]
        all_posiblities =  board_with_horizontals + [[board[0][0], board[1][1], board[2][2]]] + [[board[0][2], board[1][1], board[2][0]]]
        return any(all(option == self.turn for option in possibility) for possibility in all_posiblities)

    def make_move(self, x, y):
        if self.board[y][x] == '-'
            self.board[y][x] = self.turn
            if self.user_won():
                self.canvas.delete('all')
                self.generate_text(f'Brawo! Wygrał gracz: {self.turn}', width=self.WINDOW_SIZE // 2, height=self.WINDOW_SIZE // 2, font_size=14)
            else:
                if self.turn == 'X':
                    self.turn = 'O'
                else:
                    self.turn = 'X'
                self.make_board()

    def make_board(self):
        self.canvas.delete('all')
        self.generate_text(f'Tura gracza: {self.turn}', width=self.WINDOW_SIZE // 2, height=self.WINDOW_SIZE // 25)
        for y, line in enumerate(self.board):
            for x, block in enumerate(line):
                action = partial(self.make_move, [x, y])
                self.generate_text(block, width=self.WINDOW_SIZE // 6 + x * self.WINDOW_SIZE // 3,
                                   height=self.WINDOW_SIZE // 6 + y * self.WINDOW_SIZE // 3,
                                   tag=f'<Button>', command=self.make_move(event, x, y), font_size=5)
        self.canvas.pack()

    def play(self, event, x=None, y=None pplayer=None):
        def wrapper(player=player, x=x, y=y):
            if player:
                self.player = player
            if self.player and self.turn == player:
                make_move
            else:
                ai_turn()
    return wrapper

    def exit(self, event):
        self.destroy()

    def generate_text(self, text, width=0, height=0, font_size=25, command=None, tag=None):
        created_text = self.canvas.create_text(width, height, text=text, fill='white', font=('Franklin Gothic', -self.WINDOW_SIZE // font_size))
        if command and tag:
            self.canvas.tag_bind(created_text, tag, command)
        return created_text

    def title_screen(self):
        self.generate_text('TicTacToe!', width=self.WINDOW_SIZE // 2, height=self.WINDOW_SIZE // 7)
        self.generate_text('Play for 2 players!', width=self.WINDOW_SIZE // 2, height=self.WINDOW_SIZE // 4.8, tag='<Button-1>', command=self.play())
        self.generate_text('Play as X!', width=self.WINDOW_SIZE // 2, height=self.WINDOW_SIZE // 3.7, tag='<Button-2>', command=self.play('X'))
        self.generate_text('Play as O!', width=self.WINDOW_SIZE // 2, height=self.WINDOW_SIZE // 3, tag='<Button-3>', command=self.play('O'))


if __name__ == '__main__':
    root = TicTacToe()
    root.mainloop()
