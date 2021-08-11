import boto3

import os
import sys
import threading


s3_client = boto3.client('s3')

# def download(local_file_name, s3_bucket, s3_object_key):

#     meta_data = s3_client.head_object(Bucket=s3_bucket, Key=s3_object_key)
#     total_length = int(meta_data.get('ContentLength', 0))
#     downloaded = 0

#     def progress(chunk):
#         nonlocal downloaded
#         downloaded += chunk
#         done = int(50 * downloaded / total_length)
#         sys.stdout.write("\r[%s%s]" % ('=' * done, ' ' * (50-done)) )
#         sys.stdout.flush()

#     print(f'Downloading {s3_object_key}')
#     with open(local_file_name, 'wb') as f:
#         s3_client.download_fileobj(s3_bucket, s3_object_key, f, Callback=progress)


# download('a.mp4', 'nschmidt', 'greenview-1007/clark_hill_vineyard/R33_GH010108.MP4')


local_file_name = 'a.mp4'
s3_bucket = 'nschmidt'
s3_object_key = 'greenview-1007/clark_hill_vineyard/R33_GH010108.MP4'
with open(local_file_name, 'wb') as f:
    s3_client.download_fileobj(s3_bucket, s3_object_key, f)
