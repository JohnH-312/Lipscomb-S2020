function [y, n] = hw1_sine(x, err)
  a=0;
  n=0;
  sum = 0;
  while ( x > pi)
    x = x - (2 * pi);
  endwhile
  
  for (i=0:100) 
    a = ((-1)^i) * ((x^(2*i+1)) / factorial(2*i+1));
    n = n + 1;
    sum = sum + a;
    if (abs(a) < err)
      break
    endif
  endfor
  y = sum;
endfunction
