import matplotlib.pyplot as plt
import matplotlib.pyplot as plt
import numpy
from numpy import genfromtxt

#####################################################################

data=genfromtxt('data/project_g28_data.csv',delimiter=',',dtype=None)

#Plot 1
#AVERAGED OVER RERUN

plt.xlabel("Iteration Number")
plt.ylabel("Time in ms")
plt.title("Step time/ Total Time averaged over Rerun Value")
#plt.xlim(0,100)
#plt.ylim(-10,50)

itrno=[]
stepval=[]
looptime=[]

stepvalsum=0
looptimesum=0

for i in range(0,100):
	stepvalsum=0
	looptimesum=0
	for j in range(0,100):
		stepvalsum+=data[i+100*j][2]
		looptimesum+=data[i+100*j][6]
	itrno.append(i)
	stepval.append(stepvalsum/100)
	looptime.append(looptimesum/100)

plt.plot(itrno, stepval, 'r+',label="step time")
plt.plot(itrno, looptime, 'b*',label="Total Time")
plt.legend()
plt.savefig('plots/g28_project_plot01.png')
plt.clf()


###############################################################

#Plot 2


plt.xlabel("Iteration Number")
plt.ylabel("Time in ms")
plt.title("Step/Collision/Velocity/Position averaged over Rerun values")
#plt.xlim(0,100)
#plt.ylim(-10,30)

itrno=[]
rerun=[]
stepval=[]
collision=[]
velocity=[]
position=[]

stepvalsum=0
collisionsum=0
velocitysum=0
positionsum=0
rerunnum=0

for i in range(0,100):
	stepvalsum=0
	collisionsum=0
	velocitysum=0
	positionsum=0
	for j in range(0,100):
		stepvalsum+=data[i+100*j][2]
		collisionsum+=data[i+100*j][3]
		velocitysum+=data[i+100*j][4]
		positionsum+=data[i+100*j][5]
	itrno.append(i)
	stepval.append(stepvalsum/100)
	collision.append(collisionsum/100)
	velocity.append(velocitysum/100)
	position.append(positionsum/100)

plt.plot(itrno, stepval, 'r*',label="Step")
plt.plot(itrno, collision, 'b+',label="Collision")
plt.plot(itrno,velocity,'g+',label="Velocity")
plt.plot(itrno,position,'y*',label="Position")
plt.legend()
plt.savefig('plots/g28_project_plot02.png')
plt.clf()



#########################################################################


#Plot 3

#AVERAGED OVER ITERATION

plt.xlabel("Rerun Number")
plt.ylabel("Time in ms")
plt.title("step Time / Loop Time averged over Iteration No ")
#plt.xlim(0,100)
#plt.ylim(-10,50)

rerunno=[]
stepval=[]
looptime=[]

stepvalsum=0
looptimesum=0

for i in range(0,100):
	stepvalsum=0
	looptimesum=0
	for j in range(0,100):
		stepvalsum+=data[100*i+j][2]
		looptimesum+=data[100*i+j][6]
	rerunno.append(i)
	stepval.append(stepvalsum/100)
	looptime.append(looptimesum/100)

plt.plot(rerunno, stepval,'r.', label="step Time")
plt.plot(rerunno, looptime, 'b*',label="Loop Time")
plt.legend()
plt.savefig('plots/g28_project_plot03.png')
plt.clf()


##########################################################################

#Plot 4

#AVERAGED OVER ITERATION

plt.xlabel("Rerun Number")
plt.ylabel("Time in ms")
plt.title("Step/Collion/Velocity/Position")
#plt.xlim(0,100)
#plt.ylim(-10,30)

rerunno=[]
rerun=[]
stepval=[]
collision=[]
velocity=[]
position=[]

stepvalsum=0
collisionsum=0
velocitysum=0
positionsum=0
rerunnum=0

for i in range(0,100):
	stepvalsum=0
	collisionsum=0
	velocitysum=0
	positionsum=0
	for j in range(0,100):
		stepvalsum+=data[100*i+j][2]
		collisionsum+=data[100*i+j][3]
		velocitysum+=data[100*i+j][4]
		positionsum+=data[100*i+j][5]
	rerunno.append(i)
	stepval.append(stepvalsum/100)
	collision.append(collisionsum/100)
	velocity.append(velocitysum/100)
	position.append(positionsum/100)

plt.plot(rerunno, stepval, 'r--',label='step Time')
plt.plot(rerunno, collision, 'b.',label='Collision Time')
plt.plot(rerunno,velocity,'g.',label='Velocity Time' ),
plt.plot(rerunno,position,'y.',label='Position Time')
plt.legend()
plt.savefig('plots/g28_project_plot04.png')
plt.clf()

#####################################################################

#Plot 5
#AVERAGED OVER RERUN

plt.xlabel("Iteration Number")
plt.ylabel("Time in ms")
plt.title("Step with error bars")
#plt.xlim(0,100)
#plt.ylim(-10,10)

itrno=[]
stepval=[]
devstepval=[]

stepvalsum=0

for i in range(0,100):
	stepvalsum=0
	for j in range(0,100):
		stepvalsum+=data[i+100*j][2]
	itrno.append(i)
	stepval.append(stepvalsum/100)
	devmax=0
	stepavg=stepvalsum/100
	for j in range(0,100):
		a=abs(stepavg-data[i+100*j][2])
		if(devmax<a*10):
			devmax=a*10
	devstepval.append(devmax)

		
#plt.plot(itrno, stepval, 'r--')
plt.errorbar(itrno, stepval, yerr=devstepval, fmt='r+')
plt.savefig('plots/g28_project_plot05.png')
plt.clf()

##################################################################

#PLOT 6

plt.xlabel("Step time in ms")
plt.ylabel("Frequency")
plt.title("g28_plot06")
#plt.xlim(0,100)
#plt.ylim(0,100)


newdata= []

for i in range(0,100):
	newdata.append(data[i*100+40][2])

plt.hist(newdata,100,histtype='step',color='b',label='cumulative',cumulative=True)
plt.hist(newdata,100,color='r',label='Histogram')
plt.legend()
plt.savefig('plots/g28_project_plot06.png')
plt.clf()


