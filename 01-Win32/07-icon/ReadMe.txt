1.compiling code
	cl.exe /c /EHsc 07-Icon.cpp

2.compiling resource(.rc=> resource script) file using (resource compiler)
	rc.exe Resource.rc

3.linking obj file of cpp code and linking res file of .rc file 
	link.exe 07-Icon.obj Resource.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS