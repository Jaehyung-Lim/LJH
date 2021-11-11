from queue import LifoQueue
q=LifoQueue(10000) #입력 제한이 10000인 스택 선언
q2=LifoQueue() #크기 제한이 없는 스택

q.put(1)  #push
q.put(2)
q.put(3)

print(q.qsize()) # size확인

q.get() #pop ->값을 반환하면서 pop을 한다.

print(q.qsize()) #size 확인

if q.empty():
    print("빈 큐입니다.\n")
else:
    print('비어있지 않습니다.\n')


