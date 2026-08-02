"""
Reads q1_results.csv (produced by: ./q1_data > q1_results.csv)
and plots the growth of all 12 functions on a log-y scale, split into
two panels (slow-growing vs fast-growing) since the raw values span
from ~0.007 up to ~10^71 and won't fit legibly on one axis together.

Usage:
    gcc -O2 -o q1_data q1_data.c -lm
    ./q1_data > q1_results.csv
    python3 plot_q1.py
"""
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('q1_results.csv')

fig, axes = plt.subplots(1, 2, figsize=(15, 6.5))

# Panel 1: slower-growing functions
slow_cols = {
    'inv_n':    '1/n',
    'log2_n':   r'$\log_2 n$',
    'sqrt12':   r'$12\sqrt{n}$',
    'n50sqrt':  r'$50 n^{0.5}$',
    'pow051':   r'$n^{0.51}$',
    'nlog2n':   r'$n \log_2 n$',
}
for col, label in slow_cols.items():
    axes[0].plot(df['n'], df[col], linewidth=2, label=label)
axes[0].set_yscale('log')
axes[0].set_xlabel('n', fontsize=12)
axes[0].set_ylabel('f(n)  (log scale)', fontsize=12)
axes[0].set_title('Slower-growing functions', fontsize=13)
axes[0].legend(fontsize=10)
axes[0].grid(True, alpha=0.3, which='both')

#Panel 2: faster-growing functions
fast_cols = {
    'nlog2n':      r'$n \log_2 n$',
    'nsq_minus':   r'$n^2 - 324$',
    'hnsq_plus':   r'$100n^2 + 6n$',
    'twon3':       r'$2n^3$',
    'pow2_32n':    r'$2^{32} n$',
    'npow_log2n':  r'$n^{\log_2 n}$',
    'three_n':     r'$3^n$',
}
for col, label in fast_cols.items():
    axes[1].plot(df['n'], df[col], linewidth=2, label=label)
axes[1].set_yscale('log')
axes[1].set_xlabel('n', fontsize=12)
axes[1].set_ylabel('f(n)  (log scale)', fontsize=12)
axes[1].set_title('Faster-growing functions', fontsize=13)
axes[1].legend(fontsize=10)
axes[1].grid(True, alpha=0.3, which='both')

plt.tight_layout()
plt.savefig('q1_plot.png', dpi=150)
plt.show()
