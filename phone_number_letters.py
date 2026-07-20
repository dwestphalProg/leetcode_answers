# My solution to https://leetcode.com/problems/letter-combinations-of-a-phone-number/submissions/2074067281/

from enum import Enum
from typing import List

from numpy import size

# enum
numberLetterDict = {
    '2' : ['a','b','c'],
    '3' : ['d','e','f'],
    '4' : ['g','h','i'],
    '5' : ['j','k','l'],
    '6' : ['m','n','o'],
    '7' : ['p','q','r','s'],
    '8' : ['t','u','v'],
    '9' : ['w','x','y','z']
}

def stringCom(currentString: str, digitEnum: List[str])-> List[str]:
    returnList: List[str] = []
    for letter in digitEnum:
        resultString = currentString + letter
        returnList.append(resultString)
    return returnList


def letterCombinations(digits: str) -> List[str]:
    returnList = [""]
    #Iterate through list of characters
    for digit in list(digits):
        nextList = []
        for prefix in returnList:
            nextList.extend(stringCom(prefix, numberLetterDict[digit]))
        returnList = nextList

    return returnList


if __name__ == "__main__":
    print("Final list: " + str(letterCombinations("34")))
    print("Final list: " + str(letterCombinations("55")))
