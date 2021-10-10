void merge(void* lineptr[], int left, int mitad, int right, int (*comp)(void *, void *))
{	    
    for (int i=mitad;i<=right;i++)
    {
        for(int j=0;j<=mitad;j++)
        {
            if ((*comp)(lineptr[i],lineptr[j])<0) {
                void* tmp=lineptr[i];
                lineptr[i]=lineptr[j]; 
                lineptr[j]=tmp;
            }
        }
    }
}
void mergesort(void *lineptr[], int left, int right,int (*comp)(void *, void *)) {
	if(left<right)
    {
        int mitad=(right+left)/2;
        mergesort(lineptr,left,mitad,comp);
        mergesort(lineptr,mitad+1,right,comp);
		merge(lineptr, left, mitad, right,comp);
    }   
    return;
}
