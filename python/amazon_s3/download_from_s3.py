
import sys
import boto3

def download_from_s3(s3path, local_file_name):
    s3_bucket, s3_object_key = s3path.replace("s3://", "").split("/", 1)
    s3_client = boto3.client('s3')
    meta_data = s3_client.head_object(Bucket=s3_bucket, Key=s3_object_key)
    total_length = int(meta_data.get('ContentLength', 0))
    downloaded = 0
    def progress(chunk):
        nonlocal downloaded
        downloaded += chunk
        done = int(50 * downloaded / total_length)
#        sys.stdout.write("\r" + str(downloaded) +"/"+ str(total_length))
        sys.stdout.write("\r[%s%s]" % ('=' * done, ' ' * (50-done)) )
        sys.stdout.flush()
    print(f'Downloading {s3_object_key}')
    with open(local_file_name, 'wb') as f:
        s3_client.download_fileobj(s3_bucket, s3_object_key, f, Callback=progress)
        print('')


# download_from_s3(s3path, 'tmp.mp4')

