#include<stdio.h>
#include<stdlib.h>
#include <string.h>

// The following is a employee in the organisation, it has the pointer to two more employees a subordinate_1 and a subordinate_2
struct Employee {
    int emp_id; // emp_ids will be unique
    struct Employee* subordinate_1;
    struct Employee* subordinate_2;
};

// The following function creates a employee and returns its pointer
struct Employee* create_employee(int x) {
    struct Employee* ptr = (struct Employee*) malloc(sizeof(struct Employee));
    ptr->emp_id = x;
    ptr->subordinate_1 = NULL;
    ptr->subordinate_2 = NULL;
    return ptr;
}

// The following code creates a organisation from scanning the input file
struct Employee* create_company() {
    int x;
    scanf("%d", &x);

    if(x == -1) return NULL; // -1 is used when there is a NULL pointer ie when no value is present
    struct Employee* par = create_employee(x);

    par->subordinate_1 = create_company();
    par->subordinate_2 = create_company();
    
    return par;
}

// The following function 
void print_company_helper(struct Employee* ceo) {
    // take input
    if(!ceo) {
        printf("%d ", -1);
        return;
    }
    printf("%d ", ceo->emp_id);
    print_company_helper(ceo->subordinate_1);
    print_company_helper(ceo->subordinate_2);
    return;
}

void print_company(struct Employee* ceo) {
    print_company_helper(ceo);
    printf("\n");
    return;
} 

// --------------------------------------------------- YOU CAN EDIT BELOW THIS LINE -----------------------------------

struct Employee* CEO = NULL;
// CEO is a global pointer that points to the CEO of the company


/*  In this function you have to print all the employees at a given level, Note that ceo is at level 0
In any of the functions which involve printing you need not print -1 for NULL pointers */
void Same_Level_Helper(struct Employee* emp, int level, int given){
    if (!emp){
        return;
    }
    if (given == level){
        printf("%d ",emp->emp_id);
        return;
    }
    Same_Level_Helper(emp->subordinate_1,level+1,given);
    Same_Level_Helper(emp->subordinate_2,level+1,given);
}

void EmployeesAtSameLevel(int level) {
    Same_Level_Helper(CEO,0,level);
    return;
}

// You have to print the employees as you search the organization look for the examples in the pdf and the input.txt and output.txt for details
// Note: You do not have to print -1 for NULL pointers
void get_employees_helper(struct Employee* emp) {
    if (!emp){
        return;
    }
    printf("%d ",emp->emp_id);
    get_employees_helper(emp->subordinate_1);
    get_employees_helper(emp->subordinate_2);
}

void get_employees() {
    get_employees_helper(CEO);
    return;
}

int Boss_Helper(struct Employee* emp, int emp_id, int parent_id){
    if (!emp){
        return -1;
    }
    if (emp->emp_id == emp_id){
        return parent_id;
    }
    int temp = Boss_Helper(emp->subordinate_1, emp_id, emp->emp_id);
    if (temp == -1){
        temp = Boss_Helper(emp->subordinate_2, emp_id, emp->emp_id);
    }
    return temp;
}

/* In the following function you have to print the immediate team of a employee - it includes their boss and their subordinates
Note: You do not have to print -1 for NULL pointers */
struct Employee* ImmediateTeamHelper(struct Employee* emp, int emp_id) {
    if (emp != NULL){
        if (emp->emp_id == emp_id){
            return emp;
        }
        struct Employee* temp = ImmediateTeamHelper(emp->subordinate_1,emp_id);
        if (temp == NULL){
            temp = ImmediateTeamHelper(emp->subordinate_2,emp_id);
        }
        return temp;
    }
    return NULL;
}

void ImmediateTeam(int emp_id) {
    int boss = Boss_Helper(CEO, emp_id, -1);
    if (boss != -1){
        printf("%d ",boss);
    }
    struct Employee* temp = ImmediateTeamHelper(CEO, emp_id);
    if (temp->subordinate_1){
        printf("%d ",temp->subordinate_1->emp_id);
    }
    if (temp->subordinate_2){
        printf("%d ",temp->subordinate_2->emp_id);
    }
    return;
}

// The following function returns the level of a employee with the given emp_id
int Level_helper(struct Employee* emp, int level, int emp_id){
    if (emp == NULL){
        return 0;
    }
    if (emp->emp_id == emp_id){
        return level;
    }
    int t = Level_helper(emp->subordinate_1, level+1, emp_id);
    if (t == 0){
        t = Level_helper(emp->subordinate_2, level+1, emp_id);
    } 
    return t;
}

int Level(int emp_id) {
    int level = Level_helper(CEO,0,emp_id);
    return level;
}

