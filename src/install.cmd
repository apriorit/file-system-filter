sc create FsFilter type= filesys binPath= c:\FsFilter.sys
sc start FsFilter
pause
sc stop FsFilter
sc delete FsFilter
