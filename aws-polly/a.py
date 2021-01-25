import boto3

polly_client = boto3.Session(profile_name="default").client('polly')

f = open('pride-and-prejudice.txt')
pride_and_prejudice = f.read()
f.close()

response = polly_client.synthesize_speech(VoiceId='Joanna',
                OutputFormat='mp3', 
                Text = pride_and_prejudice[:10000])

file = open('speech.mp3', 'wb')
file.write(response['AudioStream'].read())
file.close()
