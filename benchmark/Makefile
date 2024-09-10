all: open build notify

open: open.c Dockerfile.open
	podman build -t docker.io/haih/open -f Dockerfile.open .
	podman push docker.io/haih/open

build: Dockerfile.build
	podman build -t docker.io/haih/build -f Dockerfile.build .
	podman push docker.io/haih/build

notify: Dockerfile.notify
	podman build -t docker.io/haih/notify -f Dockerfile.notify .
	podman push docker.io/haih/notify
