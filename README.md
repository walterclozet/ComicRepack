# ComicRepack
A simple tool to pack comic volumes for vol.moe site.
Put each chapter of a comic in a seperate folder, they will be packed in the order of folder name. the folder name will be set to the table of content. If the folder name begins with chapter_xxx_, the prefix will be ignored, where xxx means three digits.
In the main window chose the folder containing all volumes, set how many chapter to pack to one volume, set beginning chapter number. 
In some case each chapter may contain the same picture which is not needed, set Ignore first image will skip that file.
click pack to start, the result files will be in __res folder, two bat files will be created. you can modify vol-navpoint.txt if auto generated one is not good enough.
rarall.bat use winrar to compress each volmue, zipall.bat will use standalone zip tool to compress, so put zip.exe in any %PATH% folder before using that.
after zipping them, simple upload them to ftp, and use bath ftp upload, set prefix to vol_ and wait for a while.
For details, see the pdf file(in Chinese).
