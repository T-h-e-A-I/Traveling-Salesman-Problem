import os
import pandas as pd
import matplotlib.pyplot as plt

# Function to parse TSP file and extract coordinates
def parse_tsp(file_path):
    coords = {}
    with open(file_path, 'r') as file:
        reading_coords = False
        for line in file:
            if line.startswith("NODE_COORD_SECTION"):
                reading_coords = True
                continue
            if reading_coords and line.strip() == "EOF":
                break
            if reading_coords:
                parts = line.split()
                node_id = int(parts[0])
                x, y = map(float, parts[1:])
                coords[node_id] = (x, y)
    return coords

# Function to draw graph with the best tour
def draw_tsp_graph(coords, best_tour, output_path):
    plt.figure(figsize=(10, 8))

    # Plot all nodes
    for node, (x, y) in coords.items():
        plt.scatter(x, y, color='blue')
        plt.text(x, y, str(node), fontsize=8, color='darkgreen')

    # Plot best tour connections
    tour_nodes = best_tour + [best_tour[0]]  # Close the loop
    for i in range(len(tour_nodes) - 1):
        x1, y1 = coords[tour_nodes[i]]
        x2, y2 = coords[tour_nodes[i + 1]]
        plt.plot([x1, x2], [y1, y2], color='red')

    plt.title("TSP Graph with Best Tour")
    plt.xlabel("X Coordinate")
    plt.ylabel("Y Coordinate")
    plt.savefig(output_path, format='png')
    plt.close()

# Main function to process input folder and CSV
def main(input_folder, best_tour_csv, output_folder):
    os.makedirs(output_folder, exist_ok=True)

    # Read best tour CSV
    best_tours = pd.read_csv(best_tour_csv)

    # Process each TSP file and generate graph
    for _, row in best_tours.iterrows():
        file_name = row['file_name']
        best_tour = list(map(int, row['best_tour'].split()))

        tsp_path = os.path.join(input_folder, file_name)
        if not os.path.exists(tsp_path):
            print(f"File not found: {tsp_path}")
            continue

        coords = parse_tsp(tsp_path)
        output_path = os.path.join(output_folder, f"{os.path.splitext(file_name)[0]}_graph.png")
        draw_tsp_graph(coords, best_tour, output_path)
        print(f"Graph saved to: {output_path}")

# Example usage
if __name__ == "__main__":
    input_folder = "input"  # Folder containing TSP files
    best_tour_csv = "best_tours.csv"  # CSV with best tours
    output_folder = "output_graphs"  # Output folder for graphs
    main(input_folder, best_tour_csv, output_folder)
