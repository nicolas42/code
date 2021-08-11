# Find files in the current directory that have all the supplied keywords in them
# 
# For example
# python find.py something
# python find.py misc ass1 .c misc
# 
# Searches the entire file path

import os
import sys

def find(a,b):
	result = a.lower().find(b.lower())
	if result < 0:
		return False
	else:
		return True


current_dir = os.getcwd()

query_words = [""]
if len(sys.argv) >= 2:
	query_words = sys.argv[1:]
print(query_words)

for root, dirs, files in os.walk(current_dir, topdown=False):
	# print(root,dirs,files)

	files = dirs + files  # join the two lists together

	for file in files:
		full_path = os.path.join(root, file)
		was_found = True	
		for query_word in query_words:
			if not find(full_path, query_word):
				was_found = False
		if was_found:
			print(full_path)
