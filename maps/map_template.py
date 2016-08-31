import sys

width = 38
height = 22
wall = '0'

if(len(sys.argv)<2):
	print("Specify Map Name!")
	exit()

f = open(sys.argv[1], 'w')

#Ceiling
for i in range(width):
	f.write(wall)
f.write('\n')

#Boundary Walls
for i in range(height-2):
	f.write(wall)
	for j in range(width-2):
		f.write(' ')
	f.write(wall + '\n')

#Floor
for i in range(width):
	f.write(wall)
f.write('\n')


