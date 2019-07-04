#include "FBXLoader.h"

namespace FBXLoader 
{
	FbxManager* fbxManager;
	
	HRESULT LoadFBX(LPCSTR fileName, std::vector<Vertex>* outVertices, std::vector<DWORD>* outIndices)
	{
		// fbxManager가 생성이 안됐으면 생성하기.
		if (fbxManager == NULL)
		{
			// SDK 매니저 생성.
			fbxManager = FbxManager::Create();

			FbxIOSettings* ioSettings = FbxIOSettings::Create(fbxManager, IOSROOT);
			fbxManager->SetIOSettings(ioSettings);
		}

		// GeometryConverter 생성.
		FbxGeometryConverter geometryConverter(fbxManager);
		FbxImporter* importer = FbxImporter::Create(fbxManager, "");
		FbxScene* fbxScene = FbxScene::Create(fbxManager, "");

		// 임포터 초기화.
		if (importer->Initialize(fileName, -1, fbxManager->GetIOSettings()) == false)
		{
			return E_FAIL;
		}

		// 3D 씬(장면) 임포트.
		if (importer->Import(fbxScene) == false)
		{
			return E_FAIL;
		}

		// FBX Node 읽기.
		FbxNode* fbxRootNode = fbxScene->GetRootNode();
		if (fbxRootNode == NULL)
			return E_FAIL;

		// 모델 폴리곤 기본 구조를 삼각면으로 설정.
		geometryConverter.Triangulate(fbxScene, true);

		// 루트 노드의 하위 노드 개수 얻어오기.
		int childCount = fbxRootNode->GetChildCount();
		for (int ix = 0; ix < childCount; ++ix)
		{
			// 자식 계층 노드 읽어오기.
			FbxNode* childNode = fbxRootNode->GetChild(ix);

			// 속성 중에서 타입만 확인.
			FbxNodeAttribute::EType attrType = childNode->GetNodeAttribute()->GetAttributeType();

			// 메시 타입인지 확인.
			if (attrType != FbxNodeAttribute::EType::eMesh)
				continue;

			// 메시 정보 읽어오기.
			FbxMesh* fbxMesh = childNode->GetMesh();

			// 점 배열 얻어오기(정점).
			FbxVector4* vertices = fbxMesh->GetControlPoints();

			// 폴리곤 수 확인.
			int polygonCount = fbxMesh->GetPolygonCount();
			// 인덱스 설정용 변수.
			int vertexCounter = 0;

			// 폴리곤 순회.
			for (int jx = 0; jx < polygonCount; ++jx)
			{
				// 폴리곤을 구성하는 정점 개수 확인.
				int vertexCount = fbxMesh->GetPolygonSize(jx);

				// 폴리곤 안의 정점 순회.
				for (int kx = 0; kx < vertexCount; ++kx)
				{
					// 정점 순번 확인.
					int vertexIndex = fbxMesh->GetPolygonVertex(jx, kx);

					// 정점 정보 읽어오기.
					Vertex vertex;
					vertex.position.x = static_cast<float>(vertices[vertexIndex].mData[0]);
					vertex.position.y = static_cast<float>(vertices[vertexIndex].mData[1]);
					vertex.position.z = static_cast<float>(vertices[vertexIndex].mData[2]);

					// 정점 추가.
					outVertices->push_back(vertex);

					// 인덱스 추가.
					outIndices->push_back(vertexCounter);
					++vertexCounter;
				}
			}
		}

		return S_OK;
	}
}