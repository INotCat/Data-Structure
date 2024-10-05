import time
from collections import deque
from threading import Thread, Lock

RESET = '\033[0m'
BLUE = '\033[44m'
GREEN = '\033[42m'
RED = '\033[41m'

# define the map (grid)
# grid = [[c for c in line] for line in '''............................
# ..XXXXXXXXXX...........XXX..
# ..X........X...........X.X..
# ..XXXXXX...X....XXXXXXXX.X..
# .......X...X....X........X..
# ....XXXX...XXXXXX........X..
# ....X....................X..
# ....X.................XXXX..
# ....XXXXXXXXXXXXXXXXXXX.....'''.split('\n')]

grid = [[c for c in line] for line in '''........................................................
........................................................
........................................................
...........XXXXXX.....................XXXXXX............
.........XX......XX.................XX......XX..........
.......XX..........XX.............XX..........XX........
.....XX..............XX.........XX..............XX......
...XX..................XX.......XX................XX....
.XX....................XX.....XX....................XX..
.X.......................XX.XX.......................X..
.XX........................X........................XX..
...XX.............................................XX....
.....XX.........................................XX......
.......XX.....................................XX........
.........XX.................................XX..........
...........XX.............................XX............
.............XX.........................XX..............
...............XX.....................XX................
.................XX.................XX..................
...................XX.............XX....................
.....................XX.........XX......................
.......................XX.....XX........................
.........................XX.XX..........................
...........................X............................'''.split('\n')]


# create copies of the original matrix for flooding
dfs_matrix = [row[:] for row in grid]  # For DFS
bfs_matrix = [row[:] for row in grid]  # For BFS

# create a lock for synchronizing console output
print_lock = Lock()

def print_matrices(dfs, bfs):
    with print_lock:  # only one thread can print at a time
        # clear the screen
        print('\x1b[0J\x1b[1;1H')
        
        for dfs_row, bfs_row in zip(dfs, bfs):
            #wall: 'X', flooeded area: '#', empty space: '.' 
            #DFS
            for char in dfs_row:
                if char == 'X':  # Wall 
                    print(BLUE + 'X' + RESET, end='')
                elif char == '#': 
                    print(RED + '#' + RESET, end='')
                else:  
                    print(GREEN + '.' + RESET, end='')
            print('    ', end='')  # space between matrices
            
            #BFS
            for char in bfs_row:
                if char == 'X': 
                    print(BLUE + 'X' + RESET, end='')
                elif char == '#': 
                    print(RED + '#' + RESET, end='')
                else:  
                    print(GREEN + '.' + RESET, end='')
            print()  # new line after each row


def flood_via_DFS(matrix, start):
    maxX = len(matrix[0])
    maxY = len(matrix)

    stack = [start]  

    while stack:
        x, y = stack.pop()  # pop from the top 
        
        # boundary check
        if x < 0 or x >= maxX or y < 0 or y >= maxY:
            continue
        
        # skip if it's a wall or already flooded
        if matrix[y][x] == 'X' or matrix[y][x] == '#':
            continue
        
        # mark the current 
        matrix[y][x] = '#'
        
        # add neighbors 
        stack.extend([(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)])
        
        print_matrices(dfs_matrix, bfs_matrix)  
        time.sleep(0.5)


def flood_via_BFS(matrix, start):
    maxX = len(matrix[0])
    maxY = len(matrix)
    
    queue = deque([start])
    
    while queue:
        x, y = queue.popleft()  # pop the front
        
        if x < 0 or x >= maxX or y < 0 or y >= maxY:
            continue
        
        # skip if it's a wall or already flooded
        if matrix[y][x] == 'X' or matrix[y][x] == '#':
            continue
        
        matrix[y][x] = '#'
        
        queue.extend([(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)])
        
        print_matrices(dfs_matrix, bfs_matrix)  # print both matrices side by side
        time.sleep(0.5)


if __name__ == "__main__":
    # create threads for simultaneous flooding, (column,row)
    # start the flood from position (18, 9) in separate threads
    dfs_thread = Thread(target=flood_via_DFS, args=(dfs_matrix, (18, 9)))
    bfs_thread = Thread(target=flood_via_BFS, args=(bfs_matrix, (18, 9)))

    # start both threads
    dfs_thread.start()
    bfs_thread.start()

    # wait for both threads to finish
    dfs_thread.join()
    bfs_thread.join()

    time.sleep(3)
    print('\x1b[0J\x1b[1;1H')