function [X] = Coarse_Check()
  i = 0;
  m = 0;
  n=10000;
  per = 0;
  r = Random(n, 498432);
  for (i=1:n)
    if (r(i) <= 1/2)
      m = m+1;
    endif
    if (mod(i, 1000) == 0)
      per = 100 * real(m)/real(i);
      i, per
    endif
  endfor
endfunction
