#!/usr/bin/python
import os
import sys
import daemon

def do_stuff():
  print "Running as uid %d gid %d" % (os.getuid(), os.getgid())
  for f in os.listdir("."):
    print f

with daemon.DaemonContext(chroot_directory='/tmp/myroot',
                          umask=077,
                          detach_process=False,
                          uid=40001,
                          gid=40001,
                          stdin=sys.stdin,
                          stdout=sys.stdout,
                          stderr=sys.stderr):
  do_stuff()

