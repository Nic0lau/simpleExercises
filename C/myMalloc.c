/* Implementation of a simple memory allocator */

#include <limits.h>
#include <string.h>
#include <unistd.h>

#define MIN_ALLOC_UNITS 1024

typedef union header {
	struct {
		union	header *p;
		int	unsigned size;
	} s;
	long align;
} Header;

void freeMem(void *p);
Header *memRequest(unsigned long n);
void *alloc(unsigned long n);
void *allocZero(unsigned short n, unsigned long size);
void bfree(void *p, unsigned long n);

static Header root;
static Header *freep = NULL;

void
freeMem(void *p)
{
	Header *bp, *ptr;
	
	if (p == NULL)
		return;
	
	bp = (Header *) p - 1;
	
	if (bp->s.size == 0)
		return;
	
	for (ptr = freep;!(bp > ptr && bp < ptr->s.p);ptr = ptr->s.p)
		if (ptr >= ptr->s.p && (bp > ptr || bp < ptr->s.p))
			break;

	if (bp + bp->s.size == ptr->s.p) {
		bp->s.size += ptr->s.p->s.size;
		bp->s.p = ptr->s.p->s.p;
	} else {
		bp->s.p = ptr->s.p;	
	}

	if (ptr + ptr->s.size == bp) {
		ptr->s.size += bp->s.size;
		ptr->s.p = bp->s.p;
	} else {
		ptr->s.p = bp;	
	}

	freep = ptr;
}

Header *
memRequest(unsigned long n)
{
	char *compare;
	Header *p;
	
	if (n < MIN_ALLOC_UNITS)
		n = MIN_ALLOC_UNITS;

	compare = sbrk(n * sizeof(Header));
	
	if (compare == (char *) -1)
		return NULL;
	
	p = (Header *) compare;
	p->s.size = n;
	freeMem((void *) (p + 1));

	return freep;
}

void *
alloc(unsigned long n)
{
	Header *p, *previous;
	unsigned long numUnits;
	
	if (n == 0 || n > ULONG_MAX - sizeof(Header))
		return NULL;
	
	numUnits = (n + sizeof(Header) - 1) / sizeof(Header) + 1;
	
	if ((previous = freep) == NULL) {
		root.s.p = freep = previous = &root;
		root.s.size = 0;
	}
	
	for (p = previous->s.p;;previous = p, p = p->s.p) {
		if (p->s.size >= numUnits) {
			if (p->s.size == numUnits) {
				previous->s.p = p->s.p;
			} else {
				p->s.size -= numUnits;
				p += p->s.size;
				p->s.size = numUnits;
			}
			
			freep = previous;
			return (void *)(p + 1);
		}

		if (p == freep)
			if ((p = memRequest(numUnits)) == NULL)
				return NULL;
	}
}

void *
allocZero(unsigned short n, unsigned long size)
{
	Header *p = alloc(n * size);
	
	if (p != NULL)
		memset(p, 0, n * size);
	
	return p;	
}

void
bfree(void *p, unsigned long n)
{
	if (p == NULL || n < sizeof(Header))
		return;
	
	Header *bp = (Header *) p;
	bp->s.size = (n / sizeof(Header)) - 1;
	
	freeMem((void *)(bp + 1));
}

int
main()
{
	return 0;
}
