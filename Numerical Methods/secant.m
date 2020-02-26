function [i, e] = secant(f, a, b, nmax, e)
  n = 0;
  fa = f(a);
  fb = f(b);
  d = 0;
  
  if (abs(fa) > abs(fb))
    swap(a, b);
    swap(fa, fb);
  endif
  0, a, fa
  1, b, fb
  for (n=2:nmax)
    if (abs(fa) > abs(fb))
      #swaps them when fa is bigger than fb
      swap(a, b);
      swap(fa, fb);
    endif
    d = (b-a)/(fb-fa);
    b=a;
    fb=fa;
    d=d*fa;
    if (abs(d) < e)
      # this is true when our d-value is < error
      "convergence"
      return
    endif
    a = a-d;
    fa=f(a);
    # output
    n, a, fa 
  endfor
endfunction
