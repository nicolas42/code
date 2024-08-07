with open('in.txt', 'r') as file:
    lines = file.readlines()

out = []
for i in range(len(lines)):
    line = lines[i].strip()
    if line == "Subscribed":
        if (i+2)<len(lines):
            out.append( lines[i+2].strip())


with open('out.txt', 'w') as file:
    for i in out:
        file.write(i+'\n')

        

 


