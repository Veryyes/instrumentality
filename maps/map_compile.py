import sys

width = 38
height = 22

if(len(sys.argv) < 2):
	print("Specifiy Map!")
	sys.exit()

f = open(sys.argv[1], 'r')

map_data = []

#Loads map data into 2d array
i = 0
j = 0
for line in f:
	row = []
	for char in line:
		if(char == '\n'):
			break
		row.append(char)
	map_data.append(row)

#Optimization
new_data = ""

