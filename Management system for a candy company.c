/****************
 * Yehonatan Hadar
****************/

#include "ex_5.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    //Creating company's workers array
    Worker **workersArray = (Worker**)malloc(MAX_WORKERS * sizeof(Worker));
    //Creating company's projects array
    Project **projectsArray = (Project**) malloc(MAX_PROJECTS * sizeof(Project));

    int desiredOption=0, workerCount=INITIALIZATION_COUNTER_TO_ZERO, projectCount=INITIALIZATION_COUNTER_TO_ZERO;
    while(desiredOption!=EXIT)
    {
        printf("Welcome!\nPlease select the desired option:\n1. Join the company\n"
               "2. Open a new project\n3. Join an existing project\n"
               "4. See what projects are in work\n5. See which people are in what projects\n"
               "6. Work on existing project\n7. Leave the company\n8. Exit\nEnter your choice: ");

        scanf("%d", &desiredOption);

        switch (desiredOption)
        {
            case JOIN_THE_COMPANY:
            {
                joinCompany(*&workersArray, &workerCount);
                break;
            }

            case OPEN_A_NEW_PROJECT:
            {
                openNewProject(*&workersArray, workerCount, *&projectsArray, &projectCount);
                break;
            }

            case JOIN_AN_EXISTING_PROJECT:
            {
                workerJoinsProject(*&workersArray, workerCount,*&projectsArray, projectCount);
                break;
            }

            case SEE_WHAT_PROJECTS_ARE_IN_WORK:
            {
                displayProjects(*&projectsArray, projectCount);
                break;
            }

            case SEE_WHICH_PEOPLE_ARE_IN_WHAT_PROJECTS:
            {
                displayWorkers(*&workersArray, workerCount);
                break;
            }

            case WORK_ON_EXISTING_PROJECT:
            {
                workOnProject(*&workersArray, workerCount,&projectCount);
                break;
            }

            case LEAVE_THE_COMPANY:
            {
                leaveCompany(*&workersArray, &workerCount, *&projectsArray, &projectCount);
                break;
            }

            case EXIT:
            {
                printf("Exiting...");
                freeAllAllocations(*&workersArray, workerCount, *&projectsArray, projectCount);
                break;
            }

            default:
            {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    }
}

//This function checks if name of worker exists in the company
int isWorkerNameExists(Worker *workers[], int workerCount, const char *name)
{
    for (int i = 0; i < workerCount; i++)
    {
        if(strcmp((workers[i]->name),name)==THE_STRINGS_ARE_EQUAL)
            return WORKER_NAME_ALREADY_EXIST;
    }
    return WORKER_NAME_NOT_EXIST;
}

//This function add new worker to the company
void joinCompany(Worker *workers[], int *workerCount)
{
    //If there is already 50 workers in the company (the maximum number of workers the company can accommodate)
    if(*workerCount==MAX_WORKERS)
        printf("The quota of workers in the company is full. There is no place for additional workers.");
    //There is less than 50 workers in the company
    else
    {
        //Creating the new worker
        Worker *newWorker = (Worker*) malloc((sizeof(Worker)));
        if(newWorker==NULL)
        {
            printf("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        //Creating the new worker's name
        char *workerName = (char*)malloc(sizeof(char));
        if(workerName==NULL)
        {
            printf("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        int nameCounter=INITIALIZATION_COUNTER_TO_ZERO;
        clearInputBuffer();
        char *ptrWorkerName;
        printf("Enter the name of the new worker: ");
        scanf("%c", &workerName[nameCounter]);

        //Inputting the characters into the character array of the worker's name
        while (workerName[nameCounter] != '\0')
        {
            nameCounter++;
            ptrWorkerName = (char*) realloc(workerName,
                                            (nameCounter + INCREASING_VALUE_BY_ONE) * sizeof(char));
            if(ptrWorkerName==NULL)
            {
                printf("Memory allocation failed");
                workerName=NULL;
                newWorker=NULL;
                exit(EXIT_FAILURE);
            }
                //If the memory allocation succeed
            else
            {
                workerName=ptrWorkerName;
                scanf("%c", &workerName[nameCounter]);
                if(workerName[nameCounter]=='\n')
                    workerName[nameCounter]='\0';
                ptrWorkerName=NULL;
            }
        }
        free(ptrWorkerName);

        //Checks if the worker's name already exist in the company
        if((isWorkerNameExists(workers,*workerCount,workerName))==WORKER_NAME_ALREADY_EXIST)
        {
            printf("A worker with this name already exists.\n"
                   "There is not enough space in this company for both of us");
            free(workerName);
            free(newWorker);
        }
            //The worker's name not exist in the company
        else
        {
            //Adding the new worker to the company's workers
            workers[*workerCount]=newWorker;

            //Updating the number of the workers in the company
            (*workerCount)++;

            //Create the worker's projects array
            newWorker->projects = (Project**) malloc(sizeof(Project*));
            if(newWorker->projects==NULL)
            {
                printf("Memory allocation failed");
                exit(EXIT_FAILURE);
            }

            //Putting the new name of the new worker in 'worker->name'
            newWorker->name=workerName;

            //Initialization of the worker's project count to 0
            newWorker->projectCount=INITIALIZATION_COUNTER_TO_ZERO;
        }
    }

}

/*
This function prints all the workers's names in the company in list
according to the order of their entry into the company
*/
void displayAllWorkers(Worker *workers[], int workerCount)
{
    for (int i = 0; i < workerCount; i++)
        printf("%d. %s\n", (i+INCREASING_VALUE_BY_ONE), workers[i]->name);
}

//This function checks if name of project exists in the company
int isProjectNameExists(Project *projects[], int projectCount, const char *name)
{
    for (int i = 0; i < projectCount; i++)
    {
        if(strcmp((projects[i]->name),name)==THE_STRINGS_ARE_EQUAL)
            return PROJECT_NAME_ALREADY_EXIST;
    }
    return PROJECT_NAME_NOT_EXIST;
}

//This function open new project in the company
void openNewProject(Worker *workers[], int workerCount, Project *projects[], int *projectCount)
{
    //If there is already 100 projects in the company (the maximum number of projects the company can accommodate)
    if(*projectCount==MAX_PROJECTS)
        printf("The quota of projects in the company is full. There is no place for additional projects.");
    //There is less than 100 projects in the company
    else
    {
        int workerChoice;

        //If there are no workers in the company
        if (workerCount == NO_WORKERS_IN_COMPANY)
            printf("There are no workers in the company yet, please join the company first.\n");

            //There are workers in the company
        else
        {
            printf("Who are you? Choose a number:\n");
            displayAllWorkers(workers, workerCount);
            printf("Enter your choice: ");
            scanf("%d", &workerChoice);

            //Checks if the user's input is valid
            if((workerChoice<MIN_NUMBER_IN_DISPLAY_LIST)||(workerChoice>workerCount))
                printf("Invalid input.\n");

                //The user's input is valid
            else
            {
                char *projectName = (char *) malloc(sizeof(char));
                if(projectName==NULL)
                {
                    printf("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }

                int nameCounter=INITIALIZATION_COUNTER_TO_ZERO;
                char *ptrProjectName;
                clearInputBuffer();
                printf("Enter the name of the new project: ");
                scanf("%c", &projectName[nameCounter]);
                //Inputting the characters into the character array of the project's name
                while (projectName[nameCounter] != '\0')
                {
                    nameCounter++;
                    ptrProjectName = (char *) realloc(projectName,(nameCounter+1)*(sizeof(char)));

                    if(ptrProjectName==NULL)
                    {
                        printf("Memory allocation failed");
                        projectName=NULL;
                        exit(EXIT_FAILURE);
                    }
                        //Memory allocation succeed
                    else
                    {
                        projectName=ptrProjectName;
                        scanf("%c", &projectName[nameCounter]);
                        if(projectName[nameCounter]=='\n')
                            projectName[nameCounter]='\0';
                        ptrProjectName=NULL;
                    }
                }

                free(ptrProjectName);
                //Checks if the new project's name is exist in the company already
                if ((isProjectNameExists(projects, *projectCount, projectName)) == PROJECT_NAME_ALREADY_EXIST)
                {
                    printf("A project with name already exists.\nBetter be more creative\n");
                    free(projectName);
                }
                    //the new project's name not exist in the company already
                else
                {
                    Project *newProject = (Project*) malloc((sizeof(Project)));
                    if(newProject==NULL)
                    {
                        printf("Memory allocation failed");
                        exit(EXIT_FAILURE);
                    }

                    //Adding the new project to the company's projects array
                    projects[*projectCount]=newProject;

                    //Updating the number of the projects in the company
                    (*projectCount)++;

                    //Create the new project's workers array
                    newProject->workers = (Worker**) malloc(MAX_WORKER_IN_PROJECT * sizeof(Worker*));
                    if (newProject->workers==NULL)
                    {
                        printf("Memory allocation failed");
                        exit(EXIT_FAILURE);
                    }

                    //Putting the new name of the new project in 'project->name'
                    newProject->name=projectName;

                    //Initialization of the project's worker count to 0
                    newProject->workerCount=INITIALIZATION_COUNTER_TO_ZERO;

                    //Adding the worker that opened the new project to the new project's workers array
                    newProject->workers[newProject->workerCount]=workers[workerChoice-1];

                    //Updating the number of workers in the new project
                    newProject->workerCount++;

                    //If this is the first project of this worker, don't need to increase the array's size
                    if((workers[workerChoice-DECREASE_VALUE_BY_ONE]->projectCount)==NO_PROJECTS_WERE_ADDED)
                    {
                        //Adding the new project to the worker's projects array (the worker that opened the new project)
                        workers[workerChoice-DECREASE_VALUE_BY_ONE]->
                                projects[workers[workerChoice-DECREASE_VALUE_BY_ONE]->projectCount]=newProject;

                        //Updating the number of the worker's projects (the worker that opened the new project)
                        workers[workerChoice-DECREASE_VALUE_BY_ONE]->projectCount++;
                    }
                        /*
                        This is not the first project of this worker, so need to increase the array's size
                        for insert new project to his project's array
                        */
                    else
                    {
                        workers[workerChoice-DECREASE_VALUE_BY_ONE]->projects=
                                (Project**) realloc(workers[workerChoice-DECREASE_VALUE_BY_ONE]->
                                        projects,(workers[workerChoice-DECREASE_VALUE_BY_ONE]->
                                        projectCount+INCREASING_VALUE_BY_ONE)*
                                                 (sizeof (workers[workerChoice-DECREASE_VALUE_BY_ONE]->projects)));

                        if(workers[workerChoice-DECREASE_VALUE_BY_ONE]->projects==NULL)
                        {
                            printf("Memory allocation failed");
                            exit(EXIT_FAILURE);
                        }

                        //Adding the new project to the worker's projects array (the worker that opened the new project)
                        workers[workerChoice-DECREASE_VALUE_BY_ONE]->
                                projects[workers[workerChoice-DECREASE_VALUE_BY_ONE]->projectCount]=newProject;

                        //Updating the number of the worker's projects (the worker that opened the new project)
                        workers[workerChoice-DECREASE_VALUE_BY_ONE]->projectCount++;
                    }

                    //Initialization of the project's features
                    newProject->features=NULL;
                }
            }
        }
    }
}

/*
This function prints all the project's names in the company in list
according to the order of their entry into the company
 (designed for a print form required in the function of joining to an existing project)
*/
void displayAllProjectsInJoinAnExistingProject(Project *projects[], int projectCount)
{
    int printIndex=MIN_NUMBER_IN_DISPLAY_LIST;
    for (int i = 0; i < projectCount; i++)
    {
        printf("%d. %s (Workers: %d)\n", printIndex, projects[i]->name, projects[i]->workerCount);
        printIndex++;
    }
}

/*
This function prints all the project's names in the company in list
according to the order of their entry into the company
 (designed for a print form required in the function of work on existing project)
*/
void displayAllProjectsInWorkOnExistingProject(Project *projects[], int projectCount)
{
    int printIndex=MIN_NUMBER_IN_DISPLAY_LIST;
    for (int i = 0; i < projectCount; i++)
    {
        printf("%d. %s\n", printIndex, projects[i]->name);
        printIndex++;
    }
}

//This function checks if the worker is work in the selected project
int checkIfWorkerExitsInProject(Project *project, const char *name)
{
    for (int i = 0; i < (project->workerCount); i++)
    {
        if ((strcmp(project->workers[i]->name, name)) == THE_STRINGS_ARE_EQUAL)
            return THE_WORKER_ALREADY_WORK_ON_PROJECT;
    }
    return THE_WORKER_NOT_WORK_ON_PROJECT;
}

//This function joins a worker from the company to an existing project of another worker
void workerJoinsProject(Worker *workers[], int workerCount, Project *projects[], int projectCount)
{
    //If there are no workers in the company
    if(workerCount==NO_WORKERS_IN_COMPANY)
        printf("There are no workers in the company yet, please join the company first.\n");

    //There are workers in the company
    else
    {
        //If there are no projects in the company
        if(projectCount==NO_PROJECTS_IN_COMPANY)
            printf("There are no projects in the company yet, please create one first.\n");

        //There are projects in the company
        else
        {
            int choiceWorker;
            int choiceProject;

            printf("Select a worker to join a project:\n");
            displayAllWorkers(workers, workerCount);
            printf("Enter the worker's number: ");
            scanf("%d", &choiceWorker);

            //Checks if the user's input is valid
            if((choiceWorker<1)||(choiceWorker>workerCount))
                printf("Invalid worker selection.\n");
            //The user's input is valid
            else
            {
                printf("Select a project to join:\n");
                displayAllProjectsInJoinAnExistingProject(projects, projectCount);
                printf("Enter the project's number: ");
                scanf("%d", &choiceProject);

                //Checks if the user's input is valid
                if((choiceProject<MIN_NUMBER_IN_DISPLAY_LIST)||(choiceProject>projectCount))
                    printf("Invalid project selection.\n");

                //The user's input is valid
                else
                {
                    //Checks if the quota of workers in the project is full
                    if((projects[choiceProject-DECREASE_VALUE_BY_ONE]->workerCount)==MAX_WORKER_IN_PROJECT)
                        printf("Project is full.\n");

                    //There is enough place for an additional worker to enter the project
                    else
                    {
                        //Checks if the worker is work in the selected project already
                        if ((checkIfWorkerExitsInProject(projects[choiceProject-DECREASE_VALUE_BY_ONE],
                                                         workers[choiceWorker-DECREASE_VALUE_BY_ONE]->name))==
                                                         THE_WORKER_ALREADY_WORK_ON_PROJECT)
                            printf("The worker is already part of the project '%s'\n",
                                   projects[choiceProject-DECREASE_VALUE_BY_ONE]->name);

                        //The worker is not work in the selected project
                        else
                        {
                            //Adding the worker to the project's workers array
                            projects[choiceProject-DECREASE_VALUE_BY_ONE]->
                            workers[projects[choiceProject-DECREASE_VALUE_BY_ONE]->workerCount]=
                                    workers[choiceWorker-DECREASE_VALUE_BY_ONE];

                            //Updating the number of workers in the selected project
                            projects[choiceProject-DECREASE_VALUE_BY_ONE]->workerCount++;

                            //If this is the first project of this worker, don't need to increase the array's size
                            if((workers[choiceWorker-DECREASE_VALUE_BY_ONE]->projectCount)==NO_PROJECTS_WERE_ADDED)
                            {
                                //Adding the selected project to the worker's projects array (the selected worker)
                                workers[choiceWorker-DECREASE_VALUE_BY_ONE]->
                                projects[workers[choiceWorker-DECREASE_VALUE_BY_ONE]->projectCount]=
                                        projects[choiceProject-DECREASE_VALUE_BY_ONE];

                                //Updating the worker's project's number (the selected worker)
                                workers[choiceWorker-DECREASE_VALUE_BY_ONE]->projectCount++;
                            }
                            /*
                            This is not the first project of this worker, so need to increase the array's size
                            for insert new project to his project's array
                            */
                            else
                            {
                                workers[choiceWorker-DECREASE_VALUE_BY_ONE]->projects =
                                        (Project**) realloc(workers[choiceWorker-DECREASE_VALUE_BY_ONE]->
                                        projects, ((workers[choiceWorker-DECREASE_VALUE_BY_ONE]->projectCount+
                                        INCREASING_VALUE_BY_ONE)*(sizeof(workers[choiceWorker-DECREASE_VALUE_BY_ONE]->
                                        projects))));

                                if(workers[choiceWorker-DECREASE_VALUE_BY_ONE]->projects==NULL)
                                {
                                    printf("Memory allocation failed");
                                    exit(EXIT_FAILURE);
                                }

                                //Adding the selected project to the worker's projects array (the selected worker)
                                workers[choiceWorker-DECREASE_VALUE_BY_ONE]->
                                projects[workers[choiceWorker-DECREASE_VALUE_BY_ONE]->projectCount]=
                                        projects[choiceProject-DECREASE_VALUE_BY_ONE];

                                //Updating the worker's project's number (the selected worker)
                                workers[choiceWorker-DECREASE_VALUE_BY_ONE]->projectCount++;
                            }
                        }
                    }
                }
            }
        }
    }
}

/*
This function prints all the features's names in the selected project in list
according to the order of their entry into the project
 (designed for a print form required in the function of work on existing project)
*/
void printFeaturesInWorkOnProject(FeatureNode* head)
{
    int printIndex=MIN_NUMBER_IN_DISPLAY_LIST;

    FeatureNode* temp = head;
    while (temp != NULL)
    {
        printf("%d.%s\n", printIndex, temp->feature);
        printIndex++;
        temp = temp->next;
    }
}

/*
This function prints all the features's names in the selected project in list
according to the order of their entry into the project
 (designed for a print form required in the function of display projects)
*/
void printFeaturesInDisplayProjects(FeatureNode* head)
{
    FeatureNode* temp = head;
    while (temp != NULL)
    {
        printf("  - %s\n", temp->feature);
        temp = temp->next;
    }
}

/*
This function prints all the projects's names in the company in list
according to the order of their entry into the project
*/
void displayProjects(Project *projects[], int projectCount)
{
    //If there are no projects in the company
    if(projectCount==NO_PROJECTS_IN_COMPANY)
        printf("There are no projects to display.\n");
    //There are workers in the company
    else
    {
        for (int i = 0; i < projectCount; i++)
        {
            printf("Project: %s\n  ", projects[i]->name);

            printf("Workers in this project:\n");
            for (int j = 0; j < (projects[i]->workerCount); j++)
                printf("    - %s\n", (projects[i]->workers[j]->name));

            printf("  Features of the project:\n");
            if ((projects[i]->features) == NULL)
                printf("    No features\n\n");
            else
                printFeaturesInDisplayProjects(projects[i]->features);
        }
    }
}

/*
This function prints all the workers's names in the company in list
according to the order of their entry into the project
*/
void displayWorkers(Worker *workers[], int workerCount)
{
    //If there are no workers in the company
    if(workerCount==NO_WORKERS_IN_COMPANY)
        printf("There are no workers to display.\n");
    //There are workers in the company
    else
    {
        for (int i = 0; i < workerCount; i++)
        {
            printf("Worker: %s\n", workers[i]->name);

            if((workers[i]->projectCount)==NOT_INVOLVED_PROJECTS)
                printf("  Not involved in any projects.\n");
            else
            {
                printf("  Projects this worker is involved in:\n");
                for (int j = 0; j < (workers[i]->projectCount); j++)
                    printf("    - %s\n\n", workers[i]->projects[j]->name);
            }
        }
    }
}

//This function adding new feature to project
void addFeatureToProject(Project *project, FeatureNode *newFeature)
{
    if(project->features==NULL)
    {
        project->features=newFeature;
        newFeature->next=NULL;
    }
    else
    {
        FeatureNode *temp=project->features;

        while(temp->next != NULL)
            temp=temp->next;

        temp->next=newFeature;
        newFeature->next=NULL;
    }
}

//This function return the number of features in selected project
int findNumOfFeatures(Project *project)
{
    FeatureNode *head=project->features;
    int countFeatures=INITIALIZATION_COUNTER_TO_ZERO;

    while(head!=NULL)
    {
        countFeatures++;
        head=head->next;
    }

    return countFeatures;
}

//This function removing new feature to project
void removeFeatureFromProject(Project *project, int removeFeature)
{
    //If the selected feature is the first feature in the list
    if ((removeFeature-DECREASE_VALUE_BY_ONE)==FEATURE_LIST_HEADER)
    {
        FeatureNode *head = project->features;
        project->features = project->features->next;
        free(head->feature);
        free(head);
    }

    //If the selected feature is at the middle or at the end of the list
    else
    {
        FeatureNode *current = project->features;
        FeatureNode *prev = current;

        for (int i = 0; i < (removeFeature-1); i++)
        {
            prev = current;
            current = current->next;
        }

        prev->next = current->next;
        free(current->feature);
        free(current);
    }
}

//This function checks if feature is already exist in selected project
int isFeatureExists(Project *project, char *featureToCheck)
{
    FeatureNode *current = project->features;
    while (current != NULL)
    {
        if (strcmp(current->feature, featureToCheck)==THE_STRINGS_ARE_EQUAL)
            return THE_FEATURE_ALREADY_EXIST;
        current = current->next;
    }
    return THE_FEATURE_NOT_EXIST;
}

//Via This function, worker can edit (add/remove feature, if there is) project that he is part of it's workers
void workOnProject(Worker *workers[], int workerCount, int *projectCount)
{
    //If there are no workers in the company
    if (workerCount == NO_WORKERS_IN_COMPANY)
        printf("There are no workers in the company yet, please join the company first.\n");

    //There are workers in the company
    else
    {
        //If there are no projects in the company
        if (projectCount == NO_PROJECTS_IN_COMPANY)
            printf("There are no projects in the company yet, please create a project first.\n");

        //There are workers in the company
        else
        {
            int workerChoice;
            int projectChoice;

            printf("Select a worker:\n");
            displayAllWorkers(workers, workerCount);
            printf("Enter the worker's number: ");
            scanf("%d", &workerChoice);

            //Checks if the user's input is valid
            if ((workerChoice < MIN_NUMBER_IN_DISPLAY_LIST) || (workerChoice > workerCount))
                printf("Invalid worker selection.\n");

            //The user's input is valid
            else
            {
                //Checks if the selected worker involved in any projects
                if ((workers[workerChoice - DECREASE_VALUE_BY_ONE]->projectCount) == NOT_INVOLVED_PROJECTS)
                    printf("This worker is not involved in any projects.\n");

                //The selected worker involved in any projects
                else
                {
                    printf("Select a project:\n");
                    displayAllProjectsInWorkOnExistingProject(workers[workerChoice - DECREASE_VALUE_BY_ONE]->projects,
                                                              workers[workerChoice - DECREASE_VALUE_BY_ONE]->
                                                              projectCount);

                    printf("Enter the project number: ");
                    scanf("%d", &projectChoice);
                    //Checks if the user's input is valid
                    if ((projectChoice < MIN_NUMBER_IN_DISPLAY_LIST) ||
                    (projectChoice > workers[workerChoice - DECREASE_VALUE_BY_ONE]->projectCount))
                        printf("Invalid project selection.\n");

                    //The user's input is valid
                    else
                    {
                        char *featureAction = (char *) malloc(sizeof(char));
                        if (featureAction == NULL)
                        {
                            printf("Memory allocation failed");
                            exit(EXIT_FAILURE);
                        }

                        int featureActionIndex = INITIALIZATION_COUNTER_TO_ZERO;
                        clearInputBuffer();
                        char *ptrFeatureAction;
                        printf("Do you want to add or remove a feature? (add/remove): ");
                        scanf("%c", &featureAction[featureActionIndex]);

                        //Inputting the characters into the character array of the feature action's name
                        while (featureAction[featureActionIndex] != '\0')
                        {
                            featureActionIndex++;
                            ptrFeatureAction =(char *) realloc(featureAction,
                                                            (featureActionIndex+1)*(sizeof(char)));
                            if (ptrFeatureAction == NULL)
                            {
                                printf("Memory allocation failed");
                                featureAction=NULL;
                                exit(EXIT_FAILURE);
                            }
                            else
                            {
                                featureAction=ptrFeatureAction;

                                scanf("%c", &featureAction[featureActionIndex]);

                                if (featureAction[featureActionIndex] == '\n')
                                    featureAction[featureActionIndex] = '\0';
                                ptrFeatureAction=NULL;
                            }
                        }
                        free(ptrFeatureAction);

                        //Checks if the user's input is valid
                        if ((strcmp("add" , featureAction) != THE_STRINGS_ARE_EQUAL) &&
                        (strcmp("remove" , featureAction) != THE_STRINGS_ARE_EQUAL))
                        {
                            printf("Invalid choice.\n");
                            free(featureAction);
                        }

                        //The user's input is valid
                        else
                        {
                            //If the user choose to add a feature
                            if(strcmp(featureAction, "add") == THE_STRINGS_ARE_EQUAL)
                            {
                                free(featureAction);
                                char *featureName = (char *) malloc(sizeof(char));
                                if (featureName == NULL)
                                {
                                    printf("Memory allocation failed");
                                    exit(EXIT_FAILURE);
                                }

                                int featureNameCounter = INITIALIZATION_COUNTER_TO_ZERO;
                                char *ptrFeatureName;
                                printf("Enter the new feature: ");
                                scanf("%c", &featureName[featureNameCounter]);
                                //Inputting the characters into the character array of the new feature's name
                                while (featureName[featureNameCounter] != '\0')
                                {
                                    featureNameCounter++;
                                    ptrFeatureName =
                                            (char *) realloc(featureName,
                                                             (featureNameCounter+INCREASING_VALUE_BY_ONE)*
                                                             (sizeof(char)));

                                    if (ptrFeatureName == NULL)
                                    {
                                        printf("Memory allocation failed");
                                        featureName=NULL;
                                        exit(EXIT_FAILURE);
                                    }
                                    else
                                    {
                                        featureName=ptrFeatureName;
                                        scanf("%c", &featureName[featureNameCounter]);
                                        if (featureName[featureNameCounter] == '\n')
                                            featureName[featureNameCounter] = '\0';
                                        ptrFeatureName=NULL;
                                    }
                                }
                                free(ptrFeatureName);

                                //Creating the new feature place in the heap
                                FeatureNode *newFeature = (FeatureNode *) malloc(sizeof(FeatureNode));

                                if (newFeature == NULL)
                                {
                                    printf("Memory allocation failed");
                                    exit(EXIT_FAILURE);
                                }

                                //Checks if the feature already exist in the selected project
                                if ((isFeatureExists(workers[workerChoice-DECREASE_VALUE_BY_ONE]->
                                projects[projectChoice-DECREASE_VALUE_BY_ONE],featureName)) ==
                                THE_FEATURE_ALREADY_EXIST)

                                {
                                    printf("There is already this feature in the project.\n");
                                    free(featureName);
                                    free(newFeature);
                                }
                                //The new feature is not exist in the selected project
                                else
                                {
                                    newFeature->feature = featureName;
                                    addFeatureToProject(workers[workerChoice - DECREASE_VALUE_BY_ONE]->
                                    projects[projectChoice - DECREASE_VALUE_BY_ONE],newFeature);
                                }
                            }
                            //If the user choose to remove exist feature in the selected project
                            else
                            {
                                //Checks if there are features to remove in the selected project
                                if (((workers[workerChoice - DECREASE_VALUE_BY_ONE]->
                                projects[projectChoice - DECREASE_VALUE_BY_ONE]->features) == NULL) &&
                                ((strcmp(featureAction, "remove")) == THE_STRINGS_ARE_EQUAL))

                                {
                                    printf("There are no features to remove\n");
                                    free(featureAction);
                                }
                                //There are features to remove in the selected project
                                else
                                {
                                    if ((strcmp(featureAction, "remove")) == THE_STRINGS_ARE_EQUAL)
                                    {
                                        free(featureAction);
                                        int removeFeature;

                                        printf("Select a feature to remove:\n");
                                        printFeaturesInWorkOnProject
                                        (workers[workerChoice - DECREASE_VALUE_BY_ONE]->
                                        projects[projectChoice -DECREASE_VALUE_BY_ONE]->features);

                                        printf("Enter your choice: ");
                                        scanf("%d", &removeFeature);

                                        if ((removeFeature < MIN_NUMBER_IN_DISPLAY_LIST) ||
                                        (removeFeature >
                                        (findNumOfFeatures
                                        (workers[workerChoice - DECREASE_VALUE_BY_ONE]->
                                        projects[projectChoice - DECREASE_VALUE_BY_ONE]))))
                                            printf("Invalid choice.");
                                        else
                                            removeFeatureFromProject
                                            (workers[workerChoice - DECREASE_VALUE_BY_ONE]->
                                            projects[projectChoice - DECREASE_VALUE_BY_ONE],removeFeature);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//This function frees the features in the selected project
void freeFeatures(Project *project)
{
    int featureIndex = findNumOfFeatures(project);
    while (featureIndex>=LAST_FEATURE_PLACE)
    {
        removeFeatureFromProject(project,featureIndex);
        featureIndex--;
    }
}

//This function frees the selected project
void freeProject(Project *project)
{
    if(project->features==NULL)
    {
        free(project->name);
        free(project->workers);
        free(project);
    }
    else
    {
        freeFeatures(project);
        free(project->name);
        free(project->workers);
        free(project);
    }
}

//This function frees the selected worker
void freeWorker(Worker *worker)
{
    free(worker->name);
    free(worker->projects);
    free(worker);
}

//This function removes an employee from the company (include the projects that he was the only worker there(
void leaveCompany(Worker *workers[], int *workerCount, Project *projects[], int *projectCount)
{
    //If there are no workers in the company
    if(*workerCount==NO_WORKERS_IN_COMPANY)
        printf("There are no workers in the company yet, please join the company first.\n");

    //There are workers in the company
    else
    {
        int choiceWorker;

        printf("Select a worker to leave the company:\n");
        displayAllWorkers(workers,*workerCount);
        printf("Enter the worker's number: ");
        scanf("%d", &choiceWorker);

        //Checks if the user's input is valid
        if ((choiceWorker < MIN_NUMBER_IN_DISPLAY_LIST) || (choiceWorker > (*workerCount)))
            printf("Invalid worker selection.");

        //The user's input is valid
        else
        {
            //If the worker doesn't work on any project, simply release the worker from the company
            if ((workers[choiceWorker - DECREASE_VALUE_BY_ONE]->projectCount) == NOT_INVOLVED_PROJECTS)
            {
                freeWorker(workers[choiceWorker - DECREASE_VALUE_BY_ONE]);

                //Set the cell (in the worker's array in the company) of the leaving worker to be NULL
                workers[choiceWorker - DECREASE_VALUE_BY_ONE]=NULL;

                /*
                Deleting the empty cell created in the array and reducing the workers to the beginning
                  of the array according to their original order
                */
                for (int w = (choiceWorker - DECREASE_VALUE_BY_ONE); w < *workerCount; w++)
                {
                    workers[w] = workers[w + INCREASING_VALUE_BY_ONE];
                }

                //Set the last cell (in the worker's array in the company) to be NULL
                workers[*workerCount] = NULL;
                //Reduce the worker's count in the company by one
                (*workerCount)--;
            }
            //The worker work at least on one project
            else
            {
                /*
                We will pass on the company's projects array, and every project that the selected worker
                  is the only worker in the project we will remove this project and reduce the array
                */
                for (int y = 0; y < *projectCount; y++)
                {
                    //If the worker is the only worker in the project
                    if ((projects[y]->workerCount == THE_ONLY_WORKER_ON_PROJECT) &&
                    (isWorkerNameExists(projects[y]->workers, projects[y]->workerCount,
                                        workers[choiceWorker - DECREASE_VALUE_BY_ONE]->name) ==
                                        WORKER_NAME_ALREADY_EXIST))

                    {
                        freeProject(projects[y]);

                        //Set the cell (in the project's array in the company) of the leaving worker to be NULL
                        projects[y] = NULL;

                        /*
                        Deleting the empty cell created in the array and reducing the projects to the beginning
                          of the array according to their original order
                        */
                        for (int p = y; p < *projectCount; p++)
                        {
                            projects[p] = projects[p + INCREASING_VALUE_BY_ONE];
                        }

                        //Set the last cell (in the project's array in the company) to be NULL
                        projects[*projectCount] = NULL;
                        //Reduce the project's count in the company by one
                        (*projectCount)--;
                    }
                }

                //Pass on the project's array of the company
                for (int q = 0; q < *projectCount; q++)
                {
                    //Find the projects that the worker involved in
                    if ((isWorkerNameExists(projects[q]->workers, projects[q]->
                    workerCount,workers[choiceWorker - DECREASE_VALUE_BY_ONE]->name)) ==
                    WORKER_NAME_ALREADY_EXIST)

                    {
                        //Detecting the selected worker's place in the project's worker array
                        int workerIndex = INITIALIZATION_COUNTER_TO_ZERO;
                        for (int u = 0; u < projects[q]->workerCount; u++)
                        {
                            if (strcmp(projects[q]->workers[u]->name,
                                       workers[choiceWorker - DECREASE_VALUE_BY_ONE]->name) ==
                                       THE_STRINGS_ARE_EQUAL)

                            {
                                workerIndex = u;
                                break;
                            }
                        }
                        /*
                        Reducing the workers's array of the projects step back in the array, so that there is no gap
                        between 2 employees in an array
                        */
                        for (int b = workerIndex; b < projects[q]->workerCount; b++)
                        {
                            if(b==(projects[q]->workerCount-DECREASE_VALUE_BY_ONE))
                                break;
                            projects[q]->workers[b] = projects[q]->workers[b + INCREASING_VALUE_BY_ONE];
                        }

                        //Set the last cell (in the workers's array in the project) to be NULL
                        projects[q]->workers[projects[q]->workerCount-DECREASE_VALUE_BY_ONE] = NULL;

                        //Reduce the workers's count in the project by one
                        projects[q]->workerCount--;
                    }
                }

                freeWorker(workers[choiceWorker - 1]);
                //Set the cell (in the workers's array in the company) of the leaving worker to be NULL
                workers[choiceWorker - DECREASE_VALUE_BY_ONE]=NULL;

                /*
                Deleting the empty cell created in the array and reducing the workers to the beginning
                of the array according to their original order
                 */
                for (int w = (choiceWorker - DECREASE_VALUE_BY_ONE); w < *workerCount; w++)
                {
                    workers[w] = workers[w + INCREASING_VALUE_BY_ONE];
                }

                //Set the last cell (in the workers's array in the company) to be NULL
                workers[*workerCount] = NULL;
                //Reduce the counter of the workers's company to be NULL
                (*workerCount)--;
            }
        }
    }
}

//This function frees all the memory allocations in the program when the user want to exit
void freeAllAllocations(Worker *workers[], int workerCount, Project *projects[], int projectCount)
{
    for (int i = 0; i < projectCount; i++)
    {
        freeProject(projects[i]);
    }
    for (int j = 0; j < workerCount; j++)
    {
        free(workers[j]->name);
        free(workers[j]->projects);
        free(workers[j]);
    }

    free(projects);
    free(workers);
}

//This function clean the input buffer before scanf function
void clearInputBuffer(void)
{
    int c;
    while (((c = getchar()) != '\n') && (c != '\r'))
    {}
}