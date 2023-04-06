# Setup

## Kinvolk seccompagent

Kinvolk folks created a prototype
[seccompagent](https://github.com/kinvolk/seccompagent) that makes use of
seccomp notification. This work is mostly based on theirs.

The source is here
```
git clone https://github.com/kinvolk/seccompagent.git
cd seccompagent
```

To install the seccompagent
```
kubectl apply -f deploy/seccompagent.yaml
```

Place notify.json to the worker node
```
docker cp profiles/notify.json kind-worker:/var/lib/kubelet/seccomp/profiles
```

Start a pod that makes use of that seccomp profile
```
kubectl apply -f pods/notify-pod.yaml
```

To try if this work
```
kubectl exec -it mynotifypod sh
mkdir abc
ls
```

and you should see something like the following
```
drwxr-xr-x    2 root     root          4096 Apr  6 17:35 abc-default-mynotifypod-container1
```

The name of the directory was created using a template from notify.json here:
```
"listenerMetadata": "MKDIR_TMPL=-{{.Namespace}}-{{.Pod}}-{{.Container}}"
```

This demonstrates that the mkdir() syscall was captured by seccomp, the
seccompagent was infored of the syscall and its context via a Unix domain
socket, and was able to nsenter into the pod filesystem namespace to create a
new directory with the templated name.
