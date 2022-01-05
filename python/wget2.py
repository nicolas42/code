# Can't be called wget.py or there is a circular dependency error
#
# usage: 
# python wget2.py url
#

import wget
import sys
import ssl

ssl._create_default_https_context = ssl._create_unverified_context
# ^ curcumvents certificate errors O_o

url = sys.argv[1]
wget.download(url)
