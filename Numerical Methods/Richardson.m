function [D, i, e] = Richardson(f, x, n, h0)
  i = 1;
  h = h0;
  n = n+1
  D = ones(n, 1);
  
  for (i = 1:n)
    D(i,1) = (f(x+h) - f(x-h))/(2*h);
    for (j = 2:i)
      D(i,j) = D(i, j-1) + (D(i, j-1) - D(i-1, j-1))/(4^j - 1);      
    endfor
    h = h/2
  endfor
  
endfunction
