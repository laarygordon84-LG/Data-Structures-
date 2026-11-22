#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <cstdlib>
using namespace std;

// Graph class: each city maps to the set of cities it has a road to
class RoadNetwork {
private:
    map<string, set<string> > graph;

public:
    bool hasCity(const string& city) const {
        return graph.count(city) > 0;
    }

    bool addCity(const string& city) {
        if (hasCity(city)) return false;   // already exists
        graph[city];                       // creates an empty list of roads
        return true;
    }

    bool addRoad(const string& a, const string& b) {
        if (a == b || !hasCity(a) || !hasCity(b)) return false;
        graph[a].insert(b);
        graph[b].insert(a);
        return true;
    }

    bool removeRoad(const string& a, const string& b) {
        if (!hasCity(a) || !hasCity(b)) return false;
        if (graph[a].erase(b) == 0) return false;   // no such road
        graph[b].erase(a);
        return true;
    }

    void display() const {
        if (graph.empty()) {
            cout << "The network is empty." << endl;
            return;
        }
        map<string, set<string> >::const_iterator it;
        for (it = graph.begin(); it != graph.end(); ++it) {
            cout << it->first << " -> ";
            if (it->second.empty()) cout << "(no roads)";
            set<string>::const_iterator n;
            for (n = it->second.begin(); n != it->second.end(); ++n)
                cout << *n << "  ";
            cout << endl;
        }
    }

    // Breadth-first search: can we reach 'to' from 'from'?
    bool isConnected(const string& from, const string& to) const {
        if (!hasCity(from) || !hasCity(to)) return false;
        set<string> visited;
        queue<string> toVisit;
        toVisit.push(from);
        visited.insert(from);
        while (!toVisit.empty()) {
            string current = toVisit.front();
            toVisit.pop();
            if (current == to) return true;
            const set<string>& neighbours = graph.find(current)->second;
            set<string>::const_iterator n;
            for (n = neighbours.begin(); n != neighbours.end(); ++n) {
                if (visited.count(*n) == 0) {
                    visited.insert(*n);
                    toVisit.push(*n);
                }
            }
        }
        return false;
    }

    // Breadth-first traversal: prints every city reachable from 'start'
    void traverse(const string& start) const {
        if (!hasCity(start)) {
            cout << "City not found." << endl;
            return;
        }
        set<string> visited;
        queue<string> toVisit;
        toVisit.push(start);
        visited.insert(start);
        while (!toVisit.empty()) {
            string current = toVisit.front();
            toVisit.pop();
            cout << current << "  ";
            const set<string>& neighbours = graph.find(current)->second;
            set<string>::const_iterator n;
            for (n = neighbours.begin(); n != neighbours.end(); ++n) {
                if (visited.count(*n) == 0) {
                    visited.insert(*n);
                    toVisit.push(*n);
                }
            }
        }
        cout << endl;
    }
};

// Prints a prompt and reads a whole line (so names with spaces work)
string ask(const string& prompt) {
    string text;
    cout << prompt;
    getline(cin, text);
    return text;
}

int main() {
    RoadNetwork net;

    // Pre-load the example network from the image
    net.addCity("Accra");  net.addCity("Tema");   net.addCity("Kumasi");
    net.addCity("Sunyani"); net.addCity("Tamale");
    net.addRoad("Accra", "Tema");
    net.addRoad("Accra", "Kumasi");
    net.addRoad("Kumasi", "Sunyani");
    net.addRoad("Sunyani", "Tamale");

    int choice = -1;
    while (choice != 0) {
        cout << "\n--- Ghana City Road Network ---\n"
             << "1. Add city\n2. Add road\n3. Remove road\n"
             << "4. Display network\n5. Are two cities connected?\n"
             << "6. Traverse network\n0. Exit\n";
        choice = atoi(ask("Choose: ").c_str());

        if (choice == 1) {
            string c = ask("City name: ");
            cout << (net.addCity(c) ? "City added." : "City already exists.") << endl;
        } else if (choice == 2) {
            string a = ask("First city: ");
            string b = ask("Second city: ");
            cout << (net.addRoad(a, b) ? "Road added." : "Could not add road (check city names).") << endl;
        } else if (choice == 3) {
            string a = ask("First city: ");
            string b = ask("Second city: ");
            cout << (net.removeRoad(a, b) ? "Road removed." : "No such road.") << endl;
        } else if (choice == 4) {
            net.display();
        } else if (choice == 5) {
            string a = ask("First city: ");
            string b = ask("Second city: ");
            cout << (net.isConnected(a, b) ? "Yes, they are connected." : "No, they are not connected.") << endl;
        } else if (choice == 6) {
            net.traverse(ask("Start city: "));
        } else if (choice != 0) {
            cout << "Invalid choice." << endl;
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}
