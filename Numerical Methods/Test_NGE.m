function [n, x] = Test_NGE
  m = 50;
  A = zeros(m, m);
  b = length(m);
  x = length(m);
  for (n=4:m)
    for (i=1:n)
      for (j=1:n)
        A(i,j) = single((i+1)^(j-1));
      endfor
      b(i) = single(((i+1)^n - 1)/i);
    endfor
    naive_Gauss(A, b);
    n, x
  endfor
endfunction
