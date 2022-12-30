QUESTION Production binaries are release of an application by company X from time to time.

Now the binaries follow transitive properties, which means if v1 is compatible with v2 and v2 is compatible with v3. v1 and v3 are also compatible.

You are given signature of two APIs, which are required to be developed.

```void addVersion(version,isCompatible)```
    - API takes input of binary version in version, and if this binary is compatible with immediate previous version.

    e.g., addVersion(2,true)  -> version v2 is compatible with v1
          addVersion(3,false) -> version v3 is not compatible with v2
    
    - This API is used by company X

```bool isCompatible(srcVer,targetVer)```
    - API provides checking of a source version ( INT srcVer) is compatible with a target version (INT target version).

    e.g., isCompatible(2,1) -> true : version 1 & 2 are compatible
          isCompatible(2,3) -> false: version 2 & 3 are not compatible

Complete the API for the same.

QUESTION: Extended question:

There are few legacy binaries which are added to compatibility, 
so you need to make another API 

void makeCompatible(srcVer,tarVer)

in which one makes a certain source version (srcVer) compatible with target version ( tarVer )