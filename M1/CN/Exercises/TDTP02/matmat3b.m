function C = matmat3b(A, B)
  [n, p] = size(A);
  [p2, m] = size(B);
  C = zeros(n, m);
  for i = 1:n
    for j = 1:m
      for k = 1:p
        C(i,j) = C(i,j) + A(i,k) * B(k,j);
      end
    end
  end
end