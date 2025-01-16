#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char id[10];          
    int sales;            
    struct Node *left;    
    struct Node *right;   
} Node;


typedef struct {
    Node **line;         
    int count;           
    int totalSales;       
} BestLineResult;


Node* createNode(const char *id, int sales) 
{
    Node *node = (Node*)malloc(sizeof(Node));
    strcpy(node->id, id);
    node->sales = sales;
    node->left = NULL;
    node->right = NULL;
    return node;
}


BestLineResult findBestLine(Node *node) 
{
    BestLineResult result ={NULL, 0, 0};
    if (!node) return result;


    BestLineResult leftResult =findBestLine(node->left);
    BestLineResult rightResult =findBestLine(node->right);


    BestLineResult *bestSubPath =(leftResult.totalSales> rightResult.totalSales) ?&leftResult : &rightResult;


    result.count = bestSubPath->count + 1;
    result.totalSales = node->sales + bestSubPath->totalSales;
    result.line = (Node**)malloc(result.count * sizeof(Node*));
    result.line[0] = node;
    for (int i = 0; i < bestSubPath->count; i++) {
        result.line[i + 1] = bestSubPath->line[i];
    }


    free(bestSubPath->line);

    return result;
}


void distributeBonuses(BestLineResult bestLine,int totalBonus) {
    int totalSales=bestLine.totalSales;
    int budgetEfficiencyBonus=totalBonus*0.25; 
    int salesEfficiencyBonus=totalBonus*0.75;  

    printf("Employee Bonuses:\n");
    for (int i=0;i<bestLine.count;i++) {
        Node *employee=bestLine.line[i];

   
        int subordinateShare=(i*budgetEfficiencyBonus)/(bestLine.count-1);


        int salesShare=(employee->sales*salesEfficiencyBonus)/totalSales;

        int totalBonus=subordinateShare+salesShare;

        printf("ID: %s, Bonus: %d\n",employee->id,totalBonus);
    }

    free(bestLine.line); 
}


int main() 
{

    Node *root=createNode("SE1",10);
    root->left=createNode("SE2",12);
    root->right=createNode("SE3",7);
    root->left->left=createNode("SE4",4);
    root->left->right=createNode("SE5",17);
    root->right->left=createNode("SE6",6);
    root->right->right=createNode("SE7",3);
    root->left->left->right=createNode("SE8",9);
    root->left->right->left=createNode("SE9",10);
    root->left->right->right=createNode("SE10",11);
    root->right->left->left=createNode("SE11",18);
    root->right->left->right=createNode("SE12",2);
    root->right->right->left=createNode("SE13",13);
    root->right->right->right=createNode("SE14",15);
    root->left->left->right->left=createNode("SE15",20);
    root->left->right->left->left=createNode("SE16",8);
    root->left->right->left->left->right=createNode("SE17",18);


    BestLineResult bestLine=findBestLine(root);

    int totalBonus=3000000;
    distributeBonuses(bestLine, totalBonus);

    return 0;
}
