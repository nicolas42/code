import os
import sys

def find_case_insensitive(a,b):
    # return index or -1 if not found
	return a.lower().find(b.lower())


def find_files( top_dir, query ):

    # usage: find_files(".", "key words separated by whitespace")

    query = query.split() # split at whitespace

    for root, dirs, files in os.walk(top_dir):
        # print(root,dirs,files)

        for dir in dirs:
            files.append(dir)

        for file in files:
            full_path = os.path.join(root, file)
            was_found = True	
            for query_word in query:
                if -1 == find_case_insensitive(full_path, query_word):
                    was_found = False
            if was_found:
                print(full_path)


# find_files("c:\\", "vcvarsall")
# "c:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

