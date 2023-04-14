# Set up the environment

## K8s cluster

Clone the repo first
```
git clone git@github.com:huang195/spire-seccomp-proxy.git
cd spire-seccomp-proxy
```

Create a Kind cluster
```
kind create cluster --config=configs/kind-seccompdefault.conf
```

## Spire

Follow the [quickstart
guide](https://spiffe.io/docs/latest/try/getting-started-k8s/) to instantiate
spire agent and spire server in a k8s cluster.

First clone this repo
```
git@github.com:spiffe/spire-tutorials.git
cd spire-tutorials/k8s/quickstart
```

To start spire server
```
kubectl apply -f spire-namespace.yaml
kubectl apply \
    -f server-account.yaml \
    -f spire-bundle-configmap.yaml \
    -f server-cluster-role.yaml
kubectl apply \
    -f server-configmap.yaml \
    -f server-statefulset.yaml \
    -f server-service.yaml
```

To start spire agent
```
kubectl apply \
    -f agent-account.yaml \
    -f agent-cluster-role.yaml
kubectl apply \
    -f agent-configmap.yaml \
    -f agent-daemonset.yaml
```

To register the agent node
```
kubectl exec -n spire spire-server-0 -- \
    /opt/spire/bin/spire-server entry create \
    -spiffeID spiffe://example.org/ns/spire/sa/spire-agent \
    -selector k8s_sat:cluster:demo-cluster \
    -selector k8s_sat:agent_ns:spire \
    -selector k8s_sat:agent_sa:spire-agent \
    -node
```

Finally, to register the workload
```
kubectl exec -n spire spire-server-0 -- \
    /opt/spire/bin/spire-server entry create \
    -spiffeID spiffe://example.org/ns/default/sa/default \
    -parentID spiffe://example.org/ns/spire/sa/spire-agent \
    -selector k8s:ns:default \
    -selector k8s:sa:default
```

## Setting up seccomp agent

Now, let's go back to our `spire-seccomp-proxy` repo so we can deploy notify.json
to all the worker nodes, i.e., 
```
docker exec kind-worker mkdir -p /var/lib/kubelet/seccomp/profiles/
docker cp profiles/notify.json kind-worker:/var/lib/kubelet/seccomp/profiles/
```

We can then deploy our seccomp agent
```
kubectl apply -f deploy/seccompagent.yaml
```

