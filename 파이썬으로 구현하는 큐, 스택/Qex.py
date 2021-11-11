
#import queue
from queue import Queue
q=Queue(10000) #입력 제한이 10000인 큐 선언
q2=Queue() #크기 제한이 없는 큐
#
q.put(1)  #push
# 1 
print(q.qsize()) # size확인

q.get() #pop ->값을 반환하면서 pop을 한다.

print(q.qsize()) #size 확인

if q.empty():
    print("빈 큐입니다.\n")
else:
    print('비어있지 않습니다.\n')






