maze = [ [], [], [] ]
string_length = [0,0,0]

# Maze values:
# x: blocked. Signifies a wall.
# -: open.
# M: initial location of the mouse
# C: location of the cheese - where the mouse should get to

# Note that the maze will be visualized "upside-down" relative to
# how it is shown here. Row 0 is at the bottom of the maze.

maze[0] = [
    'xxxxxxxxxx',
    'x--------M',
    'x-xxxxx-xx',
    'x---------',
    'xxxxxx-xxx',
    'xxx----xxx',
    'xxx-xxxxxx',
    'xxx-xxxxxx',
    'x-----xxxx',
    'x-xxxxxxxx',
    'x--Cxxxxxx']
string_length[0] = 60


maze[1] = [
  'xxxxx',
  'xx---',
  'xx-x-',
  '---xM',
  'xx-xx',
  'xC--x' ]
string_length[1] = 20

maze[2] = [
  #'xxxxxxxx',
  'x----xxx',
  'x-x---x-',
  'x---x---',
  'x-x---x-',
  'x-xxx-x-',
  'xCxM--x-',
  'xxx-----' ]
string_length[2] = 30

