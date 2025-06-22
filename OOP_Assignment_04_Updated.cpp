#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_LESSONS = 10;
const int MAX_SUBTOPICS = 10;
const int MAX_TOPICS = 10;
const int MAX_COURSES = 10;
const int MAX_PROGRAMS = 5;

class Lesson {
public:
    string title;
    string content;

    void input() {
        cout << "Enter Lesson Title: ";
        getline(cin, title);
        cout << "Enter Lesson Content: ";
        getline(cin, content);
    }

    void display() {
        cout << "\t\tLesson Title: " << title << endl;
        cout << "\t\tContent: " << content << endl;
    }

    void save(ofstream& out) {
        out << title << '\n' << content << '\n';
    }

    void load(ifstream& in) {
        getline(in, title);
        getline(in, content);
    }
};

class SubTopic {
public:
    string name;
    Lesson lessons[MAX_LESSONS];
    int lessonCount = 0;

    void input() {
        cout << "Enter SubTopic Name: ";
        getline(cin, name);
    }

    void addLesson() {
        if (lessonCount < MAX_LESSONS) {
            cout << "Adding Lesson to SubTopic: " << name << endl;
            lessons[lessonCount].input();
            lessonCount++;
        } else {
            cout << "Maximum lessons reached!\n";
        }
    }

    void display() {
        cout << "\tSubTopic: " << name << endl;
        for (int i = 0; i < lessonCount; i++) {
            lessons[i].display();
        }
    }

    void save(ofstream& out) {
        out << name << '\n' << lessonCount << '\n';
        for (int i = 0; i < lessonCount; i++) {
            lessons[i].save(out);
        }
    }

    void load(ifstream& in) {
        getline(in, name);
        in >> lessonCount;
        in.ignore();
        for (int i = 0; i < lessonCount; i++) {
            lessons[i].load(in);
        }
    }
};

class Topic {
public:
    string name;
    SubTopic subTopics[MAX_SUBTOPICS];
    int subTopicCount = 0;

    void input() {
        cout << "Enter Topic Name: ";
        getline(cin, name);
    }

    void addSubTopic() {
        if (subTopicCount < MAX_SUBTOPICS) {
            cout << "Adding SubTopic to Topic: " << name << endl;
            subTopics[subTopicCount].input();
            subTopicCount++;
        } else {
            cout << "Maximum subtopics reached!\n";
        }
    }

    void addLessonToSubTopic() {
        if (subTopicCount == 0) {
            cout << "No subtopics available.\n";
            return;
        }
        cout << "Available SubTopics:\n";
        for (int i = 0; i < subTopicCount; i++) {
            cout << "  " << i + 1 << ". " << subTopics[i].name << endl;
        }
        cout << "Enter SubTopic name to add a lesson: ";
        string subtopicName;
        getline(cin, subtopicName);
        for (int i = 0; i < subTopicCount; i++) {
            if (subTopics[i].name == subtopicName) {
                subTopics[i].addLesson();
                return;
            }
        }
        cout << "SubTopic not found.\n";
    }

    void display() {
        cout << "Topic: " << name << endl;
        for (int i = 0; i < subTopicCount; i++) {
            subTopics[i].display();
        }
    }

    void save(ofstream& out) {
        out << name << '\n' << subTopicCount << '\n';
        for (int i = 0; i < subTopicCount; i++) {
            subTopics[i].save(out);
        }
    }

    void load(ifstream& in) {
        getline(in, name);
        in >> subTopicCount;
        in.ignore();
        for (int i = 0; i < subTopicCount; i++) {
            subTopics[i].load(in);
        }
    }
};

class Course {
public:
    string name;
    Topic topics[MAX_TOPICS];
    int topicCount = 0;

    void input() {
        cout << "Enter Course Name: ";
        getline(cin, name);
    }

    void addTopic() {
        if (topicCount < MAX_TOPICS) {
            cout << "Adding Topic to Course: " << name << endl;
            topics[topicCount].input();
            topicCount++;
        } else {
            cout << "Maximum topics reached!\n";
        }
    }

    void display() {
        cout << "Course: " << name << endl;
        for (int i = 0; i < topicCount; i++) {
            topics[i].display();
        }
    }

