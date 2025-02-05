import hashlib

i=0

while True:
    if hashlib.md5(f'iwrupvqb{i}'.encode('utf-8')).hexdigest().startswith('000000'):
        print(i)
        break
    i+=1
