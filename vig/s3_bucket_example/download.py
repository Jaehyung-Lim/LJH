import boto3

s3=boto3.client('s3')

bucket_name='vigwinter'

object_name='actor.jpg'

file_name_to_save = 'image/' + object_name

s3.download_file(bucket_name, object_name,file_name_to_save)