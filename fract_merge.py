import os

file = raw_input("File prompt (ie tmp/img_): ")
dest = raw_input("File dest: ")
n = input("File for line: ")

lines = ""

for i in xrange(0, n):
	f = ""
	
	line = dest+"/"+file+str(i)
	
	for j in xrange(0, n):
		f = f + " " +(file+str(i)+"_"+str(j)+".bmp")
	os.system("convert +append "+f+" "+line+".bmp")
	lines = lines + line

os.system("conver -append "+lines+" "+dest+"/"+file+"final.bmp")
