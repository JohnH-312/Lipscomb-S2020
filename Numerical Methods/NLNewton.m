function [X] = NLNewton
  X = [0.1; 1.2; 2.5];
  for (k=1:10)
    F=[x1+x2+x3-3; x1^2 + x2^2 + x3^2 - 5; e^x1 + x1*x2 - x1*x3 - 1];
    J = [1, 1, 1; 2*x1, 2*x2, 2*x3; e^x1 + x2 - x3, x1, -x1];
    H=F/J;
    X=X-H;
  endfor

endfunction
