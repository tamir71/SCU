# Tamir Enkhjargal
# CSCI 181 - Applied Cryptography
# Santa Clara University

# Python3 code to implement Vigenere Cipher encryption and decryption
# with a known plaintext/ciphertext and keyword
# This code has been adapted from Geeksforgeeks
# One disclaimer about this code is that the inputs string and key should be same case
# The output will always be in UPPERCASE, however


# We need to repeat our key for as long as our string is
def keyExtend(string, key):
	key = list(key)							# Put our key into a list so we can iterate easily
	if len(string) == len(key):					# Don't need to extend key is key is as long as string
		return(key)
	else:
		for x in range(len(string)-len(key)):			# Repeat for the rest of the missing keylength
			key.append(key[x % len(key)])			# append the key for as long as needed (keeping x modulus'd by key length)
	return(key)


# Encryption of plaintext with key
def encrypt(string, key):
	ciphertext = []
	for x in range(len(string)):
		s = (ord(string[x]) + ord(key[x])) % 26			# This is taking the addition between unicode values of the string and key
		s += ord('A')						# Then we add the unicode-integer of 'A'
		ciphertext.append(chr(s))				# chr() takes unicode value and turns it into readable ASCII letters
	return(ciphertext)


# Decryption of ciphertext with key
def decrypt(string, key):
	plaintext = []
	for x in range(len(string)):
		s = (ord(string[x]) - ord(key[x]) + 26) % 26		# This is taking the difference between unicode values (need +26 because could be negative)
		s += ord('A')
		plaintext.append(chr(s))
	return(plaintext)

# Main code that runs
def main():
	string = input("Please enter in a string to decrypt or encrypt:\n")		# Take user input for string
	key = input("\nPlease input a key\n")						# Take user input for key
	key = keyExtend(string, key)							# keyExtend the key before running encrypt/decrypt
	case = input("\nAre we encrypting or decrypting? [encrypt/decrypt]\n")		# Asking if we're decrypting or encrypting
	if(case == "encrypt"):
		print("Ciphertext: ", "".join(encrypt(string, key)))			# Need "".join() so it doesn't get printed in list format
	if(case == "decrypt"):
		print("Plaintext: ", "".join(decrypt(string, key)))

if __name__ == "__main__":						# Needed to run main()
	main()
