"""
Reads q3_results.csv (produced by: ./q3 > q3_results.csv)
and plots comparisons vs array size for both bubble sort variants.
 
How to run:
    gcc -O2 -o q3 q3.c
    ./q3 > q3_results.csv
    python3 plot_q3.py
"""
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('q3_results.csv')

fig, ax = plt.subplots(figsize=(9, 6))
ax.plot(df['Size'], df['Optimized'], marker='o', linewidth=2,
        color='#1f77b4', label='(i) Optimized (early-exit) bubble sort')
ax.plot(df['Size'], df['Standard'], marker='s', linewidth=2,
        color='#d62728', label='(ii) Standard bubble sort (always n-1 passes)')

ax.set_xlabel('Array size (n)', fontsize=12)
ax.set_ylabel('Number of comparisons', fontsize=12)
ax.set_title('Bubble Sort: Comparisons vs Array Size (random data)', fontsize=13)
ax.legend(fontsize=11)
ax.grid(True, alpha=0.3)
ax.ticklabel_format(style='plain', axis='y')

plt.tight_layout()
plt.savefig('q3_plot.png', dpi=150)
plt.show()
