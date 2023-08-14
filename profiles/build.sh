#!/bin/bash

docker build -t haih/seccomp-profile-installer .
docker push haih/seccomp-profile-installer
