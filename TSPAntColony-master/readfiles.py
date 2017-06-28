from numpy import *
import matplotlib.pyplot as plt


def cityRead():
	x,y=loadtxt('city_data.txt', unpack = True)
	order=loadtxt('Data.txt')
	print (order)
	#print x
	#print y
	'''order1[]
	x1[]
	y1[]'''
	x1=[]
	y1=[]
    
	for i in order:
		x1.append(x[i])
		y1.append(y[i])
	x1.append(x[order[0]])
	y1.append(y[order[0]])
	plt.figure('S-ACO', (8,6), 80, 'w', 'k')	
	plt.plot(x1,y1, marker='x', linestyle = '--', color = 'r', label = 'S-ACO')
	for i in range(len(order)):
		plt.text(x1[i],y1[i],order[i])
	plt.show() 

cityRead()