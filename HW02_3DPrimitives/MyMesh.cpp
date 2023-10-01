#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// This code was based off of the circle exercise,
	// before I moved on to a different method for the rest of the shapes.

	#pragma region "Build Cone"
	// - CIRCLE EXERCISE - GENERATE VERTICES - 
	
	// List of vertices
	std::vector<vector3 > vertex;
	// Current fraction value
	float theta = 0;
	// Fraction value to increment by
	float fractionValue = (2.0 * PI) / a_nSubdivisions;

	// Loop used to set up vertices
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// Create the vector based off the circle
		vector3 temp = vector3(cos(theta) * a_fRadius, 0.0f, sin(theta) * a_fRadius);
		// and change the theta value by the incremental value
		theta += fractionValue;
		vertex.push_back(temp);
	}

	// Loop used to draw cone
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// Add the trianges that form the point of the cone
		// In order to have the cone be the proper height, change the y value to the height (divided by 2)
		AddTri(vector3(0, a_fHeight/2 , 0), vertex[i], vertex[(i + 1) % a_nSubdivisions]);

		// Add the circle on the bottom of the cone
		AddTri(ZERO_V3, vertex[(i + 1) % a_nSubdivisions], vertex[i]);

		//AddTri(vector3(a_fRadius - halfOfRadius, a_fHeight / 2, i), vector3(a_fRadius + halfOfRadius, a_fHeight / 2, i), vector3(a_fRadius / 2, a_fHeight, i));	
	}
	#pragma endregion;

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();
	
	#pragma region "Build Cylinder"

	// Taking one full rotation in radians (2 * pi)
	// and dividing it by the number of subdivisions,
	// will be used to increment sections.
	float fractionValue = (2.0 * PI) / a_nSubdivisions;

	// - - CIRCLE - TOP OF CYLINDER - -
	for (int i = 0; i < a_nSubdivisions; i++) {

		// Referencing the current angle (left side) and the next angle (right side)
		float angle0 = i * fractionValue;
		float angle1 = (i + 1) * fractionValue;

		// Add the triangles based on calculated values.
		// Flip the y and z values so it faces outward.
		AddTri(
			vector3(0.0f, a_fHeight / 2.0f, 0.0f),
			vector3(a_fRadius * cos(angle1), a_fHeight / 2.0f, a_fRadius * sin(angle1)),
			vector3(a_fRadius * cos(angle0), a_fHeight / 2.0f, a_fRadius * sin(angle0)));
	}
	
	// - - CIRCLE - BOTTOM OF CYLINDER - -
	for (int i = 0; i < a_nSubdivisions; i++) {

		// Referencing the current angle (left side) and the next angle (right side)
		float angle0 = i * fractionValue;
		float angle1 = (i + 1) * fractionValue;

		// To move the circle down to the bottom of the cylinder,
		// Y values are the negative version of the top cylinder's y values.

		// Add the triangles based on the calculated values.
		AddTri(
			vector3(0.0f, -a_fHeight / 2.0f, 0.0f), 
			vector3(a_fRadius * cos(angle0), -a_fHeight / 2.0f, a_fRadius * sin(angle0)),
			vector3(a_fRadius * cos(angle1), -a_fHeight / 2.0f, a_fRadius * sin(angle1)));
	}

	// - - RECTANGLES - SIDE OF CYLINDER - -
	for (int i = 0; i < a_nSubdivisions; i++) {

		// Referencing the current angle (left side) and the next angle (right side)
		float angle0 = i * fractionValue;
		float angle1 = (i + 1) * fractionValue;

		// Identifying points to connect through AddQuad
		// Since there's a lot of points, I made them variables
		// and then added them to the AddQuad Function.
		float x0 = a_fRadius * cos(angle0);
		float y0 = -a_fHeight / 2.0f;
		float z0 = a_fRadius * sin(angle0);

		float x1 = a_fRadius * cos(angle1);
		float y1 = -a_fHeight / 2.0f;
		float z1 = a_fRadius * sin(angle1);

		float x2 = a_fRadius * cos(angle0);
		float y2 = a_fHeight / 2.0f;
		float z2 = a_fRadius * sin(angle0);

		float x3 = a_fRadius * cos(angle1);
		float y3 = a_fHeight / 2.0f;
		float z3 = a_fRadius * sin(angle1);

		// Add the Quad based on the calculated values.
		// Flipped A & B as well as C & D because of how I calculated the values.
		AddQuad(vector3(x1, y1, z1), vector3(x0, y0, z0), vector3(x3, y3, z3), vector3(x2, y2, z2));
	}

	#pragma endregion;

	//This code was my brainstorming for figuring out the best way to reference
	// the previous/next values of the vertices. I tried storing those values in different ways,
	// before arriving at the true solution.
	#pragma region "Commented-out code"
	//
	// 
	//std::vector<vector3> vertexOfBottomCircle;
	//for (int i = 0; i < a_nSubdivisions; i++)
	//{
	//	vector3 temp = vector3(cos(theta) * a_fRadius, a_fHeight, sin(theta) * a_fRadius);
	//	theta += delta;
	//	vertexOfBottomCircle.push_back(temp);
	//}

	//for (int i = 0; i < a_nSubdivisions; i++)
	//{
	//	vector3 bValue = vertexOfBottomCircle[(i + 1) % a_nSubdivisions];
	//	vector3 cValue = vertexOfBottomCircle[i];

		// Change the y values

	//	bValue.y = a_fHeight;
	//	cValue.y = a_fHeight;

	//	AddTri(vector3(0, a_fHeight, 0), bValue, cValue);

	//	int index = 0;

	//float x = 0;
	//float y = 0;
	//float z = 0;

	//for (int i = 0; i < a_nSubdivisions; i++)
	//{
	//	x = (a_fRadius * cos(theta));
	//	y = a_fHeight;
	//	z = (sin(theta) * a_fRadius);
	//	theta += delta;

	//}


		//AddQuad( vector3(vertexOfBottomCircle[i].x, a_fHeight, vertexOfBottomCircle[i].z), 
		//	vector3(vertexOfBottomCircle[i].x + delta, a_fHeight, vertexOfBottomCircle[i].z + delta), 
		//	vector3(vertexOfBottomCircle[i].x, 0, vertexOfCircle[i].z),
		//	vector3(vertexOfBottomCircle[i].x + delta, 0, vertexOfBottomCircle[i].z));


		///if (i == 0)
		//{
			//AddQuad(
			//	vector3(vertexOfBottomCircle[i].x - (fractionValue / 2), a_fHeight, vertexOfBottomCircle[i].z - (fractionValue / 2)),
			//	vector3(vertexOfBottomCircle[i].x + (fractionValue / 2), a_fHeight, vertexOfBottomCircle[i].z + (fractionValue / 2)),
			//	vector3(vertexOfBottomCircle[i].x - (fractionValue / 2), 0, vertexOfCircle[i].z+ (fractionValue / 2)),
			//	vector3(vertexOfBottomCircle[i].x + (fractionValue / 2), 0, vertexOfBottomCircle[i].z - (fractionValue / 2)));

			//AddQuad(
			//	vector3(vertexOfBottomCircle[i].x, a_fHeight, vertexOfBottomCircle[i].z),
			//	vector3(vertexOfBottomCircle[i].x - (fractionValue/2), a_fHeight, vertexOfBottomCircle[i].z - (fractionValue/2)),
			//	vector3(vertexOfBottomCircle[i].x, 0, vertexOfBottomCircle[i].z),
			//	vector3(vertexOfBottomCircle[i].x - (fractionValue/2), 0, vertexOfCircle[i].z - (fractionValue/2)));

			//AddQuad(
			//	vector3(vertexOfBottomCircle[i + 1].x + (fractionValue / 2), a_fHeight, vertexOfBottomCircle[i+1].z - (fractionValue / 2)),
			//	vector3(vertexOfBottomCircle[i].x + (fractionValue / 2), a_fHeight, vertexOfBottomCircle[i].z - (fractionValue / 2)),
			//	vector3(vertexOfBottomCircle[i + 1].x + (fractionValue / 2), 0, vertexOfCircle[i+1].z - (fractionValue / 2)),
			//	vector3(vertexOfBottomCircle[i].x + (fractionValue / 2), 0, vertexOfBottomCircle[i].z - (fractionValue / 2)));
		//}
		//if (i == a_nSubdivisions - 1)
		//{
		//	AddQuad(vector3(vertexOfBottomCircle[i].x + (fractionValue / 2), a_fHeight, vertexOfBottomCircle[i].z - (fractionValue / 2)),
		//		vector3(vertexOfBottomCircle[0].x + (fractionValue / 2), a_fHeight, vertexOfBottomCircle[0].z - (fractionValue / 2)),
		//		vector3(vertexOfBottomCircle[i].x + (fractionValue / 2), 0, vertexOfCircle[i].z - (fractionValue / 2)),
		//		vector3(vertexOfBottomCircle[0].x + (fractionValue / 2), 0, vertexOfBottomCircle[0].z - (fractionValue / 2)));
		//}
		//else {
			//AddQuad(
			//vector3(vertexOfBottomCircle[i-1].x + (fractionValue / 2), a_fHeight, vertexOfBottomCircle[i-1].z - (fractionValue / 2)),
			//vector3(vertexOfBottomCircle[i].x + (fractionValue / 2), a_fHeight, vertexOfBottomCircle[i].z - (fractionValue / 2)),
			//vector3(vertexOfBottomCircle[i-1].x + (fractionValue / 2), 0, vertexOfCircle[i-1].z - (fractionValue / 2)),
		    //	vector3(vertexOfBottomCircle[i].x + (fractionValue / 2), 0, vertexOfBottomCircle[i].z - (fractionValue / 2)));

			//AddQuad(
				//vector3(vertexOfBottomCircle[i].x + (fractionValue / 2), a_fHeight, vertexOfBottomCircle[i].z - (fractionValue / 2)),
				//vector3(vertexOfBottomCircle[i - 1].x - (fractionValue / 2), a_fHeight, vertexOfBottomCircle[i - 1].z + (fractionValue / 2)),
				//vector3(vertexOfBottomCircle[i].x + (fractionValue / 2), 0, vertexOfBottomCircle[i].z - (fractionValue / 2)),
				//vector3(vertexOfBottomCircle[i - 1].x - (fractionValue / 2), 0, vertexOfCircle[i - 1].z + (fractionValue / 2)));

			//AddQuad(
				//vector3(vertexOfBottomCircle[i].x + (fractionValue / 2), a_fHeight, vertexOfBottomCircle[i].z - (fractionValue / 2)),
				//vector3(vertexOfBottomCircle[i + 1].x + (fractionValue / 2), a_fHeight, vertexOfBottomCircle[i + 1].z - (fractionValue / 2)),
				//vector3(vertexOfBottomCircle[i].x + (fractionValue / 2), 0, vertexOfCircle[i].z - (fractionValue / 2)),
				//vector3(vertexOfBottomCircle[i + 1].x + (fractionValue / 2), 0, vertexOfBottomCircle[i + 1].z - (fractionValue / 2)));
		//}


	// -------------------------------


	//std::vector<float> sineList;

	//std::vector<float> cosineList;

	//for (int i = 0; i <= a_nSubdivisions; i++)
	//{
	//	sineList.push_back(sin(currentAngle));
	//	cosineList.push_back(cos(currentAngle));

	// Update angle
	//	currentAngle += angle;
	//std::vector<float> xCoordinates;
	//std::vector<float> zCoordinates;
	//for (int i = 0; i <= a_nSubdivisions; i++)
	//{
	//	xCoordinates.push_back(cosineList[i] * a_fRadius);
	//	std::cout << xCoordinates[i];
	//	zCoordinates.push_back(sineList[i] * a_fRadius);
	//}

	// Add cylinder side vertices
	//for (int i = 0; i <= a_nSubdivisions; i++)
	//{
	//	vector3 topPosition = vector3(xCoordinates[i], a_fHeight / 2.0f, zCoordinates[i]);
	//	vector3 bottomPosition = vector3(xCoordinates[i], -a_fHeight / 2.0f, zCoordinates[i]);
	//	AddTri(vector3(xCoordinates[i], -a_fHeight / 2.0f, zCoordinates[i]), bottomPosition, topPosition);
		//AddQuad(topPosition[i], topPosition[i + 1], bottomPosition[i], bottomPosition[i + 1]);
	//}

