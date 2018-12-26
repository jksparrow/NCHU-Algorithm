import sys
import random
import fire
import pygame
import growing_tree
import a_star
import depth_first
import ga
import time
#import os

def start(generator, search, num_rows=5, num_cols=5, WIDTH=501, HEIGHT=501, seed=None, render=True):
    ''' Generate and solve mazes.

    Args:
        generator(str): Generator algorithm to be used. (backtracker, prim)
        search (str): Pathfind algorithm to be used. (a_star, depth_first)
        num_rows (int): Number of cells of each column
        num_cols (int): Number of cells of each row
        WIDTH (int): Screen width (Number of pixels)
        HEIGHT (int): Screen height (Number of pixels)
        seed (int): The seed used by the random numbers generator
        render (bool): Whether or not to render maze while creating and solving
    '''
    # Set random seed
    if not seed:
        seed = random.randint(0, sys.maxsize)
        #print(seed)
    #random.seed(seed) #這行不知道在尬麻
    print('Seed: {}'.format(seed))
    # Create pygame window
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    # Create maze
    maze = growing_tree.create_maze(screen, generator, num_rows, num_cols, render)
    maze.draw()
    print("start searching path!!!")
    #time.sleep(3)
    # Use specified algorithm to find solution
    eval(search).search(maze, render)

    while True:
        # draw the shortest path in orange
       maze.draw()


if __name__ == '__main__':
    fire.Fire(start)
