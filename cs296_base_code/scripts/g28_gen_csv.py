import os
import re
import csv


iterations = 101
rerun =101

filename = "data/project_g28_data.csv"
def getData(s):
	return re.findall("([\d.]+)\s",s)

def analyseData(s):
	data = s.split('\n')	
	values=[0]
	for l in data:
		t = getData(l)
		if(len(t)==0):
			values.append(0)
		else:
			values.append(float(t[0]))
	
	return values
	
def getString(value):
	s=""
	for i in value:
		s=s+str(i)+","
	s=s+"\n"
	return s

def main():
	wfile = open(filename,'w')
	csvwriter = csv.writer(wfile, delimiter=',')
	for i in range(1,iterations):
		for j in range(1,rerun):
			s = "./bin/cs296_base" + " "+ str(i) + " >  test"
			os.system(s)
			f = open("test",'r')
			output=f.read()
			f.close()
			value = analyseData(output)
			value[0]=j
			value[1]=i
			value.pop()
			finalString = getString(value)
			csvwriter.writerow(value)

	wfile.close()
	os.system("rm test")
main() 
