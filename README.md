# connect-four
An application to play connect four against a friend or an ai player. Get four pieces in a row horizontally, vertically, or diagonally to win the game.

## Downloading and Compiling
1. Clone the repository using a terminal, or download the zip file from https://github.com/kchamilton/connect-four.git and extract the files.
```bash
git clone https://github.com/kchamilton/connect-four.git
```
2. Using a terminal, move into the folder containing the project using cd commands.
3. Once in the folder type `make` into the terminal and press enter.
The code has now been compiled into the executable play.

## Playing Connect Four
1. Type `./play` into the terminal and press enter to run the program.
2. The opening screen will ask if you want to start a new game. Type **y** and press enter to start, and **n** and enter to exit. If you enter incorrect input you will be notified and asked to provide either **y** or **n** as a response. The game will accept upper case or lower case responses as correct input. If you enter a valide input followed by other characters, ex) **y45**, the program will register your response as **y** and proceed with a new game.
3. The next screen will ask you to enter the mode of the game. Enter **1** to play against another player such as a friend, and **2** if you would like to play against the ai player. If you enter incorrect input, you will be notified and asked to provide either **1** or **2** as a response.
4. The following screen will ask for the desired board width. Enter an integer, which must be greater than or equal to four to allow for a win, and press enter to proceed. The standard connect four board has a width of 7, and a standard terminal not expanded to full screen can display up to a width of 26 properly. If you do not enter an integer, or enter an integer less than four, you will be notified and asked to enter a valid integer value. However, if you type a valid integer followed by other characters the program will read in the valid numbers up to the other characters and set the board width as such.
5. The next screen will ask for the desired board height. Enter an integer, which must be greater than or equal to four to allow for a win, and press enter to proceed. The standard connect four board height is 6, and a standard terminal not expanded to full screen can display up to a height of 14 properly. If you do not enter an integer, or enter an integer less than 4, you will be notified and asked to enter a valid integer value. However, if you type a valid integer followed by other characters the program will read in the valid numbers up to the other characters and set the board width as such.
6. The program will now display the game board and allow for game play. The header above the board will always state whose turn (either player 1 or player 2) it is and the piece that displays over the board will either be an **O** for player 1 or an **X** for player 2. Use the left and right arrow keys to move the piece over the board to select the desired column to play. Once you have the column you want to play in, press the down arrow key to place the piece. If the column is already filled, a notification will display to let you know that you need to choose a different column to play in.
7. If you are playing player vs. player, player 2 will now be able to make their move using the same method as the first player. If you are playing against the ai, the ai will now make its move and then notify you once it has placed its piece. Press enter to continue after the ai has played.
8. Game play continues, player 1 then player 2 repeatedly, until a player has won the game or there are no more empty spots in the game board.
9. When the game is over, the screen will display which player has won the game, or if it was a tie. Press enter to continue.
10. The program will now ask if you would like to **1** have a rematch, **2** return to the main menu (start of the program), or **3** exit the game. Enter **1**, **2**, or **3** and press enter to choose the option you want. Entering a non-valid response will cause the program to notify you of the error and ask you to provide a valid option.
    1. If you select a rematch, the program will then ask if you would like to resize the board. Type **y** and press enter to resize the board as done at the beginning of the game, or type **n** and press enter to leave the board dimensions the same as the previous game. The game will accept upper case or lower case responses, and a correct response followed by other characters, ex) **nth**, will register as **n** and the program will proceed with that input. The score will be maintained during rematches to keep track of how many matches player 1 has won vs. player 2.
    
## Video Instructions
The video containing similar instructions and walkthroughs of various game situations can be found at the following link.
https://youtu.be/MgH0lzKrnRs

## The AI Player
The ai player decides its next best move by evaluating each possible move it could make and determining which move is best.
1. If the ai player can win at the position, it plays the piece to win.
2. If the human oponent would win if it played a piece at the position, it plays the piece to block.
3. Otherwise the ai attempts to determine the best move for the ai and the best move for the oponent through a series of steps.
    1. It first temporarily adds the piece it's currently analyzing to the opponent's graph (player 1) and adds edges going from the piece to the surrounding pieces, but not from the surrounding pieces to it as it is temporary. 
    2. Then a depth first search is run from the vertex of the temporary piece and the length of the search is returned.
    3. The length of the adjacency list for the vertex of the temporary piece is also found.
    4. The visited array for the graph is cleared, and the adjacency list at the vertex of the piece is also cleared to effectively remove it from the graph.
    5. If the depth first search is longer than the previous max length of the depth first search, the max length is updated and the optimal piece location is updated to the current piece. Otherwise if the length of the depth first search is equal to the max, and has a longer adjacency list length, the optimal piece is also updated to the current piece.
    6. The same process is completed at the same time to find and set the best ai move as well.
    7. If the max depth first search length is 0 for the ai player's best move, it makes the opponent's best move to block as there is no effective winning move for the ai. If the max depth first search length is greater than 0, the ai player's best move is played.

The concept behind the depth first search process is that the longer the depth first search, the more likely the ai player is likely to get four pieces in a row to win. The place with the longest adjacency list is chosen when the length of the search is equal as it means there are more surrounding pieces to connect with, thus increasing the ai player's chance of winning the game.
