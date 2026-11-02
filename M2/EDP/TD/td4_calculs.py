#!/usr/bin/env python3
"""Reproduce TD4 numerical results (Python 3, NumPy, SciPy).

Run from the module directory: python TD/td4_calculs.py
The exercise 3 calculation uses the supplied histogram, not a regenerated one.
Exercise 4 uses a refitted exponential Monte Carlo null distribution.
Exercise 5 uses exact integer counting under a discrete uniform null.
"""

from fractions import Fraction
from math import comb

import numpy as np
from scipy import stats


SEED = 20261102
REPLICATES = 1_000_000
BATCH_SIZE = 10_000


def discrete_uniform_ks_exact_p(counts, two_sided=False):
    """Return the inclusive KS tail as a Fraction under an iid uniform null.

    For one-sided KS, the alternative is excess mass at small indices.
    With m categories, use integer deviations m*S_j - n*j to avoid
    floating-point errors at the inclusive observed boundary.
    """
    n, m = sum(counts), len(counts)
    cumulative = 0
    deviations = []
    for j, count in enumerate(counts, 1):
        cumulative += count
        deviations.append(m * cumulative - n * j)
    threshold = (max(map(abs, deviations)) if two_sided
                 else max(deviations))

    # dp[s]: number of partial assignments of n labeled observations;
    # s have been assigned to the first j categories, n-s remain.
    dp = {0: 1}
    for j in range(1, m + 1):
        nxt = {}
        for r, ways in dp.items():
            for s in range(r, n + 1):
                delta = m * s - n * j
                # Count the strict complement of the inclusive tail.
                if delta >= threshold:
                    continue
                if two_sided and delta <= -threshold:
                    continue
                nxt[s] = nxt.get(s, 0) + ways * comb(n - r, s - r)
        dp = nxt
    denominator = m ** n
    return Fraction(denominator - dp.get(n, 0), denominator)


def pearson_uniform(counts):
    observed = np.asarray(counts, dtype=float)
    expected = observed.mean()
    contributions = (observed - expected) ** 2 / expected
    statistic = contributions.sum()
    df = len(observed) - 1
    print('  expected:', expected, 'df:', df)
    print('  contributions:', contributions)
    print('  chi-square:', statistic, 'p:', stats.chi2.sf(statistic, df))
    return statistic


def fitted_exponential_ks(samples):
    """Rows contain samples; fit the rate independently in each row."""
    ordered = np.sort(np.asarray(samples, dtype=float), axis=1)
    n = ordered.shape[1]
    fitted_cdf = -np.expm1(-ordered / ordered.mean(axis=1, keepdims=True))
    d_plus = (np.arange(1, n + 1) / n - fitted_cdf).max(axis=1)
    d_minus = (fitted_cdf - np.arange(n) / n).max(axis=1)
    return np.maximum(d_plus, d_minus)


