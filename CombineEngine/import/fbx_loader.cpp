#include "stdafx.h"
#include "fbx_loader.h"


fbx_loader::fbx_loader()
{
}

int fbx_loader::LoadModel(std::string file_name){
	FbxManager* g_pFbxSdkManager = nullptr;
	if (g_pFbxSdkManager == nullptr)
	{
		g_pFbxSdkManager = FbxManager::Create();

		FbxIOSettings* pIOsettings = FbxIOSettings::Create(g_pFbxSdkManager, IOSROOT);
		g_pFbxSdkManager->SetIOSettings(pIOsettings);
	}

	FbxImporter* pImporter = FbxImporter::Create(g_pFbxSdkManager, "");
	FbxScene* pFbxScene = FbxScene::Create(g_pFbxSdkManager, "");

	bool bSuccess = pImporter->Initialize(file_name.c_str(), -1, g_pFbxSdkManager->GetIOSettings());
	if (!bSuccess) return -1;

	bSuccess = pImporter->Import(pFbxScene);
	if (!bSuccess) return -1;

	pImporter->Destroy();

	FbxNode* pFbxRootNode = pFbxScene->GetRootNode();

	if (pFbxRootNode)
	{
		//traverse models
		int number = pFbxRootNode->GetChildCount(true);
		for (int i = 0; i < pFbxRootNode->GetChildCount(); i++)
		{
			//traverse models

			//model=new model
			Model* pModel;

			//
			FbxNode* pFbxChildNode = pFbxRootNode->GetChild(i);

			if (pFbxChildNode->GetNodeAttribute() == NULL)
				continue;

			FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();

			const char *objName = (pFbxChildNode->GetNodeAttribute()->GetName());


			if (AttributeType != FbxNodeAttribute::eMesh)
				continue;

			//get mesh
			FbxMesh* pMesh = (FbxMesh*)pFbxChildNode->GetNodeAttribute();
			FbxMesh* pMesh1 = pFbxChildNode->GetMesh();

			//get 
			FbxVector4* pVertices = pMesh->GetControlPoints();

			m_vertex_list.resize(pMesh->GetControlPointsCount());
			m_uv_coord.resize(pMesh->GetPolygonCount());
			for (int s = 0; s < pMesh->GetControlPointsCount(); s++){
				m_vertex_list[s] = Vec3f((float)pVertices[s].mData[0], (float)pVertices[s].mData[1], (float)pVertices[s].mData[2]);
			}
			pMesh->GenerateTangentsData();
			//tangent
			FbxGeometryElementTangent *Tangents=pMesh->GetElementTangent(0);
			FbxGeometryElementBinormal *Binormals = pMesh->GetElementBinormal(0);

			m_polygon.resize(pMesh->GetPolygonCount());
			m_tangent.resize(pMesh->GetPolygonCount());
			m_bitangent.resize(pMesh->GetPolygonCount());

			FbxLayerElementArrayTemplate<int>* tangentIndice;
			pMesh->GetTangentsIndices(&tangentIndice, FbxLayerElement::eByPolygonVertex);
			//FbxLayerElementTangent * tangents= pMesh->GetLayer(1)->GetTangents();

			//traverse polygon
			for (int j = 0; j < pMesh->GetPolygonCount(); j++)
			{
				int iNumVertices = pMesh->GetPolygonSize(j);
				//assert(iNumVertices < 3);
				std::vector<int> Polygon;
				Polygon.resize(iNumVertices);

				//uv parameter
				FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
				FbxLayerElementArrayTemplate<FbxVector4>* tangentVertices = 0;
				FbxLayerElementArrayTemplate<FbxVector4>* bitangentVertices = 0;
				
				pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);
				pMesh->GetTangents(&tangentVertices, FbxLayerElement::eByPolygonVertex);
				pMesh->GetBinormals(&bitangentVertices, FbxLayerElement::eByPolygonVertex);
				m_uv_coord[j].resize(iNumVertices);
				m_tangent[j].resize(iNumVertices);
				m_bitangent[j].resize(iNumVertices);

				for (int k = 0; k < iNumVertices; k++)
				{
					int iControlPointIndex = pMesh->GetPolygonVertex(j, k);


					//Vec3f vertex;
					Vec3f vertex((float)pVertices[iControlPointIndex].mData[0],
						(float)pVertices[iControlPointIndex].mData[1],
						(float)pVertices[iControlPointIndex].mData[2]);
					
					//update
					m_vertex.push_back(vertex);
					//get uv

					FbxVector2 uv = (*uvVertices)[pMesh->GetTextureUVIndex(j, k)];

					FbxGeometryElementTangent *ta = pMesh->GetElementTangent(1);
					FbxGeometryElementBinormal *bin=pMesh->GetElementBinormal(1);
					

					//FbxVector4 tangent = (*tangentVertices)[tangentIndice[3*j+k]];

					m_tangent[j][k] = Vec3f(Tangents->GetDirectArray().GetAt(iControlPointIndex).mData[0], Tangents->GetDirectArray().GetAt(iControlPointIndex).mData[1], Tangents->GetDirectArray().GetAt(iControlPointIndex).mData[2]);
					
					m_bitangent[j][k] = Vec3f(Binormals->GetDirectArray().GetAt(iControlPointIndex).mData[0], Binormals->GetDirectArray().GetAt(iControlPointIndex).mData[1], Binormals->GetDirectArray().GetAt(iControlPointIndex).mData[2]);

					m_uv_coord[j][k]=Vec2f((float)uv.mData[0], (float)uv.mData[1]);

					//get polygon index
					Polygon[k] = iControlPointIndex;
				}
				m_polygon[j] = Polygon;
			}
			getVertexNormal(pMesh);
			//
			pModel = new Model(m_vertex_list, m_polygon, m_vertex_normal);
			modelList.push_back(pModel);
		}
		ComputeNormal();
		

	}
	return 0;
}


