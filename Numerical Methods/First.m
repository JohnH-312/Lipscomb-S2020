function [i, e] = First
  n= 30;
  x = 0.5;
  i = 0;
  imax = 0;
  error = 0;
  y = 0;
  h=1;
  emin = 1;
  for i=1:n
    h = 0.25*h;
    y = (sin(x+h) - sin(x))/h;
    error = abs(cos(x)-y);
    i, h, y, error
    if (error < emin)
      emin = error;
      imin = i;
    endif
  endfor
  imin, emin
endfunction