    void save(ofstream& out) {
        out << name << '\n' << topicCount << '\n';
        for (int i = 0; i < topicCount; i++) {
            topics[i].save(out);
        }
    }

    void load(ifstream& in) {
        getline(in, name);
        in >> topicCount;
        in.ignore();
        for (int i = 0; i < topicCount; i++) {
            topics[i].load(in);
        }
    }
};

class StudyProgram {
public:
    string name;
    Course courses[MAX_COURSES];
    int courseCount = 0;

    void input() {
        cout << "Enter Study Program Name: ";
        getline(cin, name);
    }

    void addCourse() {
        if (courseCount < MAX_COURSES) {
            cout << "Adding Course to Study Program: " << name << endl;
            courses[courseCount].input();
            courseCount++;
        } else {
            cout << "Maximum courses reached!\n";
        }
    }

    void display() {
        cout << "Study Program: " << name << endl;
        for (int i = 0; i < courseCount; i++) {
            courses[i].display();
        }
    }

    void save(ofstream& out) {
        out << name << '\n' << courseCount << '\n';
        for (int i = 0; i < courseCount; i++) {
            courses[i].save(out);
        }
    }

    void load(ifstream& in) {
        getline(in, name);
        in >> courseCount;
        in.ignore();
        for (int i = 0; i < courseCount; i++) {
            courses[i].load(in);
        }
    }
};

StudyProgram programs[MAX_PROGRAMS];
int programCount = 0;

void displayMenu() {
    cout << "\n=== TBCMS Main Menu ===\n";
    cout << "1. Add Study Program\n";
    cout << "2. Add Course to Last Program\n";
    cout << "3. Add Topic to Last Course\n";
    cout << "4. Add SubTopic to Last Topic\n";
    cout << "5. Add Lesson to SubTopic by Name\n";
    cout << "6. Display All Data\n";
    cout << "7. Save Data to File\n";
    cout << "8. Load Data from File\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

void saveAll() {
    ofstream out("tbcms_data.txt");
    out << programCount << '\n';
    for (int i = 0; i < programCount; i++) {
        programs[i].save(out);
    }
    out.close();
    cout << "Data saved successfully.\n";
}

void loadAll() {
    ifstream in("tbcms_data.txt");
    if (!in) {
        cout << "Data file not found.\n";
        return;
    }
    in >> programCount;
    in.ignore();
    for (int i = 0; i < programCount; i++) {
        programs[i].load(in);
    }
    in.close();
    cout << "Data loaded successfully.\n";
    
    for (int i = 0; i < programCount; i++) {
        programs[i].display();
    }
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            if (programCount < MAX_PROGRAMS) {
                programs[programCount].input();
                programCount++;
            } else {
                cout << "Max study programs reached.\n";
            }
            break;
        case 2:
            if (programCount > 0) {
                programs[programCount - 1].addCourse();
            } else {
                cout << "No program available. Add one first.\n";
            }
            break;
        case 3:
            if (programCount > 0 && programs[programCount - 1].courseCount > 0) {
                programs[programCount - 1].courses[programs[programCount - 1].courseCount - 1].addTopic();
            } else {
                cout << "No course available. Add one first.\n";
            }
            break;
        case 4:
            if (programCount > 0 && programs[programCount - 1].courseCount > 0) {
                Course& course = programs[programCount - 1].courses[programs[programCount - 1].courseCount - 1];
                if (course.topicCount > 0) {
                    course.topics[course.topicCount - 1].addSubTopic();
                } else {
                    cout << "No topic available. Add one first.\n";
                }
            }
            break;
        case 5:
            if (programCount > 0 && programs[programCount - 1].courseCount > 0) {
                Course& course = programs[programCount - 1].courses[programs[programCount - 1].courseCount - 1];
                if (course.topicCount > 0) {
                    course.topics[course.topicCount - 1].addLessonToSubTopic();
                } else {
                    cout << "No topic available. Add one first.\n";
                }
            }
            break;
        case 6:
            for (int i = 0; i < programCount; i++) {
                programs[i].display();
            }
            break;
        case 7:
            saveAll();
            break;
        case 8:
            loadAll();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
