/**
 *	@file 	D:/work/dungeon/framework/game/graphics/model/AnimeMesh.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-03
 *	@note 
 *
 */
#include "game/graphics/model/AnimeMesh.h"

#include "common/Common.h"

namespace GameLib {
	/*
		派生フレーム構造体
		(それぞれのメッシュ用の最終ワールド行列を追加)
	*/
	struct _tag_mesh_frame : public D3DXFRAME {
	public:
		D3DXMATRIXA16	m_combinend_mat;
	};
	/*
		派生メッシュコンテナ構造体
		コンテナがテクスチャーを複数持てる用にダブルポインタを追加
	*/
	struct _tag_mesh_container : public D3DXMESHCONTAINER {
	public:
		LPDIRECT3DTEXTURE9*	mpp_tex;
	};

	/*
		Xファイル内のアニメ階層をロードするクラスを派生
		これは自前で作成する必要がある。
		派生元のクラスは仮想関数
	*/
	class MeshLoadHierarchy : public ID3DXAllocateHierarchy {
	public:
		MeshLoadHierarchy() {}
		~MeshLoadHierarchy() {}

		/*
			@brief フレーム作成
		*/
		STDMETHOD(CreateFrame)( THIS_ LPCSTR ip_name, LPD3DXFRAME* ipp_new_frame )
		{
			// 基本処理
			// こちらでフレームデータを確保。
			// フレーム名と初期化をする
			// 確保したフレームを引数変数に引き渡す

			struct _tag_mesh_frame* p_frame = NULL;
			*ipp_new_frame = NULL;

			p_frame = new struct _tag_mesh_frame;
			if( p_frame == NULL ) {
				return E_OUTOFMEMORY;
			}

			int Length	= ::lstrlen(ip_name) + 1;
			p_frame->Name = new TCHAR[ Length ];
			if( !p_frame->Name ) {
				return E_FAIL;
			}
			::strcpy_s( p_frame->Name, Length, ip_name );
			// 終端を入れないとバグる
			p_frame->Name[::lstrlen(ip_name)] = NULL;

			D3DXMatrixIdentity(&p_frame->TransformationMatrix);
			D3DXMatrixIdentity(&p_frame->m_combinend_mat);
			p_frame->pMeshContainer = NULL;		// コンテナのポインタ
			p_frame->pFrameSibling = NULL;		// 階層の親ポインタ
			p_frame->pFrameFirstChild = NULL;	// 階層の兄弟ポインタ

			*ipp_new_frame = p_frame;

			return S_OK;
		}
		/*
			@brief メッシュコンテナ作成
		*/
		STDMETHOD(CreateMeshContainer)( THIS_ LPCTSTR ip_name, CONST D3DXMESHDATA* ip_mesh_data, CONST D3DXMATERIAL* ip_materials,
										CONST D3DXEFFECTINSTANCE* ip_effect_instance, DWORD i_materials_num,
										CONST DWORD* ip_adjacency, LPD3DXSKININFO ip_skin_info, LPD3DXMESHCONTAINER* ipp_mesh_container )
		{
			UNUSE( ip_skin_info );
			UNUSE( ip_effect_instance );

			struct _tag_mesh_container* p_container = NULL;
			LPD3DXMESH	p_mesh = NULL;

			// 作成してあるメッシュデータ取得
			p_mesh = ip_mesh_data->pMesh;
			p_container = new struct _tag_mesh_container;
			if( p_container == NULL )
			{
				return E_OUTOFMEMORY;
			}

			::memset( p_container, 0, sizeof(struct _tag_mesh_container) );
			p_container->Name = new TCHAR[::lstrlen(ip_name) + 1];
			if( !p_container->Name )
			{
				return E_FAIL;
			}

			::strcpy( p_container->Name, ip_name );
			// 終端を入れないとバグる
			p_container->Name[::lstrlen(ip_name)] = NULL;

			LPDIRECT3DDEVICE9	p_device = NULL;
			p_mesh->GetDevice( &p_device );
			int faces_amount = p_mesh->GetNumFaces();

			// メッシュが法線を持たない場合には法線を追加
			if( (~p_mesh->GetFVF()) & (D3DFVF_NORMAL) )
			{
				p_container->MeshData.Type = D3DXMESHTYPE_MESH;
				HRESULT hr = p_mesh->CloneMeshFVF(	p_mesh->GetOptions(),
													p_mesh->GetFVF() | D3DFVF_NORMAL,
													p_device,	&p_container->MeshData.pMesh );
				if( FAILED(hr) )
				{
					return E_FAIL;
				}
			}
			else
			{
				p_container->MeshData.pMesh = p_mesh;
				p_container->MeshData.Type = D3DXMESHTYPE_MESH;
				p_mesh->AddRef();
			}

			p_container->NumMaterials = max(1, i_materials_num);
			p_container->pMaterials = new D3DXMATERIAL[p_container->NumMaterials];
			p_container->mpp_tex = new LPDIRECT3DTEXTURE9[p_container->NumMaterials];
			p_container->pAdjacency = new DWORD[faces_amount * 3];
			if( (p_container->pAdjacency == NULL) || (p_container->pMaterials == NULL) ) {
				return E_OUTOFMEMORY;
			}
			::memcpy( p_container->pAdjacency, ip_adjacency, sizeof(DWORD) * faces_amount * 3 );
			::memset( p_container->mpp_tex, 0, sizeof(LPDIRECT3DTEXTURE9) * p_container->NumMaterials );

			if( p_container->NumMaterials > 0 ) {
				::memcpy( p_container->pMaterials, ip_materials, sizeof(D3DXMATERIAL) * p_container->NumMaterials );

				for( unsigned i=0; i<p_container->NumMaterials; i++ ) {
					if( p_container->pMaterials[i].pTextureFilename != NULL ) {
						TCHAR text_path[MAX_PATH];
						::strcpy( text_path, p_container->pMaterials[i].pTextureFilename );
						if( FAILED( D3DXCreateTextureFromFile( p_device, text_path, &p_container->mpp_tex[i] ) ) ) {
							p_container->mpp_tex[i] = NULL;
							p_container->pMaterials[i].pTextureFilename = NULL;
						}
					}
				}
			}
			else {
				p_container->pMaterials[0].pTextureFilename = NULL;
				::memset( &p_container->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9) );
				p_container->pMaterials[0].MatD3D.Diffuse.r = 0.0f;
				p_container->pMaterials[0].MatD3D.Diffuse.g = 0.0f;
				p_container->pMaterials[0].MatD3D.Diffuse.b = 0.0f;
				p_container->pMaterials[0].MatD3D.Specular = p_container->pMaterials[0].MatD3D.Diffuse;
			}
			*ipp_mesh_container = p_container;
			p_container = NULL;
			if( p_container != NULL ) {
				DestroyMeshContainer(p_container);
			}

