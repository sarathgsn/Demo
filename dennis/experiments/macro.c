

#ifdef WARNING
#define WARNING()  do {                                         \
                if ((1 & 1) &&                  \
                        ( 2& 2)) {              \
                }                                                               \
        } while(0);
#else 
#define  WARNING()  qpqppq
#endif
int main()
{
	WARNING();
}

