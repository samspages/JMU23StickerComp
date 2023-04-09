# JMU23StickerCode
A small C program, and python script used as part of a sticker design competition for the JMU CS Department.

Inspired by "Donut Math" by Andy Sloane (https://www.a1k0n.net/2011/07/20/donut-math.html) and that bouncing DVD logo from old VHS players, I decided to shape my idea around the logo itself being a fun demonstration of applied computer science. The C program "jamoo.c" renders a 72 by 18 border of ascii characters, and a 3d rendered ASCII text of the JMU logo bouncing around the box. Below is a 4 second example in the form of a GIF of a bandicam recording. 

# Example
![](https://github.com/Your_Repository_Name/jmoo.gif)

The C program is designed to run on both windows and UNIX systems though the usleep, which isn't a C standard, function seemed to have a different timing on windows so don't be surprised if it seems a little faster or slower than the example. You can compile and execute the source with a compiler like GNU gcc or the minGW collection.
The python utility script removes all whitespace from the passed file and creates a new file with all the characters squished together in lines of up to 80 characters.
I then spent an hour moving around characters into the shape of JMU letters. Originally I was going to write a script for that too but time-management got the best of me. I really like the idea of an interactive logo for the JMU CS department but currently this project is far from clean and interactive. The logo text is off centered because I made the U too wide and I was too lazy to fix it, and character widths are inconsistent. Contact me at pagesh@dukes.jmu.edu or samuel.page82@gmail.com for questions.

Thanks.
