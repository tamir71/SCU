# import neccessary libraries required for the plotting of a graph, such as matplotlib
import matplotlib.pyplot as plt

#list of x-values and y-values we want to plot
y = [5,11,14,18,14,25,26,29,28,35,36,41,40,47,47]
x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]

#the plot() function creates the plot
plt.plot(x,y) #make sure that the x and the y list contains same number of elements

#xlabel() and ylabel() functions helps in renameing the titles of x and y axis
plt.xlabel('Step (1 mb/step)')
plt.ylabel('CPU Time Used (CPU Clock Time)')

#includes the title of graph using title() function
plt.title('CPU time used per step')

#saves the graph as a file
plt.savefig("COEN146_Lab1.png")

#shows output of the graph on the screen
plt.show()
