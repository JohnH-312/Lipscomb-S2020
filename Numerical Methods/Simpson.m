function [simpson_result] = Simpson(f, a, b, err, level, level_max)
  level = level + 1;
  h = b - a;
  c = (a+b)/2;
  one_simpson = h*(f(a) + 4*f(c) + f(b)) / 6;
  d = (a+c)/2;
  e = (c+b)/2;
  two_simpson = h*(f(a) + 4*f(d) + 2*f(c) + 4*f(e) + f(b))/12;
  if level >= level_max
    simpson_result = two_simpson;
    "maximum level reached"
  else
    if abs(two_simpson - one_simpson) < 15*err
      simpson_result = two_simpson + (two_simpson - one_simpson)/15;
    else 
      left_simpson = Simpson(f, a, c, err/2, level, level_max);
      right_simpson = Simpson(f, c, b, err/2, level, level_max);
      simpson_result = left_simpson + right_simpson;
    endif
  endif
endfunction
