function [n c fc] = newton(f, fp, x, nmax, e, sig)
  # find value r for function g(x) such that g(r) = 0
  # g(x) = x^3 - 2*x^2 + x - 3
  # see pg 128
  fx = f(x);
  0, x, fx
  for n=1:nmax
    fpv = fp(x);
    if abs(fpv) < sig 
      "small derivative"
      return;
    endif
    d = fx/fpv;
    x = x - d;
    fx = f(x);
    n, x, fx
    if abs(d) < e 
      "convergence"
      return;
    endif
  endfor
endfunction
