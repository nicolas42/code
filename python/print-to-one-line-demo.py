# To print on one line use carriage return \r rather than the line feed \n character.
# from https://stackoverflow.com/questions/517127/how-do-i-write-output-in-same-place-on-the-console

import time

for i in range(100):
    time.sleep(0.1)
    print('Downloading File FooFile.txt [%d%%]' % i, end="\r")
