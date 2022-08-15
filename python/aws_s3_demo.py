# Boto3 Docs
# https://boto3.amazonaws.com/v1/documentation/api/latest/index.html


import boto3

s3 = boto3.resource('s3')

# Print out bucket names
for bucket in s3.buckets.all():
    print(bucket.name)


# s3 callback - print number of bytes transferred
# ----------------------------------------------------------
s3_transferred_bytes = 0
def s3_callback(number_of_bytes):
    global s3_transferred_bytes
    s3_transferred_bytes += number_of_bytes
    print("transferred:", s3_transferred_bytes, end='\r')


bucket = s3.Bucket('nschmidt-public')

# upload to s3
with open('downloaded.mp4', 'rb') as data:
    bucket.upload_fileobj(data, 'uploaded.mp4', Callback=None)

# download from s3
with open('downloaded.mp4', 'wb') as data:
    bucket.download_fileobj('funk_overload.mp4', data, Callback=None)

# copy file into this bucket
copy_source = { 'Bucket': 'yafoo', 'Key': 'test.html' }
bucket.copy(copy_source, 'test3.html')

# print all files in a bucket
for f in bucket.objects.all(): print(f.key)

# upload all files in dir recursively
import os 
for root, dirs, files in os.walk(os.getcwd()):
    for file in files:
        path = os.path.join(root, file)
        print(path)
        with open(path, 'rb') as data:
            bucket.upload_fileobj(data, path, Callback=s3_callback)


