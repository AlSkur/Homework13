#include <iostream>
#include <string>

using namespace std;

const int MAX_PEOPLE = 100; 


struct Graph {
    string names[MAX_PEOPLE]; 
    int adjacency[MAX_PEOPLE][MAX_PEOPLE] = { 0 }; 
    int numPeople = 0; 
};


void addPerson(Graph& graph, const string& name) {
    if (graph.numPeople < MAX_PEOPLE) {
        graph.names[graph.numPeople] = name;
        graph.numPeople++;
    }
    else {
        cout << "Достигнуто максимальное количество людей!" << endl;
    }
}


void addConnection(Graph& graph, int person1, int person2) {
    if (person1 >= 0 && person1 < graph.numPeople && person2 >= 0 && person2 < graph.numPeople) {
        graph.adjacency[person1][person2] = 1;
        graph.adjacency[person2][person1] = 1; 
    }
    else {
        cout << "Ошибка: неверные индексы людей!" << endl;
    }
}


void findPairs(const Graph& graph) {
    for (int person = 0; person < graph.numPeople; ++person) {
        bool visited[MAX_PEOPLE] = { false };
        int distance[MAX_PEOPLE] = { 0 }; 

        int queue[MAX_PEOPLE];
        int front = 0, rear = 0;

        queue[rear++] = person;
        visited[person] = true;
        distance[person] = 0;

        while (front < rear) {
            int current = queue[front++]; 

            if (distance[current] == 3) {
                cout << "Пара знакомств через три рукопожатия: "
                    << graph.names[person] << " и " << graph.names[current] << endl;
                continue; 
            }

            for (int friend_person = 0; friend_person < graph.numPeople; ++friend_person) {
                if (graph.adjacency[current][friend_person] && !visited[friend_person]) {
                    visited[friend_person] = true;
                    distance[friend_person] = distance[current] + 1;
                    queue[rear++] = friend_person;
                }
            }
        }
    }
}

int main() {
    Graph graph;

    addPerson(graph, "A");
    addPerson(graph, "B");
    addPerson(graph, "C");
    addPerson(graph, "D");
    addPerson(graph, "E");

    addConnection(graph, 0, 1); 
    addConnection(graph, 0, 2); 
    addConnection(graph, 1, 3); 
    addConnection(graph, 2, 4); 

    findPairs(graph);

    return 0;
}