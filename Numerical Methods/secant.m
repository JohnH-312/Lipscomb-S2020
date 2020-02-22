function [i, e] = secant(f, a, b, nmax, e)
  n = 0;
  fa = f(a);
  fb = f(b);
  d = 0;
  
  if (abs(fa) > abs(fb))
    tmp1= a;
    a = b;
    b = tmp1;
    tmp2 = fa;
    fa = fb;
    fb = tmp2;
  endif
  0, a, fa
  1, b, fb
  for (n=2:nmax)
    if (abs(fa) > abs(fb))
      tmp1= a;
      a = b;
      b = tmp1;
      tmp2 = fa;
      fa = fb;
      fb = tmp2;
    endif
    d = (b-a)/(fb-fa);
    b=a;
    fb=fa;
    d=d*fa;
    if (abs(d) < e)
      "convergence"
      return
    endif
    a = a-d;
    fa=f(a);
    n, a, fa
  endfor
endfunction
