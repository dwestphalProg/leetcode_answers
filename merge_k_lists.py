# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def mergeKLists(self, lists: list[ListNode | None]) -> ListNode | None:
        dummy = ListNode()
        tail = dummy

        while any(head is not None for head in lists):
            min_index = min(
                (i for i, head in enumerate(lists) if head is not None),
                key=lambda i: lists[i].val
            )

            node = lists[min_index]
            lists[min_index] = node.next  # advance that list's head

            tail.next = ListNode(node.val)  # append a new node
            tail = tail.next

        return dummy.next