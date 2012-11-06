# Mandelbrot fractal rendering with SDL
# Copyright (C) 2012  Davide Gessa
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
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
