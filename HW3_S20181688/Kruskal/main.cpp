//Kruskal
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

__int64 start, freq, end;

#define INPUT_FILE_NAME "commands.txt"
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))

float end_time;

typedef struct RESULT {

    int v;
    int e;
}Result;

typedef struct HEAP {

    int key;
    int from, to;
    int check;
}Heap;

typedef struct GRAPH {

    int n_v, n_e, max_w;
    int** weight;
}Graph;

typedef struct SUBSET {

    int rank;
    int parent;
}Subset;

Graph* init_Graph(int v, int e, int w);
Subset* init_Subset(int n_v);
Heap* init_Heap(int n_e);
int Find(Subset* s, int i);
void Union(Subset* s, int x, int y);
//void adjust(Graph* G, int parent, int n);
//void heapsort(Graph* G, int n);
void insert_min_heap(Heap* heap, int new_ele,int from, int to);
Heap delete_min_heap(Heap* heap);
void heap_sort(Heap* heap, Graph* G);
void Kruskal(Graph* G, Heap* heap, Subset* s, int n_v, int n_e, int max_w, FILE *fp);

int heap_size = 0;

Graph* init_Graph(int v, int e, int w) {

    Graph* graph = (Graph*)malloc(sizeof(Graph));

    graph->n_v = v;
    graph->n_e = e;
    graph->max_w = w;

    graph->weight = (int**)malloc(sizeof(int*) * graph->n_v);
    for (int i = 0; i < graph->n_v; i++) {

        graph->weight[i] = (int*)malloc(sizeof(int) * graph->n_v);
    }
    for (int i = 0; i < graph->n_v; i++) {
        for (int j = 0; j < graph->n_v; j++) {
            if (i == j) {

                graph->weight[i][j] = 0;
            }
            else
                graph->weight[i][j] = w+1;

        }

    }

    return graph;
}

Subset* init_Subset(int n_v) {

    Subset* subset = (Subset*)malloc(sizeof(Subset) * n_v);

    for (int i = 0; i < n_v; i++) {

        subset[i].parent = i;
        subset[i].rank = 0;
    }

    return subset;
}

Heap* init_Heap(int n_e) {

    Heap* heap = (Heap*)malloc(sizeof(Heap) * n_e);
    

    return heap;
}

int Find(Subset* s, int i) {

    if (i != s[i].parent) {

        s[i].parent = Find(s, s[i].parent);
    }

    return s[i].parent;
}

void Union(Subset* s, int x, int y) {

    int x_set = Find(s, x);
    int y_set = Find(s, y);

    if (s[x_set].rank > s[y_set].rank) {

        s[y_set].parent = x_set;
    }
    else if (s[x_set].rank < s[y_set].rank) {

        s[x_set].parent = y_set;
    }
    else {

        s[y_set].parent = x_set;
        s[x_set].rank++;
    }
}
/*
void adjust(Graph* G, int parent, int n) {

    int temp = G->weight[parent];

    int par_key = edge[parent].weight;
    int child = parent * 2;
    while (child<=n) {
        if ((child<n) && (edge[child].weight > edge[child + 1].weight))
            child++;
        if (edge[child].weight > par_key)
            break;
        else {
            edge[child / 2] = edge[child];
            child *= 2;
        }
    }
    edge[child / 2] = temp;
}

void heapsort(Graph* G, int n) {

    int i, j;
    Edge temp;

    for (i = n / 2; i > 0; i--)
        adjust(edge, i, n);
    for (i = n - 1; i > 0; i--) {
        temp = edge[1];
        edge[1] = edge[i + 1];
        edge[i + 1] = temp;
        adjust(edge, 1, i);
    }
}
*/

void insert_min_heap(Heap* heap, int new_element,int from, int to) {

    heap_size += 1;
    heap[heap_size].key = new_element;
    heap[heap_size].from = from;
    heap[heap_size].to = to;

    int child = heap_size;
    int parent = child / 2;
    while (parent) {

        if (heap[parent].key > heap[child].key) {

            Heap temp = heap[parent];
            heap[parent] = heap[child];
            heap[child] = temp;

            child = parent;
            parent = child / 2;
        }
        else {
            break;
        }
    }
    return;
}

