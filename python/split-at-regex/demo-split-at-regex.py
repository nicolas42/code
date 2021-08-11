import re
import sys

def read_file(filename):
    file = open(filename,'r')
    input_string = file.read()
    file.close()
    return input_string



filename = 'GH010013.txt';
output_filename = 'output.txt'
regex_pattern = r'\nFPS:\d*\.\d*\s*AVG_FPS:\d*\.\d*\n\n\s*cvWriteFrame\s*\nObjects:\s*\n';

input_string = read_file(filename)
output_list = re.split(regex_pattern, input_string)

# print items in output_list
for _,v in enumerate(output_list):
    print('{' + v + '}')


