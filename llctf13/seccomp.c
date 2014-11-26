/* Requires libseccomp: http://sourceforge.net/projects/libseccomp/ */
#include <seccomp.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>

void netserv(void);

int
main(int ac, char** av)
{
  // Actions: SCMP_ACT_ALLOW, SCMP_ACT_KILL, SCMP_ACT_TRAP,
  //          SCMP_ACT_TRACE(msgnum), SCMP_ACT_ERRNO(errno)
  scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_ERRNO(EPERM));
  assert(ctx != 0);

  assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0) >= 0);
  assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0) >= 0);
  assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0) >= 0);
  assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0) >= 0);
  assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(socket), 2,
                               SCMP_A0(SCMP_CMP_EQ, AF_INET),
                               SCMP_A1(SCMP_CMP_EQ, SOCK_STREAM)) >= 0);
  assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(setsockopt), 0) >= 0);
  assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(openat), 0) >= 0);
  assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(getdents), 0) >= 0);
  assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(bind), 0) >= 0);
  assert(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(listen), 0) >= 0);

  assert(seccomp_load(ctx) >= 0);

  netserv();
}
