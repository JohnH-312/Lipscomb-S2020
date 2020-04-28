// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Code for msp(a, n)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// P(a,i,j) is all products of a[i..(0..j)]
// P*(a,i,j) is all P(a,0..i,j)
// ------
// a = an array containing a finite count of ints
// if n = actual length of a 
// and INT_MIN <= n <= INT_MAX
// then
// msp(a,n) is the maximum of P*(a,n-1,n-1)
int msp(int a[],int n)
{
    int m = 1;                                      // pre loop1
    int i = 0;
    int rowM = 1;
    while (i<n) {                                   // take loop1
        // a = an array containing a finite count of ints
        // n = actual length of a 
        // 0 <= n <= INT_MAX
        // m = max of P*(a,i-1,n-1)
        // i <= n                                    
        
        rowM = max(i, n, a); 
        if (rowM > m) {
            m = rowM;
        } 

        i++;
    }                                               // exit loop1
    return m;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// PROOF OF msp(a, n)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

** pre loop1
// a = an array containing a finite count of ints
// if n = actual length of a 
// and 0 <= n <= INT_MAX
int m = 1;
int i = 0;
int rowM = 1;
// a = an array containing a finite count of ints   (A)
// n = actual length of a                           (B)
// 0 <= n <= INT_MAX                                (C)
// m = max of P*(a,i-1,n-1)                         (P*, empty set, mult identity)
// i <= n                                           (C, 2) 

** take loop1
// a = an array containing a finite count of ints   
// n = actual length of a                           
// 0 <= n <= INT_MAX                                
// m = max of P*(a,i-1,n-1)                         
// i <= n                                           
|- i<n
rowM = max(i, n, a); 
if (rowM > m) {
    m = rowM;
} 
i++;
// a = an array containing a finite count of ints   (A)
// n = actual length of a                           (B)
// 0 <= n <= INT_MAX                                (C)
// m = max of P*(a,i-1,n-1)                         (max, P*, 2, 3, 4, 6)
// i <= n                                           (E, 1)              
//additional notes
// * We know that m is the max of P*(a, i-1, n-1) because
// max(i, n, a) = the max of P(a, i, n-1), so given Line 2
// rowM = max of P(a, i, n-1)
// given P*(a,i,j) is all P(a,0..i,j), and m was max of P*(a,i-1,n-1) 
// we can deduce that if rowM is greater than m, m now contains the new max of P*(a,i-1,n-1)
// and if rowM is not greater than m, m still contains the old max of P*(a,i-1,n-1) 
// Thus either way m = max of P*(a,i-1,n-1)   

** exit loop1
// a = an array containing a finite count of ints   
// n = actual length of a                           
// 0 <= n <= INT_MAX                                
// m = max of P*(a,i-1,n-1)                         
// i <= n                                                                                    
~ i<n
return m;
// i = n                                                (1, E)
// m = max of P*(a,n-1,n-1)                             (D, above)            
// THUS msp(a,n) is the maximum of P*(a,n-1,n-1)        (above, 2)





// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Code for max(i, n, a)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// P(a,i,j) is all products of a[i..(0..j)]
// ------
// a = an array containing a finite count of ints
// if n = length of a 
// INT_MIN <= n <= INT_MAX
// 0 <= i <= n
// i0 = the value passed in as i
// Then 
// max(i, n, a) is the max of P(a, i, n-1)
int max(int i, int n,  int a[]) {
    int p = 1;
    int m = 1;
    while (i<n) {                               // take loop2
        // n = length of a
        // INT_MIN <= n <= INT_MAX
        // m = max of p
        // p = P(a, i0, i)
        // i <= n
        p *= a[i];
        if (p > m)
            m = p;
        i++;
    }                                           // exit loop2
    return m
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Proof of max(i, n, a)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


** pre loop2
// a = an array containing a finite count of ints
// if n = length of a 
// INT_MIN <= n <= INT_MAX
// 0 <= i <= n
// i0 = the value passed in as i
int p = 1;
int m = 1;
// a = an array containing a finite count of ints       (A)
// n = length of a                                      (B)
// INT_MIN <= n <= INT_MAX                              (C)
// 0 <= i <= n                                          (D)
// i0 = the value passed in as i                        (E)
// p = P(a, i0, i)                                      (Empty Set, P, 1)
// m = max state of p                                   (Mult Identity, Above, 2)

** take loop2
// a = an array containing a finite count of ints
// n = length of a
// INT_MIN <= n <= INT_MAX
// 0 <= i <= n
// i0 = the value passed in as i
// p = P(a, i0, i)
// m = max state of p
|- i < n
p *= a[i];
if (p > m)
    m = p;
i++;
// a = an array containing a finite count of ints       (A)
// n = length of a                                      (B)
// INT_MIN <= n <= INT_MAX                              (C)
// 0 <= i <= n                                          (D, 1)
// i0 = the value passed in as i                        (E)
// p = P(a, i0, i-1)                                    (P, 2, 5)
// m = max state of p                                   (G, 3, 4)*
//
//notes
//* m is still the max state of p because if in p's current state
// it becomes true that p > m, it means it is currently greater than it's 
// previous greatest state. This sets m = p, meaning m now containts the new 
// max state. IF this is not true, p is not currently it's max state, as it is
// not greater than what was before it's max state, so m is still its max state. 


** exit loop2
// a = an array containing a finite count of ints       
// n = length of a                                      
// INT_MIN <= n <= INT_MAX                              
// 0 <= i <= n                                          
// i0 = the value passed in as i                        
// p = P(a, i0, i-1)                                      
// m = max state of p                                                                
~ i < n
return m;
// i = n                                                (1, D)
// p = P(a, i0, i-1) 0                                  (F)
// p = P(a, i0, n-1)                                    (above 2)
// m = max state of p                                   (G)
// m = max of P(a,i0,n-1)                               (above 2)              
// THUS max(i, n, a) = max of P(a,i,n-1)              (2, above, def of i0)

