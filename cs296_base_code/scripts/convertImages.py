
import os

for i in range(1,7):
	s = "doc/plots/g28_project_plot0"	
	s=s+str(i)
	os.system("convert " + s + ".png " + s +".eps") 
for i in range(1,7):
	s = "doc/plots1/g28_project_plot0"	
	s=s+str(i)
	os.system("convert " + s + ".png " + s +".eps") 
for i in range(1,5):
	s = "doc/images/"	
	s=s+str(i)
	os.system("convert " + s + ".png " + s +".eps") 

os.system("convert doc/images/machine.png doc/images/machine.eps")
os.system("convert doc/images/RBM.png doc/images/RBM.eps")
os.system("convert doc/images/threading.png doc/images/threading.eps")
