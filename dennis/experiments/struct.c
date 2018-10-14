

struct ns16550 {
        unsigned int rbr;          /* 0 */
        unsigned int ier;          /* 1 */
        unsigned int fcr;          /* 2 */
        unsigned int lcr;          /* 3 */
        unsigned int mcr;          /* 4 */
        unsigned int lsr;          /* 5 */
        unsigned int msr;          /* 6 */
        unsigned int spr;          /* 7 */
        unsigned int mdr1;         /* 8 */
        unsigned int reg9;         /* 9 */
        unsigned int regA;         /* A */
        unsigned int regB;         /* B */
        unsigned int regC;         /* C */
        unsigned int regD;         /* D */
        unsigned int regE;         /* E */
        unsigned int uasr;         /* F */
        unsigned int scr;          /* 10*/
        unsigned int ssr;          /* 11*/
        unsigned int reg12;        /* 12*/
        unsigned int osc_12m_sel;  /* 13*/
};



int main()
{
	struct hello;
	printf("%d\n"hello
	struct ns16550 *p = (struct ns16550 *)malloc(sizeof(struct ns16550));
	printf("%p\n",p);
	printf("%p\n",&p->rbr);
	printf("%p\n",&p->lcr);
//	printf("%p\n",p);
}
	
