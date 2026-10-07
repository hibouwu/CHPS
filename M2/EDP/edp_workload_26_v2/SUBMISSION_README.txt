Workload practical - v2

Files
  answers.txt                  Answers to questions 1-15
  analyze.py                   Trace analysis and question 11 plot
  q11_size_distribution.png    Request-size histograms
  generate.py                  Generator for exercise 1
  generated.csv                100 generated requests, plus a header

Requirements: Python 3 and matplotlib.

To reproduce the results, put the teacher's v2 files trace_0.csv through
trace_4.csv in this folder, then run:

  python3 generate.py
  python3 analyze.py

If needed, install matplotlib with:
  python3 -m pip install matplotlib

The original trace files are not included. Conclusions refer to the supplied
v2 data; the script does not automatically select conclusions for new datasets.
Question 11 is based on visual inspection, not a formal normality test.