def main():
    np.set_printoptions(precision=9, suppress=True)
    print('Exercise 1: Student confidence intervals (microseconds)')
    x = np.array([
        [.0972, .1382, .7966],
        [.0971, .1432, .5300],
        [.0969, .1382, .5152],
        [.1954, .1730, .6675],
        [.0974, .1383, .5298],
    ])
    mean = x.mean(axis=0)
    sd = x.std(axis=0, ddof=1)
    se = sd / np.sqrt(len(x))
    print('  mean:', mean, '\n  sd:', sd, '\n  SE:', se)
    print('  CV:', sd / mean)
    for confidence in [.90, .99]:
        t = stats.t.ppf((1 + confidence) / 2, len(x) - 1)
        half_width = t * se
        print('  confidence:', confidence, 't:', t)
        print('  intervals (rows = systems):\n',
              np.column_stack([mean - half_width, mean + half_width]))
    assert np.argmin(sd) == 1

    print('\nExercise 2: die')
    chi2 = pearson_uniform([9, 4, 18, 15, 6, 8])
    print('  5% critical:', stats.chi2.ppf(.95, 5))
    assert np.isclose(chi2, 14.6)

    print('\nExercise 3: supplied generator histogram')
    chi3 = pearson_uniform([100, 96, 98, 85, 105, 93, 97, 125, 107, 94])
    print('  10% critical:', stats.chi2.ppf(.90, 9))
    assert np.isclose(chi3, 10.38)

    print('\nExercise 4: fitted exponential distribution')
    y = np.sort([133, 169, 8, 122, 58])
    rate = 1 / y.mean()
    f = -np.expm1(-rate * y)
    d_plus = np.arange(1, 6) / 5 - f
    d_minus = f - np.arange(5) / 5
    d = max(d_plus.max(), d_minus.max())
    print('  mean:', y.mean(), 'rate:', rate)
    print('  columns: x, fitted F, i/n-F, F-(i-1)/n\n',
          np.column_stack([y, f, d_plus, d_minus]))
    print('  D+:', d_plus.max(), 'D-:', d_minus.max(),
          'D:', d, 'K:', np.sqrt(5) * d)
    print('  continuous known-parameter 5% critical (not calibrated here):',
          stats.kstwo.ppf(.95, 5))
    assert np.isclose(d, .3120297086447916)

    # Scale invariance: Exp(1) is sufficient, but each sample MUST be refitted.
    rng = np.random.default_rng(SEED)
    hits = 0
    for start in range(0, REPLICATES, BATCH_SIZE):
        size = min(BATCH_SIZE, REPLICATES - start)
        simulated = rng.exponential(size=(size, 5))
        hits += np.count_nonzero(fitted_exponential_ks(simulated) >= d)
    p = (hits + 1) / (REPLICATES + 1)
    print('  refitted null: seed:', SEED, 'B:', REPLICATES,
          'exceedances:', hits, 'p:', p,
          'MC SE:', np.sqrt(p * (1 - p) / REPLICATES))
    assert abs(p - .38467) < .003

    print('\nExercise 5: cylinders')
    counts = [29, 19, 18, 25, 17, 10, 15, 11]
    n, m = sum(counts), len(counts)
    empirical = np.cumsum(counts) / n
    reference = np.arange(1, m + 1) / m
    deviations = empirical - reference
    dp, dm = max(0., deviations.max()), max(0., -deviations.min())
    print('  n:', n, 'm:', m)
    print('  columns: category, count, cumulative, Fn, F0, Fn-F0\n',
          np.column_stack([np.arange(m), counts, np.cumsum(counts),
                           empirical, reference, deviations]))
    print('  D+:', dp, 'D-:', dm, 'K:', np.sqrt(n) * max(dp, dm))
    print('  supplied continuous two-sided approximate critical D (5%, 1%):',
          np.array([1.35810, 1.62762]) / np.sqrt(n))
    p_one = discrete_uniform_ks_exact_p(counts)
    p_two = discrete_uniform_ks_exact_p(counts, two_sided=True)
    print('  exact discrete p, one-sided:', float(p_one))
    print('  exact discrete p, two-sided:', float(p_two))
    chi5 = pearson_uniform(counts)
    print('  chi-square critical (5%, 1%):', stats.chi2.ppf([.95, .99], 7))
    assert np.isclose(dp, 19 / 144) and dm == 0
    assert np.isclose(chi5, 49 / 3)
    assert abs(float(p_one) - .002238364912500474) < 1e-14
    assert abs(float(p_two) - .004476729761337440) < 1e-14

    # Small cases independently checked by enumerating all labeled assignments.
    from itertools import product
    for observed in ([2, 0], [1, 1], [2, 1, 0]):
        total, categories = sum(observed), len(observed)
        obs_delta = categories * np.cumsum(observed) - total * np.arange(1, categories + 1)
        for two_sided in (False, True):
            threshold = max(abs(obs_delta)) if two_sided else max(obs_delta)
            tail = 0
            for assignment in product(range(categories), repeat=total):
                freq = np.bincount(assignment, minlength=categories)
                delta = categories * np.cumsum(freq) - total * np.arange(1, categories + 1)
                value = max(abs(delta)) if two_sided else max(delta)
                tail += value >= threshold
            assert discrete_uniform_ks_exact_p(observed, two_sided) == Fraction(int(tail), categories ** total)
    print('\nAll numerical and small-case exact-enumeration checks passed.')


if __name__ == '__main__':
    main()
