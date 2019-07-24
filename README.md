# cppreference-pdf
Generate pdf from cppreference

## usage
```
doc source outfile
```
**source**:first html   
**outfile**:output html path   

## build
### Require
**C++ standard**:c++17    
**Libraries**:  
- [gumbo-query](https://github.com/lazytiger/gumbo-query) (That requires [gumbo-parser](https://github.com/google/gumbo-parser))  
- [wkhtmltox](https://github.com/wkhtmltopdf/wkhtmltopdf)  
**Note**:gumbo-query and this executable must link to the same c++ standard library.  
### build command
``` shell
mkdir build   
cd build   
cmake ../cppreference-pdf .   
make   
```
