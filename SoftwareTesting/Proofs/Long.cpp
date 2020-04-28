#include <iostream>
#include <cassert>
#include <string> 


// find the length of the longest valid segment
// Valid Segment = segment of s which contains only charaters in t


int lsl(string haystack, string needle) {  
    int i = 0;
    int curr = 0;
    int max = 0;

    while (i < haystack.length()) {  
        if (needle.find(haystack[i])) {
            curr ++;
        } else {
            curr = 0;
        }
        if (curr > max) {
            max = curr;
        }
        i++;
    }
    return max;
}

** pre loop1
// len(s) >= 0
// len(t) >= 0
int i = 0;
int curr = 0;
int max = 0;
// i = current length of s checked                    (1)
// i <= len(s)                                         (1, A)
// max = longest valid segmenet of string s[0..i]      (above, Empty Set)

** take loop1
// i = current length of s checked
// i <= len(s)
// max = longest valid segmenet of string s[0..i]
|- i < s.length()
if (needle.find(haystack[i])) {
    curr ++;
} else {
    curr = 0;
}
if (curr > max) {
    max = curr;
}
i++;
// i = current length of s checked
// i <= len(s)
// max = longest valid segmenet of string s[0..i]

** exit loop1
// i = current length of s checked
// i <= len(s)
// max = longest valid segmenet of string s[0..i]                                        
~ i<n
return m;
// i = n                                        (B, 1)
// max = longest valid segmenet of string s     (above, A, C, defenition of subset))
// the function returns the longest valid segment of string s      (above, 2)



int main() {    
    assert(lsl("abcdefg","z")==0);    
    assert(lsl("abcdefg","abcdefg")==7);    
    assert(lsl("abcdefg","abc")==3);    
    assert(lsl("abcdefgabcdefg","abc")==3);    
    assert(lsl("abcdefgaaabbbccc","abc")==9);    
    assert(lsl("abcdefgcbacba","abc")==6);
}