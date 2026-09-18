#!/usr/bin/env python
import time
from qat.lang.AQASM import *
from qat.qpus import PyLinalg
import matplotlib.pyplot as plt

def ghz (nq, p, q):
    p.apply(H,q[0])
    for i in range(nq-1):
        p.apply(CNOT, q[i], q[i+1])

def run_ghz (nqbits):
    prog = Program()
    qbits = prog.qalloc(nqbits)

    ghz(nqbits, prog, qbits)

    circuit = prog.to_circ()
    #circuit.display()

    job = circuit.to_job()

    linalgqpu = PyLinalg()

    result = linalgqpu.submit(job)

    for sample in result:
        print("State",sample.state,"with amplitude",
                sample.amplitude,"and probability",
                round(sample.probability*100,2),"%")

# Premier run à blanc, pour charger la lib myqlm
run_ghz(2) 

# sampling
debut = 2
n = 28 ## 32 = limite pour myQLM, à 29 l'OOM killer shoote le process 
elapsed = [0]*(n-debut)
run = ['']*(n-debut)

for i in range(debut, n):
    start = time.time()
    run_ghz(i) 
    end = time.time()
    elapsed[i-debut] = end -start
    run[i-debut] = str(i)
    print("Run ", run[i-debut], "duree=", elapsed[i-debut], "%")
    
plt.bar(run, elapsed, color='skyblue')
plt.xlabel('runs')
plt.ylabel('elapsed time')
plt.title('Runs GHZ')
#plt.show()
plt.savefig('ghz-elapsed.png')
