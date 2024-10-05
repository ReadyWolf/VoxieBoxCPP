#include "ObjExtractor.h"
ObjExtractor::ObjExtractor()
{
}

ObjExtractor::ObjExtractor(const char* fileName)
{
	extractModel(fileName);
}

ObjExtractor::~ObjExtractor()
{
}

bool ObjExtractor::reInit()
{
	if (this->fileName == "" || this->fileName == NULL) return false;


}

const char* ObjExtractor::getFileName()
{
	return this->fileName;
}

bool ObjExtractor::extractModel(const char* fileName)
{

	strcpy_s(this->fileName, fileName);
	
	std::string currentLine;
	std::ifstream myFile(this->fileName);

	std::string tempString = " ";
	std::smatch matchArray;
	std::regex materailExpression("mtllib (.*)");
	std::regex objectExpression("o (.*)");   //  object Names
	std::regex verticeExpression("v (.*) (.*) (.*)");					// 
	std::regex verticeNormalsExpression("vn (.*) (.*) (.*)");									// lighting not needed for VX rendering
	std::regex indicesExpression("f (.*?)/(.*?)/(.*?) (.*?)/(.*?)/(.*?) (.*?)/(.*?)/(.*?)");   // triangles or polys 
	std::regex uvExpression("vt (.*) (.*)");

	poltex_t poltextData = { 0 } ;
	uvPoint_t uvpoint = { 0 };
	indice_t indice = { 0 };

	if (myFile.is_open())
	{
		/* Obj file consists of a link to a  Mtl files - materials
		   *
		   *  o = name of object
		   *  v = vertices
		   *  vn = vertices normals (lighting)
		   *
		   *  f = indices (vertces for making a triangle  format: f vertice index / uv index / normal index SPACE * 3 or more depending on shape triangle or polys
		   *  l = ?
		   *  vt = texture mapping
		   *
		   *
		   *  TODO make UV index
		   *
		   */
		   //
		   // get vertices 

		while (getline(myFile, currentLine))
		{

			if (currentLine[0] == 'o' && currentLine[1] == ' ') {

				//	std::regex_search(currentLine, matchArray, objectExpression);

				if (debug) std::cout << "object name:" << matchArray[1]; // print out the data

				tempString = matchArray[1];
				objectName.push_back(tempString);

			}


			if (currentLine[0] == 'v' && currentLine[1] == ' ') {

				std::regex_search(currentLine, matchArray, verticeExpression);

				if (!matchArray.empty()) {
					if (debug)	std::cout << "vertice: (" << matchArray[1] << "," << matchArray[2] << "," << matchArray[3] << ")"; // print out the data
					 // write code to store the data here if need be 
					 // 
					// for VX go to poltex x,y,z later amend with uv data based from vt cords from the ob 

					tempString = matchArray[1];
					poltextData.x = strtof(tempString.c_str(), NULL);
					tempString = matchArray[2];
					poltextData.y = strtof(tempString.c_str(), NULL);
					tempString = matchArray[3];
					poltextData.z = strtof(tempString.c_str(), NULL);

					verticeArray.push_back(poltextData);
					if (debug)std::cout << std::endl;

				}

			}


			if (currentLine[0] == 'v' && currentLine[1] == 't' && currentLine[2] == ' ') {

				std::regex_search(currentLine, matchArray, uvExpression);

				if (!matchArray.empty()) {
					if (debug)	std::cout << "uv (vt): (" << matchArray[1] << "," << matchArray[2] << ")"; // print out the data

					tempString = matchArray[1];
					uvpoint.u = strtof(tempString.c_str(), NULL);
					tempString = matchArray[2];
					uvpoint.v = strtof(tempString.c_str(), NULL);

					uvArray.push_back(uvpoint);
					if (debug)std::cout << std::endl;
				}

			}

			// get triangles / polys - always indexes
			if (currentLine[0] == 'f' && currentLine[1] == ' ') {
				// cout << currentLine << '\n';

				  // matchArray gets filled with temporary line data if it matches the verticeExpression defined above... 
				std::regex_search(currentLine, matchArray, indicesExpression);

				if (!matchArray.empty()) {

					// 1 is vertice index 2 is vt index 3 is normal index 
					if (debug) {
						std::cout << matchArray[1] << "/" << matchArray[2] << "/" << matchArray[3] << "-1"; // print out the data
						std::cout << matchArray[4] << "/" << matchArray[5] << "/" << matchArray[6] << "-1"; // print out the data
						std::cout << matchArray[7] << "/" << matchArray[8] << "/" << matchArray[9] << "-1"; // print out the data
					}
					 // write code to store the data here if need be 
					// for for VX shapes just grab the vertice index go to int array   "matchArray[1] , matchArray[4], matchArray[7], -1" 


					// CHECK IF A MODEL IS MISSING NUMBERS

					tempString = matchArray[1];
					indice.verticeIndex = stoi(tempString);
					tempString = matchArray[2];
					indice.vtIndex = stoi(tempString);
					tempString = matchArray[3];
					indice.vnIndex = stoi(tempString);

					indiceArray.push_back(indice);
				

					tempString = matchArray[4];
					indice.verticeIndex = stoi(tempString);
					tempString = matchArray[5];
					indice.vtIndex = stoi(tempString);
					tempString = matchArray[6];
					indice.vnIndex = stoi(tempString);

					indiceArray.push_back(indice);


					tempString = matchArray[7];
					indice.verticeIndex = stoi(tempString);
					tempString = matchArray[8];
					indice.vtIndex = stoi(tempString);
					tempString = matchArray[9]; // weird bug
				//	indice.vnIndex = stoi(tempString); //TO DO FIX 

					indiceArray.push_back(indice);

					std::cout << std::endl;
				}

			}

		}
		myFile.close();


		// put the UV data into the verticeArray by using the indice array 

		// 1st vertice is always at 1 not 0

		void calcVerticesMaxMin();
		void calcCentre();
		void calcScalar();

		successfullyExtracted = true;
		
	}
	else  	successfullyExtracted = false;
	
	return successfullyExtracted;

}



