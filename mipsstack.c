void fun_last()
{
        int x = 100;
        int u = 200;
        int z = x + u;
        int xx = 100;
        int a = 1000;
        int c = 100;
        int zz = 0000;
        int mm = 100000;
        char ac[100] = "hai hello world";
        int aaa = 10;
}

void hai_fun(int p, int q, int r , int s, int t , int u)
{
/*        int x = 100;
        int u = 200;
        int z = x + u;
        int xx = 100;
        int a = 1000;
        int c = 100;
        int zz = 0000;
        int mm = 100000;
        char ac[100] = "hai hello world";
        int aaa = 10;
	fun_last(10,122,33,44,55,66,77);
	return aaa;  */

        int x = 100;
        int a = 1000;
        int c = 100;
        int z = 0000;
        int mm = 100000;
	mm = z || c && a ;
    //    char ac[100] = "hai hello world";
     //   c = c + a + x -z ;
        fun_last(x, a, c, mm,x+15, a+15);
      //  diag_printf(" in fun1 \n");
}

void demofun()   //(int p, int q, int r, int s, int t , int u)
{
        /*int x = 100;
        int a = 1000;
        int c = 100;
        int z = 0000;
        int mm = 100000;
        char ac[100] = "hai hello world";
        int aaa = 10; */
        int x = 5;
        int a = 6;
        int c = 7;
        int z = 8;
        int mm = 9;
        mm = z || c && a ;
        char ac[100] = "hai hello world";
       c = c + a + x -z ;
        hai_fun(x, a, c, mm,x+15, a+15);
        printf(" in fun1 \n");
       // hai_fun(x, z, c , mm, aaa, z+100, a+100);
}




void fun1()
{
/*        int x = 5;
        int a = 6;
        int c = 7;
        int z = 8;
        int mm = 9;
        mm = z || c && a ;
        char ac[100] = "hai hello world";
        c = c + a + x -z ;
        demofun(x, a, c, mm,x+15, a+15);
        diag_printf(" in fun1 \n");
*/
    demofun();

}





int main()
{
fun1();
}











