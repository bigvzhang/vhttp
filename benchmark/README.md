# Compare The Performances of Beast, NodeJS and  Apache
## Setup Http Servers
### Beast, based on advanced_server example
You can use the example of best to test or use the vhttp.
### NodeJS
Please setup according document at https://github.com/bigvzhang/vhttp/tree/master/src_ndjs
### Apache Http Server
Please refence apache http document. For windows, apache on cygwin is recommended to use.
## Tools
- curl
- cygwin for windows

## Test
- modify file related variables in benchmark.sh
- create media file
``` bash
./benchmark.sh create
```
- test the download performances
``` bash
./benchmark.sh
```
