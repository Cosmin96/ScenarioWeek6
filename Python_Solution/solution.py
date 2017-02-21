from canvas import canvas

file = open("robots.mat")

def parseInput():
	for line in file:
		testcase = line.split("#",1)
		robots = testcase[:1]
		obstacles = testcase[1:]
		robot = []
		obstacle = []
		x_robot = []
		y_robot = []
		n = 0
		m = 0
		for i in range(0,len(robots[0])):
			if robots[0][i] == ")":
				robot.append(robots[0][n:i+1])
				n = i+3
		for i in range(0,len(robot)):
			for j in range(0,len(robot[i])):
				if robot[i][j] == "(":
					if robot[i][j+2] == ",":
						x_robot.append(int(robot[i][j+1]))
					if robot[i][j+3] == ",":
						x_robot.append(int(robot[i][j+1].join(robot[i][j+2])))	
				if robot[i][j] == ")":
					y_robot.append(int(robot[i][j-1]))
			print(x_robot)
		#for i in range(0,len(obstacles)):
		#	if obstacles[i] == ")":
		#		obstacle.append(obstacle[m:i+1])
		#		m = i+3
		#	print(obstacle)
			

parseInput()