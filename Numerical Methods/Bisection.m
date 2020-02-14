function [n, c, fc] = Bisection(f, a, b, nmax, e)
  #f is function
  # a and b are endpoints
  # e is error cutoff
  # nmax is the max number of iterations allowed
  # output n is number of iterations
  # output c is the zero found
  # output fc is the value of f(c)
  
  # test with f(x) = x^3 - 3x + 1 on [0, 1] see pg 118
  
  fa = f(a);
  fb = f(b);
  if fa*fb > 0
    a, b, fa, fb
    disp("function has same singns at a and b")
    return;
  endif
  error = b - a;
  for n=0:nmax
    error = error/2;
    c = a + error;
    fc = f(c);
    n, c, fc, error
    if abs(error) < e
      disp("convergence")
      return;
    endif
    if sign(fa) != sign(fc)
      b = c;
      fb = fc;
    else
      a = c;
      fa = fc;
    endif
  endfor
endfunction
