function X = Random(n, seed)
  i = 0;
  k = 4269480;
  j = 2147483647;
  for (i = 1:n)
    if (i > 1)
      seed = mod(k*(seed+X(i-1)), j);
    else
     seed = mod(k*seed, j);
    endif
     X(i) = round(100*(real(seed)/real(j)));
  endfor
endfunction
