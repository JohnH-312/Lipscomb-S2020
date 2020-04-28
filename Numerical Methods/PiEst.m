function X = PiEst(n, f)
  R = 2*RandomSet(n, 29434248);
  i=0;
  sum = 0;
  for (i = 1:n)
     sum = sum + f(R(i));
  endfor
  X = 2/n * sum
endfunction
