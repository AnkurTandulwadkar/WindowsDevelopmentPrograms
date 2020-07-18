1.it will not work if linker is not linked properly.(here it gets compiled and linked if it works)
	cl.exe /EHsc sourcefile.cpp



2.It will work in any condition whether linker is linked properly or not.

	cl.exe /c /EHsc sourcefile.cpp (to compile)
	
	link.exe sourcefile.cpp user32.lib gdi32.lib /SUBSYSTEM:WINDOWS (to link)


3.If you want to do 1st option and linker is not linked properly.

	cl.exe /EHsc 06-ByCmd.cpp /link user32.lib gdi32.lib



