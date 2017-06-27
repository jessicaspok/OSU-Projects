## Jessica Spokoyny
## CS 344
## Program 5 - python exploration
## 11/21/2016

#!/usr/bin/python3

import random
import string

# generate random string of letters + newline char
def random_letters():
    return ''.join(random.choice(string.ascii_lowercase) for x in range(10)) + '\n'

# generate random int
def random_integer():
    return random.randint(1,42)

# store strings of random chars
random1 = random_letters()
random2 = random_letters()
random3 = random_letters()

print("\nFile Contents:\n")

file1 = open("file1", "w")		# open file for writing
file1.write(random1)			# add string
print(random1)					# print contents of file
file1.close()					# close file

file2 = open("file2", "w")		# open file for writing
file2.write(random2)			# add string
print(random2)					# print contents of file
file2.close()					# close file

file3 = open("file3", "w")		# open file for writing
file3.write(random3)			# add string
print(random3)					# print contents of file
file3.close()					# close file

print("Random Integers:")

rand_int1 = random_integer()	# get random int
print(rand_int1)				# print it out

rand_int2 = random_integer()	# get random int
print(rand_int2)				# print it out

print("\nProduct:")

product = rand_int1 * rand_int2	# calculate product
print(product)					# print it out
print(' ')