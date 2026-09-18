#!/usr/bin/env python
import sys
from qat.lang.AQASM import *
from qat.qpus import PyLinalg

def ghz (nq, p, q):
    p.apply(H,q[0])
    for i in range(nq-1):
        p.apply(CNOT, q[i], q[i+1])


if len(sys.argv) == 1:
    print("Merci de mettre un nombre de qubits en argument\n")
    sys.exit()

nqbits = int(sys.argv[1]) 

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