double ObjExtractor::getScalar()
{
	return this->scalar;
}

point3d ObjExtractor::getModelCentre()
{
	return this->modelCentre;
}

int ObjExtractor::getNoVertices()
{
	return verticeArray.size();
}

// fills out the info for Voxons 
bool ObjExtractor::calculateVXExtents(IVoxieBox* voxiePtr, int flagsValue)
{

	if (fileName == "") return false;

	voxiePtr->drawModelGetExtents(this->fileName, &this->modelVXExtents, flagsValue);

		return true;
}

bool ObjExtractor::convertToVXMesh() {
	int i = 0;
	bool result = false;
	int j = 0;
	int entryNo = 0;
	for (i = 0; i < MAX_INDICES; i++) {

		if (i > indiceArray.size() - 1  || j > MAX_INDICES - 1)
		{
			result = true;
			break;

		}

		if (entryNo >= 3) {
			vxMesh[j] = -1;
			j++;
			entryNo = 0;
		}


		vxMesh[j] = indiceArray[i].verticeIndex - 1;
		j++;
		entryNo++;


	}

	if (result) {

		vxMesh[j] = -1;
		j++;
		meshNo = j;
	}


	return result;
}

bool ObjExtractor::convertToVXPoltex()
{
	int i = 0;
	bool result = false;

	for (i = 0; i < MAX_VERTICES; i++) {

		if (i > verticeArray.size() - 1) {
			result = true;
			break;
		}

		vxPoltex[i].x = verticeArray[i].x;
		vxPoltex[i].z = -verticeArray[i].y;
		vxPoltex[i].y = verticeArray[i].z;

		vxPoltex[i].col = verticeArray[i].col;
		vxPoltex[i].u = verticeArray[i].u;
		vxPoltex[i].v = verticeArray[i].v;

	}

	if (result) {
		poltexNo = i;
	}

	return result;


}

poltex_t* ObjExtractor::getVXPoltex()
{
return 	vxPoltex;
}

int* ObjExtractor::getVXMesh()
{
return	vxMesh;
}

int ObjExtractor::getPoltexNo()
{
	return poltexNo;
}

int ObjExtractor::getMeshNo()
{
	return meshNo;
}

int ObjExtractor::getNoVertcies()
{
	return this->verticeArray.size();
}

int ObjExtractor::getNoIndices()
{
	return this->indiceArray.size();
}

void ObjExtractor::getPointOffset(point3d pos, point3d* offsetPos)
{
	if (scalar == 0) return;

		offsetPos->x = (pos.x - (float)modelCentre.x) * (float)scalar;
		offsetPos->y = (pos.y - (float)modelCentre.y) * (float)scalar;
		offsetPos->z = (pos.z - (float)modelCentre.z) * (float)scalar;

	

//		(position - self.center)* self.scalar


}

void ObjExtractor::calcVerticesMaxMin()
{
	maxVertices.x = FLT_MIN;
	maxVertices.y = FLT_MIN;
	maxVertices.z = FLT_MIN;

	minVertices.x = FLT_MAX;
	minVertices.y = FLT_MAX;
	minVertices.z = FLT_MAX;

	std::vector<poltex_t>::iterator i;

	for (i = verticeArray.begin(); i != verticeArray.end(); ++i) {

		if (i->x > maxVertices.x) maxVertices.x = i->x;
		if (i->y > maxVertices.y) maxVertices.y = i->y;
		if (i->z > maxVertices.z) maxVertices.z = i->z;

		if (i->x < minVertices.x) minVertices.x = i->x;
		if (i->y < minVertices.y) minVertices.y = i->y;
		if (i->z < minVertices.z) minVertices.z = i->z;


	}

}



void ObjExtractor::calcCentre()
{
	modelCentre.x = ((maxVertices.x + minVertices.x)) * .5;
	modelCentre.y = ((maxVertices.y + minVertices.y)) * .5;
	modelCentre.z = ((maxVertices.z + minVertices.z)) * .5;


}

void ObjExtractor::calcScalar()
{
	this->scalar = 1 / ((maxVertices.x - modelCentre.x) * 2);
}

void ObjExtractor::scale(double value, bool updateVX)
{
	int i = 0;

	for (i = 0; i < this->verticeArray.size(); i++) {

		verticeArray[i].x *= value;
		verticeArray[i].y *= value;
		verticeArray[i].z *= value;

	}

	if (updateVX) this->convertToVXPoltex();
}



void ObjExtractor::setModelCentre(point3d newValues)
{
	modelCentre.x = newValues.x;
	modelCentre.y = newValues.y;
	modelCentre.z = newValues.z;

}

void ObjExtractor::setScalar(double newValue)
{
	scalar = newValue;
}

bool ObjExtractor::setAllVerticeCol(int newCol)
{
	int i = 0;

	for (i = 0; i < verticeArray.size(); i++) {

		verticeArray[i].col = newCol;

	}

	return true;
}

bool ObjExtractor::isSuccessfullyExtracted()
{
	return successfullyExtracted;
}
