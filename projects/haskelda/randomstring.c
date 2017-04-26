/*
CS362 - Quiz 2 - Random Testing
David Haskell
haskelda	932430887

This is a description of the development of my random tester and how it finds the error message. 
This is a text file that outlines how I developed my solution and how it works!

1)  I read through the existing code in testme.c so I could understand what it does and how/why the error message is created.
What is does:  main calls two functions, one returns a char c, one returns a string s.  When the char 'c' is a certain value, the 'state'
variable changes value. This must happen, in a certain order, until the 'state' is = 9, after whcih it does not change. The error message
is created if the "state" variable = 9 and the string s is 'reset\0'.

2) I placed dummy code inthe two functions and ran the program to see if it worked. It did.

3) I decided upon what input domain to use for the testing.  For char c, I thought of using all kb chars or just the 9 that changes the state.
I decided to test with a partitioning scheme that covered both: chars that change the state and chars that don't. But I don't need
to include all chars that don't change the state; just a few should suffice.  The ASCII values of the chars that change the state
are all between 32-125, inclusive. So, for simplicity, I chose all the chars within that range during random generation.
	As for the string s, the string that causes error is 'reset\0'.  I thought that I would imagine that the typical domain of strings
for this program would be a set of similar words; 'on\n', 'off\o',  'switch\0' etc.  So I made up a small set of those to assign as a random
string.  I also included no string (empty) as an option, as well as some strings (including 'reset'), that did not have the trailing '\0'.
I did not concern myself with very long strings.

4) I created the functions.

5) I ran the program and examined the output.  The probability for changing state is 1/94 or so.  This needs to happen 9 times.  Then, the
probability for error to be triggered is 1/16 after reaching state = 9.  This should all happen quite quickly.  And it does.  
The output is as expected.   

Sample output:


Iteration 1: c = *	 s = mean	 state = 0
Iteration 2: c = 1	 s = max	 state = 0
Iteration 3: c = 3	 s = RESET	 state = 0
Iteration 4: c = {	 s = on	 state = 0
Iteration 5: c = ?	 s = on	 state = 0
Iteration 6: c = ,	 s = 	 state = 0
Iteration 7: c = U	 s = on	 state = 0
Iteration 8: c = A	 s = switch	 state = 0
Iteration 9: c = u	 s = off	 state = 0
Iteration 10: c = \	 s = switch	 state = 0
Iteration 11: c = D	 s = max	 state = 0
Iteration 12: c = <	 s = off	 state = 0
Iteration 13: c = \	 s = Reset	 state = 0
Iteration 14: c = Q	 s = ratio	 state = 0
Iteration 15: c = %	 s = on	 state = 0
Iteration 16: c = s	 s = off	 state = 0
Iteration 17: c = `	 s = median	 state = 0
Iteration 18: c = w	 s = max	 state = 0
Iteration 19: c = f	 s = min	 state = 0
Iteration 20: c = Y	 s = 	 state = 0
Iteration 21: c = $	 s = Reset	 state = 0
Iteration 22: c = t	 s = min	 state = 0
Iteration 23: c = _	 s = Reset	 state = 0
Iteration 24: c =  	 s = RESET	 state = 0
Iteration 25: c = *	 s = min	 state = 0
Iteration 26: c = q	 s = min	 state = 0
Iteration 27: c = W	 s = Reset	 state = 0
Iteration 28: c =  	 s = status	 state = 0
Iteration 29: c = k	 s = status	 state = 0
Iteration 30: c = 7	 s = median	 state = 0
Iteration 31: c = F	 s = RESET	 state = 0
Iteration 32: c = ;	 s = min	 state = 0
Iteration 33: c = "	 s = 	 state = 0
Iteration 34: c = 7	 s = on	 state = 0
Iteration 35: c = y	 s = 	 state = 0
Iteration 36: c = ,	 s = mean	 state = 0
Iteration 37: c = r	 s = 	 state = 0
Iteration 38: c = s	 s = switch	 state = 0
Iteration 39: c = S	 s = off	 state = 0
Iteration 40: c = F	 s = off	 state = 0
Iteration 41: c = '	 s = Reset	 state = 0
Iteration 42: c = b	 s = 	 state = 0
Iteration 43: c = c	 s = ratio	 state = 0
Iteration 44: c = I	 s = median	 state = 0
Iteration 45: c = 5	 s = off	 state = 0
Iteration 46: c = \	 s = reset	 state = 0
Iteration 47: c = ]	 s = status	 state = 0
Iteration 48: c = 9	 s = ratio	 state = 0
Iteration 49: c = b	 s = Reset	 state = 0
Iteration 50: c = J	 s = max	 state = 0
Iteration 51: c = x	 s = ratio	 state = 0
Iteration 52: c = \	 s = on	 state = 0
Iteration 53: c = r	 s = ratio	 state = 0
Iteration 54: c = \	 s = off	 state = 0
Iteration 55: c = {	 s = 	 state = 0
Iteration 56: c = A	 s = 	 state = 0
Iteration 57: c = X	 s = off	 state = 0
Iteration 58: c = }	 s = reset	 state = 0
Iteration 59: c = #	 s = 	 state = 0
Iteration 60: c = C	 s = on	 state = 0
Iteration 61: c = z	 s = off	 state = 0
Iteration 62: c = J	 s = status	 state = 0
Iteration 63: c = 5	 s = reset	 state = 0
Iteration 64: c = U	 s = status	 state = 0
Iteration 65: c = j	 s = min	 state = 0
Iteration 66: c = p	 s = on	 state = 0
Iteration 67: c = r	 s = min	 state = 0
Iteration 68: c = m	 s = status	 state = 0
Iteration 69: c = V	 s = 	 state = 0
Iteration 70: c = J	 s = median	 state = 0
Iteration 71: c = &	 s = reset	 state = 0
Iteration 72: c = Y	 s = mean	 state = 0
Iteration 73: c = ,	 s = switch	 state = 0
Iteration 74: c = R	 s = off	 state = 0
Iteration 75: c = q	 s = min	 state = 0
Iteration 76: c = b	 s = off	 state = 0
Iteration 77: c = M	 s = RESET	 state = 0
Iteration 78: c = }	 s = switch	 state = 0
Iteration 79: c = G	 s = on	 state = 0
Iteration 80: c = 1	 s = RESET	 state = 0
Iteration 81: c = p	 s = off	 state = 0
Iteration 82: c = 4	 s = off	 state = 0
Iteration 83: c = l	 s = status	 state = 0
Iteration 84: c = $	 s = 	 state = 0
Iteration 85: c = %	 s = on	 state = 0
Iteration 86: c = 4	 s = off	 state = 0
Iteration 87: c = <	 s = Reset	 state = 0
Iteration 88: c = @	 s = min	 state = 0
Iteration 89: c = |	 s = reset	 state = 0
Iteration 90: c = .	 s = off	 state = 0
Iteration 91: c = A	 s = on	 state = 0
Iteration 92: c = 5	 s = on	 state = 0
Iteration 93: c = T	 s = on	 state = 0
Iteration 94: c = m	 s = 	 state = 0
Iteration 95: c = $	 s = ratio	 state = 0
Iteration 96: c = e	 s = Reset	 state = 0
Iteration 97: c = >	 s = on	 state = 0
Iteration 98: c = 2	 s = ratio	 state = 0
Iteration 99: c = 9	 s = median	 state = 0
Iteration 100: c = j	 s = median	 state = 0
Iteration 101: c = d	 s = reset	 state = 0
Iteration 102: c = d	 s = switch	 state = 0
Iteration 103: c = D	 s = on	 state = 0
Iteration 104: c = !	 s = on	 state = 0
Iteration 105: c = 5	 s = Reset	 state = 0
Iteration 106: c = h	 s = RESET	 state = 0
Iteration 107: c = U	 s = Reset	 state = 0
Iteration 108: c = G	 s = status	 state = 0
Iteration 109: c = M	 s = 	 state = 0
Iteration 110: c = \	 s = off	 state = 0
Iteration 111: c = P	 s = on	 state = 0
Iteration 112: c = b	 s = on	 state = 0
Iteration 113: c = t	 s = on	 state = 0
Iteration 114: c = z	 s = 	 state = 0
Iteration 115: c = ,	 s = reset	 state = 0
Iteration 116: c = h	 s = Reset	 state = 0
Iteration 117: c = >	 s = 	 state = 0
Iteration 118: c = I	 s = RESET	 state = 0
Iteration 119: c = n	 s = switch	 state = 0
Iteration 120: c = [	 s = RESET	 state = 0
Iteration 121: c = /	 s = Reset	 state = 1
Iteration 122: c = \	 s = min	 state = 1
Iteration 123: c = ^	 s = 	 state = 1
Iteration 124: c = +	 s = mean	 state = 1
Iteration 125: c = o	 s = RESET	 state = 1
Iteration 126: c = 4	 s = min	 state = 1
Iteration 127: c = b	 s = reset	 state = 1
Iteration 128: c = 2	 s = switch	 state = 1
Iteration 129: c = )	 s = max	 state = 1
Iteration 130: c = #	 s = RESET	 state = 1
Iteration 131: c = f	 s = mean	 state = 1
Iteration 132: c = ]	 s = median	 state = 1
Iteration 133: c = ;	 s = 	 state = 1
Iteration 134: c = >	 s = min	 state = 1
Iteration 135: c = )	 s = reset	 state = 1
Iteration 136: c = L	 s = on	 state = 1
Iteration 137: c = Z	 s = switch	 state = 1
Iteration 138: c = }	 s = median	 state = 1
Iteration 139: c =  	 s = ratio	 state = 1
Iteration 140: c = {	 s = 	 state = 1
Iteration 141: c = .	 s = switch	 state = 1
Iteration 142: c = 3	 s = ratio	 state = 1
Iteration 143: c = E	 s = min	 state = 1
Iteration 144: c = d	 s = min	 state = 1
Iteration 145: c = +	 s = on	 state = 1
Iteration 146: c = T	 s = Reset	 state = 1
Iteration 147: c = o	 s = off	 state = 1
Iteration 148: c = M	 s = Reset	 state = 1
Iteration 149: c = p	 s = 	 state = 1
Iteration 150: c = m	 s = off	 state = 1
Iteration 151: c = #	 s = reset	 state = 1
Iteration 152: c = 3	 s = 	 state = 1
Iteration 153: c = y	 s = 	 state = 1
Iteration 154: c = 4	 s = 	 state = 1
Iteration 155: c = W	 s = status	 state = 1
Iteration 156: c = k	 s = Reset	 state = 1
Iteration 157: c = ]	 s = switch	 state = 1
Iteration 158: c = H	 s = switch	 state = 1
Iteration 159: c = 6	 s = on	 state = 1
Iteration 160: c = C	 s = 	 state = 1
Iteration 161: c = 2	 s = max	 state = 1
Iteration 162: c = h	 s = on	 state = 1
Iteration 163: c = G	 s = mean	 state = 1
Iteration 164: c = e	 s = mean	 state = 1
Iteration 165: c = ?	 s = switch	 state = 1
Iteration 166: c = 4	 s = switch	 state = 1
Iteration 167: c = E	 s = max	 state = 1
Iteration 168: c = !	 s = RESET	 state = 1
Iteration 169: c = t	 s = mean	 state = 1
Iteration 170: c = V	 s = reset	 state = 1
Iteration 171: c = a	 s = Reset	 state = 1
Iteration 172: c = $	 s = on	 state = 1
Iteration 173: c = w	 s = median	 state = 1
Iteration 174: c = _	 s = switch	 state = 1
Iteration 175: c = u	 s = RESET	 state = 1
Iteration 176: c = '	 s = reset	 state = 1
Iteration 177: c = 7	 s = RESET	 state = 1
Iteration 178: c = a	 s = median	 state = 1
Iteration 179: c = )	 s = on	 state = 1
Iteration 180: c = w	 s = ratio	 state = 1
Iteration 181: c = R	 s = max	 state = 1
Iteration 182: c = &	 s = reset	 state = 1
Iteration 183: c = +	 s = on	 state = 1
Iteration 184: c = T	 s = 	 state = 1
Iteration 185: c = q	 s = on	 state = 1
Iteration 186: c = $	 s = 	 state = 1
Iteration 187: c = %	 s = 	 state = 1
Iteration 188: c = 1	 s = min	 state = 1
Iteration 189: c = o	 s = switch	 state = 1
Iteration 190: c = b	 s = ratio	 state = 1
Iteration 191: c = J	 s = ratio	 state = 1
Iteration 192: c = +	 s = reset	 state = 1
Iteration 193: c = \	 s = reset	 state = 1
Iteration 194: c = \	 s = status	 state = 1
Iteration 195: c = k	 s = 	 state = 1
Iteration 196: c = d	 s = median	 state = 1
Iteration 197: c = 9	 s = median	 state = 1
Iteration 198: c = S	 s = on	 state = 1
Iteration 199: c = H	 s = mean	 state = 1
Iteration 200: c = y	 s = median	 state = 1
Iteration 201: c = i	 s = Reset	 state = 1
Iteration 202: c = ,	 s = on	 state = 1
Iteration 203: c = [	 s = status	 state = 1
Iteration 204: c = C	 s = on	 state = 1
Iteration 205: c = I	 s = reset	 state = 1
Iteration 206: c = 4	 s = off	 state = 1
Iteration 207: c = q	 s = ratio	 state = 1
Iteration 208: c = W	 s = max	 state = 1
Iteration 209: c = I	 s = 	 state = 1
Iteration 210: c = Q	 s = RESET	 state = 1
Iteration 211: c = &	 s = max	 state = 1
Iteration 212: c = p	 s = status	 state = 1
Iteration 213: c = W	 s = switch	 state = 1
Iteration 214: c = 9	 s = 	 state = 1
Iteration 215: c = ?	 s = switch	 state = 1
Iteration 216: c = X	 s = off	 state = 1
Iteration 217: c = g	 s = ratio	 state = 1
Iteration 218: c = 5	 s = status	 state = 1
Iteration 219: c = $	 s = median	 state = 1
Iteration 220: c = q	 s = off	 state = 1
Iteration 221: c = `	 s = min	 state = 1
Iteration 222: c = ]	 s = max	 state = 1
Iteration 223: c = |	 s = on	 state = 1
Iteration 224: c = ?	 s = 	 state = 1
Iteration 225: c = !	 s = min	 state = 1
Iteration 226: c = 3	 s = off	 state = 1
Iteration 227: c = w	 s = RESET	 state = 1
Iteration 228: c = {	 s = min	 state = 1
Iteration 229: c = "	 s = min	 state = 1
Iteration 230: c = l	 s = max	 state = 1
Iteration 231: c = !	 s = median	 state = 1
Iteration 232: c = f	 s = switch	 state = 1
Iteration 233: c = a	 s = ratio	 state = 1
Iteration 234: c = I	 s = reset	 state = 1
Iteration 235: c = p	 s = max	 state = 1
Iteration 236: c = N	 s = on	 state = 1
Iteration 237: c = y	 s = 	 state = 1
Iteration 238: c = \	 s = max	 state = 1
Iteration 239: c = w	 s = off	 state = 1
Iteration 240: c = t	 s = 	 state = 1
Iteration 241: c = ]	 s = off	 state = 1
Iteration 242: c = V	 s = 	 state = 1
Iteration 243: c = I	 s = off	 state = 1
Iteration 244: c = B	 s = status	 state = 1
Iteration 245: c = ?	 s = max	 state = 1
Iteration 246: c = )	 s = ratio	 state = 1
Iteration 247: c = -	 s = 	 state = 1
Iteration 248: c = _	 s = RESET	 state = 1
Iteration 249: c = )	 s = on	 state = 1
Iteration 250: c = o	 s = median	 state = 1
Iteration 251: c = {	 s = switch	 state = 1
Iteration 252: c = $	 s = 	 state = 1
Iteration 253: c = #	 s = on	 state = 1
Iteration 254: c = E	 s = off	 state = 1
Iteration 255: c = 3	 s = mean	 state = 1
Iteration 256: c = e	 s = switch	 state = 1
Iteration 257: c = y	 s = reset	 state = 1
Iteration 258: c = |	 s = on	 state = 1
Iteration 259: c = F	 s = status	 state = 1
Iteration 260: c = ,	 s = RESET	 state = 1
Iteration 261: c = l	 s = Reset	 state = 1
Iteration 262: c = \	 s = status	 state = 1
Iteration 263: c = @	 s = off	 state = 1
Iteration 264: c = @	 s = on	 state = 1
Iteration 265: c = b	 s = status	 state = 1
Iteration 266: c = `	 s = status	 state = 1
Iteration 267: c = '	 s = on	 state = 1
Iteration 268: c = r	 s = mean	 state = 1
Iteration 269: c = {	 s = max	 state = 1
Iteration 270: c = v	 s = median	 state = 1
Iteration 271: c = o	 s = mean	 state = 1
Iteration 272: c = W	 s = switch	 state = 1
Iteration 273: c = 7	 s = Reset	 state = 1
Iteration 274: c = J	 s = reset	 state = 1
Iteration 275: c = 2	 s = 	 state = 1
Iteration 276: c = _	 s = min	 state = 1
Iteration 277: c = '	 s = ratio	 state = 1
Iteration 278: c = P	 s = on	 state = 1
Iteration 279: c = u	 s = median	 state = 1
Iteration 280: c = .	 s = status	 state = 1
Iteration 281: c = W	 s = median	 state = 1
Iteration 282: c = ;	 s = 	 state = 1
Iteration 283: c = n	 s = Reset	 state = 1
Iteration 284: c = Z	 s = reset	 state = 1
Iteration 285: c = b	 s = 	 state = 1
Iteration 286: c = 8	 s = reset	 state = 1
Iteration 287: c = e	 s = reset	 state = 1
Iteration 288: c = Y	 s = ratio	 state = 1
Iteration 289: c = `	 s = on	 state = 1
Iteration 290: c = \	 s = off	 state = 1
Iteration 291: c = 2	 s = Reset	 state = 1
Iteration 292: c = /	 s = switch	 state = 1
Iteration 293: c = u	 s = off	 state = 1
Iteration 294: c = |	 s = mean	 state = 1
Iteration 295: c = A	 s = switch	 state = 1
Iteration 296: c = H	 s = off	 state = 1
Iteration 297: c = 6	 s = off	 state = 1
Iteration 298: c = J	 s = RESET	 state = 1
Iteration 299: c = .	 s = switch	 state = 1
Iteration 300: c = r	 s = Reset	 state = 1
Iteration 301: c = .	 s = ratio	 state = 1
Iteration 302: c = `	 s = max	 state = 1
Iteration 303: c = Q	 s = switch	 state = 1
Iteration 304: c = r	 s = mean	 state = 1
Iteration 305: c = v	 s = switch	 state = 1
Iteration 306: c = (	 s = ratio	 state = 1
Iteration 307: c = )	 s = 	 state = 2
Iteration 308: c = ^	 s = off	 state = 2
Iteration 309: c = g	 s = on	 state = 2
Iteration 310: c = n	 s = 	 state = 2
Iteration 311: c = >	 s = 	 state = 2
Iteration 312: c = @	 s = median	 state = 2
Iteration 313: c = R	 s = ratio	 state = 2
Iteration 314: c = [	 s = RESET	 state = 2
Iteration 315: c = ,	 s = mean	 state = 2
Iteration 316: c = m	 s = RESET	 state = 2
Iteration 317: c = 1	 s = ratio	 state = 2
Iteration 318: c = I	 s = switch	 state = 2
Iteration 319: c = B	 s = off	 state = 2
Iteration 320: c = 1	 s = ratio	 state = 2
Iteration 321: c = )	 s = switch	 state = 2
Iteration 322: c = x	 s = reset	 state = 2
Iteration 323: c = (	 s = reset	 state = 2
Iteration 324: c = h	 s = reset	 state = 2
Iteration 325: c = k	 s = on	 state = 2
Iteration 326: c = 6	 s = median	 state = 2
Iteration 327: c = F	 s = median	 state = 2
Iteration 328: c = z	 s = RESET	 state = 2
Iteration 329: c = v	 s = off	 state = 2
Iteration 330: c = [	 s = ratio	 state = 2
Iteration 331: c = \	 s = ratio	 state = 2
Iteration 332: c = r	 s = status	 state = 2
Iteration 333: c = P	 s = switch	 state = 2
Iteration 334: c = '	 s = RESET	 state = 2
Iteration 335: c = 1	 s = 	 state = 2
Iteration 336: c = b	 s = 	 state = 2
Iteration 337: c = )	 s = status	 state = 2
Iteration 338: c = $	 s = off	 state = 2
Iteration 339: c = l	 s = switch	 state = 2
Iteration 340: c = V	 s = max	 state = 2
Iteration 341: c = `	 s = mean	 state = 2
Iteration 342: c = !	 s = ratio	 state = 2
Iteration 343: c = y	 s = ratio	 state = 2
Iteration 344: c = =	 s = on	 state = 2
Iteration 345: c = +	 s = ratio	 state = 2
Iteration 346: c = L	 s = RESET	 state = 2
Iteration 347: c = x	 s = mean	 state = 2
Iteration 348: c = -	 s = off	 state = 2
Iteration 349: c = 5	 s = status	 state = 2
Iteration 350: c = Y	 s = ratio	 state = 2
Iteration 351: c = $	 s = 	 state = 2
Iteration 352: c = 7	 s = status	 state = 2
Iteration 353: c = Q	 s = off	 state = 2
Iteration 354: c = r	 s = 	 state = 2
Iteration 355: c = C	 s = on	 state = 2
Iteration 356: c = 4	 s = off	 state = 2
Iteration 357: c = S	 s = on	 state = 2
Iteration 358: c = b	 s = max	 state = 2
Iteration 359: c = h	 s = off	 state = 2
Iteration 360: c = ]	 s = off	 state = 2
Iteration 361: c = O	 s = max	 state = 2
Iteration 362: c = w	 s = max	 state = 2
Iteration 363: c = <	 s = max	 state = 2
Iteration 364: c = 0	 s = max	 state = 2
Iteration 365: c = p	 s = switch	 state = 2
Iteration 366: c = N	 s = RESET	 state = 2
Iteration 367: c = D	 s = max	 state = 2
Iteration 368: c = =	 s = off	 state = 2
Iteration 369: c = =	 s = off	 state = 2
Iteration 370: c = P	 s = RESET	 state = 2
Iteration 371: c = [	 s = min	 state = 2
Iteration 372: c = V	 s = Reset	 state = 2
Iteration 373: c = P	 s = median	 state = 2
Iteration 374: c = z	 s = on	 state = 2
Iteration 375: c = U	 s = 	 state = 2
Iteration 376: c = J	 s = ratio	 state = 2
Iteration 377: c = T	 s = off	 state = 2
Iteration 378: c = i	 s = off	 state = 2
Iteration 379: c = d	 s = min	 state = 2
Iteration 380: c = x	 s = 	 state = 2
Iteration 381: c = "	 s = min	 state = 2
Iteration 382: c = f	 s = median	 state = 2
Iteration 383: c = J	 s = max	 state = 2
Iteration 384: c = q	 s = off	 state = 2
Iteration 385: c = P	 s = mean	 state = 2
Iteration 386: c = 9	 s = ratio	 state = 2
Iteration 387: c = ]	 s = mean	 state = 2
Iteration 388: c = s	 s = on	 state = 2
Iteration 389: c = E	 s = 	 state = 2
Iteration 390: c = d	 s = on	 state = 2
Iteration 391: c = :	 s = median	 state = 2
Iteration 392: c = V	 s = switch	 state = 2
Iteration 393: c = n	 s = median	 state = 2
Iteration 394: c = 7	 s = 	 state = 2
Iteration 395: c = >	 s = RESET	 state = 2
Iteration 396: c = G	 s = on	 state = 2
Iteration 397: c = t	 s = max	 state = 2
Iteration 398: c = <	 s = ratio	 state = 2
Iteration 399: c = 5	 s = off	 state = 2
Iteration 400: c = w	 s = off	 state = 2
Iteration 401: c = l	 s = max	 state = 2
Iteration 402: c = I	 s = 	 state = 2
Iteration 403: c = >	 s = RESET	 state = 2
Iteration 404: c = u	 s = RESET	 state = 2
Iteration 405: c = c	 s = on	 state = 2
Iteration 406: c = 6	 s = mean	 state = 2
Iteration 407: c = B	 s = status	 state = 2
Iteration 408: c = D	 s = RESET	 state = 2
Iteration 409: c = 1	 s = off	 state = 2
Iteration 410: c = #	 s = status	 state = 2
Iteration 411: c = )	 s = median	 state = 2
Iteration 412: c = _	 s = median	 state = 2
Iteration 413: c = Y	 s = Reset	 state = 2
Iteration 414: c = t	 s = median	 state = 2
Iteration 415: c = F	 s = ratio	 state = 2
Iteration 416: c = ,	 s = RESET	 state = 2
Iteration 417: c = #	 s = off	 state = 2
Iteration 418: c = y	 s = Reset	 state = 2
Iteration 419: c = J	 s = Reset	 state = 2
Iteration 420: c = A	 s = max	 state = 2
Iteration 421: c = ?	 s = 	 state = 2
Iteration 422: c = I	 s = mean	 state = 2
Iteration 423: c = a	 s = mean	 state = 2
Iteration 424: c = 0	 s = RESET	 state = 2
Iteration 425: c = J	 s = reset	 state = 2
Iteration 426: c = 3	 s = on	 state = 2
Iteration 427: c = ]	 s = on	 state = 2
Iteration 428: c = n	 s = on	 state = 2
Iteration 429: c = o	 s = on	 state = 2
Iteration 430: c = ]	 s = 	 state = 2
Iteration 431: c = n	 s = reset	 state = 2
Iteration 432: c = e	 s = max	 state = 2
Iteration 433: c = t	 s = switch	 state = 2
Iteration 434: c = i	 s = ratio	 state = 2
Iteration 435: c = C	 s = switch	 state = 2
Iteration 436: c = j	 s = on	 state = 2
Iteration 437: c =  	 s = reset	 state = 2
Iteration 438: c = `	 s = off	 state = 2
Iteration 439: c = X	 s = RESET	 state = 2
Iteration 440: c = +	 s = median	 state = 2
Iteration 441: c = %	 s = ratio	 state = 2
Iteration 442: c = .	 s = median	 state = 2
Iteration 443: c = L	 s = min	 state = 2
Iteration 444: c = P	 s = off	 state = 2
Iteration 445: c = }	 s = max	 state = 2
Iteration 446: c = *	 s = off	 state = 2
Iteration 447: c = h	 s = Reset	 state = 2
Iteration 448: c = {	 s = off	 state = 2
Iteration 449: c = B	 s = switch	 state = 3
Iteration 450: c = U	 s = mean	 state = 3
Iteration 451: c = .	 s = status	 state = 3
Iteration 452: c = d	 s = max	 state = 3
Iteration 453: c = ,	 s = on	 state = 3
Iteration 454: c = `	 s = on	 state = 3
Iteration 455: c = 8	 s = switch	 state = 3
Iteration 456: c = ?	 s = 	 state = 3
Iteration 457: c = F	 s = Reset	 state = 3
Iteration 458: c = o	 s = status	 state = 3
Iteration 459: c = L	 s = mean	 state = 3
Iteration 460: c = f	 s = status	 state = 3
Iteration 461: c = '	 s = max	 state = 3
Iteration 462: c = n	 s = off	 state = 3
Iteration 463: c = |	 s = status	 state = 3
Iteration 464: c = &	 s = RESET	 state = 3
Iteration 465: c = m	 s = on	 state = 3
Iteration 466: c = B	 s = RESET	 state = 3
Iteration 467: c = S	 s = RESET	 state = 3
Iteration 468: c = {	 s = switch	 state = 3
Iteration 469: c = h	 s = max	 state = 3
Iteration 470: c = z	 s = min	 state = 3
Iteration 471: c = e	 s = Reset	 state = 3
Iteration 472: c = s	 s = switch	 state = 3
Iteration 473: c = i	 s = ratio	 state = 3
Iteration 474: c = W	 s = off	 state = 3
Iteration 475: c = A	 s = Reset	 state = 3
Iteration 476: c = 8	 s = on	 state = 3
Iteration 477: c = 2	 s = min	 state = 3
Iteration 478: c = *	 s = off	 state = 3
Iteration 479: c = 0	 s = min	 state = 3
Iteration 480: c = '	 s = off	 state = 3
Iteration 481: c = (	 s = Reset	 state = 3
Iteration 482: c = Q	 s = ratio	 state = 3
Iteration 483: c = k	 s = median	 state = 3
Iteration 484: c = r	 s = off	 state = 3
Iteration 485: c = .	 s = on	 state = 3
Iteration 486: c = W	 s = status	 state = 3
Iteration 487: c = ,	 s = min	 state = 3
Iteration 488: c = =	 s = Reset	 state = 3
Iteration 489: c = L	 s = RESET	 state = 3
Iteration 490: c = b	 s = on	 state = 3
Iteration 491: c = 6	 s = 	 state = 3
Iteration 492: c = (	 s = switch	 state = 3
Iteration 493: c = >	 s = switch	 state = 3
Iteration 494: c = /	 s = RESET	 state = 3
Iteration 495: c = C	 s = mean	 state = 3
Iteration 496: c = h	 s = reset	 state = 3
Iteration 497: c = z	 s = 	 state = 3
Iteration 498: c = w	 s = min	 state = 3
Iteration 499: c = j	 s = off	 state = 3
Iteration 500: c = ?	 s = switch	 state = 3
Iteration 501: c = v	 s = status	 state = 3
Iteration 502: c = m	 s = on	 state = 3
Iteration 503: c = y	 s = reset	 state = 3
Iteration 504: c = O	 s = min	 state = 3
Iteration 505: c = =	 s = status	 state = 3
Iteration 506: c = (	 s = Reset	 state = 3
Iteration 507: c = /	 s = ratio	 state = 3
Iteration 508: c = R	 s = status	 state = 3
Iteration 509: c = C	 s = reset	 state = 3
Iteration 510: c = 8	 s = switch	 state = 3
Iteration 511: c = N	 s = median	 state = 3
Iteration 512: c = g	 s = status	 state = 3
Iteration 513: c = =	 s = off	 state = 3
Iteration 514: c = i	 s = reset	 state = 3
Iteration 515: c = h	 s = ratio	 state = 3
Iteration 516: c = =	 s = ratio	 state = 3
Iteration 517: c = W	 s = status	 state = 3
Iteration 518: c =  	 s = status	 state = 3
Iteration 519: c = n	 s = off	 state = 4
Iteration 520: c = k	 s = status	 state = 4
Iteration 521: c = |	 s = mean	 state = 4
Iteration 522: c = {	 s = max	 state = 4
Iteration 523: c = %	 s = Reset	 state = 4
Iteration 524: c = 1	 s = RESET	 state = 4
Iteration 525: c = f	 s = mean	 state = 4
Iteration 526: c = J	 s = mean	 state = 4
Iteration 527: c = K	 s = RESET	 state = 4
Iteration 528: c = 8	 s = switch	 state = 4
Iteration 529: c = 1	 s = off	 state = 4
Iteration 530: c = .	 s = Reset	 state = 4
Iteration 531: c = G	 s = reset	 state = 4
Iteration 532: c = 2	 s = max	 state = 4
Iteration 533: c = r	 s = RESET	 state = 4
Iteration 534: c = *	 s = on	 state = 4
Iteration 535: c = 8	 s = 	 state = 4
Iteration 536: c = p	 s = on	 state = 4
Iteration 537: c = j	 s = off	 state = 4
Iteration 538: c = ^	 s = max	 state = 4
Iteration 539: c = r	 s = 	 state = 4
Iteration 540: c = T	 s = RESET	 state = 4
Iteration 541: c = T	 s = on	 state = 4
Iteration 542: c = G	 s = status	 state = 4
Iteration 543: c = N	 s = reset	 state = 4
Iteration 544: c = %	 s = off	 state = 4
Iteration 545: c = |	 s = status	 state = 4
Iteration 546: c = 1	 s = median	 state = 4
Iteration 547: c = y	 s = off	 state = 4
Iteration 548: c = {	 s = off	 state = 4
Iteration 549: c = o	 s = status	 state = 4
Iteration 550: c = R	 s = status	 state = 4
Iteration 551: c = 8	 s = RESET	 state = 4
Iteration 552: c = Z	 s = ratio	 state = 4
Iteration 553: c = g	 s = RESET	 state = 4
Iteration 554: c = I	 s = off	 state = 4
Iteration 555: c = E	 s = off	 state = 4
Iteration 556: c = k	 s = 	 state = 4
Iteration 557: c = :	 s = Reset	 state = 4
Iteration 558: c = 6	 s = on	 state = 4
Iteration 559: c = 0	 s = mean	 state = 4
Iteration 560: c = :	 s = off	 state = 4
Iteration 561: c = %	 s = off	 state = 4
Iteration 562: c = +	 s = RESET	 state = 4
Iteration 563: c = D	 s = switch	 state = 4
Iteration 564: c = )	 s = off	 state = 4
Iteration 565: c = c	 s = off	 state = 4
Iteration 566: c = Y	 s = mean	 state = 4
Iteration 567: c = U	 s = Reset	 state = 4
Iteration 568: c = U	 s = switch	 state = 4
Iteration 569: c = %	 s = on	 state = 4
Iteration 570: c = O	 s = on	 state = 4
Iteration 571: c = :	 s = mean	 state = 4
Iteration 572: c = y	 s = min	 state = 4
Iteration 573: c = l	 s = off	 state = 4
Iteration 574: c = X	 s = min	 state = 4
Iteration 575: c = "	 s = median	 state = 4
Iteration 576: c = a	 s = 	 state = 4
Iteration 577: c = s	 s = on	 state = 5
Iteration 578: c = A	 s = off	 state = 5
Iteration 579: c = J	 s = off	 state = 5
Iteration 580: c = O	 s = status	 state = 5
Iteration 581: c = B	 s = min	 state = 5
Iteration 582: c = F	 s = 	 state = 5
Iteration 583: c = /	 s = Reset	 state = 5
Iteration 584: c = R	 s = on	 state = 5
Iteration 585: c = 8	 s = on	 state = 5
Iteration 586: c = x	 s = on	 state = 5
Iteration 587: c = u	 s = mean	 state = 6
Iteration 588: c = B	 s = mean	 state = 6
Iteration 589: c = Z	 s = ratio	 state = 6
Iteration 590: c = {	 s = ratio	 state = 6
Iteration 591: c = E	 s = off	 state = 6
Iteration 592: c =  	 s = switch	 state = 6
Iteration 593: c = #	 s = off	 state = 6
Iteration 594: c = T	 s = on	 state = 6
Iteration 595: c = (	 s = 	 state = 6
Iteration 596: c = 3	 s = max	 state = 6
Iteration 597: c = c	 s = RESET	 state = 6
Iteration 598: c = E	 s = on	 state = 6
Iteration 599: c = -	 s = status	 state = 6
Iteration 600: c = B	 s = Reset	 state = 6
Iteration 601: c = k	 s = on	 state = 6
Iteration 602: c = w	 s = RESET	 state = 6
Iteration 603: c = K	 s = off	 state = 6
Iteration 604: c = a	 s = mean	 state = 6
Iteration 605: c = R	 s = off	 state = 6
Iteration 606: c = }	 s = max	 state = 6
Iteration 607: c = t	 s = mean	 state = 7
Iteration 608: c = 3	 s = reset	 state = 7
Iteration 609: c = u	 s = mean	 state = 7
Iteration 610: c = {	 s = reset	 state = 7
Iteration 611: c = B	 s = mean	 state = 7
Iteration 612: c = J	 s = Reset	 state = 7
Iteration 613: c = A	 s = status	 state = 7
Iteration 614: c = 5	 s = min	 state = 7
Iteration 615: c = Y	 s = Reset	 state = 7
Iteration 616: c = t	 s = RESET	 state = 7
Iteration 617: c = /	 s = mean	 state = 7
Iteration 618: c = E	 s = ratio	 state = 7
Iteration 619: c = _	 s = median	 state = 7
Iteration 620: c = 7	 s = reset	 state = 7
Iteration 621: c = g	 s = 	 state = 7
Iteration 622: c = `	 s = off	 state = 7
Iteration 623: c = &	 s = mean	 state = 7
Iteration 624: c = -	 s = 	 state = 7
Iteration 625: c = 3	 s = min	 state = 7
Iteration 626: c = 7	 s = max	 state = 7
Iteration 627: c = o	 s = reset	 state = 7
Iteration 628: c = w	 s = on	 state = 7
Iteration 629: c = )	 s = ratio	 state = 7
Iteration 630: c = {	 s = median	 state = 8
Iteration 631: c = <	 s = 	 state = 8
Iteration 632: c = ^	 s = mean	 state = 8
Iteration 633: c = P	 s = max	 state = 8
Iteration 634: c = \	 s = reset	 state = 8
Iteration 635: c = .	 s = 	 state = 8
Iteration 636: c = x	 s = 	 state = 8
Iteration 637: c = z	 s = median	 state = 8
Iteration 638: c = +	 s = max	 state = 8
Iteration 639: c = j	 s = 	 state = 8
Iteration 640: c = :	 s = off	 state = 8
Iteration 641: c = v	 s = 	 state = 8
Iteration 642: c = n	 s = 	 state = 8
Iteration 643: c = i	 s = off	 state = 8
Iteration 644: c = P	 s = RESET	 state = 8
Iteration 645: c = 2	 s = reset	 state = 8
Iteration 646: c = ,	 s = on	 state = 8
Iteration 647: c = t	 s = on	 state = 8
Iteration 648: c = 5	 s = off	 state = 8
Iteration 649: c = ,	 s = status	 state = 8
Iteration 650: c = r	 s = switch	 state = 8
Iteration 651: c = W	 s = status	 state = 8
Iteration 652: c = e	 s = off	 state = 8
Iteration 653: c = c	 s = switch	 state = 8
Iteration 654: c = p	 s = mean	 state = 8
Iteration 655: c = D	 s = reset	 state = 8
Iteration 656: c = $	 s = status	 state = 8
Iteration 657: c = 4	 s = mean	 state = 8
Iteration 658: c = [	 s = max	 state = 8
Iteration 659: c = \	 s = reset	 state = 8
Iteration 660: c = -	 s = switch	 state = 8
Iteration 661: c = u	 s = 	 state = 8
Iteration 662: c = X	 s = off	 state = 8
Iteration 663: c = Z	 s = switch	 state = 8
Iteration 664: c = h	 s = median	 state = 8
Iteration 665: c = 7	 s = 	 state = 8
Iteration 666: c = <	 s = ratio	 state = 8
Iteration 667: c = "	 s = Reset	 state = 8
Iteration 668: c = ^	 s = reset	 state = 8
Iteration 669: c = 0	 s = on	 state = 8
Iteration 670: c = k	 s = on	 state = 8
Iteration 671: c = 3	 s = mean	 state = 8
Iteration 672: c = a	 s = median	 state = 8
Iteration 673: c =  	 s = on	 state = 8
Iteration 674: c = a	 s = mean	 state = 8
Iteration 675: c = f	 s = reset	 state = 8
Iteration 676: c = g	 s = status	 state = 8
Iteration 677: c = x	 s = ratio	 state = 8
Iteration 678: c = :	 s = RESET	 state = 8
Iteration 679: c = L	 s = mean	 state = 8
Iteration 680: c = p	 s = 	 state = 8
Iteration 681: c = R	 s = ratio	 state = 8
Iteration 682: c = T	 s = ratio	 state = 8
Iteration 683: c = f	 s = switch	 state = 8
Iteration 684: c = o	 s = 	 state = 8
Iteration 685: c =  	 s = median	 state = 8
Iteration 686: c = "	 s = 	 state = 8
Iteration 687: c = $	 s = RESET	 state = 8
Iteration 688: c = v	 s = on	 state = 8
Iteration 689: c = X	 s = 	 state = 8
Iteration 690: c = {	 s = median	 state = 8
Iteration 691: c =  	 s = off	 state = 8
Iteration 692: c = S	 s = max	 state = 8
Iteration 693: c = C	 s = 	 state = 8
Iteration 694: c = i	 s = 	 state = 8
Iteration 695: c = c	 s = on	 state = 8
Iteration 696: c = n	 s = reset	 state = 8
Iteration 697: c = &	 s = median	 state = 8
Iteration 698: c = '	 s = RESET	 state = 8
Iteration 699: c = r	 s = median	 state = 8
Iteration 700: c =  	 s = reset	 state = 8
Iteration 701: c = E	 s = status	 state = 8
Iteration 702: c = C	 s = reset	 state = 8
Iteration 703: c = =	 s = off	 state = 8
Iteration 704: c = #	 s = mean	 state = 8
Iteration 705: c = 0	 s = reset	 state = 8
Iteration 706: c = R	 s = mean	 state = 8
Iteration 707: c = <	 s = mean	 state = 8
Iteration 708: c = ,	 s = off	 state = 8
Iteration 709: c = e	 s = reset	 state = 8
Iteration 710: c = j	 s = RESET	 state = 8
Iteration 711: c = m	 s = RESET	 state = 8
Iteration 712: c = a	 s = min	 state = 8
Iteration 713: c = U	 s = ratio	 state = 8
Iteration 714: c = |	 s = Reset	 state = 8
Iteration 715: c = 7	 s = mean	 state = 8
Iteration 716: c = X	 s = on	 state = 8
Iteration 717: c = <	 s = off	 state = 8
Iteration 718: c = A	 s = mean	 state = 8
Iteration 719: c = l	 s = 	 state = 8
Iteration 720: c = j	 s = mean	 state = 8
Iteration 721: c = _	 s = on	 state = 8
Iteration 722: c = d	 s = off	 state = 8
Iteration 723: c = 6	 s = RESET	 state = 8
Iteration 724: c = v	 s = Reset	 state = 8
Iteration 725: c = =	 s = RESET	 state = 8
Iteration 726: c = H	 s = off	 state = 8
Iteration 727: c = s	 s = Reset	 state = 8
Iteration 728: c = =	 s = median	 state = 8
Iteration 729: c = J	 s = status	 state = 8
Iteration 730: c = /	 s = off	 state = 8
Iteration 731: c = :	 s = min	 state = 8
Iteration 732: c = Y	 s = min	 state = 8
Iteration 733: c = ;	 s = min	 state = 8
Iteration 734: c = e	 s = on	 state = 8
Iteration 735: c = t	 s = RESET	 state = 8
Iteration 736: c = w	 s = on	 state = 8
Iteration 737: c = F	 s = off	 state = 8
Iteration 738: c = )	 s = RESET	 state = 8
Iteration 739: c = i	 s = on	 state = 8
Iteration 740: c = Z	 s = on	 state = 8
Iteration 741: c = :	 s = ratio	 state = 8
Iteration 742: c = 5	 s = reset	 state = 8
Iteration 743: c = c	 s = median	 state = 8
Iteration 744: c = s	 s = status	 state = 8
Iteration 745: c = n	 s = off	 state = 8
Iteration 746: c = ,	 s = min	 state = 8
Iteration 747: c = C	 s = off	 state = 8
Iteration 748: c = 7	 s = median	 state = 8
Iteration 749: c = 7	 s = min	 state = 8
Iteration 750: c = >	 s = ratio	 state = 8
Iteration 751: c = j	 s = max	 state = 8
Iteration 752: c = T	 s = max	 state = 8
Iteration 753: c = t	 s = off	 state = 8
Iteration 754: c = E	 s = off	 state = 8
Iteration 755: c = 5	 s = status	 state = 8
Iteration 756: c = $	 s = min	 state = 8
Iteration 757: c = Y	 s = status	 state = 8
Iteration 758: c = y	 s = off	 state = 8
Iteration 759: c = (	 s = off	 state = 8
Iteration 760: c = $	 s = min	 state = 8
Iteration 761: c = J	 s = max	 state = 8
Iteration 762: c = V	 s = mean	 state = 8
Iteration 763: c = L	 s = off	 state = 8
Iteration 764: c = g	 s = on	 state = 8
Iteration 765: c = (	 s = on	 state = 8
Iteration 766: c = H	 s = min	 state = 8
Iteration 767: c = s	 s = ratio	 state = 8
Iteration 768: c = u	 s = on	 state = 8
Iteration 769: c = u	 s = Reset	 state = 8
Iteration 770: c = !	 s = mean	 state = 8
Iteration 771: c = X	 s = 	 state = 8
Iteration 772: c = w	 s = ratio	 state = 8
Iteration 773: c = Y	 s = RESET	 state = 8
Iteration 774: c = m	 s = off	 state = 8
Iteration 775: c = 9	 s = max	 state = 8
Iteration 776: c = /	 s = off	 state = 8
Iteration 777: c = >	 s = Reset	 state = 8
Iteration 778: c = l	 s = off	 state = 8
Iteration 779: c = o	 s = switch	 state = 8
Iteration 780: c = k	 s = off	 state = 8
Iteration 781: c = N	 s = off	 state = 8
Iteration 782: c = [	 s = mean	 state = 8
Iteration 783: c = M	 s = 	 state = 8
Iteration 784: c = I	 s = switch	 state = 8
Iteration 785: c = p	 s = off	 state = 8
Iteration 786: c = k	 s = min	 state = 8
Iteration 787: c = &	 s = min	 state = 8
Iteration 788: c = x	 s = status	 state = 8
Iteration 789: c = s	 s = off	 state = 8
Iteration 790: c = \	 s = RESET	 state = 8
Iteration 791: c = 1	 s = off	 state = 8
Iteration 792: c = H	 s = off	 state = 8
Iteration 793: c = m	 s = on	 state = 8
Iteration 794: c = V	 s = median	 state = 8
Iteration 795: c = \	 s = 	 state = 8
Iteration 796: c = -	 s = on	 state = 8
Iteration 797: c = .	 s = on	 state = 8
Iteration 798: c = P	 s = Reset	 state = 8
Iteration 799: c = =	 s = reset	 state = 8
Iteration 800: c = V	 s = status	 state = 8
Iteration 801: c = 6	 s = max	 state = 8
Iteration 802: c = 0	 s = off	 state = 8
Iteration 803: c = D	 s = min	 state = 8
Iteration 804: c = |	 s = Reset	 state = 8
Iteration 805: c = H	 s = off	 state = 8
Iteration 806: c = 7	 s = off	 state = 8
Iteration 807: c = b	 s = reset	 state = 8
Iteration 808: c = *	 s = off	 state = 8
Iteration 809: c = L	 s = off	 state = 8
Iteration 810: c = K	 s = median	 state = 8
Iteration 811: c = Z	 s = RESET	 state = 8
Iteration 812: c = Q	 s = off	 state = 8
Iteration 813: c = ]	 s = 	 state = 8
Iteration 814: c = z	 s = switch	 state = 9
Iteration 815: c = R	 s = median	 state = 9
Iteration 816: c = `	 s = mean	 state = 9
Iteration 817: c = 2	 s = 	 state = 9
Iteration 818: c = B	 s = median	 state = 9
Iteration 819: c = 6	 s = min	 state = 9
Iteration 820: c = E	 s = ratio	 state = 9
Iteration 821: c = Q	 s = switch	 state = 9
Iteration 822: c = 9	 s = ratio	 state = 9
Iteration 823: c = X	 s = min	 state = 9
Iteration 824: c = #	 s = median	 state = 9
Iteration 825: c = u	 s = Reset	 state = 9
Iteration 826: c = J	 s = max	 state = 9
Iteration 827: c = C	 s = status	 state = 9
Iteration 828: c = p	 s = RESET	 state = 9
Iteration 829: c = :	 s = off	 state = 9
Iteration 830: c = S	 s = off	 state = 9
Iteration 831: c = A	 s = status	 state = 9
Iteration 832: c = .	 s = status	 state = 9
Iteration 833: c = A	 s = ratio	 state = 9
Iteration 834: c = +	 s = status	 state = 9
Iteration 835: c = F	 s = ratio	 state = 9
Iteration 836: c = l	 s = switch	 state = 9
Iteration 837: c = I	 s = off	 state = 9
Iteration 838: c = d	 s = Reset	 state = 9
Iteration 839: c = !	 s = 	 state = 9
Iteration 840: c = ]	 s = RESET	 state = 9
Iteration 841: c = l	 s = reset	 state = 9
error 

Notice how empty string "", "RESET", and "Reset" all were tested when state = 9.  This was random, but the iterations were sufficient
to allow for each case to be executed.  If not, I would have changed the code for a more thorough coverage.