function X = maxim(f)
  i = 0;
  j=0;
  sum = 0;
  vol = 0;
  x=0;
  y=0;
  nmax = 5000;
  iprt = 1000;
  for (n = 1000:250:nmax)
    max = 0;
    R1 = RandomSet(n, 13483948);
    R2 = 2*RandomSet(n, 14492354);
    R3 = 2 + RandomSet(n, 52342534);
    for (i=1:n)
      x1 = R1(i);
      x2 = R2(i);
      x3 = R3(i);
      val = f(x1, x2, x3);
      if (val > max)
        max = val;
      endif
    endfor
    n, max
  endfor
endfunction
