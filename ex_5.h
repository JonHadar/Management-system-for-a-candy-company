#ifndef ASSIGNMENT_5_EX_5_H

#define ASSIGNMENT_5_EX_5_H

#endif //ASSIGNMENT_5_EX_5_H

#define DECREASE_VALUE_BY_ONE 1
#define LAST_FEATURE_PLACE 1
#define INITIALIZATION_COUNTER_TO_ZERO 0
#define INCREASING_VALUE_BY_ONE 1
#define NO_PROJECTS_WERE_ADDED 0
#define MIN_NUMBER_IN_DISPLAY_LIST 1
#define EXIT_FAILURE 1
#define MAX_WORKER_IN_PROJECT 4
#define THE_WORKER_ALREADY_WORK_ON_PROJECT 1
#define THE_WORKER_NOT_WORK_ON_PROJECT 0
#define THE_STRINGS_ARE_EQUAL 0
#define NO_WORKERS_IN_COMPANY 0
#define NO_PROJECTS_IN_COMPANY 0
#define NOT_INVOLVED_PROJECTS 0
#define WORKER_NAME_ALREADY_EXIST 1
#define WORKER_NAME_NOT_EXIST 0
#define PROJECT_NAME_ALREADY_EXIST 1
#define PROJECT_NAME_NOT_EXIST 0
#define THE_FEATURE_ALREADY_EXIST 1
#define THE_FEATURE_NOT_EXIST 0
#define FEATURE_LIST_HEADER 0
#define THE_ONLY_WORKER_ON_PROJECT 1
#define JOIN_THE_COMPANY 1
#define OPEN_A_NEW_PROJECT 2
#define JOIN_AN_EXISTING_PROJECT 3
#define SEE_WHAT_PROJECTS_ARE_IN_WORK 4
#define SEE_WHICH_PEOPLE_ARE_IN_WHAT_PROJECTS 5
#define WORK_ON_EXISTING_PROJECT 6
#define LEAVE_THE_COMPANY 7
#define EXIT 8

#define MAX_WORKERS 50
#define MAX_PROJECTS 100

// Forward declarations
typedef struct Worker Worker;
typedef struct FeatureNode FeatureNode;
typedef struct Project Project;

struct Worker
{
    char *name;
    Project **projects;
    int projectCount;
};

struct FeatureNode
{
    char *feature;
    struct FeatureNode *next;
};

struct Project
{
    char *name;
    Worker **workers;
    int workerCount;
    FeatureNode *features;
};

void clearInputBuffer(void);
int readNumber(void);
int isWorkerNameExists(Worker *workers[], int workerCount, const char *name);
int isFeatureExists(Project *project, char *featureToCheck);
void joinCompany(Worker *workers[], int *workerCount);
void openNewProject(Worker *workers[], int workerCount, Project *projects[], int *projectCount);
void workerJoinsProject(Worker *workers[], int workerCount, Project *projects[], int projectCount);
void displayWorkers(Worker *workers[], int workerCount);
void displayProjects(Project *projects[], int projectCount);
void displayAllProjectsInJoinAnExistingProject(Project *projects[], int projectCount);
void displayAllProjectsInWorkOnExistingProject(Project *projects[], int projectCount);
void displayAllWorkers(Worker *workers[], int workerCount);
void workOnProject(Worker *workers[], int workerCount, int *projectCount);
void addFeatureToProject(Project *project, FeatureNode *newFeature);
void removeFeatureFromProject(Project *project, int removeFeature);
void leaveCompany(Worker *workers[], int *workerCount, Project *projects[], int *projectCount);
void freeProject(Project *project);
void freeFeatures(Project *project);
void freeAllAllocations(Worker *workers[], int workerCount, Project *projects[], int projectCount);
int checkIfWorkerExitsInProject(Project *project, const char *name);
void printFeaturesInDisplayProjects(FeatureNode* head);
void printFeaturesInWorkOnProject(FeatureNode* head);
int findNumOfFeatures(Project *project);
void freeWorker(Worker *worker);
