# Tamir Enkhjargal
# CSCI 181 - Applied Cryptography
# Santa Clara University


# Python3 code to implement Keystream generation
# for the RC4 stream cipher


# Takes two integer inputs number and n.
# Postcondition: Outputs an array of length n giving
#   the binary representation of number in list format
def DecimalToBinary(number, n):
	result = []						# First initialize result as an empty list

	for x in range(0, n):
		result.insert(0, int(number % 2))		# Front-append a 0 or 1, as in repeated division
		number /= 2
	
	return result


# Takes in int array k and integer n.
# Postcondition: Outputs an array of integers with every
#   n bits converted to its decimal representation
def ConvertBitArraytoInt(k, n):
	result = [0]*int(len(k)/n)				# Initialize list of 0s of size k/n
	
	for x in range(0, int(len(k)/n)):			# Splits key into n-bit partitions, and then
		for y in range(0, n):				# converts each partition into their
			result[x] += k[(x*n)+y]*pow(2, n-y-1)	# decimal equivalent
	
	return result


# Takes in int n and int array key
# Postcondition: Initializes S for stream generation
#   from lecture notes
def Permutation(n, key):
	S = []
	T = []

	for x in range(0, pow(2, n)):				# This loop is to fill in S and T vectors
		S.append(x)					# S is filled in order from 0 to 2^n
		T.append(key[x % len(key)])			# T is from K[i mod keylen]
	
	j = 0
	for x in range(0, pow(2, n)):				# This loop is to now scramble and permutate based on key
		j = (j+S[x]+T[x]) % pow(2, n)

		temp = S[x]					# Swapping
		S[x] = S[j]
		S[j] = temp
	
	return S


# Takes in integers n, l (length of PT/CT), and key array)
# Postcondition: Outputs the fully generated keystream from given
#   n, l, and key initialization vector, code translated from
#   lecture notes
def KeystreamGeneration(n, l, key):
	keystream = []
	K = ConvertBitArraytoInt(key, n)
	S = Permutation(n, K)
	i = j = 0

	for x in range(0, l):
		i = (i+1) % pow(2, n)
		j = (j+S[i]) % pow(2, n)

		temp = S[i]					# Swapping
		S[i] = S[j]
		S[j] = temp

		t = (S[i]+S[j]) % pow(2, n)			 
		keystream.extend(DecimalToBinary(S[t], n))	# Appends to the end of the keystream
	
	return keystream

# Main code, running with given n, l, and key array
def main():
	print(KeystreamGeneration(8, 24, [1, 0, 1, 1, 1, 0, 0, 1 , 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1]))



if __name__ == "__main__":						# Needed to run main()
	main()
