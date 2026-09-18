
#1
A = rand(n, n);

#2
xex = rand(n, 1);

#3
b = A * xex;

#4
tstart = tic;
x = A \ b;
temps = toc(tstart)

#5 erreur avant
frelres = norm(x - xex) / norm(xex)
# erreur arriere
brelres = norm(b - A * x) / norm(b)

borne = cond(A) * brelres
cond(A)
norm(A)*norm(inverse(A))
