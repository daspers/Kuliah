import sys
import time
import random
from collections import defaultdict

#GLOBAL VARIABEL
finish = False

class ListJawaban(object): 
	__slot__ = ['hor','i','j','len']
	def __init__(self, hor, i, j, len):
		self.hor = hor
		self.i = i
		self.j = j
		self.len = len

def readfile() :
	filename = input("Input the file name : ")
	try:
		file = open(filename, "r")
	except IOError:
		print("Error openning the file")
		sys.exit()
	a = file.read(1)
	b = ""
	#read tts size
	while(a!='\n') :
		b+=a
		a = file.read(1)
	n = int(b)
	#read tts
	tts =[];
	for i in range (0, n):
		a = file.read(1)
		temp=[]
		while(a!='\n' and a!='') :
			temp.append(a)
			a = file.read(1)
		tts.append(temp)
	#read the word
	kata=defaultdict(list)
	cekkata = dict()
	a = file.read(1)
	while (a!='' and a!='\n'):
		b = ""
		while (a!=';' and a!='' and a!='\n') :
			b+=a
			a = file.read(1)
		kata[len(b)].append(b)
		if (b in cekkata) :
			cekkata[b] +=1
		else :
			cekkata[b] = 1
		a = file.read(1)
	file.close()
	return n, tts, kata, cekkata

def GetPosisiJawaban(n):
	jawaban = []
	for i in range (0, n) :
		for j in range (0, n) :
			if (tts[i][j]=='-') :
				if (j>0 and j+1<n) :
					if(tts[i][j-1]=='#' and tts[i][j+1]=='-') :
						k=j+1
						len=1
						while(k<n and tts[i][k]=='-') :
							len+=1
							k+=1
						jawaban.append(ListJawaban(True, i, j, len))
				elif (j+1<n) :
					if(tts[i][j+1]=='-') :
						k=j+1
						len=1
						while(k<n and tts[i][k]=='-') :
							len+=1
							k+=1
						jawaban.append(ListJawaban(True, i, j, len))
				if (i>0 and i+1<n) :
					if(tts[i-1][j]=='#' and tts[i+1][j]=='-') :
						k=i+1
						len=1
						while(k<n and tts[k][j]=='-') :
							len+=1
							k+=1
						jawaban.append(ListJawaban(False, i, j, len))
				elif (i+1<n) :
					if(tts[i+1][j]=='-') :
						k=i+1
						len=1
						while(k<n and tts[k][j]=='-') :
							len+=1
							k+=1
						jawaban.append(ListJawaban(False, i, j, len))
	return jawaban

def SelesaikanTTS(idx):
	global finish, fulltts, kata, jawaban, cekkata,tts
	if (finish) :
		return
	if (idx == len(jawaban)) :
		finish = True
		return
	for x in kata[jawaban[idx].len] :
		if (cekkata[x]>0) :
			fitin = True
			k = 0
			if (jawaban[idx].hor) :
				while (k<jawaban[idx].len and fitin) :
					if (tts[jawaban[idx].i][jawaban[idx].j+k] != '-' and tts[jawaban[idx].i][jawaban[idx].j+k] != x[k]) :
						fitin = False
					k += 1
			else :
				while (k<jawaban[idx].len and fitin) :
					if (tts[jawaban[idx].i+k][jawaban[idx].j] != '-' and tts[jawaban[idx].i+k][jawaban[idx].j] != x[k]) :
						fitin = False
					k += 1
			if(fitin) :
				temp=[]
				if (jawaban[idx].hor) :
					for k in range(0, jawaban[idx].len) :
						temp.append(tts[jawaban[idx].i][jawaban[idx].j+k])
						tts[jawaban[idx].i][jawaban[idx].j+k] = x[k]
				else :
					for k in range(0, jawaban[idx].len) :
						temp.append(tts[jawaban[idx].i+k][jawaban[idx].j])
						tts[jawaban[idx].i+k][jawaban[idx].j] = x[k]
				cekkata[x] -= 1
				SelesaikanTTS(idx+1)
				if (finish) :
					return
				cekkata[x] += 1
				if (jawaban[idx].hor) :
					for k in range(0, jawaban[idx].len) :
						tts[jawaban[idx].i][jawaban[idx].j+k] = temp[k]
				else :
					for k in range(0, jawaban[idx].len) :
						tts[jawaban[idx].i+k][jawaban[idx].j] = temp[k]


##############
#MAIN PROGRAM#
##############
panjang, tts, kata, cekkata = readfile()
#shuffling for various result
for x in kata :
	random.shuffle(kata[x])
#starting the algorithm
start = time.time()
tot = 0
jawaban = GetPosisiJawaban(panjang)
SelesaikanTTS(0)
end = time.time()
print("Brute Force time : ", end-start, " s")
# tot = 0
# for x in kata :
	# tot+=len(kata[x])
# print(tot)
# print(len(jawaban))
# for x in jawaban :
	# print(x.hor," ", x.i, " ", x.j," ", x.len)
if (finish) :
	for x in tts :
		for y in x :
			sys.stdout.write(y)
		sys.stdout.write('\n')
else :
	print("Crossword can't be filled")
# for x in kata :
	# for y in kata[x] :
		# if(cekkata[y]) :
			# print (y)
