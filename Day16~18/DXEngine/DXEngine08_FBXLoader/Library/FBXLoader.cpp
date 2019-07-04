#include "FBXLoader.h"

namespace FBXLoader 
{
	FbxManager* fbxManager;
	
	HRESULT LoadFBX(LPCSTR fileName, std::vector<Vertex>* outVertices, std::vector<DWORD>* outIndices)
	{
		// fbxManager�� ������ �ȵ����� �����ϱ�.
		if (fbxManager == NULL)
		{
			// SDK �Ŵ��� ����.
			fbxManager = FbxManager::Create();

			FbxIOSettings* ioSettings = FbxIOSettings::Create(fbxManager, IOSROOT);
			fbxManager->SetIOSettings(ioSettings);
		}

		// GeometryConverter ����.
		FbxGeometryConverter geometryConverter(fbxManager);
		FbxImporter* importer = FbxImporter::Create(fbxManager, "");
		FbxScene* fbxScene = FbxScene::Create(fbxManager, "");

		// ������ �ʱ�ȭ.
		if (importer->Initialize(fileName, -1, fbxManager->GetIOSettings()) == false)
		{
			return E_FAIL;
		}

		// 3D ��(���) ����Ʈ.
		if (importer->Import(fbxScene) == false)
		{
			return E_FAIL;
		}

		// FBX Node �б�.
		FbxNode* fbxRootNode = fbxScene->GetRootNode();
		if (fbxRootNode == NULL)
			return E_FAIL;

		// �� ������ �⺻ ������ �ﰢ������ ����.
		geometryConverter.Triangulate(fbxScene, true);

		// ��Ʈ ����� ���� ��� ���� ������.
		int childCount = fbxRootNode->GetChildCount();
		for (int ix = 0; ix < childCount; ++ix)
		{
			// �ڽ� ���� ��� �о����.
			FbxNode* childNode = fbxRootNode->GetChild(ix);

			// �Ӽ� �߿��� Ÿ�Ը� Ȯ��.
			FbxNodeAttribute::EType attrType = childNode->GetNodeAttribute()->GetAttributeType();

			// �޽� Ÿ������ Ȯ��.
			if (attrType != FbxNodeAttribute::EType::eMesh)
				continue;

			// �޽� ���� �о����.
			FbxMesh* fbxMesh = childNode->GetMesh();

			// �� �迭 ������(����).
			FbxVector4* vertices = fbxMesh->GetControlPoints();

			// ������ �� Ȯ��.
			int polygonCount = fbxMesh->GetPolygonCount();
			// �ε��� ������ ����.
			int vertexCounter = 0;

			// ������ ��ȸ.
			for (int jx = 0; jx < polygonCount; ++jx)
			{
				// �������� �����ϴ� ���� ���� Ȯ��.
				int vertexCount = fbxMesh->GetPolygonSize(jx);

				// ������ ���� ���� ��ȸ.
				for (int kx = 0; kx < vertexCount; ++kx)
				{
					// ���� ���� Ȯ��.
					int vertexIndex = fbxMesh->GetPolygonVertex(jx, kx);

					// ���� ���� �о����.
					Vertex vertex;
					vertex.position.x = static_cast<float>(vertices[vertexIndex].mData[0]);
					vertex.position.y = static_cast<float>(vertices[vertexIndex].mData[1]);
					vertex.position.z = static_cast<float>(vertices[vertexIndex].mData[2]);

					// ���� �߰�.
					outVertices->push_back(vertex);

					// �ε��� �߰�.
					outIndices->push_back(vertexCounter);
					++vertexCounter;
				}
			}
		}

		return S_OK;
	}
}