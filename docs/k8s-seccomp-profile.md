# Requirements

- kernel >= 5.9 (`uname -a`)
- runc >= 1.1.0 (`runc -v`)
- containerd >= 1.5.5 (`containerd -v`)
- libseccomp >= 2.5.2

# Environment setup

We need a K8s cluster that is fairly recent due to the runc and containerd
requirements. However, if we install K8s cluster from a fairly recent version
of `kind`, all the requirements should be satisfied.

To create a kind cluster
```
kind create cluster --config configs/kind.conf
```

To delete a kind cluster
```
kind delete cluster
```

# Testing

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
kind create cluster --config configs/kind-seccompdefault.conf
```

Now, when you run the above `amicontained` command, you will see the following
```
Seccomp: filtering
```
