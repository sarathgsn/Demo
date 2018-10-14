

 int *array[10] ; /* = {0x1000,0x2000,0x3000}; */




fun()
{
int i;
for ( i = 0 ; i < 4; i++){
                printf("%s\n",array[i]);

}
}
int main()
{
	int i;
	char *arr = "hello";
	char *arr1 = "hai";
	char *arr2 = "how";
	char *arr3 = "ho";
	
	array[0] = arr;
	array[1] = arr1;
	array[2] = arr2;
	array[3] = arr3;
		 
	fun();
}


	
