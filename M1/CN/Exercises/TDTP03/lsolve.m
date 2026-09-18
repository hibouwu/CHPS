function x = lsolve(L, b)
  n = length(b);
  x = zeros(n,1);
  x(n) = b(n) / L(n,n);
  for i = 1:n-1
    x(i) = (b(i) - L(i, i+1:n) * x(i+1:n)) / L(i,i);
  end
end
