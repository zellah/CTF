#include <unistd.h>
#include <assert.h>

void netserv(void);

static const int sandbox_gid = 60000;
static const int sandbox_uid = 60000;

int
main(int ac, char** av)
{
  assert(setresgid(sandbox_gid, sandbox_gid, sandbox_gid) >= 0);
  assert(setresuid(sandbox_uid, sandbox_uid, sandbox_uid) >= 0);
  netserv();
}
