function [n, x] = TestBisection()
  nmax = 20;
  e = 1/2*10^-6;
  external function f;
  a = 0.0;
  b = 1.0;
  call bisection(f, a, b, nmax, e);
endfunction

function[f] = f(x)
  f = x^3 - 3*x + 1
endfunction
