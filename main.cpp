#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person {
private:
    string name = "unknown";
public:
    string getName() {
        return name;
    }

    void setName(const string name) {
        this->name = name;
    }
};

class Worker : public Person {
private:
    char task = '-';
public:
    char getTask() {
        return task;
    }

    void setTask(char task) {
        this->task = task;
    }

    bool getBusy() {
        return task != '-';
    }
};

class Manager : public Person {
    int id = 0;
    vector<Worker> workers;

public:
    Manager(const string &name, int id) {
        setName(name);
        this->id = id;
    }

    void setWorkers(int countWorkers) {
        int i = 1;
        workers.resize(countWorkers);
        for (auto&& worker: workers) {
            worker.setName("Worker" + to_string(i++));
        }
    }

    void setTask(int command) {
        int hash = command + id;
        srand(hash);
        int taskCount = rand() % (workers.size() + 1);

        for (int i = 0; i < workers.size() and taskCount > 0; ++i) {
            char task = 'A' + rand() % 3;

            if (!workers[i].getBusy()) {
                taskCount--;
                workers[i].setTask(task);
            }
        }
    }

    bool teamBusy() {
        cout << getName() << "\'s team." << endl;
        bool found = false;

        for (auto&& worker: workers) {
            if (!worker.getBusy()) {
                if (!found) {
                    found = true;
                }
            }
            string task = "Task ";
            cout << worker.getName() << ": " << (worker.getBusy() ? task + worker.getTask() : "free") << endl;
        }
        return !found;
    }
};

class Director : public Person {
    vector<Manager> teams;
public:
    void setTeams(int teamsCount) {
        for (int i = 0; i < teamsCount; ++i) {
            cout << "Input the manager's name and count workers in his team: ";
            string name;
            int workersCount;
            cin >> name >> workersCount;
            teams.push_back(Manager(name, i + 1));
            teams[i].setWorkers(workersCount);
        }
    }

    void setCommand(int command) {
        for (auto&& team: teams) {
            team.setTask(command);
        }
    }

    bool companyBusy(){
        bool found = false;
        for(auto&& team : teams){
            if (!team.teamBusy() && !found){
                found = true;
            }
        }
        return !found;
    }
};

int main() {
    auto director = new Director;
    cout << "Input the count team: ";
    int countTeams;
    cin >> countTeams;

    director->setTeams(countTeams);

    do {
        cout << "Input the command: ";
        int command = 0;
        cin >> command;
        system("clear");
        director->setCommand(command);
    } while (!director->companyBusy());

    delete director;
    director = nullptr;
    return 0;
}
