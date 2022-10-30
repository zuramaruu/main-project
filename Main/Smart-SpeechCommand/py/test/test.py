import requests

print(requests.get("http://192.168.200.6:5000").content)
print(type(requests.get("http://192.168.200.6:5000").content))
print(requests.get("http://192.168.200.6:5000").content.decode("utf-8"))
val = requests.get("http://192.168.200.6:5000").content.decode("utf-8").split(" ")
for i in val:
    print(i)
