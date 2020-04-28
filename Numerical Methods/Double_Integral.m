function X = Double_Integral(f)
  i = 0;
  j=0;
  sum = 0;
  vol = 0;
  x=0;
  y=0;
  n = 5000;
  iprt = 1000;
   R1 = RandomSet(n, 13483948);
   R2 = RandomSet(n, 14492354);
  for (i=1:n)
    x = R1(i);
    y=R2(i);
    if (((x - 1/2)^2 + (y - 1/2)^20) <= 1/4)
      j = j+1;
      sum = sum + f(x,y);
      if ((mod(j, iprt)) == 0)
        vol = (pi/4)*sum/real(j);
        j, vol
      endif
    endif
  endfor
  vol = (pi/4)*sum/real(j);
  j, vol
endfunction
