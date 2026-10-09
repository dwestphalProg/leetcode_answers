class Solution:
    def generateParenthesis(self, n: int) -> list[str]:
        strings = {"()"}

        for _ in range(n - 1):
            new_strings = set()

            for s in strings:
                for pos in range(len(s) + 1):
                    # candidate = s[:pos] + "()" + s[pos:]
                    # if self.is_valid(candidate):
                    new_strings.add(s[:pos] + "()" + s[pos:])

            strings = new_strings

        return list(strings)

    @staticmethod
    def is_valid(s: str) -> bool:
        balance = 0
        for char in s:
            balance += 1 if char == "(" else -1
            if balance < 0:
                return False
        return balance == 0