README.txt
==========================================================================================
Author:		Andrew Moran	|
Date:		10/10/2012	|
6.837 Computer Graphics		|
Assignment 2			|
=================================
__________________________________________________________________________________________
Compiling Instructions
==========================================================================================
	When I completed the assignment, I managed to run Linux through my Macbook Pro laptop with a Virtual Machine called VirtualBox.  I also tested on the campus Athena computer to make sure that it worked correctly.  Here are instructions
	1.	Unzip submission on Stellar and extract all files to designated directory
	2.	In terminal, cd to directory containing "distrib" folder
	3.	command make
	4.	command ./a2 data/ModelX (X = 1,2,3, or 4)
	5.	EXTRA CREDIT: press 'c' when in mesh mode (drawSkeleton is 0)
		This toggles coloring of the vertices refering to a certain joint.
	6.	"distrib" folder contains all necessary files including updated 
		MatrixStack, SkeletalModel & Mesh cpp files, artifact bmp images, etc. 

__________________________________________________________________________________________
Collaboration
==========================================================================================
	TA help:
	
	Ray Gonzalez: He helped me understand the joint DAG tree and how to fix my rotation of joints when using the slider in the user interface.	

	Other than help from TAs at office hours, I got help from other students in the class:

	Rebecca Krosnick: After implementing SSD, Rebecca helped me conceptualize what bind pose and current pose matrices are and how to correctly represent them when going through my joint tree.  She also helped me catch my bug in my SSD implementation in which I was creating a new vertice from currentVertices instead of bindVertices.

__________________________________________________________________________________________
References
==========================================================================================
	⁃	6.837 Lecture Notes
	⁃	http://www.lighthouse3d.com/opengl/terrain/index.php3?normals
        -	graphics.ucsd.edu/courses/cse169_w05/
	-	en.wikipedia.org/wiki/Web_colors
	-	www.cplusplus.com/reference

__________________________________________________________________________________________
Problems
==========================================================================================
	Currently, my code is functioning properly.  I feel potential problems may arise from tryng to implement part of the extra credit.
	•	I changed ModelerView.cpp so you can now toggle Lighting with the key 'c' so you could see the colors of the joints when viewing the mesh
	•	I implemented coloring in Mesh.cpp, so hopefully no problems arise with gl and implementing color and enabling/disabling lighting.
	•	Any other problems were fixed with debugging

__________________________________________________________________________________________
Extra Credit
==========================================================================================
	Implemented coloring of the joints for the extra credit (difficulty: EASY).  As I read the attachments file, I created a weighted sum that produced a number ranging from one of the 17 joints (0-16) that a current vertice was most closely attached with.  In the Mesh.cpp file, I created a helper function that took in the color and prodiced the associated RGB value associated with the color name (similar to CGA to RBG conversion).  To notice the extra credit you need to be in the drawSkeleton is 0 phase.  Then you can toggle coloring by pressing 'c'.  The helper function in Mesh.cpp describes what colors goes with which joints.  It was tricky to get the lighting to work only when I wanted to.  It was also tedious to try and extract RGB values with a given joint number.  Something I found peculoar was that the chest area had many colors which I could not find out why.

__________________________________________________________________________________________
Comments
==========================================================================================
	I had fun with this assignment.  Since I started early, I was able to answer my questions at a reasonable time and get progress on the assignment fast.  I felt that I understood the assignment, however, debugging is what killed me.  Simple mistakes that could have been avioded wasted valuable time.  However, office hours was very helpful.  Something that I wish could have been re-iterated was the order in which matrices are multiplied.  I had trouble figuring out what order to push (especially rotations) onto the stack.  I mainly did guess and check.  Also, I had trouble figuring out that glNormal needed to be called before calling glVertex.  Again, I did guess and check.  Overall, this was a good assignment.

 