Heap delete_min_heap(Heap* heap) {

    int parent=1, child=2;
    Heap root, temp;
    root = heap[1];
    heap[1].key = heap[heap_size].key;
    heap[1].from = heap[heap_size].from;
    heap[1].to = heap[heap_size].to;

    heap_size -= 1;

    while(child <= heap_size) {

        if (child + 1 <= heap_size && heap[child].key > heap[child + 1].key) {

            child += 1;
        }

        if (heap[parent].key > heap[child].key) {

            temp = heap[parent];
            heap[parent] = heap[child];
            heap[child] = temp;

            parent = child;
            child = parent * 2;
        }
        else {
            break;
        }
    }
    return root;
}

void Kruskal(Graph* G, Heap* heap, Subset* s, int n_v, int n_e, int max_w, FILE *fp) {

    int x = 0, y = 0, i, j;
    int num_connected = 0;
    
    Heap temp;
   
    Heap* h;
    int size = heap_size;
    h = (Heap*)malloc(sizeof(Heap) * heap_size+1);
    memcpy(h, heap, heap_size);
    
    for (i = 0; i < size; i++) {

        temp = delete_min_heap(heap);
        temp.check = 0;
        int x = Find(s, temp.from);
        int y = Find(s, temp.to);

        if (x != y) {

            Union(s, x, y);
            h [i+1].check = 1;
        }
  
    }

    for (i = 0; i < G->n_v; i++) {

        if (i == Find(s, i)) {

            num_connected++;
        }
    }
    
    Result *result = (Result*)malloc(sizeof(Result) * num_connected);
    int* root = (int*)malloc(sizeof(int) * num_connected);
    
    i = 0;
    for (j = 0; j < G->n_v; j++) {

        if (j == Find(s, j)) {

            root[i] = j;
          
            i++;
            
        }
    }

    for (i = 0; i < num_connected; i++) {

        result[i].e = 0;
        result[i].v = 0;
    }

    for (i = 0; i < G->n_v; i++) {

        for (j = 0; j < num_connected; j++) {

            if (root[j] == Find(s, i)) {

                result[j].v++;
                break;
            }
        }
    }
    heap_size = size;
    memcpy(heap, h, heap_size);
    for(i=0;i<size;i++) {

        temp = delete_min_heap(heap);
        int x = Find(s, temp.from);
        int y = Find(s, temp.to);


        if (x == y && temp.check == 1) {
            for (int k = 0; k < num_connected; k++) {

                if (root[k] == Find(s, x)) {

                    result[k].e += temp.key;
                    break;
                }
            }
        }
    }
    
     
    fprintf(fp, "%d\n", num_connected);

    for (i = 0; i < num_connected; i++) {

        fprintf(fp, "%d %d\n", result[i].v, result[i].e);
    }
    free(h);
    free(result);
    free(root);
}

int main(void) {

    Graph* G;
    FILE* fp;
    Heap* heap;
    Subset* s;
    char temp[256], dir_path[256], data_file[256], result_file[256];
    int i=0, n=0, from=0, to=0, weight=0, v=0, e=0, w=0, size = 0;
    

    fp = fopen(INPUT_FILE_NAME, "r");
    fgets(dir_path, sizeof(dir_path), fp);
    dir_path[strlen(dir_path) - 1] = '\\';

    fgets(data_file, sizeof(data_file), fp);
    data_file[strlen(data_file) - 1] = '\0';

    fgets(result_file, sizeof(result_file), fp);
    //result_file[strlen(result_file) - 1] = '\0';

    fclose(fp);
    strcpy(temp, dir_path);
    strcat(dir_path, data_file);

    fp = fopen(dir_path, "r");
    fscanf(fp, "%d %d %d", &v, &e, &w);

    G = init_Graph(v, e, w);
    s = init_Subset(G->n_v);
    heap = init_Heap(G->n_e);

    CHECK_TIME_START;
       
    for (i = 0; i < G->n_e; i++) {

        fscanf(fp, "%d %d %d", &from, &to, &weight);        

        if (G->weight[from][to] > weight ){

            G->weight[from][to] = weight;
            G->weight[to][from] = weight;
        }
        
    }
    
    for (i = 0; i < G->n_v; i++) {

        for (int j = i; j < G->n_v; j++) {

            if (G->weight[i][j] > 0 && G->weight[i][j] <= w) {

                insert_min_heap(heap, G->weight[i][j], i, j);
            }
        }
    }
    fclose(fp);

    strcat(temp, result_file);
    temp[strlen(temp) - 1] = '\0';
    fp = fopen(temp, "w");
    Kruskal(G, heap, s, G->n_v, G->n_e, G->max_w, fp);
    
    CHECK_TIME_END(end_time);
    printf("%f", end_time);
    free(heap);
    free(G);
    free(s);
    fclose(fp);   

    return 0;
}