from collections import defaultdict

class LRUCache:
	def __init__(self, capacity: int):
		self.cache = DoubleList()
		self.map = defaultdict(ListNode)
		self.cap = capacity

	def get(self, key: int) -> int:
		if key not in self.map:
			return -1
        
		self.makeRecently(key)
		return self.map[key].val

	def put(self, key: int, value: int) -> None:
		if key in self.map:
			self.deleteKey(key)
			self.addRecently(key,value)
			return

		if self.cap == self.cache.size():
			self.removeLeastRecently()

		self.addRecently(key, value)

	def makeRecently(self, key):
		node = self.map[key]
		self.cache.remove(node)
		self.cache.addLast(node)

	def addRecently(self, key, val):
		node = ListNode(val = val, key = key)
		self.cache.addLast(node)
		self.map[key] = node

	def deleteKey(self, key):
		node = self.map[key]
		self.cache.remove(node)
		self.map.pop(key)

	def removeLeastRecently(self):
		node = self.cache.removeFirst()
		self.map.pop(node.key)


class ListNode:
	def __init__(self, val = 0, key = 0, next = None, prev = None):
		self.val = val
		self.key = key
		self.next = next
		self.prev = prev


class DoubleList:
	def __init__(self):
		self.head = ListNode()
		self.tail = ListNode()
		self.head.next = self.tail
		self.tail.prev = self.head
		self.sz = 0

	def addLast(self, node):
		node.prev = self.tail.prev
		node.next = self.tail
		self.tail.prev.next = node
		self.tail.prev = node
		self.sz += 1

	def remove(self, node):
		node.prev.next = node.next
		node.next.prev = node.prev
		self.sz -= 1

	def removeFirst(self):
		if self.head.next == self.tail:
			return
		first = self.head.next
		self.remove(self.head.next)
		return first

	def size(self):
		return self.sz