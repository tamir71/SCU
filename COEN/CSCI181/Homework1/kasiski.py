# Tamir Enkhjargal
# CSCI 181 - Applied Cryptography
# Santa Clara University

# Python3 code to implement the Letter frequency analysis of
# the Kasiski cryptanalysis method.

import re								# Necessary for searching


# This function was implemented to find the indices of where these
# substrings all began the purpose was to find the distance between
# these substrings, so we can guess the key-length
def find(string):
	res = [i.start() for i in re.finditer('kvx', string)]		# Given ciphertext, find all occurences of 'kvx'
	print(str(res))
	res = [i.start() for i in re.finditer('hal', string)]		# Given ciphertext, find all occurences of 'hal'
	print(str(res))
	res = [i.start() for i in re.finditer('alv', string)]		# Given ciphertext, find all occurences of 'alv'
	print(str(res))
	res = [i.start() for i in re.finditer('lrk', string)]		# Given ciphertext, find all occurences of 'lrk'
	print(str(res))
	res = [i.start() for i in re.finditer('vfx', string)]		# Given ciphertext, find all occurences of 'vfx'
	print(str(res))


# After we found the length of the key from above, we can now separate
# our string into columns, and find letter frequency of each letter in
# their respective columns
def frequency(string):
	keylength = 5
	alphabet = "abcdefghijklmnopqrstuvwxyz"
	alphabet = list(alphabet)

	# Search first column: 0, k, 2k, 3k, ...
	counts = [0]*26
	for k in range(0, len(string), keylength):
		for a in range(len(alphabet)):
			if(string[k] == alphabet[a]):
				counts[a] += 1
	print(counts)
	
	# Search second column: 1, k+1, 2k+1, 3k+1, ...
	counts = [0]*26
	for k in range(1, len(string), keylength):
		for a in range(len(alphabet)):
			if(string[k] == alphabet[a]):
				counts[a] += 1
	print(counts)
	
	# Search third column: 2, k+2, 2k+2, 3k+2, ...
	counts = [0]*26
	for k in range(2, len(string), keylength):
		for a in range(len(alphabet)):
			if(string[k] == alphabet[a]):
				counts[a] += 1
	print(counts)
	
	# Search fourth column: 3, k+3, 2k+3, 3k+3, ...
	counts = [0]*26
	for k in range(3, len(string), keylength):
		for a in range(len(alphabet)):
			if(string[k] == alphabet[a]):
				counts[a] += 1
	print(counts)
	
	# Search fifth column: 4, k+4, 2k+4, 3k+4, ...
	counts = [0]*26
	for k in range(4, len(string), keylength):
		for a in range(len(alphabet)):
			if(string[k] == alphabet[a]):
				counts[a] += 1
	print(counts)

# Main() which runs the find() and frequency() functions
def main():
	string = input("Please enter in a string to analyze:\n")
	find(string)
	frequency(string)

if __name__ == "__main__":						# Needed to run main()
	main()
