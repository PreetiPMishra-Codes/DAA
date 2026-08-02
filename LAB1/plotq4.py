"""
Reads q4_results.csv (produced by: ./q4 > q4_results.csv)
and plots number of moves vs number of discs, on both a linear
and a log scale (log scale makes the exponential growth a straight line).

How to run:
    gcc -O2 -o q4 q4.c
    ./q4 > q4_results.csv
    python3 plot_q4.py
"""
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('q4_results.csv')

fig, axes = plt.subplots(1, 2, figsize=(13, 5.5))

#linear scale k liye
axes[0].plot(df['N'], df['Moves'], marker='o', linewidth=2,
             color='#2ca02c', label='Simulated moves')
axes[0].plot(df['N'], df['Theoretical'], linestyle='--', color='black',
             label='Theoretical $2^n - 1$')
axes[0].set_xlabel('Number of discs (n)', fontsize=12)
axes[0].set_ylabel('Number of moves', fontsize=12)
axes[0].set_title('Towers of Hanoi: Moves vs n (linear scale)', fontsize=12)
axes[0].legend()
axes[0].grid(True, alpha=0.3)

# log scale (base 2) — exponential growth becomes a straight line
axes[1].plot(df['N'], df['Moves'], marker='o', linewidth=2,
             color='#2ca02c', label='Simulated moves')
axes[1].set_yscale('log', base=2)
axes[1].set_xlabel('Number of discs (n)', fontsize=12)
axes[1].set_ylabel('Number of moves (log2 scale)', fontsize=12)
axes[1].set_title('Towers of Hanoi: Exponential Growth (log scale)', fontsize=12)
axes[1].grid(True, alpha=0.3, which='both')

plt.tight_layout()
plt.savefig('q4_plot.png', dpi=150)
plt.show()
