n_list = [10, 50, 100];
for n = n_list
  [~, temps, frelres, brelres, borne] = Ex7(n);
  printf("Ex7: n=%d, temps=%gs, err_avant=%.2e, err_arriere=%.2e, borne=%.2e\n", ...
         n, temps, frelres, brelres, borne);
end

n_values = [10, 30, 50];
for n = n_values
  A = rand(n, n);
  B = rand(n, n);
  printf("\n===== Taille n = %d =====\n", n);

  tic;
  C1 = matmat3b(A, B);
  t1 = toc;
  printf("Temps matmat3b (3 boucles): %f s\n", t1);

  tic;
  C2 = matmat2b(A, B);
  t2 = toc;
  printf("Temps matmat2b (2 boucles): %f s\n", t2);

  tic;
  C3 = matmat1b(A, B);
  t3 = toc;
  printf("Temps matmat1b (1 boucle): %f s\n", t3);

  C4 = C = A * B;

  printf("Test de valeur de matmat3d %f \n", norm(C4-C1)/norm(C4));
  printf("Test de valeur de matmat2d %f \n", norm(C4-C2)/norm(C4));
  printf("Test de valeur de matmat1d %f \n", norm(C4-C3)/norm(C4));

  printf("Erreur entre méthodes: %.2e\n", norm(C1 - C3));
end

