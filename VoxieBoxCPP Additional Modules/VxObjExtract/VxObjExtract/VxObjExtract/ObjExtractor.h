#pragma once

#include "../../../../Headers and DLLs/vxCpp.h"
#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>

/*
 * A program to report the findings of an OBJ file can work with Voxon software or stand alone 
 *
 *
 */

class ObjExtractor  
{
public:

	ObjExtractor();
	ObjExtractor(const char* fileName);
	~ObjExtractor();

	bool reInit();
	const char* getFileName();
	bool extractModel(const char* fileName);

	double getScalar();
	point3d getModelCentre();

	int getNoVertices();

	bool calculateVXExtents(IVoxieBox* voxiePtr, int flagsValue);



	int getNoVertcies();

	int getNoIndices();

	std::vector<poltex_t> getVerticeArray();

	std::vector<poltex_t> getIndiceArray();

	extents_t getVXExtents();

	void getPointOffset(point3d pos, point3d* offsetPos);


	void calcVerticesMaxMin();
	void calcCentre();
	void calcScalar();

	void scale(double value, bool updateVX = false);


	void setModelCentre(point3d newValues);
	void setScalar(double newValue);


	bool setAllVerticeCol(int newCol);

	bool isSuccessfullyExtracted();

	// VX1 style mesh

	bool convertToVXMesh();
	bool convertToVXPoltex();

	poltex_t* getVXPoltex();
	int* getVXMesh();
	int getPoltexNo();
	int getMeshNo();




private:

	typedef struct uvPoint { float u, v; } uvPoint_t;
	typedef struct indice { int verticeIndex, vtIndex, vnIndex; } indice_t;

	static const int MAX_VERTICES = 1000;
	static const int MAX_INDICES = 5000;


	int debug = 0;
	std::vector<uvPoint_t>		uvArray; 
	std::vector<poltex_t>		verticeArray;
	std::vector<indice_t>			indiceArray;
	std::vector<int>			VxVerticeIndexArray; // use for VX drawing
	std::vector<int>			rawVerticeIndexArray;
	std::vector<int>			rawUVIndexArray;
	std::vector<int>			rawNormsIndexArray;

	poltex_t vxPoltex[MAX_VERTICES] = { 0 };
	int vxMesh[MAX_INDICES] = { 0 };
	int poltexNo;
	int meshNo;


	std::vector<std::string>	MaterailsName;
	std::vector<std::string>	objectName;
	extents_t					modelVXExtents = { 0 };
	double						scalar = 0;
	char fileName[MAX_PATH] = "";
	point3d modelCentre = { 0,0,0 };
	point3d maxVertices = { FLT_MIN, FLT_MIN, FLT_MIN };
	point3d minVertices = { FLT_MAX,FLT_MAX,FLT_MAX };

	bool successfullyExtracted = false;


};