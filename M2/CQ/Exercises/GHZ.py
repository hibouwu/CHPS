#!/usr/bin/env python
from qat.lang.AQASM import *
from qat.qpus import PyLinalg
import matplotlib.pyplot as plt


def ghz (nq, p, q):
    p.apply(H,q[0])
    for i in range(nq-1):
        p.apply(CNOT, q[i], q[i+1])

nqbits = 4 

prog = Program()
qbits = prog.qalloc(nqbits)

ghz(nqbits, prog, qbits)

circuit = prog.to_circ()
circuit.display()

job = circuit.to_job()

linalgqpu = PyLinalg()

result = linalgqpu.submit(job)
l = len(result);
states = ['']*l
probabilities= [0]*l

i=0
for sample in result:
    print("State",sample.state,"with amplitude",
            sample.amplitude,"and probability",
            round(sample.probability*100,2),"%")
    states[i] = str(sample.state)
    probabilities[i] = round(sample.probability*100,2)
    i = i+1

plt.bar(states, probabilities, color='skyblue')
plt.xlabel('States')
plt.ylabel('Probabilities')
plt.title('GHZ State')
plt.show()
