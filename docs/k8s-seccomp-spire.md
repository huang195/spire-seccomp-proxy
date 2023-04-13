# Set up the environment

## Spire

Follow the [quickstart
guide](https://spiffe.io/docs/latest/try/getting-started-k8s/) to instantiate
spire agent and spire server in a k8s cluster. In the step to register an ID for the workload,
modify the namespace and service account to be `seccomp-agent` to match that of our seccomp-agent.

## Seccomp agent

First deploy notify.json to the worker nodes, i.e., `docker cp`.

We can then deploy our seccomp agent
```
kubectl apply -f deploy/seccompagent.yaml
```

