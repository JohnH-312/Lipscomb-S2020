function z = Spline3_Coef(n, t, y)
  i = 0;
  for (i = 1:n)
    h(i) = t(i+1) - t(i);
    b(i) = (y(i+1) - y(i))/h(i);
  endfor
  u(1) = 2*(h(1) + h(2));
  v(1) = 6*(b(2) - b(1));
  for (i = 2:n)
    u(i) = 2*(h(i) + h(i-1)) - (h(i-1)^2)/u(i-1);
    v(i) = 6*(b(i) - b(i-1)) - (h(i-1)*v(i-1))/u(i-1);
  endfor
  z(n+1) = 0;
  for (i = n:-1:2)
    z(i) = (v(i) - h(i)*z(i+1))/u(i);
  endfor
  z(1) = 0;
endfunction
