#labels.py
import boto3
from pprint import pprint
import requests
import image_helpers

client=boto3.client('rekognition')

imgurl ='https://www.planetware.com/wpimages/2020/02/france-in-pictures-beautiful-places-to-photograph-eiffel-tower.jpg'

#imgbytes = image_helpers.get_image_from_file('deer.jpg')
imgbytes = image_helpers.get_image_from_url(imgurl)
rekresp= client.detect_labels(Image={'Bytes': imgbytes}, MinConfidence=90)

pprint(rekresp)

print("here's what I see in the image:")
for label in rekresp['Labels']:
    print(label['Name'])

    