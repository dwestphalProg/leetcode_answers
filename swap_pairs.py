# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def swapPairs(self, head: ListNode | None) -> ListNode | None:
        if head is None or head.next is None:
            return head
        base = head.next
        prev_head = head
        while head is not None and head.next is not None:
            head_next = head.next
            prev_head.next = head_next
            head.next = head_next.next
            head_next.next = head
            prev_head = head
            head = head.next

        return base





