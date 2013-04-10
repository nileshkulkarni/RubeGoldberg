
import os

for i in range(1,7):
	s = "plots/g28_project_plot0"	
	s=s+str(i)
	os.system("convert " + s + ".png " + s +".eps") 

