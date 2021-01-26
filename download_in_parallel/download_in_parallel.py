# doesn't work if pasted into python shell

import multiprocessing
import wget

urls = [ 'https://www.cia.gov/library/publications/the-world-factbook/fields/rawdata_' +str(i) +'.txt' for i in range(1,500) ]

def download(url):
    try:
        wget.download(url)
    except Exception as e:
        print(url +': \t'+ str(e))
    
    print(url)
    


if __name__ == '__main__':
    with multiprocessing.Pool(50) as p:
        r = p.map( download, urls )

