#include "Mesh.h"

using namespace std;


void Mesh::load( const char* filename )
{
	// 2.1.1. load() should populate bindVertices, currentVertices, and faces

	// Add your code here.

	  ifstream inFile;
	  inFile.open(filename);

	  string currentLine;

          while ( getline(inFile, currentLine) )
          {
              if (currentLine[0] == 'v' && currentLine[1] == ' ' )
              {
		 vector<string> testString;
                 string tempLine = currentLine.substr(2, currentLine.size());

 	      	 stringstream s(tempLine);
		 string temp;

		 while(getline(s, temp, ' ')){
			testString.push_back(temp);
		 }

		 Vector3f vertex( (float)atof(testString[0].c_str()),
		                  (float)atof(testString[1].c_str()),
		                  (float)atof(testString[2].c_str())
		                  );
		 bindVertices.push_back(vertex);
              }
		
	      if (currentLine[0] == 'f' && currentLine[1] == ' ')
              {

		 vector<string> testString;
		 vector<int> finalString;
                 
		 string tempLine = currentLine.substr(2, currentLine.size());

 	      	 stringstream s(tempLine);
		 string temp;

		 while(getline(s, temp, ' ')){
			testString.push_back(temp);
		 }

		 Tuple3u currentFace( (int)atof(testString[0].c_str()),
		                  (int)atof(testString[1].c_str()),
		                  (int)atof(testString[2].c_str())
		                  );
		 faces.push_back(currentFace);

	      }
	  }

	// make a copy of the bind vertices as the current vertices
	currentVertices = bindVertices;

}

//==========================================================
//EXTRA-CREDIT (Coloring of Joints)
//----------------------------------------------------------
//Given a color (joint#) from 0-16, produce a RGB value

Vector3f getRGBfromCGA(double *avgC){
	double cgaColor = *avgC;

	float red;
	float green;
	float blue;

	if (cgaColor == 0) 	{red = 0; green = 0; blue = 0;}		//Chest		   - Black
	else if (cgaColor == 1) {red = 0; green = 0; blue = 0.5;}	//Waist		   - Navy
	else if (cgaColor == 2) {red = 0; green = 0.5; blue = 0;}	//Neck		   - Green
	else if (cgaColor == 3) {red = 0; green = 0.5; blue = 0.5;}	//Right hip	   - Teal
	else if (cgaColor == 4) {red = 0.5; green = 0; blue = 0;}	//Right leg	   - Maroon
	else if (cgaColor == 5)	{red = 0.5; green = 0; blue = 0.5;}	//Right knee	   - Purple
	else if (cgaColor == 6) {red = 0.5; green = 0.5; blue = 0;}	//Right foot	   - Brown
	else if (cgaColor == 7) {red = 0.75; green = 0.75; blue = 0.75;}//Left hip	   - Silver
	else if (cgaColor == 8) {red = 0.5; green = 0.5; blue = 0.5;}	//Left leg	   - Gray
	else if (cgaColor == 9) {red = 0; green = 0; blue = 1;}		//Left knee	   - Blue
	else if (cgaColor == 10){red = 0; green = 1; blue = 0;}		//Left foot	   - Lime
	else if (cgaColor == 11){red = 0; green = 1; blue = 1;}		//Right collarbone - Aqua
	else if (cgaColor == 12){red = 1; green = 0; blue = 0;}		//Right shoulder   - Red
	else if (cgaColor == 13){red = 1; green = 0; blue = 1;}		//Right elbow	   - Fuchsia
	else if (cgaColor == 14){red = 1; green = 1; blue = 0;}		//Left collarbone  - Yellow
	else if (cgaColor == 15){red = 1; green = 1; blue = 0.5;}	//Left shoulder    - Faded Yellow
	else			{red = 1; green = 1; blue = 1;}	  //16	//Left elbow	   - White

	return Vector3f(red, green, blue);
}




void Mesh::draw()
{
	// Since these meshes don't have normals
	// be sure to generate a normal per triangle.
	// Notice that since we have per-triangle normals
	// rather than the analytical normals from
	// assignment 1, the appearance is "faceted".

	//==========================================================
	//EXTRA-CREDIT (Coloring of Joints)
	//----------------------------------------------------------
	//Enable Color Material.
	//Produce a vector of numbers ranging from 0-16 which is a
	//rounded weighted sum representing which of the 17 joints
	//does a vertex have the closest connection with.

	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

	vector<double> colorV;
	for (unsigned v=0; v<currentVertices.size(); v++)
        {
	    double sumC = 0.0;
	    for (int a = 0; a<attachments[v].size(); a++){
	        sumC = sumC + (double)(attachments[v][a]*(a+1));
	    }
	    colorV.push_back(floor(sumC+0.5)-1);    //produce 0-16 number

	}
	//==========================================================
		
	glBegin(GL_TRIANGLES);
        for (unsigned i=0; i<faces.size(); i++)
        {
	    
	    double c_1 = colorV.at(faces[i][0]-1);
	    double c_2 = colorV.at(faces[i][0]-1);
            double c_3 = colorV.at(faces[i][0]-1);

	    double* c1 = &c_1;		//Pass by Reference
	    double* c2 = &c_2;
	    double* c3 = &c_3;

	    Vector3f t1 = currentVertices[faces[i][0]-1];
	    Vector3f t2 = currentVertices[faces[i][1]-1];
            Vector3f t3 = currentVertices[faces[i][2]-1];

	    Vector3f v1 = t2-t1;
	    Vector3f v2 = t3-t1;

	    Vector3f n1 = Vector3f::cross(v1, v2);
	    n1 = n1.normalized();

	    glNormal3f(n1[0], n1[1], n1[2]);

	    //Generate colors and vertices
	    glColor3f(getRGBfromCGA(c1)[0], getRGBfromCGA(c1)[1], getRGBfromCGA(c1)[2]);
	    glVertex3f(t1[0], t1[1], t1[2]);
	    glColor3f(getRGBfromCGA(c3)[0], getRGBfromCGA(c3)[1], getRGBfromCGA(c3)[2]);
	    glVertex3f(t3[0], t3[1], t3[2]);
	    glColor3f(getRGBfromCGA(c2)[0], getRGBfromCGA(c2)[1], getRGBfromCGA(c2)[2]);
	    glVertex3f(t2[0], t2[1], t2[2]);

        }
        glEnd();

}

void Mesh::loadAttachments( const char* filename, int numJoints )
{
	// 2.2. Implement this method to load the per-vertex attachment weights
	// this method should update m_mesh.attachments
	
	ifstream inFile;
	inFile.open(filename);

	string line;
	while(getline(inFile, line)){

	    vector<float> attachString;

	    stringstream s(line);
	    string temp;
	    int count = 0;	

            while(getline(s, temp, ' ') && count < 17){
		count = count + 1;
		attachString.push_back((float)atof(temp.c_str()));
		
            }	    

	    attachments.push_back(attachString);
	}

}
