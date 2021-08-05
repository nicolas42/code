import random

import requests

print('\nreading https://www.gutenberg.org/files/2701/2701-0.txt (Moby Dick)...\n')
r = requests.get('https://www.gutenberg.org/files/2701/2701-0.txt')
# print( r.encoding )
r.encoding = 'utf-8'
data = r.text

# # write to file
# f = open('moby_dick.txt','w',encoding="utf-8")
# f.write(r.text)
# f.close()

# # read from file
# f = open('moby_dick.txt', encoding="utf-8")
# data = f.read()
# f.close()


result = []
data = data.split() # split at whitespace

position = 24158 # random.randint(0, len(data)-3)

result.append(data[position])
result.append(data[position+1])

for num_iterations in range(20):

    locations_of_matches = []
    for i,_ in enumerate(data):
        if data[i].lower() == result[-2].lower() and data[i+1].lower() == result[-1].lower():
            # print(i)
            locations_of_matches.append(i)

    # print(locations_of_matches)        
    # for l in locations_of_matches:
    #     print(data[l], data[l+1], data[l+2])
    random_match_location = random.choice(locations_of_matches)
    result.append(data[random_match_location+2])


joined_result = ' '.join(result)
print(joined_result)

