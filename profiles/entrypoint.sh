#!/bin/sh

set -e

# Assume host machine's /var directory is mounted at /hostvar
mkdir -p /hostvar/lib/kubelet/seccomp/profiles/

cp /notify.json  /hostvar/lib/kubelet/seccomp/profiles/notify.json

echo "Installed seccomp profile"
