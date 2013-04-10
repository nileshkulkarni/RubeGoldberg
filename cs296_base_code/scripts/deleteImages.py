
import os

for i in range(1,7):
	s = "doc/plots/g28_project_plot0"	
	s=s+str(i)
	os.system("rm  " + s + ".eps") 
for i in range(1,7):
	s = "doc/plots1/g28_project_plot0"	
	s=s+str(i)
	os.system("rm  " + s + ".eps") 
for i in range(1,5):
	s = "doc/images/"	
	s=s+str(i)
	os.system("rm  " + s + ".eps") 

os.system("rm  doc/images/machine.eps")
os.system("rm  doc/images/RBM.eps")
os.system("rm   doc/images/threading.eps")
