#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

void netserv(void);

static const int sandbox_gid = 60000;
static const int sandbox_uid = 60000;

int
main(int ac, char** av)
{
  if (mkdir("/tmp/myroot", 0777) < 0)
    assert(errno == EEXIST);
  assert(chown("/tmp/myroot", sandbox_uid, sandbox_gid) >= 0);
  assert(chroot("/tmp/myroot") >= 0);

  assert(setresgid(sandbox_gid, sandbox_gid, sandbox_gid) >= 0);
  assert(setresuid(sandbox_uid, sandbox_uid, sandbox_uid) >= 0);

  netserv();
}
