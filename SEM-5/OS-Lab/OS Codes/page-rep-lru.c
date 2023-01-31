#include <stdio.h>
#include <stdlib.h>


struct page {
    int no;
    long int lru;
};

int search(struct page temp[], int l, int page){
    for (int i=0; i<l; i++){
        if (temp[i].no == page){
            return i;
        }
    }

    return -1;
}

int findLru(struct page temp[], int l){
    int minimum = INT32_MAX;
    int pos = -1;

    for (int i=0; i<l; i++){
        if (temp[i].lru <  minimum ){
            minimum = temp[i].lru;
            pos = i;
        }
    }

    return pos;
}


int main(){

    int hits = 0;
    int faults = 0;


    int n;
    printf("Enter the length of page refrence sequence: ");
    scanf("%d", &n);

    int ref[n];

    printf("Enter the reference string: \n");
    for (int i=0; i<n; i++){
        scanf("%d", &ref[i]);
    }

    int l;
    printf ("Enter the number of frames: ");
    scanf("%d", &l);

    struct page temp[l];

    for (int i=0; i<l; i++){
        temp[i].no = -1;
        temp[i].lru = 0;
    }


    int index;
    for (int i=0; i<n; i++){
        if ((index = search(temp, l, ref[i])) != -1){
            hits += 1;
            temp[index].lru = (temp[index].lru | 2147483648) >> 1;
            for (int j = 0; j<l; j++){
                if (j != index){
                    temp[j].lru = temp[j].lru >> 1;
                }
            }
        }

        else{
            int pos;
            faults += 1;
            pos = findLru(temp, l);
            temp[pos].no = ref[i];
            temp[pos].lru = 2147483648;

            for (int j = 0; j<l; j++){
                if ( j!= pos){
                    temp[j].lru = (temp[j].lru) >> 1;
                }
            }
            //printf("%d -> pos", pos);
        }
    }

    
    printf("Total number of page faults = %d\nTotal number of hits = %d", faults, hits);



}