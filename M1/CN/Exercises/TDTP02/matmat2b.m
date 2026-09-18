function C = matmat2b(A, B)
  [n, p] = size(A);
  [p2, m] = size(B);
  C = zeros(n, m);
  for i = 1:n
    for j = 1:m
      C(i,j) = A(i,:) * B(:,j);
    end
  end
end

