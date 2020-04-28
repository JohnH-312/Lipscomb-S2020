function [R] = Romberg(f, a, b, n)
  h = b-a;
  r=zeros(n:n);
  R(1, 1) = (h/2)*(f(a)+f(b));
  for i = 2:n
    h=h/2;
    sum = 0;
    for k=2:2:(2^i - 1)
      sum = sum + f(a+k*h);
    endfor
    R(i,1) = 1/2*R(i-1,1) + sum * h;
    for j=2:i
      R(i,j) = R(i, j-1) + (R(i,j-1) - R(i-1, j-1))/(4^j - 1);
    endfor
  endfor
endfunction
