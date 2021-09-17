import wget
import sys
import ssl

ssl._create_default_https_context = ssl._create_unverified_context
url = sys.argv[1]
wget.download(url)
