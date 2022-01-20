import boto3

#S3 클라이언트 생성
s3 = boto3.client('s3')

#S3에 있는 현재 버킷 리스트의 정보 가져오기
res=s3.list_buckets()

#print(res['Buckets'])

#for list in res['Buckets']:
#   print(list['Name'])

buckets = [bucket['Name'] for bucket in res['Buckets']]
print(buckets)

#S3 Buckets 이름 출력
print("Bucket Name: %s " % buckets)

#여기까지 이름 출력하는 것.

bucket_name='vigwinter'

#root(vig)부터 
file_name='image/girls.jpg'

file_name_in_bucket = 'girls.jpg'

s3.upload_file(file_name, bucket_name, file_name_in_bucket)
