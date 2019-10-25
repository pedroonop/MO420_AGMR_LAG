import os

def menor(a, b):
	if (int(a[2]) < int(b[2])): return True
	if (int(a[2]) > int(b[2])): return False

	if (int(a[3]) < int(b[3])): return True
	if (int(a[3]) > int(b[3])): return False

	return a[4] < b[4]

path = "./rl/"

s = os.listdir(path)

aux = []
for i in s:
	aux.append(i.split("_"))

for i in range(len(s)):
	for j in range(i + 1, len(s)):
		if (menor(aux[j], aux[i])):
			s[i], s[j] = s[j], s[i]
			aux[i], aux[j] = aux[j], aux[i]

temp = 0
best_dual = 0
time_dual = 0
best_primal = 0
time_primal = 0

for file in s:
	temp += 1
	f = open(path + file)

	a = f.read().split()

	qtd = float(a[4])

	best_dual += float(a[0])
	time_dual += 10 * (int(a[1]) / qtd)

	best_primal += float(a[2])
	time_primal += 10 * (int(a[3]) / qtd)


	if temp % 5 == 0:
		print(str(best_dual/5) + ";" + str(time_dual / 5) + ";" + str(best_primal/5) + ";" + str(time_primal / 5))
		temp = 0
		best_dual = 0
		time_dual = 0
		best_primal = 0
		time_primal = 0

	f.close()