#pragma endregion

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	#pragma region "Build Tube"

	// Taking one full rotation in radians (2 * pi)
	// and dividing it by the number of subdivisions,
	// will be used to increment sections.
	float fractionValue = 2 * PI / a_nSubdivisions;

	// - TUBE - OUTSIDE
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// Referencing the current angle (left side) and the next angle (right side)
		float angle0 = i * fractionValue;
		float angle1 = (i + 1) * fractionValue;

		// Storing calcuations in variables for debugging
		float x0 = a_fOuterRadius * cos(angle0);
		float y0 = -a_fHeight / 2.0f;
		float z0 = a_fOuterRadius * sin(angle0);

		float x1 = a_fOuterRadius * cos(angle1);
		float y1 = -a_fHeight / 2.0f;
		float z1 = a_fOuterRadius * sin(angle1);

		float x2 = a_fOuterRadius * cos(angle0);
		float y2 = a_fHeight / 2.0f;
		float z2 = a_fOuterRadius * sin(angle0);

		float x3 = a_fOuterRadius * cos(angle1);
		float y3 = a_fHeight / 2.0f;
		float z3 = a_fOuterRadius * sin(angle1);

		// Add the Quad based on the calculated values.
		AddQuad(vector3(x1, y1, z1), vector3(x0, y0, z0), vector3(x3, y3, z3), vector3(x2, y2, z2) );
	}

	// - TUBE - INSIDE
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// Referencing the current angle (left side) and the next angle (right side)
		float angle0 = i * fractionValue;
		float angle1 = (i + 1) * fractionValue;

		// Storing calcuations in variables for debugging
		float x0 = a_fInnerRadius * cos(angle0);
		float y0 = -a_fHeight / 2.0f;
		float z0 = a_fInnerRadius * sin(angle0);

		float x1 = a_fInnerRadius * cos(angle1);
		float y1 = -a_fHeight / 2.0f;
		float z1 = a_fInnerRadius * sin(angle1);

		float x2 = a_fInnerRadius * cos(angle0);
		float y2 = a_fHeight / 2.0f;
		float z2 = a_fInnerRadius * sin(angle0);

		float x3 = a_fInnerRadius * cos(angle1);
		float y3 = a_fHeight / 2.0f;
		float z3 = a_fInnerRadius * sin(angle1);

		// Add the Quad based on the calculated values.
		AddQuad(vector3(x0, y0, z0), vector3(x1, y1, z1), vector3(x2, y2, z2), vector3(x3, y3, z3));
	}

	// - TUBE - TOP CAP
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// Referencing the current angle (left side) and the next angle (right side)
		float angle0 = i * fractionValue;
		float angle1 = (i + 1) * fractionValue;

		float x0 = a_fOuterRadius * cos(angle0);
		float y0 = a_fHeight / 2.0f;
		float z0 = a_fOuterRadius * sin(angle0);

		float x1 = a_fOuterRadius * cos(angle1);
		float y1 = a_fHeight / 2.0f;
		float z1 = a_fOuterRadius * sin(angle1);

		float x2 = a_fInnerRadius * cos(angle0);
		float y2 = a_fHeight / 2.0f;
		float z2 = a_fOuterRadius * sin(angle0);

		float x3 = a_fInnerRadius * cos(angle1);
		float y3 = a_fHeight / 2.0f;
		float z3 = a_fOuterRadius * sin(angle1);
		// Add the Quad based on the calculated values.
		AddQuad(vector3(x0, y0, z0), vector3(x1, y1, z1), vector3(x3, y3, z3), vector3(x2, y2, z2));
	}

	// - TUBE - BOTTOM CAP
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// Referencing the current angle (left side) and the next angle (right side)
		float angle0 = i * fractionValue;
		float angle1 = (i + 1) * fractionValue;

		float x0 = a_fOuterRadius * cos(angle0);
		float y0 = -a_fHeight / 2.0f;
		float z0 = a_fOuterRadius * sin(angle0);

		float x1 = a_fOuterRadius * cos(angle1);
		float y1 = -a_fHeight / 2.0f;
		float z1 = a_fOuterRadius * sin(angle1);

		float x2 = a_fInnerRadius * cos(angle0);
		float y2 = -a_fHeight / 2.0f;
		float z2 = a_fOuterRadius * sin(angle0);

		float x3 = a_fInnerRadius * cos(angle1);
		float y3 = -a_fHeight / 2.0f;
		float z3 = a_fOuterRadius * sin(angle1);
		// Add the Quad based on the calculated values.
		AddQuad(vector3(x0, y0, z0), vector3(x1, y1, z1), vector3(x2, y2, z2), vector3(x3, y3, z3));
	}

