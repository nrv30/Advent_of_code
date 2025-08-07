import hashlib

def gen_hash(key, i):
    return hashlib.md5((key + str(i)).encode()).hexdigest()

key = "bgvyzdsv"
i = 0
md5_hash = None
while(True):
    md5_hash = gen_hash(key, i)
    print(md5_hash)
    if str(md5_hash)[:6] == '000000': break
    i+=1
print(i)