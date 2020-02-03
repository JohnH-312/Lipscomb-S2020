function [x] = Gauss(n, A, b)
  l = length(n);
  for (i=1:n)
    l(i) = i;
    smax = 0;
    for (j=1:n)
      smax = max(smax, abs(A(i, j)));
    endfor
    s(i) = smax;
  endfor
  for (k=1:(n-1))
    rmax = 0;
    for (i = k:n)
      r = abs(A(l(i),k)/s(l(i)));
      if (r > rmax)
        rmax = r;
        j = i;
      endif
    endfor
    temp = l(j);
    l(j) = l(k);
    l(k) = temp;
    for (i=(k+1):n)
      xmult = (A(l(i),k))/(A(l(k),k));
      (A(l(i),k)) = xmult;
      for (j=(k+1):n)
        A(l(i),j) = A(l(i),j) - xmult*A(l(k),j);
      endfor
    endfor
  endfor
  #Solve part
  x = length(n);
  for (k=1:(n-1))
    for (i=(k+1):n)
      b(l(i)) = b(l(i))-A(l(i),k)*b(l(k));
    endfor
  endfor
  x(n) = b(l(n))/A(l(n),n);
  for (i=(n-1):1)
    sum = b(l(i));
    for (j=(i+1):n)
      sum = sum - A(l(i),j)*x(j)
    endfor
    x(i) = sum/A(l(i),i)
  endfor
  
endfunction
