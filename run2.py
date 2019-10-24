import os

path = "rl-tp-instancias/"

for i in os.listdir(path):
	command = "./codigo/relaxlag " + path + i + " 1000000000 10 0.1 0 >results/rl/" + i 

	print(command)
	os.system(command)
