import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from io import StringIO

# -------------------------- Налаштування --------------------------
CSV_FILE = 'experiment_results.csv'
TIME_UNIT = 'Time (microseconds, μs)' 
# ------------------------------------------------------------------

# Крок 1: Завантаження та Усереднення даних 
try:
    df = pd.read_csv(CSV_FILE)
except FileNotFoundError:
    print(f"Помилка: Файл '{CSV_FILE}' не знайдено. Переконайтеся, що він знаходиться в тому ж каталозі.")
    exit()

# Фільтрація: ВИДАЛЕННЯ НУЛЬОВИХ/ВІД'ЄМНИХ ЗНАЧЕНЬ ЧАСУ
df = df[df['Time_us'] > 0]

# Конвертуємо Volume у мільйони для кращої візуалізації
df['Volume_M'] = df['Volume'] / 1_000_000

# Усереднення: Групуємо за всіма параметрами експерименту та обчислюємо середній час
grouping_keys = ['Algorithm', 'Optimization', 'Volume', 'Threads', 'Volume_M']
df_avg = df.groupby(grouping_keys, as_index=False)['Time_us'].mean()


# -------------------------- Крок 2: Візуалізація усереднених результатів --------------------------

sns.set_theme(style="whitegrid")
plt.rcParams['figure.dpi'] = 100 
plt.rcParams['font.size'] = 10 

fig, axes = plt.subplots(1, 3, figsize=(21, 7)) 
# ВИПРАВЛЕННЯ: Додано більше горизонтального та вертикального простору
plt.subplots_adjust(wspace=0.3, hspace=0.3, top=0.9) 

# === Графік 1: Експеримент 1 та 3 (Оптимізація та Об'єм, Threads=1) ===
df_single_thread = df_avg[df_avg['Threads'] == 1].copy()

sns.lineplot(data=df_single_thread, 
             x='Volume_M', 
             y='Time_us', 
             hue='Optimization', 
             marker='o',
             ax=axes[0])

axes[0].set_title('Експеримент 1 та 3: Вплив Об\'єму та Оптимізації (Threads=1)', fontsize=12)
axes[0].set_xlabel('Об\'єм даних (мільйони елементів)')
axes[0].set_ylabel(TIME_UNIT)
axes[0].set_yscale('log') 
axes[0].legend(title='Оптимізація', loc='upper left')
axes[0].set_xticks(df_single_thread['Volume_M'].unique()) 


# === Графік 2: Експеримент 2 (Багатопотоковість) ===
df_multi_thread = df_avg[df_avg['Algorithm'] == 'parallel'].copy()
MAX_VOL = df_multi_thread['Volume'].max()
df_multi_thread = df_multi_thread[df_multi_thread['Volume'] == MAX_VOL]


sns.lineplot(data=df_multi_thread, 
             x='Threads', 
             y='Time_us', 
             marker='o',
             ax=axes[1])

axes[1].set_title(f'Експеримент 2: Вплив К-сті Потоків (Volume={MAX_VOL:,} елем.)', fontsize=12)
axes[1].set_xlabel('Кількість потоків')
axes[1].set_ylabel(TIME_UNIT)
axes[1].set_ylim(bottom=0) 
axes[1].set_xticks(df_multi_thread['Threads'].unique()) 


# === Графік 3: Порівняння Standard vs Parallel (O2) ===
VOLUME_TO_COMPARE = df['Volume'].max() 
df_comparison = df_avg[(df_avg['Volume'] == VOLUME_TO_COMPARE) & (df_avg['Optimization'] == 'O2')].copy()
df_comparison['Algorithm'] = df_comparison['Algorithm'].replace({'parallel': 'parallel'}) 

sns.barplot(data=df_comparison, 
            x='Threads', 
            y='Time_us', 
            hue='Algorithm',
            ax=axes[2])

axes[2].set_title(f'Порівняння Standard vs Parallel (O2, {VOLUME_TO_COMPARE:,} елем.)', fontsize=12)
axes[2].set_xlabel('Кількість потоків')
axes[2].set_ylabel(TIME_UNIT)
axes[2].legend(title='Алгоритм')


# Забезпечення того, що всі елементи помістяться (фінальний штрих)
# Ми все одно використовуємо tight_layout(), але після регулювання підкладок
plt.tight_layout() 

# ВАЖЛИВО: Якщо ви зберігаєте, використовуйте bbox_inches='tight'
# plt.savefig('performance_visualization.png', bbox_inches='tight')

# Якщо ви просто відображаєте, plt.tight_layout() має бути достатньо після налаштувань
plt.show()