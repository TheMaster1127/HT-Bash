import os
import platform
import re
import sys

def LoopParseFunc(var, delimiter1="", delimiter2=""):
    if not delimiter1 and not delimiter2:
        # If no delimiters are provided, return a list of characters
        items = list(var)
    else:
        # Construct the regular expression pattern for splitting the string
        pattern = r'[' + re.escape(delimiter1) + re.escape(delimiter2) + r']+'
        # Split the string using the constructed pattern
        items = re.split(pattern, var)
    return items

# used the print func

# Convert value to string
def STR(value):
    if isinstance(value, (int, float)):
        return str(value)
    elif isinstance(value, bool):
        return "1" if value else "0"
    elif isinstance(value, str):
        return value  # If the value is already a string, return it as-is
    else:
        raise TypeError("Unsupported type")

# Convert value to integer
def INT(value):
    try:
        # Try converting the value to an integer
        return int(float(value))
    except ValueError:
        # If conversion fails, raise a TypeError
        raise TypeError("Cannot convert to integer")

# Function to find the position of needle in haystack (str overload)
def InStr(haystack: str, needle: str) -> int:
    pos = haystack.find(needle)
    return pos + 1 if pos != -1 else 0

def FileDelete(path: str) -> bool:
    # Check if the file exists and remove it
    if os.path.exists(path):
        os.remove(path)
        return True
    return False

def FileAppend(content: str, path: str) -> bool:
    # Open the file in append mode and write the content
    try:
        with open(path, 'a') as file:
            file.write(content)
        return True
    except IOError:
        print("Error: Could not open the file for appending.")
        return False

def FileRead(path: str) -> str:
    # Check if the path is absolute, if not prepend the current working directory
    if not os.path.isabs(path):
        path = os.path.join(os.getcwd(), path)
    # Open and read the file content with utf-8 encoding to avoid decode errors
    with open(path, 'r', encoding='utf-8') as file:
        return file.read()

def StrLen(s: str) -> int:
    # Return the length of the given string
    return len(s)

def Chr(number: int) -> str:
    # Return the character corresponding to the Unicode code point, or an empty string if out of range
    return chr(number) if 0 <= number <= 0x10FFFF else ""

def SubStr(s, startPos, length=-1):
    result = ""
    strLen = len(s)
    # Handle negative starting positions (counting from the end)
    if startPos < 0:
        startPos = strLen + startPos
        if startPos < 0:
            startPos = 0  # Ensure it doesn't go beyond the start of the string
    else:
        startPos -= 1  # Convert to 0-based index for internal operations
    # Handle length
    if length < 0:
        length = strLen - startPos  # Length to the end of the string
    elif startPos + length > strLen:
        length = strLen - startPos  # Adjust length to fit within the string
    # Extract the substring
    result = s[startPos:startPos + length]
    return result

def Trim(inputString):
    return inputString.strip() if inputString else ""

def StrReplace(originalString, find, replaceWith):
    return originalString.replace(find, replaceWith)

def StringTrimLeft(input, numChars):
    return input[numChars:] if numChars <= len(input) else input

def StringTrimRight(input, numChars):
    return input[:-numChars] if numChars <= len(input) else input

def StrLower(string):
    return string.lower()

def StrSplit(inputStr, delimiter, num):
    parts = inputStr.split(delimiter)
    return parts[num - 1] if 0 < num <= len(parts) else ""

def Mod(dividend, divisor):
    return dividend % divisor

def isWindows():
    return platform.system().lower() == "windows"

def GetParams():
    # Check if any command line arguments are provided
    if len(sys.argv) < 2:
        return ""
    # Store the provided command line arguments
    params = []
    for arg in sys.argv[1:]:
        if os.path.exists(arg):
            arg = os.path.abspath(arg)
        params.append(arg)
    return "\n".join(params)

def RegExReplace(inputStr, regexPattern, replacement):
    # Convert `$1`, `$2`, etc. to `\1`, `\2` so Python understands
    replacement = re.sub(r'\$(\d+)', r'\\\1', replacement)
    regex = re.compile(regexPattern, re.MULTILINE)
    return regex.sub(replacement, inputStr)

def RegExMatch(haystack, needle):
    match = re.search(needle, haystack)
    return match.start() + 1 if match else 0 # 1-based index or 0 if no match

def HTVM_Append(arr, value):
    arr.append(value)

def HTVM_Pop(arr):
    if arr:
        arr.pop()

def HTVM_Size(arr):
    return len(arr)


# HT-Bash
# Licensed under the GNU General Public License v3 (GPL v3)
# Copyright (c) 2026 TheMaster1127 aka Mr. Compiler
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.
#
# start of HT-Lib.htvm
# global vars NEEDED
HT_LIB_theIdNumOfThe34 = 0
HT_Lib_theIdNumOfThe34theVar = []
#;;;;;;;;;;;;;;;;;;;;;;;;;
def preserveStrings(code, keyWordEscpaeChar = "\\"):
    global HT_Lib_theIdNumOfThe34theVar
    global HT_LIB_theIdNumOfThe34
    HT_LIB_theIdNumOfThe34 = 0
    HT_Lib_theIdNumOfThe34theVar = []
    getAllCharForTheFurtureSoIcanAddEscapeChar = []
    ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = ""
    str21 = ""
    htCodeOUT754754 = ""
    OutFixDoubleQuotesInsideDoubleQuotes = ""
    fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0
    removeNexFixkeyWordEscpaeChar = 0
    areWEinSome34sNum = 0
    items1 = LoopParseFunc(code)
    for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
        HTVM_Append(HT_Lib_theIdNumOfThe34theVar, "")
        HTVM_Append(HT_Lib_theIdNumOfThe34theVar, "")
    items2 = LoopParseFunc(code)
    for A_Index2 , A_LoopField2 in enumerate(items2, start=0):
        HT_Lib_theIdNumOfThe34theVar[A_Index2] = HT_Lib_theIdNumOfThe34theVar[A_Index2] + Chr(34)
        HTVM_Append(getAllCharForTheFurtureSoIcanAddEscapeChar, A_LoopField2)
    HTVM_Append(getAllCharForTheFurtureSoIcanAddEscapeChar, " ")
    ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuuhuuhtheidFor" + str21 + "--" + str21 + "asds" + str21 + "as--" + str21 + "theuhtuwaesphoutr" + Chr(34)
    items3 = LoopParseFunc(code)
    for A_Index3 , A_LoopField3 in enumerate(items3, start=0):
        if (A_LoopField3 == keyWordEscpaeChar and getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index3 + 1] == Chr(34)):
            fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1
            OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes
        else:
            if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1):
                OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField3
            else:
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0
    code = OutFixDoubleQuotesInsideDoubleQuotes
    if (keyWordEscpaeChar != Chr(92)):
        code = StrReplace(code, Chr(92), Chr(92) + Chr(92))
    if (keyWordEscpaeChar == Chr(92)):
        items4 = LoopParseFunc(code)
        for A_Index4 , A_LoopField4 in enumerate(items4, start=0):
            if (A_LoopField4 == Chr(34)):
                areWEinSome34sNum += 1
            if (areWEinSome34sNum == 1):
                if (A_LoopField4 != Chr(34)):
                    if (A_LoopField4 == keyWordEscpaeChar):
                        HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] = HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] + Chr(92)
                    else:
                        HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] = HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] + A_LoopField4
                else:
                    HT_LIB_theIdNumOfThe34 += 1
                    htCodeOUT754754 += "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(HT_LIB_theIdNumOfThe34) + Chr(65) + Chr(65)
            if (areWEinSome34sNum == 2 or areWEinSome34sNum == 0):
                if (A_LoopField4 != Chr(34)):
                    htCodeOUT754754 += A_LoopField4
                areWEinSome34sNum = 0
    else:
        items5 = LoopParseFunc(code)
        for A_Index5 , A_LoopField5 in enumerate(items5, start=0):
            if (A_LoopField5 == Chr(34)):
                areWEinSome34sNum += 1
            if (areWEinSome34sNum == 1):
                if (A_LoopField5 != Chr(34)):
                    if (A_LoopField5 == keyWordEscpaeChar and keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index5 + 1]):
                        HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] = HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] + keyWordEscpaeChar
                        removeNexFixkeyWordEscpaeChar = 1
                    elif (A_LoopField5 == keyWordEscpaeChar):
                        if (removeNexFixkeyWordEscpaeChar != 1):
                            HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] = HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] + Chr(92)
                        else:
                            removeNexFixkeyWordEscpaeChar = 0
                    else:
                        HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] = HT_Lib_theIdNumOfThe34theVar[HT_LIB_theIdNumOfThe34] + A_LoopField5
                else:
                    HT_LIB_theIdNumOfThe34 += 1
                    htCodeOUT754754 += "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(HT_LIB_theIdNumOfThe34) + Chr(65) + Chr(65)
            if (areWEinSome34sNum == 2 or areWEinSome34sNum == 0):
                if (A_LoopField5 != Chr(34)):
                    htCodeOUT754754 += A_LoopField5
                areWEinSome34sNum = 0
    code = htCodeOUT754754
    for A_Index6 in range(0, HT_LIB_theIdNumOfThe34):
        HT_Lib_theIdNumOfThe34theVar[A_Index6] = HT_Lib_theIdNumOfThe34theVar[A_Index6] + Chr(34)
    HTVM_Append(HT_Lib_theIdNumOfThe34theVar, Chr(34))
    return code
