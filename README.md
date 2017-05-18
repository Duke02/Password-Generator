# Password-Generator   
This project is for generating passwords, if you couldn't tell. It uses two methods to achieve this.     

###Synthesis

This process combines two user inputted (or randomly generated from the dict.txt file)
and inserts one letter from one word, another letter from the other word, and so on.

To prevent dictionary words from occurring (which isn't often in most cases), it inserts
randomly selected characters from the alphabet into the middle. It also does the same
procedure to the beginning and ending to make the password look more like the usual 
password.

###Length Substitution
This process takes in a length and a keyword that the program bases the password on.
To make the outputted password the desired length, the program adds or removes characters 
from the initial keyword until it is the length that was requested. 

##TODO
* Add different languages to dictionary file for harder decryption.
* Make sure length substitution outputs a password that is the desired length.