// The following function gives the distance between employees with emp_id1 and emp_id2
struct Employee* Distance_Helper(struct Employee* emp, int emp_id1, int emp_id2){
    if (!emp){
        return NULL;
    }
    if (emp->emp_id == emp_id1 || emp->emp_id == emp_id2){
        return emp;
    }
    struct Employee* left = Distance_Helper(emp->subordinate_1, emp_id1, emp_id2);
    struct Employee* right = Distance_Helper(emp->subordinate_2, emp_id1, emp_id2);
    if (left != NULL){
        if (right != NULL){
            return emp;
        }
        else{
            return left;
        }
    }
    else{
        if (right != NULL){
            return right;
        }
        else{
            return NULL;
        }
    }
}

int Distance(int emp_id1, int emp_id2) {
    struct Employee* common = Distance_Helper(CEO, emp_id1, emp_id2);
    int x = Level_helper(common, 0, emp_id1);
    int y = Level_helper(common, 0, emp_id2);
    return x+y;
}

/* The following function takes an emp_id this will belong to a employee in the organisation and your task is to return the emp_id of its boss
Note: If the boss does not exit return -1 */


int Boss(int emp_id) {
    if (CEO != NULL){
        int boss = Boss_Helper(CEO,emp_id,-1);
        return boss;
    }
    else{
        return -1;
    }
}
 
 int max(int x, int y){
    if (x>=y){
        return x;
    }
    return y;
 }

/* The following function returns the diameter of a Organisation - 
a diameter is the maximum distance between any two emp_ids in the organisation. You can use the distance function implemented above */
int Diameter_Helper(struct Employee* emp){
    if (!emp){
        return 0;
    }
    if (Diameter_Helper(emp->subordinate_1) > Diameter_Helper(emp->subordinate_2)){
        return 1 + Diameter_Helper(emp->subordinate_1);
    }
    return 1 + Diameter_Helper(emp->subordinate_2);
}

int Diameter_Help(struct Employee* tree) {
    if (tree != NULL){
        int lh = Diameter_Helper(tree->subordinate_1);
        int rh = Diameter_Helper(tree->subordinate_2);
        int ld = Diameter_Help(tree->subordinate_1);
        int rd = Diameter_Help(tree->subordinate_2);
        return (max(max(ld,rd),lh+rh));
    }
    return 0;
}

int Diameter() {
    int d = Diameter_Help(CEO);
    return d;
}

/* The following function takes an emp_id of a employee and returns the number of employees directly connected to it.
NULL pointers are not included */
int TeamSizeHelper(struct Employee* emp){
    if (emp == NULL){
        return 0;
    }
    int count = 1;
    count += (TeamSizeHelper(emp->subordinate_1) + TeamSizeHelper(emp->subordinate_2));
    return count;
}

int TeamSize(int emp_id) {
    struct Employee* temp = ImmediateTeamHelper(CEO, emp_id);
    if (temp){
        if (Level(emp_id) > 0){
            if (temp->subordinate_1 != NULL && temp->subordinate_2 != NULL){
                return 3;
            }
            if (temp->subordinate_1 != NULL || temp->subordinate_2 != NULL){
                return 2;
            }
            else{
                return 1;
            }
        }
        if (Level(emp_id) == 0){
            if (temp->subordinate_1 != NULL && temp->subordinate_2 != NULL){
                return 2;
            }
            if (temp->subordinate_1 != NULL || temp->subordinate_2 != NULL){
                return 1;
            }
            else{
                return 0;
            }
        }
    }
    return 0;
}


/* The following driver code creates a organisation for you and based on the input file
it will call all the functions that are necessary, your job is to edit the functions
above the line. Their descriptions are in the pdf and in the comments in the code. */

int main(int argc, char const *argv[])
{
    CEO = create_company();
    print_company(CEO);

    int T; 
    scanf("%d", &T);

    char operation_type[50];

    while(T--) {
        scanf("%s", operation_type);

        if(strcmp(operation_type, "level") == 0) {
            int x;
            scanf("%d", &x);
            int d = Level(x);
            printf("%d\n", d);
        } 

        if(strcmp(operation_type, "distance") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            int d = Distance(x, y);
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "employees_at_same_level") == 0) {
            int x;
            scanf("%d", &x);
            EmployeesAtSameLevel(x);
            printf("\n");
        }

        if(strcmp(operation_type, "get_employees") == 0) {
            get_employees();
            printf("\n");
        }

        if(strcmp(operation_type, "boss") == 0) {
            int x;
            scanf("%d", &x);
            int d = Boss(x);
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "diameter") == 0) {
            int d = Diameter();
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "immediate_team") == 0) {
            int x;
            scanf("%d", &x);
            ImmediateTeam(x);
            printf("\n");
        }

        if(strcmp(operation_type, "team_size") == 0) {
            int x;
            scanf("%d", &x);
            int d = TeamSize(x);
            printf("%d\n", d);
        }
    }

    return 0;
}