#;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;
def restoreStrings(codeOUT, keyWordEscpaeChar = Chr(92)):
    for A_Index7 in range(0, HT_LIB_theIdNumOfThe34):
        if (HT_LIB_theIdNumOfThe34 == A_Index7 + 1):
            codeOUT = StrReplace(codeOUT, "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(A_Index7 + 1) + Chr(65) + Chr(65), StrReplace(HT_Lib_theIdNumOfThe34theVar[A_Index7 + 1], keyWordEscpaeChar, "\\") + Chr(34))
        else:
            codeOUT = StrReplace(codeOUT, "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(A_Index7 + 1) + Chr(65) + Chr(65), StrReplace(HT_Lib_theIdNumOfThe34theVar[A_Index7 + 1], keyWordEscpaeChar, "\\"))
    return codeOUT
def cleanUpFirst(code):
    code = StrReplace(code, Chr(13), "")
    out = ""
    items8 = LoopParseFunc(code, "\n", "\r")
    for A_Index8 , A_LoopField8 in enumerate(items8, start=0):
        out += Trim(A_LoopField8) + Chr(10)
    out = StringTrimRight(out, 1)
    return out
def getLangParams(binName, langExtension, extra = ""):
    params = Trim(GetParams())
    if (params == ""):
        if (isWindows()):
            print("Usage:" + Chr(10) + Trim(binName) + " your_file." + Trim(langExtension) + " " + Trim(extra))
        else:
            print("Usage:" + Chr(10) + "./" + Trim(binName) + " your_file." + Trim(langExtension) + " " + Trim(extra))
        return ""
    else:
        # Loop through the parameters and return the VERY FIRST one.
        items9 = LoopParseFunc(params, "\n", "\r")
        for A_Index9 , A_LoopField9 in enumerate(items9, start=0):
            first_param = Trim(A_LoopField9)
            if (first_param != ""):
                return first_param
        # If all lines were empty for some reason, return nothing.
        return ""
    # This is now unreachable, but good practice to keep.
    return "MASSIVE ERROR"
def saveOutput(outCode, fileName):
    FileDelete(Trim(fileName))
    FileAppend(Trim(outCode), Trim(fileName))
    print("Generation finished: " + Trim(fileName) + " generated.")
def beginning(line, what):
    if (SubStr(line, 1, StrLen(what)) == what):
        return True
    return False
def formatCurlyBracesForParsing(code, openBrace = "{", closeBrace = "}"):
    code = StrReplace(code, openBrace, Chr(10) + "{" + Chr(10))
    code = StrReplace(code, closeBrace, Chr(10) + "}" + Chr(10))
    code = cleanUpFirst(code)
    return code
def handleComments(code, commentKeyword = ";"):
    str1 = ""
    items10 = LoopParseFunc(code, "\n", "\r")
    for A_Index10 , A_LoopField10 in enumerate(items10, start=0):
        str1 += StrSplit(A_LoopField10, commentKeyword, 1) + Chr(10)
    code = StringTrimRight(str1, 1)
    return code
# Define the function to check odd spaces at the beginning
def CheckOddLeadingSpaces(string123):
    # Initialize a variable to count the spaces
    spaceCount = 0
    # Loop through the string one character at a time
    items11 = LoopParseFunc(string123)
    for A_Index11 , A_LoopField11 in enumerate(items11, start=0):
        # Check if the current character is a space
        if (A_LoopField11 == Chr(32)):
            spaceCount += 1
        else:
            # When we hit a non-space character, break the loop
            break
    # Return true if the number of spaces is odd, false otherwise
    sdsfawasd = STR(Mod(spaceCount, 2) == 1)
    #MsgBox, % sdsfawasd
    return sdsfawasd
def RepeatSpaces(count):
    spaces = ""
    for A_Index12 in range(0, count):
        spaces += Chr(32)
    return spaces
# if you wanna convert to python, nim etc... indentation style we set modeCurlyBracesOn to 0
def indent_nested_curly_braces(input_string, modeCurlyBracesOn = 1):
    indent_size = 4
    current_indent = 0
    result = ""
    trimmed_line = ""
    resultOut = ""
    culyOpenFix = "{"
    culyCloseFix = "}"
    #MsgBox, % input_string
    items13 = LoopParseFunc(input_string, "\n", "\r")
    for A_Index13 , A_LoopField13 in enumerate(items13, start=0):
        trimmed_line = Trim(A_LoopField13)
        if (trimmed_line == Chr(123)):
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + Chr(10)
            current_indent = current_indent + indent_size
        elif (trimmed_line == Chr(125)):
            current_indent = current_indent - indent_size
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + Chr(10)
        else:
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + Chr(10)
    if (modeCurlyBracesOn == 0):
        resultOut = ""
        items14 = LoopParseFunc(result, "\n", "\r")
        for A_Index14 , A_LoopField14 in enumerate(items14, start=0):
            if (Trim(A_LoopField14) != "{" and Trim(A_LoopField14) != "}"):
                resultOut += A_LoopField14 + Chr(10)
        result = StringTrimRight(resultOut, 1)
    else:
        # format curly braces in a K&R style
        lookIntoFurture = []
        items15 = LoopParseFunc(result, "\n", "\r")
        for A_Index15 , A_LoopField15 in enumerate(items15, start=0):
            HTVM_Append(lookIntoFurture, Trim(A_LoopField15))
        HTVM_Append(lookIntoFurture, " ")
        resultOut = ""
        skipNext = 0
        items16 = LoopParseFunc(result, "\n", "\r")
        for A_Index16 , A_LoopField16 in enumerate(items16, start=0):
            skipNext -= 1
            if (skipNext <= 0):
                skipNext = 0
            if (Trim(lookIntoFurture[A_Index16 + 1]) == "{"):
                resultOut += A_LoopField16 + " " + culyOpenFix + Chr(10)
                skipNext = 2
            if (skipNext == 0):
                resultOut += A_LoopField16 + Chr(10)
        result = StringTrimRight(resultOut, 1)
        lookIntoFurture2 = []
        items17 = LoopParseFunc(result, "\n", "\r")
        for A_Index17 , A_LoopField17 in enumerate(items17, start=0):
            HTVM_Append(lookIntoFurture2, Trim(A_LoopField17))
        HTVM_Append(lookIntoFurture2, " ")
        resultOut = ""
        skipNext = 0
        addSpacesAtTheBegginig = None
        items18 = LoopParseFunc(result, "\n", "\r")
        for A_Index18 , A_LoopField18 in enumerate(items18, start=0):
            skipNext -= 1
            if (skipNext <= 0):
                skipNext = 0
            if (Trim(A_LoopField18) == "}" and Trim(lookIntoFurture2[A_Index18 + 1]) == "else {"):
                skipNext = 2
                addSpacesAtTheBegginig = ""
                items19 = LoopParseFunc(A_LoopField18)
                for A_Index19 , A_LoopField19 in enumerate(items19, start=0):
                    if (A_LoopField19 == " "):
                        if (A_LoopField19 != " "):
                            break
                        addSpacesAtTheBegginig += StrReplace(A_LoopField19, "}", culyCloseFix)
                resultOut += addSpacesAtTheBegginig + culyCloseFix + " else " + culyOpenFix + Chr(10)
            if (skipNext == 0):
                resultOut += A_LoopField18 + Chr(10)
        result = StringTrimRight(resultOut, 1)
    resultOut = ""
    ALoopField = None
    items20 = LoopParseFunc(result, "\n", "\r")
    for A_Index20 , A_LoopField20 in enumerate(items20, start=0):
        if (CheckOddLeadingSpaces(A_LoopField20) == "1"):
            ALoopField = StringTrimLeft(A_LoopField20, 1)
            resultOut += ALoopField + Chr(10)
        else:
            resultOut += A_LoopField20 + Chr(10)
    result = StringTrimRight(resultOut, 1)
    # Return the result
    return result
# end of HT-Lib.htvm
def getLastChars(line, count):
    out = ""
    out_temp = ""
    len = StrLen(line)
    for A_Index21 in range(0, count):
        len -= 1
        items22 = LoopParseFunc(line)
        for A_Index22 , A_LoopField22 in enumerate(items22, start=0):
            if (A_Index22 == len):
                out_temp = A_LoopField22
        out = out_temp + out
    return out
def restoreStrings_bash(codeOUT, keyWordEscpaeChar = Chr(92)):
    for A_Index23 in range(0, HT_LIB_theIdNumOfThe34):
        if (HT_LIB_theIdNumOfThe34 == A_Index23 + 1):
            if (InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\a") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\b") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\e") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\f") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\r") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\t") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\v") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\n")):
                codeOUT = StrReplace(codeOUT, "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(A_Index23 + 1) + Chr(65) + Chr(65), "$" + StrReplace(StrReplace(StrReplace(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], Chr(34), Chr(39)), "$", "\\$"), keyWordEscpaeChar, "\\") + Chr(39))
            else:
                codeOUT = StrReplace(codeOUT, "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(A_Index23 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "$", "\\$"), keyWordEscpaeChar, "\\") + Chr(34))
        else:
            if (InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\a") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\b") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\e") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\f") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\r") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\t") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\v") or InStr(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "\\n")):
                codeOUT = StrReplace(codeOUT, "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(A_Index23 + 1) + Chr(65) + Chr(65), "$" + StrReplace(StrReplace(StrReplace(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], Chr(34), Chr(39)), "$", "\\$"), keyWordEscpaeChar, "\\"))
            else:
                codeOUT = StrReplace(codeOUT, "VYIGUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFC" + Chr(65) + Chr(65) + STR(A_Index23 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(HT_Lib_theIdNumOfThe34theVar[A_Index23 + 1], "$", "\\$"), keyWordEscpaeChar, "\\"))
    return codeOUT
def transformBracesToHT_Bash(code):
    out = ""
    blockStack = []
    ifNestLevel = 0
    loopNestLevel = 0
    items24 = LoopParseFunc(code, "\n", "\r")
    for A_Index24 , A_LoopField24 in enumerate(items24, start=0):
        currentLine = A_LoopField24
        trimmedLine = StrLower(Trim(currentLine))
        if (SubStr(trimmedLine, 1, 5) == "func "):
            HTVM_Append(blockStack, "func:0")
            out += currentLine + Chr(10)
            continue
        # ===================================================================
        # IF BLOCKS
        # ===================================================================
        if (SubStr(trimmedLine, 1, 3) == "if "):
            ifNestLevel += 1
            HTVM_Append(blockStack, "if:" + STR(ifNestLevel))
            newIfKeyword = "if"
            conditionPart = SubStr(Trim(currentLine), 3)
            modifiedIfLine = newIfKeyword + " " + conditionPart
            indentLen = InStr(StrLower(currentLine), "if") - 1
            indentation = SubStr(currentLine, 1, indentLen)
            out += indentation + modifiedIfLine + Chr(10)
            continue
        # ===================================================================
        # LOOP BLOCKS
        # ===================================================================
        if (SubStr(trimmedLine, 1, 5) == "loop,"):
            loopNestLevel += 1
            HTVM_Append(blockStack, "loop:" + STR(loopNestLevel))
            newLoopKeyword = "loop"
            loopParams = SubStr(Trim(currentLine), 6)
            modifiedLoopLine = newLoopKeyword + ", " + Trim(loopParams)
            indentLen = InStr(StrLower(currentLine), "loop,") - 1
            indentation = SubStr(currentLine, 1, indentLen)
            out += indentation + modifiedLoopLine + Chr(10)
            continue
        if (SubStr(trimmedLine, 1, 6) == "while "):
            loopNestLevel += 1
            HTVM_Append(blockStack, "while:" + STR(loopNestLevel))
            newLoopKeyword = "while"
            loopParams = SubStr(Trim(currentLine), 6)
            modifiedLoopLine = newLoopKeyword + " " + loopParams
            indentLen = InStr(StrLower(currentLine), "while") - 1
            indentation = SubStr(currentLine, 1, indentLen)
            out += indentation + modifiedLoopLine + Chr(10)
            continue
        if (SubStr(trimmedLine, 1, 12) == "loop, parse,"):
            loopNestLevel += 1
            HTVM_Append(blockStack, "loopp:" + STR(loopNestLevel))
            newLoopKeyword = "loop, parse,"
            loopParams = SubStr(Trim(currentLine), 12)
            modifiedLoopLine = newLoopKeyword + " " + loopParams
            indentLen = InStr(StrLower(currentLine), "loop, parse,") - 1
            indentation = SubStr(currentLine, 1, indentLen)
            out += indentation + modifiedLoopLine + Chr(10)
            continue
        if (trimmedLine == "loop"):
            loopNestLevel += 1
            HTVM_Append(blockStack, "loopi:" + STR(loopNestLevel))
            newLoopKeyword = "loop"
            loopParams = SubStr(Trim(currentLine), 4)
            modifiedLoopLine = newLoopKeyword + "," + loopParams
            indentLen = InStr(StrLower(currentLine), "loop") - 1
            indentation = SubStr(currentLine, 1, indentLen)
            out += indentation + "loop" + Chr(10)
            continue
        # ===================================================================
        # BRACES HANDLING
        # ===================================================================
        if (trimmedLine == "{"):
            continue
        if (trimmedLine == "}"):
            if (HTVM_Size(blockStack) == 0):
                out += "SYNTAX ERROR: Unmatched closing brace found in HT-Bash." + Chr(10)
                continue
            blockInfo = blockStack[HTVM_Size(blockStack) - 1]
            HTVM_Pop(blockStack)
            blockType = StrSplit(blockInfo, ":", 1)
            level = INT(StrSplit(blockInfo, ":", 2))
            indentLen = InStr(currentLine, "}") - 1
            indentation = SubStr(currentLine, 1, indentLen)
            if (blockType == "func"):
                out += indentation + "funcend" + Chr(10)
            elif (blockType == "if"):
                ender = "fi"
                out += indentation + ender + Chr(10)
                ifNestLevel -= 1
            elif (blockType == "loop"):
                ender = "done"
                out += indentation + ender + Chr(10)
                loopNestLevel -= 1
            elif (blockType == "loopi"):
                ender = "done"
                out += indentation + ender + Chr(10)
                loopNestLevel -= 1
            elif (blockType == "while"):
                ender = "done2"
                out += indentation + ender + Chr(10)
                loopNestLevel -= 1
            elif (blockType == "loopp"):
                ender = "pdone"
                out += indentation + ender + Chr(10)
                loopNestLevel -= 1
            continue
        out += currentLine + Chr(10)
    if (HTVM_Size(blockStack) > 0):
        out += "SYNTAX ERROR: " + STR(HTVM_Size(blockStack)) + " unclosed blocks at end of file in HT-Bash." + Chr(10)
    return Trim(out)
def expressionTranspiler_2(line, mode = 0):
    out = ""
    isConcat = 0
    isFirstTimeMath = 0
    isFirstTimeMath2 = 0
    items25 = LoopParseFunc(line, " ")
    for A_Index25 , A_LoopField25 in enumerate(items25, start=0):
        if (A_LoopField25 == "."):
            isConcat = 1
            break
    if (isConcat == 1):
        items26 = LoopParseFunc(line, " ")
        for A_Index26 , A_LoopField26 in enumerate(items26, start=0):
            if (RegExMatch(A_LoopField26, "^-?\\d+(\\.\\d+)?$")):
                out += Chr(34) + A_LoopField26 + Chr(34) + " "
            elif (InStr(A_LoopField26, "GUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFCAA")):
                out += A_LoopField26 + " "
            elif (RegExMatch(A_LoopField26, "^[a-zA-Z_][a-zA-Z0-9_]*$")):
                out += Chr(34) + "$" + A_LoopField26 + Chr(34) + " "
            else:
                out += A_LoopField26 + " "
        line = Trim(out)
        out = ""
        items27 = LoopParseFunc(line, " ")
        for A_Index27 , A_LoopField27 in enumerate(items27, start=0):
            if (A_LoopField27 == "."):
                out += ""
            else:
                out += A_LoopField27
    else:
        if (InStr(line, " + ") or InStr(line, " - ") or InStr(line, " * ") or InStr(line, " / ") or InStr(line, " ** ") or InStr(line, " % ") or RegExMatch(line, "^-?\\d+(\\.\\d+)?$")):
            isFirstTimeMath = 1
            if (mode == 0):
                out += "$(("
            items28 = LoopParseFunc(line, " ")
            for A_Index28 , A_LoopField28 in enumerate(items28, start=0):
                out += A_LoopField28
            if (mode == 0):
                out += "))"
        else:
            items29 = LoopParseFunc(line, " ")
            for A_Index29 , A_LoopField29 in enumerate(items29, start=0):
                if (RegExMatch(A_LoopField29, "^-?\\d+(\\.\\d+)?$")):
                    out += A_LoopField29 + " "
                elif (InStr(A_LoopField29, "GUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFCAA")):
                    out += A_LoopField29 + " "
                elif (RegExMatch(A_LoopField29, "^[a-zA-Z_][a-zA-Z0-9_]*$")):
                    out += Chr(34) + "$" + A_LoopField29 + Chr(34) + " "
                else:
                    out += A_LoopField29 + " "
            line = Trim(out)
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    return Trim(out)
def expressionTranspiler(line, mode = 0):
    out = ""
    temp = ""
    if (InStr(line, ".size(") == False and InStr(line, ".add(") == False and InStr(line, ".pop(") == False):
        line = Trim(StrReplace(line, "(", " ( "))
        line = Trim(StrReplace(line, ")", " ) "))
        if (RegExMatch(line, "(^|[^.])\\b([a-zA-Z_]\\w*)\\s*\\(")):
            line = Trim(StrReplace(line, ",", " "))
            line = Trim(StrReplace(line, "  ", " "))
            line = Trim(StrReplace(line, "(", " "))
            line = Trim(StrReplace(line, ")", ""))
            items30 = LoopParseFunc(line, " ")
            for A_Index30 , A_LoopField30 in enumerate(items30, start=0):
                temp = Trim(A_LoopField30)
                if (A_Index30 == 0):
                    out += "$(" + A_LoopField30 + " "
                else:
                    if (InStr(temp, "[@]")):
                        out += StringTrimRight(temp, 3) + " "
                    else:
                        out += expressionTranspiler_2(A_LoopField30, mode) + " "
            out = Trim(out) + ")"
        else:
            out = expressionTranspiler_2(line, mode)
    else:
        out = Trim(line)
    out = RegExReplace(out, "([a-zA-Z0-9_]+)\\[(.*?)\\]", Chr(34) + "${$1[$2]}" + Chr(34))
    out = RegExReplace(out, "([a-zA-Z0-9_]+)\\.size\\(\\)", "${#$1[@]}")
    return Trim(out)
code = ""
out = ""
str1 = ""
str2 = ""
str3 = ""
str4 = ""
str5 = ""
str6 = ""
str7 = ""
str8 = ""
str9 = ""
whereBeginFuncOptanalParams = 0
whereBeginFuncOptanalParams_help = 0
whereBeginFuncOptanalParams_help_once = 0
outTemp1 = ""
outTemp2 = ""
outTemp3 = ""
outTemp4 = ""
count = 0
mathMode = 0
firstLoop = 0
firstLoop_parse = 0
firstLoop_func = 0
firstLoop_parse_func = 0
inFunc = 0
fix_curly_else_if = ""
fix_curly_else_if_ARR = []
fixCode_runARR = []
fixCode_run = ""
fixCode_run_INT = 0
params = getLangParams("HT-Bash", "htsh")
if (params != ""):
    code = FileRead(params)
    items31 = LoopParseFunc(code, "\n", "\r")
    for A_Index31 , A_LoopField31 in enumerate(items31, start=0):
        if (SubStr(StrLower(Trim(A_LoopField31)), 1, 4) == "run "):
            str1 = Trim(StringTrimLeft(Trim(A_LoopField31), 4))
            HTVM_Append(fixCode_runARR, str1)
            fixCode_run += "run ht-bash_runrsfdhgiosdxxszpxx--ashdzxkcxwaSsdx--AA" + STR(fixCode_run_INT) + "AA" + Chr(10)
            fixCode_run_INT += 1
        else:
            fixCode_run += A_LoopField31 + Chr(10)
    code = Trim(fixCode_run)
    code = cleanUpFirst(code)
    code = preserveStrings(code)
    code = handleComments(code, ";")
    code = formatCurlyBracesForParsing(code)
    # code
    if (InStr(code, "{")):
        fix_curly_else_if = ""
        items32 = LoopParseFunc(code, "\n", "\r")
        for A_Index32 , A_LoopField32 in enumerate(items32, start=0):
            HTVM_Append(fix_curly_else_if_ARR, A_LoopField32)
        HTVM_Append(fix_curly_else_if_ARR, " ")
        items33 = LoopParseFunc(code, "\n", "\r")
        for A_Index33 , A_LoopField33 in enumerate(items33, start=0):
            if (Trim(A_LoopField33) == "}" and SubStr(Trim(StrLower(fix_curly_else_if_ARR[A_Index33 + 1])), 1, 8) == "else if "):
                fix_curly_else_if += ""
            elif (Trim(A_LoopField33) == "{" and SubStr(Trim(StrLower(fix_curly_else_if_ARR[A_Index33 - 1])), 1, 8) == "else if "):
                fix_curly_else_if += ""
            elif (Trim(A_LoopField33) == "}" and Trim(StrLower(fix_curly_else_if_ARR[A_Index33 + 1])) == "else"):
                fix_curly_else_if += ""
            elif (Trim(A_LoopField33) == "{" and Trim(StrLower(fix_curly_else_if_ARR[A_Index33 - 1])) == "else"):
                fix_curly_else_if += ""
            else:
                fix_curly_else_if += A_LoopField33 + Chr(10)
        code = Trim(fix_curly_else_if)
        code = transformBracesToHT_Bash(code)
    items34 = LoopParseFunc(code, "\n", "\r")
    for A_Index34 , A_LoopField34 in enumerate(items34, start=0):
        if (SubStr(StrLower(Trim(A_LoopField34)), 1, 4) == "run "):
            str1 = Trim(StringTrimLeft(A_LoopField34, 4))
            out += str1 + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 5) == "func "):
            firstLoop_func = 0
            firstLoop_parse_func = 0
            inFunc = 1
            str1 = ""
            str2 = ""
            str3 = ""
            str4 = ""
            str5 = ""
            str6 = ""
            str7 = ""
            str8 = ""
            str9 = ""
            whereBeginFuncOptanalParams = 0
            whereBeginFuncOptanalParams_help = 0
            whereBeginFuncOptanalParams_help_once = 0
            str1 = Trim(StringTrimLeft(A_LoopField34, 5))
            str1 = Trim(StringTrimRight(str1, 1))
            str2 = Trim(StrSplit(str1, "(", 1))
            str3 = Trim(StrSplit(str1, "(", 2))
            out += str2 + "() {" + Chr(10)
            str4 = ""
            if (str3 != ""):
                str4 = ""
                str6 = ""
                str7 = ""
                whereBeginFuncOptanalParams = 0
                items35 = LoopParseFunc(str3, ",")
                for A_Index35 , A_LoopField35 in enumerate(items35, start=0):
                    str5 = ""
                    if (InStr(A_LoopField35, " := ")):
                        whereBeginFuncOptanalParams_help_once += 1
                        if (whereBeginFuncOptanalParams_help_once == 1):
                            whereBeginFuncOptanalParams = A_Index35 + 1
                        str5 = Trim(StrSplit(A_LoopField35, " := ", 1))
                        str7 += Trim(StrSplit(A_LoopField35, " := ", 1)) + Chr(10)
                        str6 += expressionTranspiler(Trim(StrSplit(A_LoopField35, " := ", 2))) + Chr(10)
                        if (InStr(str5, "[@]")):
                            str5 = Trim(str5)
                            str5 = StringTrimRight(str5, 3)
                            str4 += "local -n " + Trim(str5) + "=" + "$" + STR(A_Index35 + 1) + Chr(10)
                        elif (InStr(str5, "[]")):
                            str5 = Trim(str5)
                            str5 = StringTrimRight(str5, 2)
                            str4 += "local -n " + Trim(str5) + "=" + "$" + STR(A_Index35 + 1) + Chr(10)
                        else:
                            str4 += "local " + Trim(str5) + "=" + Chr(34) + "$" + STR(A_Index35 + 1) + Chr(34) + Chr(10)
                    else:
                        str5 = A_LoopField35
                        if (InStr(str5, "[@]")):
                            str5 = Trim(str5)
                            str5 = StringTrimRight(str5, 3)
                            str4 += "local -n " + Trim(str5) + "=" + "$" + STR(A_Index35 + 1) + Chr(10)
                        elif (InStr(str5, "[]")):
                            str5 = Trim(str5)
                            str5 = StringTrimRight(str5, 2)
                            str4 += "local -n " + Trim(str5) + "=" + "$" + STR(A_Index35 + 1) + Chr(10)
                        else:
                            str4 += "local " + Trim(str5) + "=" + Chr(34) + "$" + STR(A_Index35 + 1) + Chr(34) + Chr(10)
            out += Trim(str4) + Chr(10)
            if (str6 != ""):
                str8 = ""
                whereBeginFuncOptanalParams_help = 0
                items36 = LoopParseFunc(str6, "\n", "\r")
                for A_Index36 , A_LoopField36 in enumerate(items36, start=0):
                    whereBeginFuncOptanalParams_help = A_Index36
                    items37 = LoopParseFunc(str7, "\n", "\r")
                    for A_Index37 , A_LoopField37 in enumerate(items37, start=0):
                        if (A_Index37 == whereBeginFuncOptanalParams_help):
                            str8 = A_LoopField37
                            break
                    if (Trim(str8) != ""):
                        out += "[ " + Chr(34) + "$#" + Chr(34) + " -lt " + STR(whereBeginFuncOptanalParams) + " ] && " + Trim(str8) + "=" + Trim(A_LoopField36) + Chr(10)
                    whereBeginFuncOptanalParams += 1
        elif (Trim(StrLower(A_LoopField34)) == "funcend" or Trim(StrLower(A_LoopField34)) == "endfunc"):
            out += "}" + Chr(10)
            inFunc = 0
        elif (Trim(StrLower(A_LoopField34)) == "return"):
            out += "echo" + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 7) == "return "):
            str1 = Trim(StringTrimLeft(A_LoopField34, 7))
            out += "echo " + expressionTranspiler(str1) + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 11) == "return_arr "):
            str1 = Trim(StringTrimLeft(A_LoopField34, 11))
            out += "printf " + Chr(34) + "%s\\n" + Chr(34) + " " + expressionTranspiler(str1) + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 6) == "print("):
            str1 = Trim(StringTrimLeft(A_LoopField34, 6))
            str1 = Trim(StringTrimRight(str1, 1))
            if (InStr(str1, "GUOYIYVIUCFCYIUCFCYIGCYGICFHYFHCTCFTFDFGYGFCAA")):
                out += "printf " + Chr(34) + "%s\\n" + Chr(34) + " " + Trim(str1) + " >&2" + Chr(10)
            else:
                out += "printf " + Chr(34) + "%s\\n" + Chr(34) + " " + expressionTranspiler(str1) + " >&2" + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 10) == "local arr "):
            str1 = Trim(StringTrimLeft(A_LoopField34, 10))
            str2 = Trim(StrSplit(str1, " := ", 1))
            str3 = Trim(StrSplit(str1, " := ", 2))
            if (InStr(str1, " := ")):
                str3 = StrReplace(str3, "[", "")
                str3 = StrReplace(str3, "]", "")
                str4 = ""
                if (InStr(str3, ",")):
                    items38 = LoopParseFunc(str3, ",")
                    for A_Index38 , A_LoopField38 in enumerate(items38, start=0):
                        str4 += expressionTranspiler(A_LoopField38) + " "
                    str3 = Trim(str4)
                out += "local " + str2 + "=(" + str3 + ")" + Chr(10)
            else:
                out += "local " + str2 + "=(" + expressionTranspiler(str3) + ")" + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 10) == "local str " or SubStr(StrLower(A_LoopField34), 1, 10) == "local int " or SubStr(StrLower(A_LoopField34), 1, 10) == "local var "):
            str1 = Trim(StringTrimLeft(A_LoopField34, 10))
            str2 = Trim(StrSplit(str1, " := ", 1))
            str3 = Trim(StrSplit(str1, " := ", 2))
            out += "local " + str2 + "=" + expressionTranspiler(str3) + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 6) == "local " and InStr(A_LoopField34, " := ")):
            str1 = Trim(StringTrimLeft(A_LoopField34, 6))
            str1 = Trim(A_LoopField34)
            str2 = Trim(StrSplit(str1, " := ", 1))
            str3 = Trim(StrSplit(str1, " := ", 2))
            out += str2 + "=" + expressionTranspiler(str3) + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 4) == "str " or SubStr(StrLower(A_LoopField34), 1, 4) == "int " or SubStr(StrLower(A_LoopField34), 1, 4) == "var "):
            str1 = Trim(StringTrimLeft(A_LoopField34, 4))
            str2 = Trim(StrSplit(str1, " := ", 1))
            str3 = Trim(StrSplit(str1, " := ", 2))
            out += str2 + "=" + expressionTranspiler(str3) + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 4) == "arr "):
            str1 = Trim(StringTrimLeft(A_LoopField34, 4))
            str2 = Trim(StrSplit(str1, " := ", 1))
            str3 = Trim(StrSplit(str1, " := ", 2))
            if (InStr(str1, " := ")):
                str3 = StrReplace(str3, "[", "")
                str3 = StrReplace(str3, "]", "")
                str4 = ""
                if (InStr(str3, ",")):
                    items39 = LoopParseFunc(str3, ",")
                    for A_Index39 , A_LoopField39 in enumerate(items39, start=0):
                        str4 += expressionTranspiler(A_LoopField39) + " "
                    str3 = Trim(str4)
                out += str2 + "=(" + str3 + ")" + Chr(10)
            else:
                out += str2 + "=(" + expressionTranspiler(str3) + ")" + Chr(10)
        elif (InStr(A_LoopField34, " := []")):
            str1 = Trim(A_LoopField34)
            str2 = Trim(StrSplit(str1, " := ", 1))
            out += str2 + "=()" + Chr(10)
        elif (InStr(A_LoopField34, ".add(")):
            str1 = Trim(A_LoopField34)
            str1 = Trim(StringTrimRight(str1, 1))
            str2 = Trim(StrSplit(str1, ".add(", 1))
            str3 = Trim(StrSplit(str1, ".add(", 2))
            out += str2 + "+=(" + expressionTranspiler(str3) + ")" + Chr(10)
        elif (InStr(A_LoopField34, ".pop()")):
            str1 = Trim(A_LoopField34)
            str1 = Trim(StringTrimRight(str1, 1))
            str2 = Trim(StrSplit(str1, ".pop(", 1))
            out += str2 + "=(" + Chr(34) + "${" + str2 + "[@]:0:${#" + str2 + "[@]}-1}" + Chr(34) + ")" + Chr(10)
        elif (InStr(A_LoopField34, " := ") and InStr(A_LoopField34, " [") and InStr(A_LoopField34, "]")):
            str1 = Trim(A_LoopField34)
            if (InStr(str1, " := ")):
                str2 = Trim(StrSplit(str1, " := ", 1))
                str3 = Trim(StrSplit(str1, " := ", 2))
                str3 = StrReplace(str3, "[", "")
                str3 = StrReplace(str3, "]", "")
                str4 = ""
                if (InStr(str3, ",")):
                    items40 = LoopParseFunc(str3, ",")
                    for A_Index40 , A_LoopField40 in enumerate(items40, start=0):
                        str4 += expressionTranspiler(A_LoopField40) + " "
                    str3 = Trim(str4)
                out += str2 + "=(" + str3 + ")" + Chr(10)
            else:
                out += str2 + "=(" + expressionTranspiler(str3) + ")" + Chr(10)
        elif (InStr(A_LoopField34, " := @")):
            str1 = Trim(A_LoopField34)
            str2 = Trim(StrSplit(str1, " := @", 1))
            str3 = Trim(StrSplit(str1, " := @", 2))
            str3 = Trim(expressionTranspiler(str3))
            str3 = Trim(StringTrimLeft(str3, 1))
            out += "mapfile -t " + str2 + " < <" + str3 + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 13) == "loop, parse, "):
            str1 = Trim(StringTrimLeft(A_LoopField34, 13))
            if (inFunc == 0):
                firstLoop += 1
                firstLoop_parse += 1
                if (firstLoop == 1):
                    out += "A_Index_stack=()" + Chr(10)
                    out += "A_Index=0" + Chr(10)
                if (firstLoop_parse == 1):
                    out += "A_LoopField_stack=()" + Chr(10)
                    out += "A_LoopField=" + Chr(34) + Chr(34) + Chr(10)
                out += "A_Index_stack+=(" + Chr(34) + "$A_Index" + Chr(34) + ")" + Chr(10)
                out += "A_LoopField_stack+=(" + Chr(34) + "$A_LoopField" + Chr(34) + ")" + Chr(10)
                if (InStr(str1, ",")):
                    str2 = Trim(StrSplit(str1, ",", 1))
                    str3 = Trim(StrSplit(str1, ",", 2))
                    str4 = Chr(10)
                    str4 += "_parse_str=" + Chr(34) + "$" + str2 + Chr(34) + Chr(10)
                    str4 += "_parse_delim=" + str3 + Chr(10)
                    str4 += "_temp_arr_" + STR(firstLoop_parse) + "=(); IFS=" + Chr(34) + "$_parse_delim" + Chr(34) + " read -r -d '' -a _temp_arr_" + STR(firstLoop_parse) + " <<< " + Chr(34) + "$_parse_str" + Chr(34) + "; _temp_arr_" + STR(firstLoop_parse) + "[-1]=" + Chr(34) + "${_temp_arr_" + STR(firstLoop_parse) + "[-1]%$'\\n'}" + Chr(34) + Chr(10)
                    str4 += "for ((A_Index=0; A_Index<${#_temp_arr_" + STR(firstLoop_parse) + "[@]}; A_Index++)); do" + Chr(10)
                    str4 += "A_LoopField=" + Chr(34) + "${_temp_arr_" + STR(firstLoop_parse) + "[$A_Index]}" + Chr(34) + Chr(10)
                else:
                    #;;;;;;;;;;;;;
                    #;;;;;;;;;;;;;
                    str2 = Trim(str1)
                    str4 = Chr(10)
                    str4 += "_temp_arr_" + STR(firstLoop_parse) + "=" + Chr(34) + "$" + str2 + Chr(34) + Chr(10)
                    str4 += "for ((A_Index=0; A_Index<${#_temp_arr_" + STR(firstLoop_parse) + "}; A_Index++)); do" + Chr(10)
                    str4 += "A_LoopField=" + Chr(34) + "${_temp_arr_" + STR(firstLoop_parse) + ":A_Index:1}" + Chr(34) + Chr(10)
                    #;;;;;;;;;;;;;
                    #;;;;;;;;;;;;;
                out += str4 + Chr(10)
            else:
                #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                firstLoop_func += 1
                firstLoop_parse_func += 1
                if (firstLoop_func == 1):
                    out += "local A_Index_stack=()" + Chr(10)
                    out += "local A_Index=0" + Chr(10)
                if (firstLoop_parse_func == 1):
                    out += "local A_LoopField_stack=()" + Chr(10)
                    out += "local A_LoopField=" + Chr(34) + Chr(34) + Chr(10)
                out += "A_Index_stack+=(" + Chr(34) + "$A_Index" + Chr(34) + ")" + Chr(10)
                out += "A_LoopField_stack+=(" + Chr(34) + "$A_LoopField" + Chr(34) + ")" + Chr(10)
                if (InStr(str1, ",")):
                    str2 = Trim(StrSplit(str1, ",", 1))
                    str3 = Trim(StrSplit(str1, ",", 2))
                    str4 = Chr(10)
                    str4 += "local _parse_str=" + Chr(34) + "$" + str2 + Chr(34) + Chr(10)
                    str4 += "local _parse_delim=" + str3 + Chr(10)
                    str4 += "local -a _temp_arr_" + STR(firstLoop_parse_func) + "; IFS=" + Chr(34) + "$_parse_delim" + Chr(34) + " read -r -d '' -a _temp_arr_" + STR(firstLoop_parse_func) + " <<< " + Chr(34) + "$_parse_str" + Chr(34) + "; _temp_arr_" + STR(firstLoop_parse_func) + "[-1]=" + Chr(34) + "${_temp_arr_" + STR(firstLoop_parse_func) + "[-1]%$'\\n'}" + Chr(34) + Chr(10)
                    str4 += "for ((A_Index=0; A_Index<${#_temp_arr_" + STR(firstLoop_parse_func) + "[@]}; A_Index++)); do" + Chr(10)
                    str4 += "A_LoopField=" + Chr(34) + "${_temp_arr_" + STR(firstLoop_parse_func) + "[$A_Index]}" + Chr(34) + Chr(10)
                else:
                    #;;;;;;;;;;;;;
                    #;;;;;;;;;;;;;
                    str2 = Trim(str1)
                    str4 = Chr(10)
                    str4 += "local _temp_arr_" + STR(firstLoop_parse_func) + "=" + Chr(34) + "$" + str2 + Chr(34) + Chr(10)
                    str4 += "for ((A_Index=0; A_Index<${#_temp_arr_" + STR(firstLoop_parse_func) + "}; A_Index++)); do" + Chr(10)
                    str4 += "A_LoopField=" + Chr(34) + "${_temp_arr_" + STR(firstLoop_parse_func) + ":A_Index:1}" + Chr(34) + Chr(10)
                    #;;;;;;;;;;;;;
                    #;;;;;;;;;;;;;
                out += str4 + Chr(10)
                #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        elif (SubStr(StrLower(A_LoopField34), 1, 6) == "loop, "):
            str1 = Trim(StringTrimLeft(A_LoopField34, 6))
            if (inFunc == 0):
                firstLoop += 1
                if (firstLoop == 1):
                    out += "A_Index_stack=()" + Chr(10)
                    out += "A_Index=0" + Chr(10)
                out += "A_Index_stack+=(" + Chr(34) + "$A_Index" + Chr(34) + ")" + Chr(10)
                if (InStr(str1, ".size(")):
                    out += "for ((A_Index=0; A_Index<" + expressionTranspiler(Trim(str1)) + "; A_Index++)); do" + Chr(10)
                else:
                    out += "for ((A_Index=0; A_Index<" + Trim(str1) + "; A_Index++)); do" + Chr(10)
            else:
                firstLoop_func += 1
                if (firstLoop_func == 1):
                    out += "local A_Index_stack=()" + Chr(10)
                    out += "local A_Index=0" + Chr(10)
                out += "A_Index_stack+=(" + Chr(34) + "$A_Index" + Chr(34) + ")" + Chr(10)
                if (InStr(str1, ".size(")):
                    out += "for ((A_Index=0; A_Index<" + expressionTranspiler(Trim(str1)) + "; A_Index++)); do" + Chr(10)
                else:
                    out += "for ((A_Index=0; A_Index<" + Trim(str1) + "; A_Index++)); do" + Chr(10)
        elif (Trim(StrLower(A_LoopField34)) == "loop"):
            if (inFunc == 0):
                firstLoop += 1
                if (firstLoop == 1):
                    out += "A_Index_stack=()" + Chr(10)
                    out += "A_Index=0" + Chr(10)
                out += "A_Index_stack+=(" + Chr(34) + "$A_Index" + Chr(34) + ")" + Chr(10)
                out += "for ((A_Index=0;; A_Index++)); do" + Chr(10)
            else:
                firstLoop_func += 1
                if (firstLoop_func == 1):
                    out += "local A_Index_stack=()" + Chr(10)
                    out += "local A_Index=0" + Chr(10)
                out += "A_Index_stack+=(" + Chr(34) + "$A_Index" + Chr(34) + ")" + Chr(10)
                out += "for ((A_Index=0;; A_Index++)); do" + Chr(10)
        elif (Trim(A_LoopField34) == "done"):
            out += Trim(A_LoopField34) + Chr(10)
            out += "A_Index=" + Chr(34) + "${A_Index_stack[-1]}" + Chr(34) + Chr(10)
            out += "unset 'A_Index_stack[-1]'" + Chr(10)
        elif (Trim(A_LoopField34) == "pdone"):
            out += "done" + Chr(10)
            out += "A_Index=" + Chr(34) + "${A_Index_stack[-1]}" + Chr(34) + Chr(10)
            out += "unset 'A_Index_stack[-1]'" + Chr(10)
            out += "A_LoopField=" + Chr(34) + "${A_LoopField_stack[-1]}" + Chr(34) + Chr(10)
            out += "unset 'A_LoopField_stack[-1]'" + Chr(10)
        elif (Trim(A_LoopField34) == "break"):
            out += Trim(A_LoopField34) + Chr(10)
        elif (Trim(A_LoopField34) == "continue"):
            out += Trim(A_LoopField34) + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 3) == "if " or SubStr(StrLower(A_LoopField34), 1, 8) == "else if "):
            if (SubStr(StrLower(A_LoopField34), 1, 8) == "else if "):
                str1 = Trim(StringTrimLeft(A_LoopField34, 8))
            else:
                str1 = Trim(StringTrimLeft(A_LoopField34, 3))
            mathMode = 0
            if (getLastChars(Trim(A_LoopField34), 1) == ")"):
                str1 = Trim(StringTrimLeft(str1, 1))
                str1 = Trim(StringTrimRight(str1, 1))
                mathMode = 1
            str2 = ""
            items41 = LoopParseFunc(str1, " ")
            for A_Index41 , A_LoopField41 in enumerate(items41, start=0):
                if (RegExMatch(A_LoopField41, "^-?\\d+(\\.\\d+)?$")):
                    str2 += A_LoopField41 + " "
                    mathMode = 1
                elif (A_LoopField41 == "."):
                    str2 += ""
                elif (A_LoopField41 == "=="):
                    str2 += " == "
                elif (A_LoopField41 == "="):
                    str2 += " == "
                elif (A_LoopField41 == ">"):
                    str2 += " > "
                elif (A_LoopField41 == "<"):
                    str2 += " < "
                elif (A_LoopField41 == ">="):
                    str2 += " >= "
                elif (A_LoopField41 == "<="):
                    str2 += " <= "
                elif (A_LoopField41 == "!="):
                    str2 += " != "
                else:
                    if (mathMode == 0):
                        str2 += expressionTranspiler(A_LoopField41)
                    else:
                        str2 += A_LoopField41 + " "
            if (SubStr(StrLower(A_LoopField34), 1, 8) == "else if "):
                if (mathMode == 0):
                    out += "elif [[ " + str2 + " ]]; then" + Chr(10)
                else:
                    out += "elif (( " + str2 + " )); then" + Chr(10)
            else:
                if (mathMode == 0):
                    out += "if [[ " + str2 + " ]]; then" + Chr(10)
                else:
                    out += "if (( " + str2 + " )); then" + Chr(10)
        elif (Trim(A_LoopField34) == "fi"):
            out += Trim(A_LoopField34) + Chr(10)
        elif (Trim(A_LoopField34) == "else"):
            out += Trim(A_LoopField34) + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 6) == "while "):
            str1 = Trim(StringTrimLeft(A_LoopField34, 6))
            mathMode = 0
            if (getLastChars(Trim(A_LoopField34), 1) == ")"):
                str1 = Trim(StringTrimLeft(str1, 1))
                str1 = Trim(StringTrimRight(str1, 1))
                mathMode = 1
            str2 = ""
            items42 = LoopParseFunc(str1, " ")
            for A_Index42 , A_LoopField42 in enumerate(items42, start=0):
                if (RegExMatch(A_LoopField42, "^-?\\d+(\\.\\d+)?$")):
                    str2 += A_LoopField42 + " "
                    mathMode = 1
                elif (A_LoopField42 == "."):
                    str2 += ""
                elif (A_LoopField42 == "=="):
                    str2 += " == "
                elif (A_LoopField42 == "="):
                    str2 += " == "
                elif (A_LoopField42 == ">"):
                    str2 += " > "
                elif (A_LoopField42 == "<"):
                    str2 += " < "
                elif (A_LoopField42 == ">="):
                    str2 += " >= "
                elif (A_LoopField42 == "<="):
                    str2 += " <= "
                elif (A_LoopField42 == "!="):
                    str2 += " != "
                else:
                    if (mathMode == 0):
                        str2 += expressionTranspiler(A_LoopField42)
                    else:
                        str2 += A_LoopField42 + " "
            if (mathMode == 0):
                out += "while [[ " + str2 + " ]]; do" + Chr(10)
            else:
                out += "while (( " + str2 + " )); do" + Chr(10)
        elif (Trim(A_LoopField34) == "done2"):
            out += "done" + Chr(10)
        elif (SubStr(StrLower(A_LoopField34), 1, 6) == "local " and InStr(A_LoopField34, " := ")):
            str1 = Trim(StringTrimLeft(A_LoopField34, 6))
            str1 = Trim(A_LoopField34)
            str2 = Trim(StrSplit(str1, " := ", 1))
            str3 = Trim(StrSplit(str1, " := ", 2))
            out += "local " + str2 + "=" + expressionTranspiler(str3) + Chr(10)
        elif (InStr(A_LoopField34, " := ")):
            str1 = Trim(A_LoopField34)
            str2 = Trim(StrSplit(str1, " := ", 1))
            str3 = Trim(StrSplit(str1, " := ", 2))
            out += str2 + "=" + expressionTranspiler(str3) + Chr(10)
        elif (InStr(A_LoopField34, " += ")):
            str1 = Trim(A_LoopField34)
            str2 = Trim(StrSplit(str1, " += ", 1))
            str3 = Trim(StrSplit(str1, " += ", 2))
            out += "(( " + str2 + " += " + expressionTranspiler(str3, 1) + " ))" + Chr(10)
        elif (InStr(A_LoopField34, " -= ")):
            str1 = Trim(A_LoopField34)
            str2 = Trim(StrSplit(str1, " -= ", 1))
            str3 = Trim(StrSplit(str1, " -= ", 2))
            out += "(( " + str2 + " -= " + expressionTranspiler(str3, 1) + " ))" + Chr(10)
        elif (InStr(A_LoopField34, " *= ")):
            str1 = Trim(A_LoopField34)
            str2 = Trim(StrSplit(str1, " *= ", 1))
            str3 = Trim(StrSplit(str1, " *= ", 2))
            out += "(( " + str2 + " *= " + expressionTranspiler(str3, 1) + " ))" + Chr(10)
        elif (InStr(A_LoopField34, " /= ")):
            str1 = Trim(A_LoopField34)
            str2 = Trim(StrSplit(str1, " /= ", 1))
            str3 = Trim(StrSplit(str1, " /= ", 2))
            out += "(( " + str2 + " /= " + expressionTranspiler(str3, 1) + " ))" + Chr(10)
        elif (InStr(A_LoopField34, " %= ")):
            str1 = Trim(A_LoopField34)
            str2 = Trim(StrSplit(str1, " %= ", 1))
            str3 = Trim(StrSplit(str1, " %= ", 2))
            out += "(( " + str2 + " %= " + expressionTranspiler(str3, 1) + " ))" + Chr(10)
        elif (InStr(A_LoopField34, " **= ")):
            str1 = Trim(A_LoopField34)
            str2 = Trim(StrSplit(str1, " **= ", 1))
            str3 = Trim(StrSplit(str1, " **= ", 2))
            out += "(( " + str2 + " = " + str2 + " ** " + expressionTranspiler(str3, 1) + " ))" + Chr(10)
        elif (InStr(A_LoopField34, " .= ")):
            str1 = Trim(A_LoopField34)
            str2 = Trim(StrSplit(str1, " .= ", 1))
            str3 = Trim(StrSplit(str1, " .= ", 2))
            out += str2 + "+=" + expressionTranspiler(str3) + Chr(10)
        elif (getLastChars(Trim(A_LoopField34), 2) == "++"):
            str1 = Trim(A_LoopField34)
            str1 = StringTrimRight(str1, 2)
            out += "(( " + str1 + "++ ))" + Chr(10)
        elif (getLastChars(Trim(A_LoopField34), 2) == "--"):
            str1 = Trim(A_LoopField34)
            str1 = StringTrimRight(str1, 2)
            out += "(( " + str1 + "-- ))" + Chr(10)
        elif (getLastChars(Trim(A_LoopField34), 1) == ")"):
            str1 = Trim(A_LoopField34)
            str1 = expressionTranspiler(str1)
            str1 = StringTrimLeft(str1, 2)
            str1 = StringTrimRight(str1, 1)
            str1 = StrReplace(str1, Chr(34) + "(", " ")
            out += str1 + Chr(10)
        else:
            # else we allow stuff e.g.: program param param param ... so we can allow anything else
            out += A_LoopField34 + Chr(10)
    code = StringTrimRight(out, 1)
    # end code
    code = restoreStrings_bash(code)
    code = StrReplace(code, Chr(34) + "$" + Chr(34), "")
    code = StrReplace(code, Chr(34) + "ihuiuuhuuhtheidFor-" + Chr(45) + "asdsas--theuhtuwaesphoutr" , "\\")
    for A_Index43 in range(0, HTVM_Size(fixCode_runARR)):
        code = StrReplace(code, "ht-bash_runrsfdhgiosdxxszpxx--ashdzxkcxwaSsdx--AA" + STR(A_Index43) + "AA", fixCode_runARR[A_Index43])
    code = "#!/usr/bin/env bash" + Chr(10) + "if ((BASH_VERSINFO[0] < 4 || (BASH_VERSINFO[0] == 4 && BASH_VERSINFO[1] < 3))); then" + Chr(10) + "    echo " + Chr(34) + "Error: This script requires Bash 4.3+. Update bash." + Chr(34) + " >&2" + Chr(10) + "    exit 1" + Chr(10) + "fi" + Chr(10) + Chr(10) + "source " + Chr(34) + "$(dirname " + Chr(34) + "$0" + Chr(34) + ")/HT-Bash_Lib.sh" + Chr(34) + Chr(10) + code
    saveOutput(code, StringTrimRight(params, 4) + "sh")
