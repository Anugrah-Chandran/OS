#include <stdio.h>
int main(){
	int n,m,i,j,k;
	printf("Enter the no. of processes:");
	scanf("%d",&n);
	printf("Enter the no. of resources:");
	scanf("%d",&m);
	int alloc[n][m],max[n][m],need[n][m],avail[m];
	printf("\nEnter Allocation Matrix:\n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			scanf("%d",&alloc[i][j]);
			}
		}
	printf("\nEnter Max Matrix:\n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			scanf("%d",&max[i][j]);
			}
		}
	printf("\nEnter Available Matrix:\n");
	for(i=0;i<m;i++){
		scanf("%d",&avail[i]);
		}
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			need[i][j] = max[i][j] - alloc[i][j];
			}
		}
	int finish[n];
	int safeSeq[n];
	int work[m];
	for(i=0;i<n;i++){
		finish[i] = 0;
		}
	for(i=0;i<m;i++)
		work[i] = avail[i];
	int count = 0;
	while(count < n){
		int found = 0;
		for(i=0;i<n;i++){
			if(finish[i] == 0){
				for(j=0;j<m;j++){
					if(need[i][j] > work[j])
					break;
					}
				if(j==m){
					for(k=0;k<m;k++){
						work[k] += alloc[i][k];
						}
						safeSeq[count++] = i;
						finish[i] = 1;
						found = 1;
						}
					}
					}
				if(found == 0){
					printf("\nSystem is not safe!!\n");
					return 0;
					}
				}
		printf("\nSystem is safe:\n");
		printf("Safe sequence:\n");
		for(i=0;i<n;i++){
			printf("P %d",safeSeq[i]);
			}
		printf("\n");
		return 0;
	
	
	}
