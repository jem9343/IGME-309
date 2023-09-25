#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Jay Miller - jem9343@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Initialize the mesh
	//m_pMesh = new MyMesh();
	//m_pMesh->GenerateCube(1.0f, C_WHITE);
	
	for (int i = 0; i < 46; i++)
	{
		MyMesh* newCube = new MyMesh();
		newCube->GenerateCube(1.0f, C_BLACK);
		vectorOfMeshes.push_back(newCube);
		//vectorOfMeshes[i]->GenerateCube(1.0f, C_BLACK)
	}
		
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// Calculate the model, view and projection matrix

	// How to project the image on the screen
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();

	// Get view of the camera
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	// Identity matrix for default
	matrix4 m4Model = IDENTITY_M4;

	// - - SCALE - - 
	// Scale it by 2
	// matrix4 m4Scale = glm::scale(vector3(5.0f, 5.0f, 5.0f));

	// Scale it by 2 using GLOBAL coordinates
	// matrix4 m4ScaleGlobal = glm::scale(IDENTITY_M4, vector3(5.0f, 5.0f, 5.0f));

	// - - TRANSLATION - - 
	// Translating object
	// matrix4 m4Translation = glm::translate(vector3(1.0f, 0.0f, 0.0f));

	// Translating object using GLOBAL coordinates
	// matrix4 m4TranslationGlobal = glm::translate(IDENTITY_M4, vector3(1.0f, 0.0f, 0.0f));

	// Allows us to rotate the cube
	//m4Model = ToMatrix4(m_qArcBall);

	// - - MOVING OBJECT - -
	// static float value = 0.0f;
	// matrix4 m4TranslationContinuous = glm::translate(IDENTITY_M4, vector3(value, 0.0f, 0.0f));
	// value += 0.01f;

	// ORDER MATTERS!!
	// m4Translation * m4Scale != m4Scale * m4Translate
	// m4Model = m4Translation * m4Scale;

	// m4Model = m4Scale * m4TranslationContinuous;

	// To move the model, we will have to use LER

	// m_pMesh->Render(m4Projection, m4View, m4Model);

	uint i = 0;
	matrix4 m4Position = glm::translate(vector3(-5.0f, -3.0f, -15.0f));
	static float value = 0.0f;
	value += 0.01f;

	// Set positions of each cube
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3.0f + value, 0.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f + value, 0.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f + value, 0.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(7.0f + value, 0.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f + value, 1.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f + value, 1.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8.0f + value, 1.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(10.0f + value, 1.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(0.0f + value, 2.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f + value, 2.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3.0f + value, 2.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f + value, 2.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(5.0f + value, 2.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f + value, 2.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(7.0f + value, 2.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8.0f + value, 2.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(10.0f + value, 2.0f, 0.0f))); i++;

	// Row four
	for (int count4thRow = 0; count4thRow < 11; count4thRow++)
	{
		vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(count4thRow + value, 3.0f, 0.0f))); ++i;
	}

	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(1.0f + value, 4.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2.0f + value, 4.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(4.0f + value, 4.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(5.0f + value, 4.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(6.0f + value, 4.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8.0f + value, 4.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(9.0f + value, 4.0f, 0.0f))); i++;

	// Row Six
	for (int count6thRow = 2; count6thRow < 9; ++count6thRow)
	{
		vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(count6thRow + value, 5.0f, 0.0f))); i++;
	}

	//seventh row
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(3 + value, 6.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(7 + value, 6.0f, 0.0f))); i++;

	//eight row
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(2 + value, 7.0f, 0.0f))); i++;
	vectorOfMeshes[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(8 + value, 7.0f, 0.0f))); i++;

	//matrix4 m4TranslationContinuous = glm::translate(IDENTITY_M4, vector3(value, 0.0f, 0.0f));
	//value += 0.01f;


	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release meshes
	SafeDelete(m_pMesh);

	std::vector<MyMesh*> vectorOfMeshes;
	int vectorMeshSize = vectorOfMeshes.size();
	for (int i = 0; i < vectorMeshSize; i++)
	{
		if (vectorOfMeshes[i] != nullptr)
		{
			delete vectorOfMeshes[i];
			vectorOfMeshes[i] = nullptr;
		}
	}

	//release GUI
	ShutdownGUI();
}