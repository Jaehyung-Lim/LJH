import queue

stack=queue.LifoQueue()

for i in range(10):
    stack.put(i)

sz=stack.qsize()

while not stack.empty():
    print(stack.get())
    