#include<stdio.h>
#include <time.h>
#include<stdlib.h>

int grammes(void); //rows
int sthles(void);  //columns
int bomb(int koutia); //number of bombs
void insertbombs(int *mpla, int total, int M, int N, int K); //place bombs randomly
void insertnumbers(int *mpla, int N, int M, int total, FILE *fp); //calculate numbers around bombs


int main(void)
{
  int K, M, N, *nark, total;
  FILE *fp;
  
  //system("chcp 1253"); //for greek display
  
  M = grammes(); //get rows
  N = sthles();  //get columns
  total = N*M;   //total cells in grid

//Allocate memory for the grid
  
  nark = (int*) malloc(total*sizeof(int));
  if(nark==NULL)
  exit(1);
  
  K = bomb(total);  // Get number of bombs
  
  insertbombs( nark, total, M, N, K); // Place bombs in the grid

  
  // Open file to save results
  fp = fopen("test_narkaliefth.txt", "w");
  if(fp == NULL)
  exit(1);

  // Compute numbers around bombs and print result
  
  insertnumbers(nark, N, M, total, fp);
  
  fclose(fp);
  free(nark);
  return 0;
  	
}


// Ask user for number of rows
int grammes(void)
{
	int M;
	printf("\n\nEnter number of rows: ");
	scanf("%d", &M);
	return M;
}

// Ask user for number of columns
int sthles(void)
{
	int N;
	printf("\nEnter number of columns: ");
	scanf("%d", &N);
	return N;
}

//Ask user for number of bombs, ensuring it does not exceed total cells
int bomb(int koutia)
{	
	int K;
	do 
	{
	   printf("\nEnter number of bombs: ");
	   scanf("%d", &K);
    }while(K > (koutia));
    return K;
}



// Randomly place bombs in the grid (represented by value 10)
void insertbombs(int *mpla, int total, int M, int N, int K)
{
	int i, luck, b, eight;
	
 // Initialize all cells to 0
	for(b=0; b < total; b++)     
	mpla[b] = 0;
	
// Seed random number generator
	srand(time(NULL));

    // Place K bombs randomly
	for(i=0; i < K; i++)            
	{
		do
		{
		  luck = rand() % total;  // Random position
    	}while(mpla[luck] == 10); // Ensure no duplicate bomb positions
	    mpla[luck] = 10;    // Mark bomb
	   
    }
    printf("\n");		    
}


// Compute numbers for each cell based on surrounding bombs
void insertnumbers(int *mpla, int N, int M, int total, FILE *fp)
{

	int j, l, s, count=0, five, eight;

// j: position in array
    // l: current row
    // s: current column
	
	for(j=0, l=0, s=0; j<total; j++, s++, count=0)  
      {
         if(s==N)            // Reset column index when end of row is reached
    		s=0;

         // If not a bomb, count neighboring bombs
		 if(mpla[j]!= 10)
    	 {
            // Top-left corner
			if(s==0 && l==0)            
    		{
    			if(mpla[j+1]==10)
    			   count++;
    		    if(mpla[j+N]==10)
    			   count++;
    		    if(mpla[j+N+1]==10)
				   count++;   
			}
			else if(s==N-1 && l==0)     // Top-right corner
			     {
			     	if(mpla[j-1]==10)
    			       count++;
    			    if(mpla[j+N]==10)
    			       count++;
    			    if(mpla[j+N-1]==10)
					   count++;   
				 }
				 else if(s>0 && s<N-1 && l==0)      // Top row (excluding corners)
				      {
				 	      for(five=j-1;five<=j+N+1; five++)
				 	      {
				 		      if(five==j)
				 		        five=j+1;  // skip self
						      if(five==j+2)
				 		        five=j-1+N;
						      if(mpla[five]==10)
				 		        count++;
					      }
				      }
				      else if(s==0 && l==M-1)        // Bottom-left corner
				           {
				           	if(mpla[j+1]==10)
				           	count++;
				           	if(mpla[j-N]==10)
				           	count++;
				           	if(mpla[j-N+1]==10)
				           	count++;
						   }
						   else if(s==N-1 && l==M-1)     // Bottom-right corner          
						        {
						        	if(mpla[j-1]==10)
						        	count++;
						        	if(mpla[j-N]==10)
						        	count++;
						        	if(mpla[j-N-1]==10)
						        	count++;
								}
								else if(s>0 && s<(N-1) && l>0 && l<(M-1)) // General case (inner cells) up to 8 neighbors
								    {
									    for(eight=j-1-N;eight<=j+N+1; eight++)
									    {
									    	if(eight==j-N+2)
									    	eight=j-1;
									    	if(eight==j)
									    	eight=j+1;
									    	if(eight==j+2)
									    	eight=j+N-1;
									    	if(mpla[eight]==10)
									    	count++;
										}
								    }
								    else if(l==M-1 && s!=0 && s!=(N-1))   // Last row (excluding corners)
								         {
								            for(five=j-N-1; five<=j+1; five++)
				 	                        {
				 		                        if(five==j)
				 		                        five=j+1;
						                        if(five==j-N+2)
				 		                        five=j-1;
						                        if(mpla[five]==10)
				 		                        count++;
					                        }
										 }
										 else if(s==0 && l<M-1 && l>0)    // First column (excluding corners)
										      {
										      	for(five=j-N; five<=j+1+N; five++)
										      	{
										      		if(five==j+2-N)
										      		five=j+1;
										      		if(five==j+2)
										      		five=j+N;
										      		if(mpla[five]==10)
										      		count++;
												}
											  }
											  else if(s==N-1 && l>0 && l<(M-1)) // Last column (excluding corners)       
											       {
											       	   for(five=j-N-1; five<=j+N; five++)
											       	   {
											       	   	  if(five==j-N+1)
											       	   	  five=j-1;
											       	   	  if(five==j)
											       	   	  five=j+N-1;
											       	   	  if(mpla[five]==10)
											       	   	  count++;
													   }
											       }                                     
				
				                             mpla[j]= count;  // Assign bomb count to cell
		     }

// Print result to console and file
	        if(mpla[j]==10)
	        {
			  printf("* ");
	          fprintf(fp, "* ");
	        }
	        else
		    {
			  printf("%d ", mpla[j]);
			  fprintf(fp, "%d", mpla[j]);
            }

// End of row -> new line
			if(j==(l+1)*N-1)                                                 
		    {
		       printf("\n");
		       fprintf(fp, "\n");
			   l++;
		    }
	   }
}
    

























