function [x, M] = naive_Gauss(A, b)
  n = length(b);
  x = zeros(n, 1);
  M = zeros(n, n);
  
  for (k = 1:n-1)
    for (i = k+1:n)
      xmult = A(i,k)/A(k,k);
      A(i,k) = xmult;
      for (j = k + 1:n)
        A(i,j) = A(i,j) - (xmult*A(k,j));
      endfor
      b(i) = b(i) - xmult * b(k);
    endfor
  endfor
  x(n) = b(n)/A(n,n);
  for (i = n-1:-1:1)
    sum = b(i);
    for (j=i+1:n)
      sum = sum-A(i,j)*x(j);
    endfor
    x(i) = sum/A(i,i);
  endfor
  M = A;
endfunction
