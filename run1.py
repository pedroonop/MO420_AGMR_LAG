import os

path = "rl-tp-instancias/"

for i in os.listdir(path):
	command = "./codigo/relaxlag " + path + i + " 1000000000 10 0.1 1 >results/pp/" + i 

	print(command)
	os.system(command)