#pragma endregion

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	#pragma region "Build Torus"
	
	// Fraction value to increment by, for inner and outer of the torus.
	float innerFractionValue = (2.0 * PI) / a_nSubdivisionsA;
	float outerFractionValue = (2.0 * PI) / a_nSubdivisionsB;

	for (int i = 0; i < a_nSubdivisionsA;  i++) {
		for (int j = 0; j < a_nSubdivisionsB; j++) {

			// We need two angles to build the sphere,
			// Represented by phi and theta.

			// Save the value of the current phi and theta,
			// as well as the next values for correct quad placement.
			float phi0 = i * innerFractionValue;
			float phi1 = (i + 1) * innerFractionValue;
			float theta0 = j * outerFractionValue;
			float theta1 = (j + 1) * outerFractionValue;


			// Identifying points to connect through AddQuad
			// Since there's a lot of points, I made them variables
			// and then added them to the AddQuad Function.
				float x0 = (a_fOuterRadius + a_fInnerRadius * cos(theta0)) * cos(phi0);
				float y0 = (a_fOuterRadius + a_fInnerRadius * cos(theta0)) * sin(phi0);
				float z0 = a_fInnerRadius * sin(theta0);

				float x1 = (a_fOuterRadius + a_fInnerRadius * cos(theta1)) * cos(phi0);
				float y1 = (a_fOuterRadius + a_fInnerRadius * cos(theta1)) * sin(phi0);
				float z1 = a_fInnerRadius * sin(theta1);

				float x2 = (a_fOuterRadius + a_fInnerRadius * cos(theta0)) * cos(phi1);
				float y2 = (a_fOuterRadius + a_fInnerRadius * cos(theta0)) * sin(phi1);
				float z2 = a_fInnerRadius * sin(theta0);

				float x3 = (a_fOuterRadius + a_fInnerRadius * cos(theta1)) * cos(phi1);
				float y3 = (a_fOuterRadius + a_fInnerRadius * cos(theta1)) * sin(phi1);
				float z3 = a_fInnerRadius * sin(theta1);

				// Add the Quad via generation of vectors based on x,y,z values found
				// Flipped A&B as well as C&D because of the order of calculations performed 
				// in order for the quads to face the right direction.
				AddQuad(vector3(x1, y1, z1), vector3(x0, y0, z0), vector3(x3,y3,z3), vector3(x2, y2, z2));
			}
		}

	#pragma endregion;

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	#pragma region "Build Sphere"
	// We need two angles to build the sphere,
	// represented by phi and theta.
	float phiAngle = 2 * PI / a_nSubdivisions;
	float thetaAngle = PI / a_nSubdivisions;

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		for (int j = 0; j < a_nSubdivisions; j++)
		{
			// We need two angles to build the sphere,
			// Represented by phi and theta.

			// Save the value of the current phi and theta,
			// as well as the next values for correct quad placement.
			float phi0 = i * phiAngle;
			float phi1 = (i + 1) * phiAngle;

			float theta0 = j * thetaAngle;
			float theta1 = (j + 1) * thetaAngle;

			// Added the values of the quad directly based on calcuations
			AddQuad(
				vector3(
					a_fRadius * sin(theta0) * cos(phi0),
					a_fRadius * sin(theta0) * sin(phi0),
					a_fRadius * cos(theta0)),
				vector3(
					a_fRadius * sin(theta0) * cos(phi1),
					a_fRadius * sin(theta0) * sin(phi1),
					a_fRadius * cos(theta0)),
				vector3(
					a_fRadius * sin(theta1) * cos(phi0),
					a_fRadius * sin(theta1) * sin(phi0),
					a_fRadius * cos(theta1)),
				vector3(
					a_fRadius * sin(theta1) * cos(phi1),
					a_fRadius * sin(theta1) * sin(phi1),
					a_fRadius * cos(theta1)));
		}
	}

	#pragma endregion
	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}