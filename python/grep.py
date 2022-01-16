# regular expressions matches
# ----------------------------
# >>> m.group(0)       # The entire match
# >>> m.group(1)       # The first parenthesized subgroup.
# >>> m.group(2)       # The second parenthesized subgroup.
# >>> m.group(1, 2)    # Multiple arguments give us a tuple.
# https://docs.python.org/3/library/re.html


import re
import sys

def grep(filename, expression):
    f = open(filename)
    text = f.read()
    f.close()

    out=[]
    for line in text.split("\n"):
        matches = re.search(expression, line)
        if matches: # and matches.group(1) not in out: # make matches unique
            out.append(matches.group(1))

    return out 


def run_from_terminal_args(argv):
    if len(argv) != 3: 
        print("usage: python grep.py filename expression")
        exit()
    filename   = argv[1]
    expression = argv[2]

    matches = grep(filename, expression)
    for match in matches: print(match)

def demo():
    filename   = "/Users/nick/Downloads/Liked videos - YouTube.html"
    expression = "href=\"(https://www.youtube.com/watch\?v=.*?)\""
    matches = grep(filename, expression)
    for match in matches: print(match)

    # output a file
    f = open("youtube_likes.txt","w")
    f.write("\n".join(matches))
    f.close()


def demo2():
    m = grep("../data/bookmarks_20220108.html", "HREF=\"(https://.*?)\"")
    for i in m: print(i)
    with open("out.txt","w") as f:
        f.write("\n".join(m))


if __name__ == "__main__":
    run_from_terminal_args(sys.argv)

