When using newer version of SPIRE, where workload entry is added by the controller manager dyanmically, seccomp agent will fail.
A workaround to this problem is to statically creating workload entries, e.g.,

```
kubectl -n spire-server exec -it spire-server-0 -- spire-server entry create -spiffeID spiffe://spire-lifecycle-hook.ibm.com/ns/default/sa/default -parentID  spiffe://spire-lifecycle-hook.ibm.com/spire/agent/k8s_psat/spire-lifecycle-hook/226f3559-ffc0-45fb-bc5c-23d8e82c2a04 -selector k8s:ns:default -selector k8s:sa:default
```
