function C = matmat1b(A, B)
  [n, p] = size(A);
  [p2, m] = size(B);
  C = zeros(n, m);
  for i = 1:n
    C(i,:) = A(i,:) * B + C(i,:);
  endfor
end

