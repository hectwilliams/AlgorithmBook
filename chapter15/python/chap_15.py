import bst 

bst_obj = bst.BST()

arr = [50, 40, 100, 30, 75, 150, 200]
for num in arr:
    bst_obj.add(num)

print(bst_obj.smallest_distance())
print(bst_obj.partition(44))