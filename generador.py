

import string


import sys
from random import *




if(len(sys.argv) != 3):
	print("error, se usa asi: cantidad de datos, nombre del archivo")

else:

	file = open(sys.argv[2], "a")
	charSet = 'abcdefghijklmnopqrstuvwxyz'
	minLength = 1	
	maxLength = 30
	length = randint(minLength, maxLength)

	for x in range(int(sys.argv[1])):

		length = randint(minLength, maxLength)
		palabra = "".join(choice(charSet) for x in range(length))

		file.write(palabra)  
		file.write("\n")	

	file.close()

