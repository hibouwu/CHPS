n_list = [50, 100, 300, 500, 800];
err = zeros(size(n_list));

for idx = 1:length(n_list)
  n = n_list(idx);
  U = triu(rand(n)) + eye(n);
  xex = rand(n, 1);
  b = U * xex;
  x = usolve(U, b);
  err(idx) = norm(x - xex) / norm(xex);
  printf("n=%d, err_rel=%.2e\n", n, err(idx));
end
