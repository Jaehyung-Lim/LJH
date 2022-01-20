import boto3
import json

def recognize_celebrities(photo):
    client=boto3.client('rekognition')
    with open(photo, 'rb') as image:
        response = client.recognize_celebrities(Image={'Bytes': image.read()})
    #print(response)
    print('Detected faces for ' + photo)
    for celebrity in response['CelebrityFaces']:
        print ('Name: ' + celebrity['Name'])
        print ('Id: ' + celebrity['Id'])
        print ('KnownGender: ' + str(celebrity['KnownGender']))
        #print ('Smile: ' + celebrity['Smile'])
        print ('Position:')
        print ('Left: ' + '{:.2f}'.format(celebrity['Face']['BoundingBox']
        ['Height']))
        print ('Top: ' + '{:.2f}'.format(celebrity['Face']['BoundingBox']
        ['Top']))
        for url in celebrity['Urls']:
            print (' ' + url)
        print

    return len(response['CelebrityFaces'])

def main():
    photo='image/tony.jpg'
    celeb_count=recognize_celebrities(photo)
    print("Celebrities detected: " + str(celeb_count))

if __name__ == "__main__":
    main()