import queue
q=queue.Queue()

for i in range(10):
    q.put(i)
#0,1,2,3, '''  8, 9
print('사이즈: %d'%q.qsize())

sz=q.qsize()

# for i in range(sz):
#     print(q.get())

while not q.empty():
    print(q.get())

# 0 1 2 3 
    
