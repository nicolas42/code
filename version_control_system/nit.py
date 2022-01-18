import os
import sys

def find(a,b):
    # find(a,b) => bool
	result = a.lower().find(b.lower())
	if result == -1:
		return False
	else:
		return True



def sha1(filepath):
    # hash the contents of a file to get a unique identifier
    # from https://stackoverflow.com/questions/22058048/hashing-a-file-in-python
    
    import hashlib

    # BUF_SIZE is totally arbitrary, change for your app!
    BUF_SIZE = 65536  # lets read stuff in 64kb chunks!

    sha1 = hashlib.sha1()

    with open(filepath, 'rb') as f:
        while True:
            data = f.read(BUF_SIZE)
            if not data:
                break
            sha1.update(data)

    return sha1.hexdigest()


def date_time_string():
    import datetime
    return datetime.datetime.now().strftime("%Y%m%d_%H%M%S")


def init():
    for dir in [ ".nit", ".nit/files", ".nit/versions" ]:
        if not os.path.exists(dir): os.makedirs(dir)


def commit():
    top_dir = "."
    for root, dirs, files in os.walk(top_dir, topdown=False):

        # skip the .nit directory
        nit_directory = "/".join([top_dir, ".nit"])
        if root == nit_directory: continue

        version_file = "/".join([nit_directory, "versions", date_time_string() ])

        with open(version_file, "w") as output_file:
            for file in files: 
                path = "/".join([root, file])
                sha1_path = "/".join([nit_directory, "files", sha1(path) ])
                print(sha1_path, path)
                output_file.write(sha1_path +" "+ path +"\n")

# def revert( file ):
#     with open(filename) as f:
#         lines = f.read().split("\n")

#     for line in lines:

    