#include <stdio.h>
#include <stdlib.h>

int search(int temp[], int l, int page){
    for (int i=0; i<l; i++){
        if (temp[i] == page){
            return 1;
        }
    }

    return 0;
}

int main(){

    int hits = 0;
    int faults = 0;


    int n;
    printf("Enter the length of page refrence sequence: ");
    scanf("%d", &n);

    int ref[n];

    int tracker = 0;


    printf("Enter the reference string: \n");
    for (int i=0; i<n; i++){
        scanf("%d", &ref[i]);
    }

    int l;
    printf ("Enter the number of frames: ");
    scanf("%d", &l);

    int frames[l];

    for (int i=0; i<l; i++){
        frames[i] = -1;
    }

    for (int i=0; i<n; i++){
        if (search(frames, l, ref[i]) == 0){
            faults += 1;
            frames[tracker] = ref[i];
            tracker = (tracker+1)%l;

        }

        else{
            hits += 1;
        }
    }


    printf("Total number of page faults = %d\nTotal number of hits = %d", faults, hits);


}