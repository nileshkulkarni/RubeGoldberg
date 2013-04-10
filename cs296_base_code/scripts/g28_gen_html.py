import string

html = open('doc/g28_project_report.html', 'w')
html.write('''
<html>
<head>
<title stype="text-align:center;">RubeGolberg Machine </title>
</head>

<body > 
<h1 style="text-align:center"> RubeGoldberg Machine</h1>
 ''')

tagList=['begin','cite','bibliography','bibliographystyle','includegraphics','itemize','item','caption','label','verbatim','end','pagebreak']

def isTag(word):
	wordList= "".join((char if (not char in string.punctuation) else " ") for char in word).split()
	#print("Here ",wordList)
	if(len(wordList)>0 and (wordList[0] in tagList)):
		return wordList[0]
	else:
		return False

#def processTag(word): #process the word 
	#html.write("Word is "+word + "**")


def processData(data):
	html.write("<p>")
	dataList=data.split()
	#print(dataList)
	s=""
	i=0
	while(i<len(dataList)):
		word=dataList[i]
		#a=False
		a=isTag(word)
		if (a!=False):
			if(a=='begin'):
				wordList= "".join((char if (not char in string.punctuation) else " ") for char in word).split()
				if(len(wordList)>1 and wordList[1]=='equation'):# here i assume that word breaks into list and second word the inside curly braces item
					html.write('<img src="equation.png">') #inserted the image of equation # see for indents
					i+=1
					word=dataList[i]
					while(word!='\end{equation}'):
						#html.write(word+" ")
						i+=1
						word=dataList[i]
				elif(len(wordList)>1 and wordList[1]=='verbatim'):
					i+=1
					word=dataList[i]
					html.write("<p>")
					while(word!='\end{verbatim}'):
						html.write(word+" ")
						i+=1
						word=dataList[i]
					html.write("</p>")
				elif(len(wordList)>1 and wordList[1]=='itemize'):
						
					html.write('<ul>')
					i+=1
				else:
					i+=1 #that whole begin one is discarded
			elif(a=='includegraphics'):
				bracesBegin=word.find("{")
				bracesEnd=word.find("}")
				html.write('<div class="image">')
				html.write('<img src= "'+word[bracesBegin+1:bracesEnd-3]+"png"+'">')
				#print(word[bracesBegin+1:bracesEnd])
				i+=1

				word=dataList[i]
				if(word.find("\caption")!=-1):
					bracesBegin=word.find("{")
					#bracesEnd=word.find("}")
					html.write('<p>')
					html.write(word[bracesBegin+1:]+" ")
					#print("####################")
					i+=1
					while(dataList[i]!='}'):
						html.write(dataList[i]+" ")
						i+=1
					i+=1
					#print(dataList[i:])
					html.write('</p>')
					html.write('</div>')
				else:
					html.write('</div>')
					html.write(word)#in case the next word is not a caption u can include some indentation or whatever here
			elif(a=='item'):
				i+=1
				if(i<len(dataList)):
					word=dataList[i]
					#print(word)
					html.write('<li>')
					while(((word !="\item") and (word!="\end{itemize}")) and (i<len(dataList))):
						html.write(word+" ")
						i= i + 1
						if(i<len(dataList)):
							word=dataList[i]
					if(word=='\item'):
						html.write('</li>') #dont go to next word
					elif(word=='\end{itemize}'):
						i+=1 # go to next word
						html.write('</li>')
						html.write('</ul>')

			else:
				i+=1
			#processTag(word,a) # Anything in between can be tag'''
		else:
			if(word=='\\\\'):
				html.write("</br>")
			else:
				html.write(word+" ")
			i+=1
	html.write("</p>")


def processSection(data):
	subSecStart=0
	subSecEnd=0

	subSecStart=data.find("\subsection")
	if(subSecStart>0):
		processData(data[0:subSecStart]) ######
	if(subSecStart==-1):
		processData(data) #########
	else:
		while(subSecEnd!=len(data)):

			subSecStart=data.find("\subsection")
			subSecEnd=data[subSecStart+1:].find("\subsection")
			
			if(subSecEnd==-1):
				subSecEnd=len(data)
			else:
				subSecEnd+=1+subSecStart
			
			if(subSecStart!=-1):
				subSecTitleStart=data[subSecStart:].find("{")+subSecStart
				subSecTitleEnd=data[subSecStart:].find("}")+subSecStart

				html.write("<h3>")
				html.write(data[subSecTitleStart+1:subSecTitleEnd])
				html.write("</h3>")

				processData(data[subSecTitleEnd+1:subSecEnd]) # process the contents of subsection

				data=data[subSecEnd:]
				subSecEnd=0


def secPart(data):
	secStart=0
	secEnd=0
	while(secEnd!=len(data)):
		secStart=data.find("\section")
		secEnd=data[secStart+1:].find("\section")
		
		if(secEnd==-1):
			secEnd=len(data)
		else:
			secEnd=secEnd+secStart+1;
		
		if(secStart!=-1):
			secTitleStart=data[secStart:].find("{")+secStart
			secTitleEnd=data[secStart:].find("}")+secStart
			
			html.write("<h3>")
			html.write(data[secTitleStart+1:secTitleEnd])
			html.write("</h3>")

			processSection(data[secTitleEnd+1:secEnd])

			data=data[secEnd:]
			secEnd=0

file=open("doc/report_project_g28.tex",'r')
data=file.read()
secPart(data)

html.write('''
		</body>
		</html>
		 ''')