void fbx_loader::getVertexNormal(FbxMesh *pMesh){
	//normal
	FbxGeometryElementNormal* leNormals = pMesh->GetElementNormal();

	m_vertex_normal.resize(pMesh->GetControlPointsCount());

	for (unsigned int i = 0; i < pMesh->GetControlPointsCount(); i++){
		Vec3f Normal(
			(float)leNormals->GetDirectArray().GetAt(i).mData[0],
			(float)leNormals->GetDirectArray().GetAt(i).mData[1],
			(float)leNormals->GetDirectArray().GetAt(i).mData[2]
			);
		m_vertex_normal[i] = Normal;
	}
	pMesh->GetElementUV();
	
}

void fbx_loader::draw(){
	if (m_vertex.size()>0){

		//convert format
		const unsigned int size = m_vertex.size() * 3;
		std::vector<float> vertex_array;
		vertex_array.resize(size);
		for (unsigned int i = 0; i < m_vertex.size(); i++){
			vertex_array[i * 3] = m_vertex[i].x();
			vertex_array[i * 3+1] = m_vertex[i].y();
			vertex_array[i * 3+2] = m_vertex[i].z();
		}

		//define vertex buffer
		GLuint VertexBuffer;

		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1,&VertexBuffer);

		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, vertex_array.size()*sizeof(float), vertex_array.data(), GL_STATIC_DRAW);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		/*glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDrawArrays(GL_POLYGON, 0, 3);
		glDisableClientState(GL_VERTEX_ARRAY);*/
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);
		/*glVertexPointer(2,GL_FLOAT,3*sizeof(float),0);*/

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertex_array.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle

		glDisableVertexAttribArray(0);

		//////vertex normal /////////////////////

		//construct buffer object
		std::vector<float> normal_buffer;

		for (unsigned int i = 0; i < m_polygon.size(); i++){
			for (unsigned int j = 0; j < m_polygon[i].size(); j++){
				normal_buffer.push_back(m_vertex_normal[m_polygon[i][j]].x());
				normal_buffer.push_back(m_vertex_normal[m_polygon[i][j]].y());
				normal_buffer.push_back(m_vertex_normal[m_polygon[i][j]].z());
			}
		}

		//define normal buffer
		GLuint NormalBuffer;
		//generate buffer
		glGenBuffers(1, &NormalBuffer);
		//bind buffer
		glBindBuffer(GL_ARRAY_BUFFER, NormalBuffer);

		glBufferData(GL_ARRAY_BUFFER, normal_buffer.size()*sizeof(float), normal_buffer.data(),GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, NormalBuffer);
		glVertexAttribPointer(
			1,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
			);
	}
}

void fbx_loader::easydraw(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	glBegin(GL_QUADS);
	int count = 0;
	for (unsigned int i = 0; i < m_polygon.size(); i++){
		for (unsigned int j = 0; j < m_polygon[i].size(); j++){
			glNormal3fv(computed_Vert_norm[m_polygon[i][j]].getPtr());
			glVertex3fv(m_vertex_list[m_polygon[i][j]].getPtr());
			count++;
		}
	}
	glEnd();
}

void fbx_loader::drawNormal(){
	float scale = 5;
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	for (unsigned int i = 0; i < m_vertex_list.size(); i++){
		glVertex3fv(m_vertex_list[i].getPtr());
	}
	glEnd();
	glBegin(GL_LINES);
	for (unsigned int i = 0; i < m_vertex_list.size(); i++){
		glVertex3fv(m_vertex_list[i].getPtr());
		//glVertex3fv(((m_vertex_list[i] + computed_Vert_norm[i]*scale)).getPtr());
		glVertex3fv(((m_vertex_list[i] + m_vertex_normal[i] * scale)).getPtr());
	}
	glEnd();
}

fbx_loader::~fbx_loader()
{
}

void fbx_loader::ComputeNormal(){
	std::vector<std::vector<int>> Face_connect;
	Face_connect.resize(m_vertex_list.size());
	//compute face normal
	computed_face_norm.resize(m_polygon.size());
	for (unsigned int i = 0; i < m_polygon.size(); i++){
		Vec3f vector1 = m_vertex_list[m_polygon[i][1]] - m_vertex_list[m_polygon[i][0]];
		Vec3f vector2 = m_vertex_list[m_polygon[i][m_polygon[i].size() - 1]] - m_vertex_list[m_polygon[i][0]];
		Vec3f normal = vector1.cross(vector2);
		normal.normalize();
		computed_face_norm[i] = normal;
		for (unsigned int j = 0; j < m_polygon[i].size(); j++){
			Face_connect[m_polygon[i][j]].push_back(i);
		}
	}
	//compute vertex normal
	computed_Vert_norm.resize(m_vertex_list.size());
	for (unsigned int i = 0; i < Face_connect.size(); i++){
		Vec3f normal;
		for (unsigned int j = 0; j < Face_connect[i].size(); j++){
			normal += computed_face_norm[Face_connect[i][j]];
		}
		normal.normalize();
		computed_Vert_norm[i]=normal;
	}

}

//convert to model
Model* fbx_loader::CreateModel(){
	if (haveUV){ //model have uv
		//
		Model *pModel = new Model(m_vertex_list, m_polygon, m_vertex_normal);
		return pModel;
	} 
	else{     //model does not have uv
		//
		Model *pModel = new Model(m_vertex_list, m_polygon, m_vertex_normal,computed_face_norm, m_uv_coord);
	}
	return NULL;
}