    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define  max 48
    #define  MAX_VERTEX_NUM 256
    #define  VertexType int

    typedef enum{false,true} bool;
    // early time

    VertexType ve[MAX_VERTEX_NUM];
    // latest time

    VertexType vl[MAX_VERTEX_NUM];

    typedef struct ArcNode{
        int adjvex;                 // activity
        struct ArcNode * nextarc;   //point to next arc
        VertexType dut;
    }ArcNode;

    typedef struct VNode{
        VertexType data;    //vetex
        ArcNode * firstarc; //point to next arc
    }VNode,AdjList[MAX_VERTEX_NUM]; //store head node

    typedef struct ALGraph{
        AdjList vertices;   // vetex & neighbor
        int vexnum,arcnum;  // vetex & tasks
    }ALGraph;

    // vertex & activity
    int LocateVex(ALGraph G, VertexType u){
    int i;
        for (i = 0; i < G.arcnum; i++) {
            if (G.vertices[i].data == u) {
       //     printf("%d\n", G.vertices[i].data);
                return i;
            }
        }
        return -1;
    }

    void CreateAOE(ALGraph **G, int task, int vertex, char filename[]){
        *G = (ALGraph*)malloc(sizeof(ALGraph));

        (*G)->vexnum = vertex + 1;
        (*G)->arcnum = task;
        int i;
   //     printf("%d\n", (*G)->vexnum);
        for (i = 0; i < (*G)->vexnum; i++) {
            (*G)->vertices[i].data = i;
            (*G)->vertices[i].firstarc = NULL;
   //         printf("%d\n", (*G)->vertices[i].data);
        }

        FILE *fb;
        fb = fopen(filename, "r");
        fscanf(fb, "%d", &task);

        VertexType begin,end,dut;
        for (i = 0; i < (*G)->arcnum; i++) {
            fscanf(fb,"%d %d %d\n",&begin,&end,&dut);
       //     printf("%d,%d,%d\n", begin, end, dut);

            ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex = LocateVex(*(*G), end);
            p->nextarc = NULL;
            p->dut = dut;

            int locate = LocateVex(*(*G), begin);
            p->nextarc = (*G)->vertices[locate].firstarc;
            (*G)->vertices[locate].firstarc = p;
        }
    }

    typedef struct stack{
        VertexType data;
        struct stack * next;
    }stack;
    stack *T;

    void initStack(stack* *S){
        (*S)=(stack*)malloc(sizeof(stack));
        (*S)->next=NULL;
    }

    bool StackEmpty(stack S){
        if (S.next==NULL) {
            return true;
        }
        return false;
    }

    void push(stack *S, VertexType u){
        stack *p = (stack*)malloc(sizeof(stack));
        p->data = u;
        p->next = NULL;
        p->next = S->next;
        S->next = p;
    }

    void pop(stack *S, VertexType *i){
        stack *p = S->next;
        *i = p->data;
        S->next = S->next->next;
        free(p);
    }

    void FindInDegree(ALGraph G,int indegree[]){

        int i;
        for (i = 0; i < G.vexnum; i++) {
            indegree[i] = 0;
        }
        // according to activity , indegree+1
        for (i = 0; i < G.vexnum; i++) {
            ArcNode *p = G.vertices[i].firstarc;
            while (p) {
                indegree[p->adjvex]++;
                p = p->nextarc;
            }
        }
    }
    bool TopologicalOrder(ALGraph G){
        int indegree[G.vexnum];     //record vetex's in-degree
        FindInDegree(G,indegree);

        stack *S;

        initStack(&S);
        int i;
        for ( i=0; i < G.vexnum; i++) {
            ve[i]=0;
        }

        for (i = 0; i < G.vexnum; i++) {
            if (!indegree[i]) {
                push(S, i);
            }
        }
        int count=0;

        while (!StackEmpty(*S)) {
            int index;

            pop(S, &index);
            // latest time
            push(T, index);
            ++count;
            //if in-degree = 1, after delete prev node , vetex's in-degree = 0
            ArcNode *p;
            for (p = G.vertices[index].firstarc; p ; p = p->nextarc) {

                VertexType k = p->adjvex;

                if (!(--indegree[k])) {
                    //in-degree = 0
                    push(S, k);
                }
                // long path + distence longer than long path => ve =>  longest path length
                if (ve[index] + p->dut > ve[k]) {
                    ve[k] = ve[index] + p->dut;
                }
            }
        }
        //direct graph have cycle
        if (count < G.vexnum) {
            printf("No solution");
            return false;
        }
        return true;
    }

    // find early time & lastest time
    void CriticalPath(ALGraph G, FILE *fw){
        if (!TopologicalOrder(G)) {
            fprintf(fw,"No solution");
            return ;    // No solution
        }
        int i;
        for (i = 0 ; i < G.vexnum ; i++) {
            vl[i] = ve[G.vexnum - 1];
        }
        int j, k;
        while (!StackEmpty(*T)) {
            pop(T, &j);
            ArcNode* p;
            for (p = G.vertices[j].firstarc ; p ; p = p->nextarc) {
                k = p->adjvex;
                // if vetex - distence < arc_vetex
                if (vl[k] - p->dut < vl[j]) {
                    vl[j] = vl[k] - p->dut;
                }
            }
        }
        for (j = 0; j < G.vexnum; j++) {
        ArcNode*p;
            for (p = G.vertices[j].firstarc; p ;p = p->nextarc) {
                k = p->adjvex;
                int ee = ve[j];
                int el = vl[k] - p->dut; // latest time
                char tag = (ee == el) ? 'Y':'N';
                int flag = -1;

                if(tag == 'Y')
                flag = 0;

                if(el < 0 || flag == -1)
                {
                    printf("No solution");
                    fprintf(fw,"No solution");
                    return ;
                }
                printf("%3d%3d%3d%2c\n",ee,el, el - ee,tag);
                fprintf(fw,"%3d%3d%3d%2c\n",ee,el, el - ee,tag);
            }
        }
    }
    int main(){
        ALGraph *G;
     FILE *fp, *fw;
    char filename[max];
    scanf("%s", filename);
//    strcpy(filename,"input.txt");
    fp = fopen(filename, "r");
    fw = fopen("output.txt", "w");

    int task = 0;
    int i;
    int vertex = 0;
    int begin, end, value;
    fscanf(fp, "%d\n", &task);
    for(i = 0; i < task; i++)
    {
        fscanf(fp, "%d %d %d\n", &begin, &end, &value);
        if(vertex < end) vertex = end; // nodes
    }

    fclose(fp);
        CreateAOE(&G, task, vertex, filename);
        initStack(&T);
        TopologicalOrder(*G);
        CriticalPath(*G, fw);
        return  0;
    }
