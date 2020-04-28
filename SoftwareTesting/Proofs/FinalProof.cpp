//Proof - Jonny Hughes

//DEFS
// sorted - this means within an array A, the elements from [0..n] are considered to be sorted if 
// A[i] <= A[i+1] for all i in the range [0..n-1]. 
  
// If a[0..n] exists 
// Then after insertion_sort(a, n), a[0..n] is sorted
void insertion_sort(int a[], int n) {  
    int i = 0;
    while (i < n) {  
        // a[0..n] exists                                   
        // 0 <= n <= INT_MAX                                
        // a[0..i] is sorted                                
        // i <=n 
        i++;
        putInPlaceLeft(a, i);
    }  
}  

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// PROOF OF insertionSort(arr, n)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

** pre loop
// a[0..n] exists
// 0 <= n <= INT_MAX
int i = 0;
// a[0..n] exists                                   (A)
// 0 <= n <= INT_MAX                                (B)
// a[0..i] is sorted                                (single element = sorted, 1)
// i <=n                                            (1, B)

** take loop
// a[0..n] exists                                   
// 0 <= n <= INT_MAX                                
// a[0..i] is sorted                                
// i <=n                                                                
|- i<n
i++;
putInPlaceLeft(a, i);
// a[0..n] exists                                   (A)
// 0 <= n <= INT_MAX                                (B)
// a[0..i] is sorted                                (C, putInPlaceLeft, 2, 3) 
// i <=n                                            (D, 1)           
 

** exit loop
// a[0..n] exists                                   
// 0 <= n <= INT_MAX                                
// a[0..i] is sorted                                
// i <=n                                                                                                           
~ i<n
//  a[0..n] exists                                  (A)
// 0 <= n <= INT_MAX                                (C)
// i = n                                            (D, 1)
// a[0..n] is sorted                                (above, C)  



// If // a[0..i] exist and a[0..i-1] are sorted
// Then after putInPlaceLeft(a, i) a[0..i] is sorted
void putInPlaceLeft(int a[], int i) {
    int val = a[i];  
    int j = i - 1;  
    while (j > 0 && a[j] > val) {  
        // a[0..i] exist                    
        // a[0..j] and a[j+1..i] are sorted            
        // 1 <= i <= INT_MAX                
        // a[j+1..i] >= val  
        // j>= 0 
        a[j + 1] = a[j];  
        j = j - 1;  
    }
    a[j + 1] = val;  
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// PROOF OF putInPlaceLeft(a, i)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


** pre loop1
// a[0..i] exist 
// a[0..i-1] are sorted
// 1 <= i <= INT_MAX 
int val = a[i];  
int j = i - 1; 
// a[0..i] exist                    (A)
// a[0..j] and a[j+1..i] are sorted (B, empty list)
// 0 <= i <= INT_MAX                (C)
// a[j+1..i] >= val                 (1, 2, equivalency/Single Element)
// j >= 0                           (C, 2)

** take loop1
// a[0..i] exist                    
// a[0..j] and a[j+1..i] are sorted           
// 1 <= i <= INT_MAX                
// a[j+1..i] >= val      
// j >= 0                                                                                                  
|- j > 0 && a[j] > val
a[j + 1] = a[j];  
j = j - 1; 
// a[0..i] exist                    (A)
// a[0..j] and a[j+1..i] are sorted (B)
// 0 <= i <= INT_MAX                (C)
// a[j+1..i] >= val                 (1, D)  
// j >= 0                           (E, 1, 3)
 

** exit loop1
// a[0..i] exist                    
// a[0..j] and a[j+1..i] are sorted            
// 1 <= i <= INT_MAX                
// a[j+1..i] >= val  
// j>= 0                                                                                                               
~ a[j] > val
a[j + 1] = val;  
// a[0..i] exist                    (A)
// 0 <= i <= INT_MAX                (C)
// a[0..j] and a[j+1..i] are sorted (B, D, 2)
// a[j-1] <= a[j]                   (1 above)
// a[j] <= a[j+1]                   (1, 2)
// a[0..i] is sorted                (B, above, sorted)


** exit loop1v2
// a[0..i] exist                    
// a[0..j] and a[j+1..i] are sorted             
// 1 <= i <= INT_MAX                
// a[j+1..i] >= val    
// j>= 0                                                                                                            
~ j > 0 
a[j + 1] = val;  
// a[0..i] exist                    (A)
// 0 <= i <= INT_MAX                (C)\
// j = 0                            (1, E)
// a[0] <= a[j]                      (above)
// a[0..j] and a[j+1..i] are sorted (B, 1, 2, empty list)
// a[j] <= a[j+1]                   (1, 2)
// a[0..i] is sorted                (2above, above, sorted)