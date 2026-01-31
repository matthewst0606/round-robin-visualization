#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define READY 0
#define RUNNING 1
#define FINISHED 2

typedef struct Process {
    int pid; // process id
    int TA;  // arrival time
    int TE;  // execution time
    int TT;  // turnaround time
    int RT;  // response time
    int state;

    struct Process *next;
} Process;

int getValidInt(const char *prompt);
void printQueue(struct Process *p);
void addProcess(Process **p);
void runRR(Process **p, int TQ);
void freeQueue(Process **p);

int getValidInt(const char *prompt) {
    int value;
    int result;
    do {
        printf("%s", prompt);
        result = scanf("%d", &value);
        if (result != 1) {
            printf("Invalid input — please enter an integer.\n");
            while (getchar() != '\n'); // clear buffer
        }
    } while (result != 1);
    return value;
}


void addProcess(Process **p) { 
    
    Process *newP = malloc(sizeof(struct Process));
    newP->pid = newP->TA = newP->TE = newP->TT = newP->RT = -1;

    printf("Add a Process to Queue:\n");
    newP->TA = getValidInt("Enter arrival time: ");
    printf("\n");
    newP->TE = getValidInt("Enter execution time: ");


    printf("\nProccess added successfully!\n");

    newP->next = *p;
    *p = newP;

    printQueue(*p);
}

void printQueue(Process *p) {
        
    
    while (p != NULL) {
        printf("| Process: P%d |" 
               "Arrival Time: %d |" 
               "Execution Time %d |"
               "Turnaround Time: %d |" 
               "Response Time: %d |\n",
              p->pid, p->TA, p->TE, p->TT, p->RT);
       
        p = p->next;
    }
}


void runRR(Process **p, int TQ) {
    Process *current = *p;


    printf("Time ->\n");

    while (current != NULL) {
        printf("P%d| ", current->pid);
        int time = 0;
        int remaining = current->TE;


        while (time != TQ) {
            if (remaining > 0) current->state = RUNNING;
            else if (remaining == 0) current->state = FINISHED;
            else current->state = READY;
            
            switch(current->state) {
                case READY:
                    printf("-");
                    break;
                case RUNNING:
                    printf("=");
                    break;
                case FINISHED:
                    printf("X");
                    break;
                default: break;
            }
            remaining--;
            time++;
        }
        printf("\n");
        current = current->next;
    }
}


void freeQueue(Process **p) {
    if ((*p) == NULL) printf("Nothing to free!\n");
    else printf("List is freed!\n");

    while ((*p) != NULL) {
        Process *temp = (*p);
        *p = (*p)->next;
        
        free(temp);
    }
    *p = NULL;
}






int main() {
    int option = 0;
    bool running = true;
    int timeQuantum = -1;

    Process *p = NULL;
    

    printf("Round Robin Scheduler Visualization\n"
            "-----------------------------------\n"
            "1. Add Process\n"
            "2. View Process Queue\n"
            "3. Run Simulation\n"
            "4. Clear Process Queue\n"
            "5. Exit\n"
        
    );

    
    timeQuantum = getValidInt("Enter time quantum: ");
        
    while (running) {
        option = getValidInt("\n\n>> Select an Option: ");
        
        
        switch (option) {
            case 1:
                addProcess(&p); 
                break;
            case 2:
                printQueue(p);
                break;
            case 3:
                runRR(&p, timeQuantum);
                break;
            case 4:
                freeQueue(&p);
                break;
            case 5:
                running = false;
                break;
            default: 
                printf("please enter a valid number!\n");
                break;
        }
    }   


    printf("goodbye!");
    return 0;
}
