TIMViewer Short and Basic ReadMe

This program was made for Windows and requires only about 7-8+ megs of memory (depending on how big the image you want to load/convert is).

Features

It can Open TIM and BMP files. Can convert single or multiple file from tim->bmp and vice versa. It can also scroll through multiple CLUTs and can view/edit the current CLUT.
The best feature in it though is that it can scan, extract, and insert tim files back into a file (not the cdimage; For a cd image you must extract the raw files from it, then use this program on the raw files and, once done, re-insert the raw files back into the cd image).

Menus Explained

Open TIM	
Open BMP		Opens a TIM/BMP file for viewing

Scan Raw File		Scans a File for a TIM header

Save TIM File		Will save the Image as a TIM regardless
			of whether it was originally BMP or TIM
Save Multiple Files	Saves Multiple TIM files found during a
			scan and will create a script that can be
			used to reinsert		
Insert TIM Files	Inserts a bunch of TIM files back into a
			Raw File using a script made when the files
			were extracted

Close Image/File	Closes the current Image/File loaded

Split Image		It cuts the image in half and merges both
			halves together

Transparency		Allows to show transparency in the image.

0.5x, 1.0x, 1.5x, 2.0x	Allows you to resize the current image to
			the selected ratio

Copy			Allows you to copy the image into memory
			so it can be pasted into other graphic programs
			(not recommended for converting to bmp and
			then back to tim)

View CLUT		Displays the current CLUT (double click
			a CLUT to change it)

Convert to BMP		Will save the Image as a BMP regardless
			of whether it was originally BMP or TIM

24bpp->16bpp		Converts the current TIM from 24bpp to 16.
16bpp->24bpp		Converts the current TIM from 16bpp to 24.
			(Warning: invisible pixels is lost)

TIM to BMP
BMP to TIM		Converts all the files in a directory to
			its other type

Warnings

1) You can't scan the CD Image. It has extra data that prevents the picture from displaying right. Instead extract a file from the CD and scan it.


Notes

The program now saves all the extra info in the tim to an extra file when you convert it to a bmp. This file has the exact same file name as the bmp file but with a new extension (tmext). When you want to convert the bmp back to a tim, this new file must be in the same dir as the bmp and must be using the same file name (except for the extension).


Thats it for the short readme.

Made by rveach