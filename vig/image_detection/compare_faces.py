import boto3

def compare_faces(sourceFile, targetFile):

    client=boto3.client('rekognition')

    imageSource=open(sourceFile, 'rb')
    imageTarget=open(targetFile, 'rb')

    response=client.compare_faces(SimilarityThreshold=80,
                                  SourceImage={'Bytes': imageSource.read()},
                                  TargetImage={'Bytes': imageTarget.read()})
    
    for faceMatch in response['FaceMatches']:
        position = faceMatch['Face']['BoundingBox']
        similarity = str(faceMatch['Similarity'])
        print('The face at ' + ' ' +
        str(position['Top']) +
        ' matches with ' + similarity + '% confidence')

    imageSource.close()
    imageTarget.close()
    return len(response['FaceMatches'])

def main():
    source_file='image/박보검.jpg'
    target_file='image/동석1.jpg'
    face_matches=compare_faces(source_file, target_file)
    print("Face matches: " + str(face_matches))

if __name__ == "__main__":
    main()

