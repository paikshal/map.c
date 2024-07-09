

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NUM_LOCATIONS 10

typedef struct {
    char name[20];
    int distance[NUM_LOCATIONS];
} Location;


Location locations[NUM_LOCATIONS] = {
    {"Amer Fort", {0, 10, 20, 30, 40, 50, 60, 70, 80, 90}},
    {"City Palace", {10, 0, 15, 25, 35, 45, 55, 65, 75, 85}},
    {"Hawa Mahal", {20, 15, 0, 10, 20, 30, 40, 50, 60, 70}},
    {"Jantar Mantar", {30, 25, 10, 0, 15, 25, 35, 45, 55, 65}},
    {"Nahargarh Fort", {40, 35, 20, 15, 0, 10, 20, 30, 40, 50}},
    {"Albert Hall Museum", {50, 45, 30, 25, 10, 0, 15, 25, 35, 45}},
    {"Birla Mandir", {60, 55, 40, 35, 20, 15, 0, 10, 20, 30}},
    {"Jal Mahal", {70, 65, 50, 45, 30, 25, 10, 0, 15, 25}},
    {"Sisodia Rani Garden", {80, 75, 60, 55, 40, 35, 20, 15, 0, 10}},
    {"Jaipur Zoo", {90, 85, 70, 65, 50, 45, 30, 25, 10, 0}}
};

void printMenu() {
    printf("Jaipur Map Navigation System\n");
    printf("-------------------------------\n");
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        printf("%d. %s\n", i + 1, locations[i].name);
    }
    printf("-------------------------------\n");
    printf("Enter your choice (1-10): ");
}

void printGraph() {
    printf("Graph:\n");
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        for (int j = 0; j < NUM_LOCATIONS; j++) {
            printf("%3d ", locations[i].distance[j]);
        }
        printf("\n");
    }
}

void navigate(Location* locations, int source, int destination) {
    int distances[NUM_LOCATIONS];
    int visited[NUM_LOCATIONS];
    int previous[NUM_LOCATIONS];

    // Initialize distances and visited arrays
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
        previous[i] = -1;
    }

    distances[source] = 0;

    int current = source;
    while (current != -1) {
        visited[current] = 1;

        for (int i = 0; i < NUM_LOCATIONS; i++) {
            if (!visited[i] && locations[current].distance[i] != 0 && distances[current] + locations[current].distance[i] < distances[i]) {
                distances[i] = distances[current] + locations[current].distance[i];
                previous[i] = current;
            }
        }

        int minDistance = INT_MAX;
        current = -1;
        for (int i = 0; i < NUM_LOCATIONS; i++) {
            if (!visited[i] && distances[i] < minDistance) {
                minDistance = distances[i];
                current = i;
            }
        }
    }

    // Print the shortest path
    if (distances[destination] != INT_MAX) {
        printf("Shortest path from %s to %s: ", locations[source].name, locations[destination].name);
        int path[NUM_LOCATIONS];
        int index = 0;
        for (int i = destination; i != -1; i = previous[i]) {
            path[index++] = i;
        }
        for (int i = index - 1; i >= 0; i--) {
            printf("%s ", locations[path[i]].name);
        }
        printf("\nDistance: %d km\n", distances[destination]);
    } else {
        printf("No path from %s to %s\n", locations[source].name, locations[destination].name);
    }
}

int main() {
    int source, destination;

    printMenu();
    printf("Enter source location (1-10): ");
    scanf("%d", &source);
    source--; // adjust for 0-based indexing

    printMenu();
    printf("Enter destination location (1-10): ");
    scanf("%d", &destination);
    destination--; // adjust for 0-based indexing

    printGraph(); // Call printGraph function to print the graph
    navigate(locations, source, destination);
    return 0; // Add a return statement to indicate successful execution
}