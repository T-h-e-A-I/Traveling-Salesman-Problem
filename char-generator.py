import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os
from math import pi

# Load data from CSV file
file_path = "tsp_results.csv"  # Replace with your actual file path
data = pd.read_csv(file_path)

# Create an output directory for charts
output_dir = "charts"
os.makedirs(output_dir, exist_ok=True)

# Helper function to save charts
def save_chart(filename, format='png'):
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, filename), format=format, dpi=300)
    plt.close()

# 1. Bar Chart: Tour Length Comparison for Each TSP File
for instance in data['file_name'].unique():
    instance_data = data[data['file_name'] == instance].drop(columns=['file_name']).melt(var_name='Method', value_name='Tour Length')
    plt.figure(figsize=(10, 6))
    sns.barplot(data=instance_data, x='Method', y='Tour Length', palette='viridis')
    plt.title(f'Tour Length Comparison for {instance}')
    plt.xticks(rotation=45, ha='right')
    save_chart(f"{instance}_bar_chart.png")

# 2. Histogram: Best Performing Methods Across Instances
best_methods = data.drop(columns=['file_name']).idxmin(axis=1)
best_methods.value_counts().plot(kind='bar', figsize=(10, 6), color='skyblue')
plt.title('Best Performing Methods Across Instances')
plt.xlabel('Method')
plt.ylabel('Frequency')
save_chart("best_methods_histogram.png")

# 3. Line Chart: Method Performance Across Instances
for method in data.columns[1:]:
    plt.figure(figsize=(10, 6))
    sns.lineplot(data=data, x='file_name', y=method, marker='o', label=method)
    plt.title(f'Tour Length for {method} Across Instances')
    plt.xticks(rotation=45, ha='right')
    plt.ylabel('Tour Length')
    save_chart(f"{method}_line_chart.png")

# 4. Clustered Bar Chart: Impact of Improvement Heuristics
methods = [col for col in data.columns if '_2opt' in col or '_nodeshift' in col or '_nodeswap' in col]
improvement_data = data[['file_name'] + methods].melt(id_vars='file_name', var_name='Method', value_name='Tour Length')
plt.figure(figsize=(12, 8))
sns.barplot(data=improvement_data, x='file_name', y='Tour Length', hue='Method', dodge=True)
plt.title('Impact of Improvement Heuristics Across Instances')
plt.xticks(rotation=45, ha='right')
save_chart("improvement_heuristics_comparison.png")

# 5. Box Plot: Tour Length Distribution for Each Method
data_long = data.melt(id_vars='file_name', var_name='Method', value_name='Tour Length')
plt.figure(figsize=(12, 8))
sns.boxplot(data=data_long, x='Method', y='Tour Length', palette='Set3')
plt.title('Tour Length Distribution for Each Method')
plt.xticks(rotation=45, ha='right')
save_chart("method_distribution_boxplot.png")

# 6. Radar Chart: Instance-Wise Performance
for instance in data['file_name'].unique():
    instance_data = data[data['file_name'] == instance].set_index('file_name')
    categories = list(instance_data.columns)
    values = instance_data.values.flatten().tolist()

    # Radar chart setup
    angles = [n / float(len(categories)) * 2 * pi for n in range(len(categories))]
    angles += angles[:1]
    values += values[:1]

    plt.figure(figsize=(8, 8))
    ax = plt.subplot(111, polar=True)
    plt.xticks(angles[:-1], categories, color='grey', size=8)
    ax.plot(angles, values, linewidth=2, linestyle='solid')
    ax.fill(angles, values, alpha=0.4)
    plt.title(f'Performance Radar for {instance}', size=12, color='blue', y=1.1)
    save_chart(f"{instance}_radar_chart.png")

# 7. Cumulative Line Chart: Overall Efficiency
cumulative_data = data.drop(columns=['file_name']).cumsum()
plt.figure(figsize=(12, 8))
sns.lineplot(data=cumulative_data)
plt.title('Cumulative Tour Length Across Methods')
plt.ylabel('Cumulative Tour Length')
plt.xlabel('Instance')
save_chart("cumulative_performance.png")
