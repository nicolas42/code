
# Download files in parallel
# ------------------------------
# doesn't work if pasted into python shell

import multiprocessing
import wget
import os

# Circumvent SSL: CERTIFICATE_VERIFY_FAILED errors
# https://stackoverflow.com/questions/50236117/scraping-ssl-certificate-verify-failed-error-for-http-en-wikipedia-org
import ssl
ssl._create_default_https_context = ssl._create_unverified_context

# How to get image urls from google images
# ------------------------------
# Search google images and use the following javascript
# urls = Array.from(document.querySelectorAll('.rg_di .rg_meta')).map(el=>JSON.parse(el.textContent).ou);
# window.open('data:text/csv;charset=utf-8,' + escape(urls.join('\n')));


def wget_process(args):
    url = args[0]
    output_dir = args[1]
    try:
        wget.download(url, out=output_dir, bar=None)
        return ('Downloaded', url)
    except Exception as e:
        return (str(e), url )

def parallel_wget_demo():

    print("\n")
    print("parallel_wget_demo")
    print("---------------------")

    output_dir = "Downloads_gitignore"
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    args = [
        [ "https://upload.wikimedia.org/wikipedia/commons/4/4b/Ursidae-01.jpg" , output_dir ], 
        [ "https://upload.wikimedia.org/wikipedia/commons/thumb/7/71/2010-kodiak-bear-1.jpg/1200px-2010-kodiak-bear-1.jpg" , output_dir ], 
        [ "https://media.4-paws.org/8/a/a/0/8aa007ca1ea6b56e152eaa378cac580af6fcbdc1/YAR_6487-5272x3648.jpg" , output_dir ], 
        [ "https://image.pbs.org/video-assets/ae5wgeQ-asset-mezzanine-16x9-MqD4B29.jpg" , output_dir ], 
        [ "https://www.sciencenewsforstudents.org/wp-content/uploads/2021/04/1440_bb_brown_black_bear_explainer_feat-1030x580.jpg" , output_dir ], 
        [ "https://gutenberg.net.au/ebooks15/1500401h.html" , output_dir ], 
    ]

    with multiprocessing.Pool(10) as pool:
        # imap_unordered allows for results to be returned in the order in which they are generated
        for result in pool.imap_unordered(wget_process, args):
            print(' '.join(result))




