# Basic setup

## Requirements

- kernel >= 5.9 (`uname -a`)
- runc >= 1.1.0 (`runc -v`)
- containerd >= 1.5.5 (`containerd -v`)
- libseccomp >= 2.5.2 (`apt list --installed | grep libseccomp`)

## Create K8s cluster with Kind

We need a K8s cluster that is fairly recent due to the runc and containerd
requirements. However, if we install K8s cluster from a fairly recent version
of `kind`, all the requirements should be satisfied.

To create a kind cluster
```
kind create cluster --config=configs/kind.conf
```

To delete a kind cluster
```
kind delete cluster
```

## Enable Seccomp default profile

Once the K8s cluster is up and running, run the following commands to test
seccomp profile associated with a running pod

```
kubectl run -it bash --image=bash --restart=Never bash
apk add curl
curl -LO k8s.work/amicontained
chmod +x amicontained
./amicontained
```

By default, K8s doesn't apply any seccomp profile to pods, so you might see
```
Seccomp: disabled
```

To turn on the default K8s seccomp profile for pods, we need supply additional
feature flags to the kubelet
```
kind create cluster --config=configs/kind-seccompdefault.conf
```

Now, when you run the above `amicontained` command, you will see the following
```
Seccomp: filtering
```

Note that we do not need to turn on the default Seccomp profile for our use
case.

# Custom seccomp profile

For our use case, we need to install and apply custom seccomp profiles.

## Install seccomp profiles

Seccomp profiles are just one or more json files container runtimes are expecting
to find at `/var/lib/kubelet/seccomp` directory. For now, we can just use `curl` or 
`docker cp` to place these json files to this location, i.e.:
```
docker cp profiles/ kind-worker:/var/lib/kubelet/seccomp
```

Note that `/var/lib/kubelet/seccomp` might not exist, in which case, we might need
to manually create that directory before running the `docker cp` command.

Once the seccomp profiles are installed, pods can be created specifying those installed profiles. An example is [audit-pod.yaml](../pods/audit-pod.yaml)
