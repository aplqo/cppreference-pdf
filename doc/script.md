# Tool scripts
Scripts in `script/` directory are used to create a tempatory developmant environment.

## Variables
Variables are set in var.sh.Template var.sh is [var_t.sh](../script/var_t.sh)

### project
**project**:The path to the source code.  
**tmp**:The tempatory directory to set up environment.  
**id**:Commnad to start ide.  
**tmp_remote**:tempatory remote for git  
### Pdf reader
Variables for opening pdf file on a remote device through ssh.If don't use remote device to open pdf file,don't set these variables.
**ip**:The ip of remote device that can open pdf file.  
**reader**:The reader path of the remote device.
### Html file
Variables for downloading html files.
**html_ip**:The ip of remote device to download html files.  
**html_dir**:The directory of html files.  
**html_file**:The file name of html archive.  
**html_download**:The command to download html file.  
### compiler select
**CC**:C compiler path  
**CXX**:c++ compiler path  
**PATH**:path variable  
### Ide start
**start_ide**: function to start ide.  

## Scripts
**copy.sh**:script for copy output pdf file to remote device  
**reset_\*.sh**:Reset item in environment.  
**set.sh**:script to set up a tempatory environment.  
**sync.sh**:Script to synchronism source between the environment and source  

## Directories
Directories in tempatory environment.
- remote: Git bare repo
- src: source code
- build: build result of source code
- output: pdf and log output