			return S_OK;
		}
		STDMETHOD(DestroyFrame)( THIS_ LPD3DXFRAME ip_frame_to_free )
		{
			SAFE_DELETE_ARRAY( ip_frame_to_free->Name );
			SAFE_DELETE( ip_frame_to_free );
			return S_OK;
		}
		STDMETHOD(DestroyMeshContainer)( THIS_ LPD3DXMESHCONTAINER ip_mesh_container_base )
		{
			struct _tag_mesh_container* p_container = (struct _tag_mesh_container*)(ip_mesh_container_base);

			for( unsigned i=0; i<p_container->NumMaterials; i++ ) {
				SAFE_RELEASE(p_container->mpp_tex[i]);
			}

			SAFE_DELETE_ARRAY( p_container->Name);
			SAFE_DELETE_ARRAY(p_container->pMaterials);
			SAFE_DELETE_ARRAY(p_container->pAdjacency);


			SAFE_DELETE_ARRAY(p_container->mpp_tex);
			SAFE_RELEASE( p_container->MeshData.pMesh );

			SAFE_DELETE(p_container);

			return S_OK;
		}
	};

	AnimeMesh::AnimeMesh( const _TCHAR*	ip_filename )	:
	mp_frame_root(NULL),
	mp_anim_ctrl(NULL),
	m_pos(0,0,0)
	{
		D3DXMatrixIdentity( &m_mat_yaw );

		::memset( &m_pos, 0, sizeof(m_pos) );
		LPDIRECT3DDEVICE9	device = DirectX::Manager::Inst().GetDevice();

		mp_hierarchy = new MeshLoadHierarchy();
		if( FAILED( D3DXLoadMeshHierarchyFromX( ip_filename, D3DXMESH_MANAGED, device, mp_hierarchy, NULL,
												&mp_frame_root, &mp_anim_ctrl)) ) {
			STRING_ASSERT(false, "Error Object\n");
		}
	}

	AnimeMesh::~AnimeMesh()
	{
		if( mp_frame_root ){
			D3DXFrameDestroy( mp_frame_root, mp_hierarchy );
			mp_frame_root = NULL;
		}
		// データ解放
		SAFE_RELEASE(mp_anim_ctrl);
		SAFE_DELETE(mp_hierarchy);
	}

	/*
		@brief メッシュ更新
	*/
	void AnimeMesh::Update()
	{
		D3DXMATRIX	mat_position;
		D3DXMatrixIdentity( &m_mat_world );
		D3DXMatrixIdentity( &mat_position );

		D3DXMatrixTranslation( &mat_position, m_pos.x, m_pos.y, m_pos.z );

		D3DXMatrixMultiply( &m_mat_world, &m_mat_world, &m_mat_yaw );
		D3DXMatrixMultiply( &m_mat_world, &m_mat_world, &mat_position);
				
		UpdateFrameMesh( mp_frame_root, &m_mat_world );
	}

	/*
		@brief メッシュ描画
	*/
	void AnimeMesh::Draw()
	{
		LPDIRECT3DDEVICE9	device = DirectX::Manager::Inst().GetDevice();
		device->SetTransform( D3DTS_WORLD, &m_mat_world );
		// フレームメッシュ描画
		DrawFrameMesh( mp_frame_root );
	}

	/*
		@brief	座標設定
		@param	i_pos	:	座標
	*/
	void AnimeMesh::SetPos( const Vec3& i_pos )
	{
		m_pos = i_pos;
	}

	/*
		@brief	衝突検地
		@param	ip_object	:	オブジェクト
		@note	各メッシュとのレイ衝突判定をしている
				メッシュの数が多いのほど判定処理数が増えるので重い
				処理を軽くする案
					オブジェクト単体でのボックス or スフィアでの判定
						一番軽い
					各メッシュとの判定にボックス or スフィアでの判定
						レイより処理が軽い。
						でもメッシュごとに衝突判定する。
	*/
	bool	AnimeMesh::IsImpact( AnimeMesh* const ip_object )
	{
		return (IsFrameImpact( ip_object->mp_frame_root, ip_object ));
	}

	/*
		@brief	アニメタイム設定
		@param	i_time	:	アニメタイム
	*/
	void AnimeMesh::SetAnimTime( float i_time )
	{
		mp_anim_ctrl->AdvanceTime( i_time, NULL );
	}

	/*
		@brief	階層ごとに衝突判定
		@param	ip_frame_base		:	フレームメッシュ
		@param	ip_object			:	衝突検地オブジェクト
	*/
	bool	AnimeMesh::IsFrameImpact( LPD3DXFRAME ip_frame_base, AnimeMesh* const ip_object )
	{
		struct _tag_mesh_frame* p_frame = (struct _tag_mesh_frame*)(ip_frame_base);
		if( NULL != p_frame->pMeshContainer )
		{
			// レイによる衝突判定
			// 頂点との交点で判定する。
			LPD3DXMESH p_mesh = p_frame->pMeshContainer->MeshData.pMesh;
			if( NULL != p_mesh )
			{
				D3DXVECTOR3	start_pos, end_pos;
				start_pos = end_pos = GetPos();
				end_pos.z += 1.0f;
					
				D3DXVECTOR3	pos = ip_object->GetPos();
				D3DXMATRIX	mat_world;
				D3DXMatrixTranslation( &mat_world, pos.x, pos.y, pos.z );
				D3DXMatrixMultiply( &mat_world, &p_frame->m_combinend_mat, &mat_world );
				D3DXMatrixInverse( &mat_world, NULL, &mat_world );
				D3DXVec3TransformCoord( &start_pos, &start_pos, &mat_world );
				D3DXVec3TransformCoord( &end_pos, &end_pos, &mat_world );

				D3DXVECTOR3	direction;
				direction = end_pos - start_pos;
				BOOL b_hit = FALSE;
				float distance = 0;
				D3DXIntersect( p_mesh, &start_pos, &direction, &b_hit, NULL, NULL, NULL, &distance, NULL, NULL);
				if( b_hit == TRUE )
				{
					return true;
				}
			}
		}

		// 再帰判断(他のメッシュをチェック)
		if( NULL != p_frame->pFrameSibling )
		{
			if( IsFrameImpact( p_frame->pFrameSibling, ip_object ) )
			{
				return true;
			}
		}

		if( NULL != p_frame->pFrameFirstChild ) {
			if( IsFrameImpact( p_frame->pFrameFirstChild, ip_object ) )
			{
				return true;
			}
		}

		return false;
	}

	/*
		@brief	階層を含めてすべてのメッシュ更新
		@param	ip_frame			:	フレームメッシュ
		@param	ip_mat_world		:	ワールドマトリックス
	*/
	void AnimeMesh::UpdateFrameMesh( LPD3DXFRAME ip_frame, D3DXMATRIX* const ip_mat_world )
	{
		struct _tag_mesh_frame*	p_mesh_frame = (struct _tag_mesh_frame*)(ip_frame);
		if( NULL != ip_mat_world )
		{
			D3DXMatrixMultiply( &p_mesh_frame->m_combinend_mat, &p_mesh_frame->TransformationMatrix, ip_mat_world );
		}
		else
		{
			p_mesh_frame->m_combinend_mat = p_mesh_frame->TransformationMatrix;
		}

		// 現在の階層に兄弟メッシュがいるか
		if( p_mesh_frame->pFrameSibling != NULL )
		{
			// 兄弟メッシュは階層上同じ位置にいる
			UpdateFrameMesh( p_mesh_frame->pFrameSibling, ip_mat_world );
		}

		// 現在の階層の下に子供メッシュがいるか
		if( p_mesh_frame->pFrameFirstChild != NULL )
		{
			// 子供メッシュは階層上現在のより下にいるので
			// 階層下のマトリクスを設定
			UpdateFrameMesh( p_mesh_frame->pFrameFirstChild, &p_mesh_frame->m_combinend_mat );
		}
	}

	/*
		@brief	階層を含めてすべてのメッシュ描画
		@param	ip_mesh_frame	:	大本のメッシュフレーム
	*/
	void AnimeMesh::DrawFrameMesh( LPD3DXFRAME ip_mesh_frame )
	{
		LPD3DXMESHCONTAINER	p_mesh_ctrl = ip_mesh_frame->pMeshContainer;
		while( p_mesh_ctrl != NULL )
		{
			DrawMesh( p_mesh_ctrl, ip_mesh_frame );
			// 他にメッシュがあるか
			p_mesh_ctrl = p_mesh_ctrl->pNextMeshContainer;
		}

		// 現在の階層に兄弟メッシュがいるか
		if( ip_mesh_frame->pFrameSibling != NULL )
		{
			DrawFrameMesh( ip_mesh_frame->pFrameSibling );
		}

		// 現在の階層の下に子供メッシュがいるか
		if( ip_mesh_frame->pFrameFirstChild != NULL )
		{
			DrawFrameMesh( ip_mesh_frame->pFrameFirstChild );
		}
	}

	/*
		@brief	メッシュ描画
	*/
	void AnimeMesh::DrawMesh( LPD3DXMESHCONTAINER ip_mesh_ctrl_base, LPD3DXFRAME ip_mesh_frame )
	{
		struct _tag_mesh_container* p_mesh_ctrl = (struct _tag_mesh_container*)(ip_mesh_ctrl_base);
		struct _tag_mesh_frame*		p_mesh_frame = (struct _tag_mesh_frame*)(ip_mesh_frame);

		LPDIRECT3DDEVICE9	device = DirectX::Manager::Inst().GetDevice();
		device->SetTransform( D3DTS_WORLD, &p_mesh_frame->m_combinend_mat );

		// メッシュ描画
		for( UINT i=0; i<p_mesh_ctrl->NumMaterials; ++i )
		{
			if( p_mesh_ctrl->pMaterials )
			{
				device->SetMaterial( &p_mesh_ctrl->pMaterials[i].MatD3D );
			}

			if( p_mesh_ctrl->mpp_tex )
			{
				device->SetTexture( 0, p_mesh_ctrl->mpp_tex[i] );
			}

			p_mesh_ctrl->MeshData.pMesh->DrawSubset(i);
		}
	}
} // namespace GameLib
